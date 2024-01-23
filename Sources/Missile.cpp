#include <SDL2/SDL.h>
#include "../Includes/auxFuncs.h"
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/Missile.h"
#include "../Includes/grenadeSettings.h"
#include "../Includes/missileSettings.h"
#include "../Includes/gunSettings.h"

Missile::Missile(float x,float y,float chargeForce,int explosionDuration,int timer,float tx, float ty,float speed):Entity(DEFAULTMISSILERGBA,x,y,DEFAULTMISSILESIZE,DEFAULTMISSILESIZE,DEFAULTMISSILEE,DEFAULTMISSILEM,DEFAULTMISSILECAR,DEFAULTMISSILEQ){
this->chargeForce=chargeForce;
this->explosionDuration=explosionDuration;
this->timer=timer;
this->currTime=0;
this->active=1;
this->explosionHappening=0;
this->speed=speed;
targetx=tx;
targety=ty;


}
Missile* Missile::defaultMissile(){

return new Missile(0,0,DEFAULTMISSILEBFORCE,DEFAULTEXPLOSIONDUR,DEFAULTMISSILETIMER,0,0,DEFAULTMISSILESPEED);


}

void Missile::update(float tx, float ty){

targetx=tx;
targety=ty;

SDL_FPoint vec=Aux::makeUnitVector(getCenter(),(SDL_FPoint){targetx,targety});
Aux::scaleVec(&vec,this->speed);
setVec(vec);
if(active){
if((currTime==timer||(fabs(this->getPos().x-targetx)<10&&fabs(this->getPos().y-targety)<10))&&!explosionHappening){
explosionHappening=1;
currTime=0;
return;
}
if(explosionHappening){
currTime++;
if(currTime==explosionDuration){
deactivate();
return;

}
return;

}
currTime++;
}


}
void Missile::render(SDL_Renderer* ren){
if(explosionHappening){

   SDL_SetRenderDrawColor(ren,255,0,255,255);
   SDL_FRect rect=(SDL_FRect){this->getPos().x-100,this->getPos().y-100,body.w+200,body.h+200};
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
void Missile::deactivate(){
if(this->active){
this->active=0;
explosionHappening=0;
}

}

int Missile::isActive(){

return active;

}

int Missile::blowingUp(){
return explosionHappening;

}
float Missile::getForce(){


return chargeForce;
}
Missile::~Missile(){




}
