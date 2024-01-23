
#include <SDL2/SDL.h>
#include "../Includes/auxFuncs.h"
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include "../Includes/Bullet.h"
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/missileSettings.h"
#include "../Includes/Missile.h"
#include "../Includes/gunSettings.h"
#include "../Includes/IOSettings.h"
#include "../Includes/MLauncher.h"
#include "../Includes/Collider.h"
#include "../Includes/physicsAux.h"

MLauncher::MLauncher(SDL_Color clr,float x, float y, float w, float h,float e,float m,float Car,float force,float charge,float recoilFactor,float barrelLen,float spreadIndex,int capacity,int reloadTime,int shootperiod):Entity(clr,x,  y,  w,  h, e,  m, Car,charge){
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
MLauncher* MLauncher::defaultMLauncher(){

return new MLauncher(DEFAULTMLAUNCHERRGBA,0,0,
    DEFAULTMLAUNCHERW,
    DEFAULTMLAUNCHERH,
    DEFAULTMLAUNCHERE,
    DEFAULTMLAUNCHERM,
    DEFAULTMLAUNCHERCAR,
    DEFAULTMLAUNCHERQ,
    DEFAULTMLAUNCHERFORCE,
    DEFAULTMLAUNCHERRECOIL,
    DEFAULTMLAUNCHERBARRELLENGTH,
    DEFAULTMLAUNCHERSPREAD,
    DEFAULTMLAUNCHERCAP,
    DEFAULTMLAUNCHERRELTIME,
    DEFAULTMLAUNCHERSHOTTIME);

}
void MLauncher::render(SDL_Renderer* ren){
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
SDL_FPoint MLauncher::getPos(){

    return (SDL_FPoint){this->pos.x,this->pos.y};
}
float MLauncher::getBarrelLength(){

    return this->barrelLen;
}
float MLauncher::getTilt(){

return Aux::getRandomFloat(-spreadMaxAngle,spreadMaxAngle);



}
float MLauncher::getRecoilFactor(){

    return recoilFactor;
}
void MLauncher::reload(){

currAmmo=capacity;
reloadCounter=reloadTime;
shootCounter=0;

}
int MLauncher::inCooldown(){
return shootCounter>0;
}
int MLauncher::isEmpty(){

return currAmmo==0;
}

int MLauncher::getReloadTime(){

return reloadTime;

}

float MLauncher::getShootingForce(){

return this->force;

}
void MLauncher::setTarget(float x, float y){


    SDL_FPoint master=(SDL_FPoint){x,y},
                slave=getCenter();
    SDL_FPoint vec= Aux::makeUnitVector(slave,master);
    Aux::scaleVec(&vec,getShootingForce());
    setShootVec(vec);

}
Missile* MLauncher::shoot(){

//    std::cout<<this->shootVec->getX()<<" , "<<this->shootVec->getY()<<" \n";
    SDL_FPoint launchPos=getCenter();
    Missile* grenade= Missile::defaultMissile();
    grenade->setPos(this->getCenter());
    //dou-lhe o pointer para o vetor da MLauncher. Mais tarde, quando apago as MLaunchers, apago o vetor. quando
    //tento apagar as entities, dá merda.
    float shootSpread=getTilt();
    PhysicsAux::railAcceleration<Missile>(grenade,getShootVec(),shootSpread,getBarrelLength());
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
void MLauncher::setShootVec(SDL_FPoint newVec){
    this->shootVec->setCoords(newVec);

}
int MLauncher::canShoot(){

return !isEmpty()&&!inCooldown();

}
void MLauncher::updateMLauncher(){

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
SDL_FPoint MLauncher::getShootVec(){
    return this->shootVec->getCoords();

}
MLauncher::~MLauncher(){
    delete this->shootVec;

}



