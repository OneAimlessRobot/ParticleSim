

#include <SDL2/SDL.h>
#include "../Includes/auxFuncs.h"
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include "../Includes/Bullet.h"
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/grenadeSettings.h"
#include "../Includes/Grenade.h"
#include "../Includes/gunSettings.h"
#include "../Includes/IOSettings.h"
#include "../Includes/GLauncher.h"
#include "../Includes/Collider.h"
#include "../Includes/physicsAux.h"

GLauncher::GLauncher(SDL_Color clr,float x, float y, float w, float h,float e,float m,float Car,float force,float charge,float recoilFactor,float barrelLen,float spreadIndex,int capacity,int reloadTime,int shootperiod):Entity(clr,x,  y,  w,  h, e,  m, Car,charge){
this->force=force;
this->barrelLen=barrelLen;
this->capacity=capacity;
this->reloadTime=reloadTime;
this->currAmmo=capacity;
this->pos=(SDL_FPoint){x,y};
this->shootperiod=shootperiod;
this->existenceTime=0;
this->spreadMaxAngle=3.14159*0.5*spreadIndex;
this->shootCounter=0;
this->recoilFactor=recoilFactor;
this->shootVec=new GVector(1,1);



}
GLauncher* GLauncher::defaultGLauncher(){

return new GLauncher(DEFAULTGLAUNCHERRGBA,0,0,
    DEFAULTGLAUNCHERW,
    DEFAULTGLAUNCHERH,
    DEFAULTGLAUNCHERE,
    DEFAULTGLAUNCHERM,
    DEFAULTGLAUNCHERCAR,
    DEFAULTGLAUNCHERQ,
    DEFAULTGLAUNCHERFORCE,
    DEFAULTGLAUNCHERRECOIL,
    DEFAULTGLAUNCHERBARRELLENGTH,
    DEFAULTGLAUNCHERSPREAD,
    DEFAULTGLAUNCHERCAP,
    DEFAULTGLAUNCHERRELTIME,
    DEFAULTGLAUNCHERSHOTTIME);

}
void GLauncher::render(SDL_Renderer* ren){
if(isEmpty()){

   SDL_SetRenderDrawColor(ren,255,0,0,255);
   SDL_FRect rect=(SDL_FRect){this->getPos().x-10,this->getPos().y-10,body.w+20,body.h+20};
    SDL_RenderFillRectF(ren,&rect);

}

SDL_SetRenderDrawColor(ren,this->bodyColor.r,this->bodyColor.g,this->bodyColor.b,this->bodyColor.a);

    SDL_RenderFillRectF(ren,&this->body);

    for(SDL_FPoint point: this->lastPositions){
        SDL_RenderDrawPointF(ren,point.x,point.y);
    }
    SDL_SetRenderDrawColor(ren,this->bodyColor.r,this->bodyColor.g,this->bodyColor.b,this->bodyColor.a);

        SDL_FRect rect=(SDL_FRect){this->getLastPos().x,this->getLastPos().y,this->body.w*0.01f,this->body.h*0.01f};
        SDL_RenderFillRectF(ren,&rect);


}
SDL_FPoint GLauncher::getPos(){

    return (SDL_FPoint){this->pos.x,this->pos.y};
}
float GLauncher::getBarrelLength(){

    return this->barrelLen;
}
float GLauncher::getTilt(){

return Aux::getRandomFloat(-spreadMaxAngle,spreadMaxAngle);



}
float GLauncher::getRecoilFactor(){

    return recoilFactor;
}
void GLauncher::reload(){

currAmmo=capacity;
reloadCounter=reloadTime;
shootCounter=0;

}
int GLauncher::inCooldown(){
return shootCounter>0;
}
int GLauncher::isEmpty(){

return currAmmo==0;
}

int GLauncher::getReloadTime(){

return reloadTime;

}

float GLauncher::getShootingForce(){

return this->force;

}
void GLauncher::setTarget(float x, float y){


    SDL_FPoint master=(SDL_FPoint){x,y},
                slave=getCenter();
    SDL_FPoint vec= Aux::makeUnitVector(slave,master);
    Aux::scaleVec(&vec,getShootingForce());
    setShootVec(vec);

}
Grenade* GLauncher::shoot(){

//    std::cout<<this->shootVec->getX()<<" , "<<this->shootVec->getY()<<" \n";
    SDL_FPoint launchPos=getCenter();
    Grenade* grenade= Grenade::defaultGrenade();
    grenade->setPos(this->getCenter());
    //dou-lhe o pointer para o vetor da GLauncher. Mais tarde, quando apago as GLaunchers, apago o vetor. quando
    //tento apagar as entities, dá merda.
    float shootSpread=getTilt();
    PhysicsAux::railAcceleration<Grenade>(grenade,getShootVec(),shootSpread,getBarrelLength());
    grenade->setVec(GVector::tiltVector(grenade->getVec(),shootSpread));
    SDL_FPoint tiltedVec=GVector::tiltVector(getShootVec(),getTilt());
    Aux::scaleVec(&tiltedVec,-getRecoilFactor());
    this->currAmmo--;
    shootCounter=shootperiod;
    if(isEmpty()){

    this->reloadCounter=reloadTime;
    }
    else{

    setVec(GVector::add(tiltedVec,getVec()));

    }

    return grenade;



}
void GLauncher::setShootVec(SDL_FPoint newVec){
    this->shootVec->setCoords(newVec);

}
int GLauncher::canShoot(){

return !isEmpty()&&!inCooldown();

}
void GLauncher::updateGLauncher(){

this->existenceTime++;
if(isEmpty()){
this->reloadCounter--;
if(reloadCounter==0){
reload();
}
}
if(inCooldown()){
    shootCounter--;
return;
}
}
SDL_FPoint GLauncher::getShootVec(){
    return this->shootVec->getCoords();

}
GLauncher::~GLauncher(){
    delete this->shootVec;

}


