#include <SDL2/SDL.h>
#include "../Includes/auxFuncs.h"
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/Grenade.h"
#include "../Includes/grenadeSettings.h"
#include "../Includes/gunSettings.h"
Grenade::Grenade(float x,float y,float chargeForce,int explosionDuration,int timer):Entity(DEFAULTGRENADERGBA,x,y,DEFAULTGRENADESIZE,DEFAULTGRENADESIZE,DEFAULTGRENADEE,DEFAULTGRENADEM,DEFAULTGRENADECAR,DEFAULTGRENADEQ){
this->chargeForce=chargeForce;
this->explosionDuration=explosionDuration;
this->timer=timer;
this->currTime=0;
this->active=1;
this->explosionHappening=0;


}
Grenade* Grenade::defaultGrenade(){

return new Grenade(0,0,DEFAULTGRENADEBFORCE,DEFAULTEXPLOSIONDUR,DEFAULTGRENADETIMER);


}

void Grenade::update(){
if(active){
if(currTime==timer&&!explosionHappening){
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
void Grenade::render(SDL_Renderer* ren){
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
void Grenade::deactivate(){
if(this->active){
this->active=0;
explosionHappening=0;
}

}

int Grenade::isActive(){

return active;

}

int Grenade::blowingUp(){
return explosionHappening;

}
float Grenade::getForce(){


return chargeForce;
}
Grenade::~Grenade(){




}
