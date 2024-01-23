
#include <SDL2/SDL.h>
#include "../Includes/auxFuncs.h"
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/Collider.h"
#include "../Includes/physicsAux.h"

Entity::Entity(SDL_Color clr,float x, float y, float w, float h,float e, float m,float Car,float charge){

    this->bodyColor=clr;
    if(w<=0){
        w=1;
    }
    if(h<=0){
        h=1;
    }
    this->body=(SDL_FRect){x,y,w,h};
    this->pos=(SDL_FPoint){x,y};
    this->moveVec= new GVector(0.000001,0.00001);
    this->lastPositions={};
    if(e==0){
    this->e=0.001;
    }
    else{
    this->e=e;
    }
    this->mass=m;
    this->Car=Car;
    this->charge=charge;


}
void Entity::render(SDL_Renderer*ren){
    SDL_SetRenderDrawColor(ren,this->bodyColor.r,this->bodyColor.g,this->bodyColor.b,this->bodyColor.a);
    SDL_RenderFillRectF(ren,&this->body);

    for(SDL_FPoint point: this->lastPositions){
        SDL_RenderDrawPointF(ren,point.x,point.y);
    }

        SDL_FRect rect=(SDL_FRect){this->getLastPos().x,this->getLastPos().y,this->body.x*0.01f,this->body.y*0.01f};
        SDL_RenderFillRectF(ren,&rect);
}
void Entity::setPos(SDL_FPoint point){

    this->lastPos=pos;
    this->pos.x=point.x;
    this->pos.y=point.y;
    this->body.x=point.x;
    this->body.y=point.y;

}
SDL_FPoint Entity::getPos(){

    return (SDL_FPoint){this->body.x,this->body.y};

}
float Entity::getDragConstant(){

    return this->body.w*this->Car*0.001f;
}
SDL_FPoint Entity::getLastPos(){

    if(this->lastPositions.empty()){
        return pos;
    }
    return this->lastPositions.at(this->lastPositions.size()-std::min(COLLDISTANCE,(int)this->lastPositions.size()));

}
void Entity::translate(){
    this->lastPositions.push_back(this->pos);
    if(this->lastPositions.size()>TRAILLENGTH){
        this->lastPositions.erase(this->lastPositions.begin());
    }
    this->pos.x+=this->moveVec->getX();
    this->pos.y+=this->moveVec->getY();
    this->body.x+=this->moveVec->getX();
    this->body.y+=this->moveVec->getY();

}

float Entity::getElasticity(){

    return this->e;
}
float Entity::getInvElasticity(){

    return 1.0f/this->e;
}
float Entity::getMass(){
 return this->mass;
}
float Entity::getCharge(){
 return this->charge;
}
void Entity::bounce(){
    float newSpeed=PhysicsAux::getReboundSpeed(GVector::getNorm(this->getVec()),this->e);
    //O vetor e (nan, nan)
// ----------           if(newSpeed!=newSpeed){
//    std::cout<<"ERRO!!!!!\n";
//    }

    SDL_FPoint newVector=Aux::makeUnitVector((SDL_FPoint){0,0},(SDL_FPoint){this->moveVec->getX(),this->moveVec->getY()});
    Aux::scaleVec(&newVector,newSpeed);
//---------                if(newVector.x!=newVector.x||newVector.y!=newVector.y){
//    std::cout<<"ERRO!!!!!\n";
//    }

    this->setVec(newVector);

}
int Entity::areTouching(Entity*a,Entity*b){


 return (Aux::calculateDistance(a->getCenter(),b->getCenter()))<=a->getRadius()+b->getRadius();

}
Entity* Entity::randEnt(float width, float height,float maxMass,float maxSize,float maxSpeed,float maxCharge){
//float size= Aux::getRandomFloat(10,maxSize);
float maxAngle=Aux::getRandomFloat(0,2*3.14159);
//float inve=Aux::getRandomFloat(0,1);
float e=1;
//float e=0;

//float newMass=Aux::getRandomFloat(0,maxMass);
int arrSize=2;
float masses[arrSize]={0.5*maxMass,maxMass};
int index= (int)round(Aux::getRandomFloat(0,arrSize-1));
float newMass=masses[index];
float size= newMass;
float charge= Aux::getRandomFloat(-maxCharge,maxCharge);
//float charge= maxCharge;
float x= Aux::getRandomFloat(1,width-size-1);
float y=Aux::getRandomFloat(1,height-size-1);
float coeffOfAirR=Aux::getRandomFloat(0,1);
float dx= std::cos(maxAngle);
float dy=std::sin(maxAngle);
float speed=Aux::getRandomFloat(maxSpeed,maxSpeed);
SDL_Color color= Aux::randColor();
SDL_FPoint resmoveVec= Aux::makeUnitVector((SDL_FPoint){0,0},(SDL_FPoint){dx,dy});
// --------       if(resmoveVec.x!=resmoveVec.x||resmoveVec.y!=resmoveVec.y){
//    std::cout<<"ERRO!!!!!\n";
//    }

Aux::scaleVec(&resmoveVec,speed);
Entity* result=new Entity(color,x,y,size,size,e,newMass,coeffOfAirR,charge);
result->setVec(resmoveVec);
//----------if(result->getVec().x!=result->getVec().x||result->getVec().y!=result->getVec().y){
//    std::cout<<"ERRO!!!!!\n";
//    }
return result;


}
SDL_FPoint Entity::getVec(){

return this->moveVec->getCoords();
}
SDL_FRect Entity::getBody(){

    return (this->body);
}
float Entity::getRadius(){

    return this->body.w*0.5;

}

float Entity::getTotalEnergy(){
    float v=GVector::getNorm(this->getVec()),m=this->getMass();
    return v*v*m*0.5;

}


float Entity::getQuality(){
//quanto mais pequeno "e", melhor
    return (GVector::getNorm(this->getVec()))/(getDragConstant()*getElasticity());


}
SDL_FPoint Entity::getCenter(){

    float x=this->pos.x+this->body.w*0.5f;
    float y=this->pos.y+this->body.h*0.5f;
    return (SDL_FPoint){x,y};


}
    SDL_FPoint getCoords();
    void setCoords(SDL_FPoint point);
void Entity::setVec(SDL_FPoint coords){
this->moveVec->setCoords(coords);
}
Entity::~Entity(){
delete this->moveVec;
}



