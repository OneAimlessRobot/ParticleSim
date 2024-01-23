#include "../Includes/auxFuncs.h"
#include <fstream>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "../Includes/colliderSettings.h"
#include "../Includes/IOSettings.h"
#include "../Includes/Collider.h"


Collider::Collider(SDL_Color color,float x,float y,float w,float h,float thickness,float airDensity){

this->left=(SDL_FRect){x-thickness,y,thickness,h};
this->top=(SDL_FRect){x-thickness,y-thickness,w+2*thickness,thickness};
this->right=(SDL_FRect){left.x+w+thickness,y,thickness,h};
this->bottom=(SDL_FRect){x-thickness,left.y+h,w+2*thickness,thickness};
this->containedObject=(SDL_FRect){x,y,w,h};
this->bodyColor = color;
this->airDensity=airDensity;



}

SDL_FRect Collider::getInter(SDL_FRect body,int where){

    SDL_FRect result;
    if(where<=0){

        return (SDL_FRect){body.x,body.y,0,0};

    }
    if(where==1){

        SDL_IntersectFRect(&body,&this->left,&result);
        return result;

    }
    if(where==2){

        SDL_IntersectFRect(&body,&this->right,&result);
        return result;

    }
    if(where==3){

        SDL_IntersectFRect(&body,&this->top,&result);
        return result;

    }
    if(where==4){

        SDL_IntersectFRect(&body,&this->bottom,&result);
        return result;

    }



}

SDL_FRect Collider::getColliderInsideData(){

	return (SDL_FRect){containedObject.x,containedObject.y,containedObject.w,containedObject.h};

}

int Collider::bodyIsInside(SDL_FRect body){

    return SDL_HasIntersectionF(&body,&this->containedObject)
		||SDL_HasIntersectionF(&body,&this->left)
		||SDL_HasIntersectionF(&body,&this->right)
		||SDL_HasIntersectionF(&body,&this->bottom)
		||SDL_HasIntersectionF(&body,&this->top);




}

Collider* Collider::defaultCollider(){


    return new Collider(DEFAULTCOLRGB,DEFAULTCOLX,DEFAULTCOLY,DEFAULTCOLW,DEFAULTCOLH,DEFAULTTHICKNESS,DEFAULTAIRDENSITY);



}



void Collider::fullRender(SDL_Renderer* ren){

    SDL_SetRenderDrawColor(ren,this->bodyColor.r,this->bodyColor.g,this->bodyColor.b,this->bodyColor.a);
    SDL_RenderFillRectF(ren,&this->containedObject);

    SDL_SetRenderDrawColor(ren,255,0,0,255);
    SDL_FRect  rlist[]= {left,right,top,bottom};
    SDL_RenderFillRectsF(ren,rlist,4);
    SDL_RenderPresent(ren);


}
void Collider::render(SDL_Renderer* ren){


    SDL_SetRenderDrawColor(ren,this->bodyColor.r,this->bodyColor.g,this->bodyColor.b,this->bodyColor.a);
    SDL_RenderFillRectF(ren,&this->containedObject);
    SDL_RenderPresent(ren);



}
float Collider::getAirDensity(){

    return this->airDensity;
}
int Collider::whereIsColliding(SDL_FRect rect){
//
// -------   std::cout<<rect.x<<" , "<<rect.y<<"\n";

    if(SDL_HasIntersectionF(&rect,&this->left)){

        return 1;

    }
    else if(SDL_HasIntersectionF(&rect,&this->right)){

        return 2;

    }
    else if(SDL_HasIntersectionF(&rect,&this->top)){

        return 3;

    }
    else if(SDL_HasIntersectionF(&rect,&this->bottom)){

        return 4;

    }

    else{

        return 0;

    }




}

