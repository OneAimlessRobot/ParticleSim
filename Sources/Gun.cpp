

#include <SDL2/SDL.h>
#include "../Includes/auxFuncs.h"
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include "../Includes/Bullet.h"
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/gunSettings.h"
#include "../Includes/IOSettings.h"
#include "../Includes/Gun.h"
#include "../Includes/Collider.h"
#include "../Includes/physicsAux.h"

Gun::Gun(SDL_Color clr,float x, float y, float w, float h,float e,float m,float Car,float charge,float force,float recoilFactor,float barrelLen,float spreadIndex,int capacity,int reloadTime,int shootperiod):Entity(clr,x,  y,  w,  h, e,  m, Car,charge){
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
this->muzzleFlashPeriod=30;


}

void Gun::setCaliber(caliber bType){

    this->bulletType=bType;
}

caliber Gun::getCaliber(){

    return this->bulletType;
}
//void Gun::setCaliber(caliber bType){
//
//
//    this->bulletType=bType;
//
//}
Gun* Gun::defaultGun(){

return new Gun(DEFAULTGUNRGBA,0,0,
    DEFAULTGUNW,
    DEFAULTGUNH,
    DEFAULTGUNE,
    DEFAULTGUNM,
    DEFAULTGUNCAR,
    DEFAULTGUNQ,
    DEFAULTGUNFORCE,
    DEFAULTGUNRECOIL,
    DEFAULTGUNBARRELLENGTH,
    DEFAULTGUNSPREAD,
    DEFAULTGUNCAP,
    DEFAULTGUNRELTIME,
    DEFAULTGUNSHOTTIME);

}
void Gun::render(SDL_Renderer* ren){
if(isEmpty()){

   SDL_SetRenderDrawColor(ren,255,0,0,255);
   SDL_FRect rect=(SDL_FRect){this->getPos().x-10,this->getPos().y-10,body.w+20,body.h+20};
    SDL_RenderFillRectF(ren,&rect);

}
if(inCooldown()&&muzzleFlashPeriod){
SDL_SetRenderDrawColor(ren,255,255,50,255);
SDL_FRect rect=(SDL_FRect){this->getPos().x-5,this->getPos().y-5,body.w+10,body.h+10};
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
SDL_FPoint Gun::getPos(){

    return (SDL_FPoint){this->pos.x,this->pos.y};
}
float Gun::getBarrelLength(){

    return this->barrelLen;
}
float Gun::getTilt(){

return Aux::getRandomFloat(-spreadMaxAngle,spreadMaxAngle);



}
float Gun::getRecoilFactor(){

    return recoilFactor;
}
void Gun::reload(){

currAmmo=capacity;
reloadCounter=reloadTime;
shootCounter=0;

}
int Gun::inCooldown(){
return shootCounter>0;
}
int Gun::isEmpty(){

return currAmmo==0;
}

int Gun::getReloadTime(){

return reloadTime;

}

float Gun::getShootingForce(){

return this->force;

}
void Gun::setTarget(float x, float y){


    SDL_FPoint master=(SDL_FPoint){x,y},
                slave=getCenter();
    SDL_FPoint vec= Aux::makeUnitVector(slave,master);
    Aux::scaleVec(&vec,getShootingForce());
    setShootVec(vec);

}
Entity* Gun::shoot(){

    caliber bType=getCaliber();
//    std::cout<<this->shootVec->getX()<<" , "<<this->shootVec->getY()<<" \n";
    SDL_FPoint launchPos=getCenter();
    Entity* bullet= new Entity(Aux::randColor(),launchPos.x,launchPos.y,bType.size,bType.size,bType.e,bType.mass,bType.Car,bType.charge);
    //dou-lhe o pointer para o vetor da gun. Mais tarde, quando apago as guns, apago o vetor. quando
    //tento apagar as entities, dá merda.
    float shootSpread=getTilt();
    PhysicsAux::railAcceleration<Entity>(bullet,getShootVec(),shootSpread,getBarrelLength());
    bullet->setVec(GVector::tiltVector(bullet->getVec(),shootSpread));
    SDL_FPoint tiltedVec=GVector::tiltVector(getShootVec(),getTilt());
    Aux::scaleVec(&tiltedVec,-getRecoilFactor());
    this->currAmmo--;
    shootCounter=shootperiod;
    muzzleFlashPeriod=30;
    if(isEmpty()){
	
    this->reloadCounter=reloadTime;
    }
    else{

    setVec(GVector::add(tiltedVec,getVec()));

    }

    return bullet;



}
void Gun::setShootVec(SDL_FPoint newVec){
    this->shootVec->setCoords(newVec);

}
int Gun::canShoot(){

return !isEmpty()&&!inCooldown();

}
void Gun::updateGun(){

this->existenceTime++;
if(isEmpty()){
this->reloadCounter--;
if(reloadCounter==0){
reload();
}
}
if(inCooldown()){
    if(muzzleFlashPeriod){
    muzzleFlashPeriod--;
    }
    shootCounter--;
return;
}
}
SDL_FPoint Gun::getShootVec(){
    return this->shootVec->getCoords();

}
Gun::~Gun(){
    delete this->shootVec;

}


