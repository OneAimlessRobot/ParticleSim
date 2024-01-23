#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "../Includes/GVector.h"
#include "../Includes/auxFuncs.h"
#include <iostream>
    GVector::GVector(float x,float y){

    this->x=x;
    this->y=y;


    }
    float GVector::getX(){
        return this->x;

    }
    float GVector::getY(){
        return this->y;

    }
    void GVector::setX(float newX){
        this->x=newX;

    }
    void GVector::setY(float newY){
        this->y=newY;

    }
    void GVector::setCoords(SDL_FPoint point){

        this->x=point.x;
        this->y=point.y;

    }
    SDL_FPoint GVector::getCoords(){

        return (SDL_FPoint){this->x,this->y};
    }
    float GVector::getNorm(SDL_FPoint vec){

        return Aux::calculateDistance((SDL_FPoint){0,0},vec);

    }
    float GVector::angleBetween(SDL_FPoint v1,SDL_FPoint v2){
        float result=(GVector::dotProduct(v1,v2)/(GVector::getNorm(v1)*GVector::getNorm(v2)));
        if(std::fabs(result)>1){
            return 3.14159;

        }
        return std::acos(result);


    }
    float GVector::dotProduct(SDL_FPoint v1,SDL_FPoint v2){

        return v1.x*v2.x+v1.y*v2.y;


    }

    SDL_FPoint GVector::tiltVector(SDL_FPoint v,float angle){
        float norm=GVector::getNorm(v);
        float vAngle=std::atan2(v.y,v.x);
        float newX=std::cos(vAngle)*std::cos(angle)-std::sin(vAngle)*std::sin(angle);
        float newY=std::sin(vAngle)*std::cos(angle)+std::cos(vAngle)*std::sin(angle);
        SDL_FPoint newVec= Aux::makeUnitVector((SDL_FPoint){0,0},(SDL_FPoint){newX,newY});
        Aux::scaleVec(&newVec,norm);
        return newVec;


    }
    void GVector::Reflect(SDL_FPoint* velocity, GVector* collisionNormal) {
    float dotProduct = velocity->x * collisionNormal->x + velocity->y * collisionNormal->y;
    velocity->x = velocity->x - 2.0f * dotProduct * collisionNormal->x;
    velocity->y = velocity->y - 2.0f * dotProduct * collisionNormal->y;
    delete collisionNormal;
    }
    SDL_FPoint GVector::add(SDL_FPoint v1, SDL_FPoint v2){

        return (SDL_FPoint){v1.x+v2.x,v1.y+v2.y};


    }
    GVector::~GVector(){


    }
