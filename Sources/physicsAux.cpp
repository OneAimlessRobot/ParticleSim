#include <random>
#include <utility>
#include <set>
#include <cmath>
#include "../Includes/auxFuncs.h"
#include "../Includes/allSettings.h"
#include <iostream>
#include "../Includes/GVector.h"
#include "../Includes/Entity.h"
#include "../Includes/Collider.h"
#include "../Includes/physicsAux.h"

float PhysicsAux::getReboundSpeed(float initSpeed,float coeff){
float result= initSpeed-(initSpeed*coeff);

//  -----          if(initSpeed!=initSpeed){
//    std::cout<<"ERRO!!!!!\n";
//    }

//  -------          if(result!=result){
//    std::cout<<"ERRO!!!!!\n";
//    }
    return result;

}
float PhysicsAux::electricForce(SDL_FPoint p1,SDL_FPoint p2,float q1,float q2){


float dist=Aux::calculateDistance(p1,p2);
float chargeProduct=q1*q2;
float chargeProdAbs=fabs(chargeProduct);
if(chargeProduct>=0){
return (-1*chargeProdAbs*10*PhysicsAux::ECONST)/(dist*dist);

}
else{

return (chargeProdAbs*10*PhysicsAux::ECONST)/(dist*dist);

}

}


float PhysicsAux::blastForce(SDL_FPoint p1,SDL_FPoint p2,float forceConst){


float dist=Aux::calculateDistance(p1,p2);

return (forceConst*PhysicsAux::GCONST)/(dist*dist);
}

SDL_FPoint PhysicsAux::blastVector(SDL_FPoint p1,SDL_FPoint p2,float forceConst){


        SDL_FPoint newVec=Aux::makeUnitVector(p1,p2);
        float accel= PhysicsAux::blastForce(p1,p2,forceConst);
        if(Aux::calculateDistance(p1 ,p2)<=4){
            Aux::scaleVec(&newVec,10);
        }
        else{
        Aux::scaleVec(&newVec,accel);
        }
        return newVec;


}

void PhysicsAux::accelerateEntity(Entity* ent,SDL_FPoint forceVec){



        SDL_FPoint accelVec=getAccelVec(forceVec,ent->getMass());
        ent->setVec(GVector::add(accelVec,ent->getVec()));


}
SDL_FPoint PhysicsAux::getAccelVec(SDL_FPoint forcevec,float mass){


        SDL_FPoint accel= forcevec;
        Aux::scaleVec(&accel,1/mass);

        return accel;
}
SDL_FPoint PhysicsAux::gravVector(SDL_FPoint p1,SDL_FPoint p2,float m1,float m2){


        SDL_FPoint newVec=Aux::makeUnitVector(p2,p1);
        float accel= PhysicsAux::gravForce(p1,p2,m1,m2);
        if(Aux::calculateDistance(p1 ,p2)>4){
            Aux::scaleVec(&newVec,accel);
        }
        return newVec;

}
SDL_FPoint PhysicsAux::electricVector(SDL_FPoint p1,SDL_FPoint p2,float q1,float q2){


        SDL_FPoint newVec=Aux::makeUnitVector(p2,p1);
        float accel= PhysicsAux::electricForce(p1,p2,q1,q2);
        if(Aux::calculateDistance(p1 ,p2)>4){
            Aux::scaleVec(&newVec,accel);
        }
        return newVec;

}

SDL_FPoint PhysicsAux::dragNeutralWindVector(SDL_FPoint vVec,float k, float airD){

        SDL_FPoint newVec=Aux::makeUnitVector((SDL_FPoint){0,0},vVec);
        float dragMag= PhysicsAux::dragNeutralWind(k,airD,GVector::getNorm(vVec));
        Aux::scaleVec(&newVec,-dragMag);
        return newVec;



}
void PhysicsAux::separateEntities(Entity *a ,Entity* b){
SDL_FPoint va=a->getVec(),
        vb=b->getVec();
    SDL_FPoint separatorB=Aux::makeUnitVector(a->getCenter(),b->getCenter());
    SDL_FPoint separatorA=Aux::makeUnitVector(b->getCenter(),a->getCenter());
    a->setVec(separatorA);
    b->setVec(separatorB);
    while(Entity::areTouching(a,b)){
    a->translate();
    b->translate();

    }
    a->setVec(va);
    b->setVec(vb);


}
void PhysicsAux::separateEntityFromCollider(Entity* a,Collider *col,int where){
    if(where==0){
        return;
    }
//  -------          if(og.x!=og.x||og.y!=og.y){
//    std::cout<<"ERRO!!!!!\n";
//    }


// -----   std::cout<<a->getPos().x<<" , "<<a->getPos().y<<"\n";
//    }
/*
    do{
    where=col->whereIsColliding(a->getBody());

//------------        if(a->getPos().x!=a->getPos().x||a->getPos().y!=a->getPos().y){
//    std::cout<<"ERRO!!!!!\n";
//    }

    a->translate();

    }while(where!=0);
*/
//
// -------   std::cout<<rect.x<<" , "<<rect.y<<"\n";
  where=col->whereIsColliding(a->getBody());

	SDL_FRect inter;
	SDL_FRect playArea= col->getColliderInsideData();
switch(where){
	case 1:
	
	//left
	inter= col->getInter(a->getBody(),1);
	a->setPos((SDL_FPoint){playArea.x+1,a->getPos().y});
   	//std::cout<<"Esquerda!!!\n";
	break;
	case 2:
	
	//right
	inter= col->getInter(a->getBody(),2);
	a->setPos((SDL_FPoint){(playArea.x+playArea.w)-1-a->getBody().w,a->getPos().y});
	
   	//std::cout<<"Direita!!!\n";
    break;
	case 3:
	//top
	inter= col->getInter(a->getBody(),3);
	a->setPos((SDL_FPoint){a->getPos().x,playArea.y+1});
	
   	//std::cout<<"Cima!!!\n";
 break;
	case 4:
	//bottom
	inter= col->getInter(a->getBody(),4);
	a->setPos((SDL_FPoint){a->getPos().x,(playArea.y+playArea.h)-1-a->getBody().h});
	
   	//std::cout<<"Baixo!!!\n";
	break;
	default:
	break;
}



}
void PhysicsAux::rebound(Entity *a ,Entity* b){
//Direçao do normal e de 'a' para 'b'
float ma=a->getMass(),mb=b->getMass();

SDL_FPoint directionA=Aux::makeUnitVector(a->getCenter(),b->getCenter()),
		n=Aux::makeUnitVector(a->getCenter(),b->getCenter()),
            directionB=Aux::makeUnitVector(b->getCenter(),a->getCenter());

float normalAngleA=GVector::angleBetween(a->getVec(),n);
float normalAngleB=GVector::angleBetween(b->getVec(),n);
if(normalAngleA<0 || normalAngleB <0){

	std::cout<<"ERROR ON COLLISIONSS!!!!\n";
}
//--------if(normalAngleB!=normalAngleB){
//    std::cout<<"ERRO!!!!!\n";
//    }
//    if(normalAngleA!=normalAngleA){
//    std::cout<<"ERRO!!!!!\n";
//    }
//tudo bem.
SDL_FPoint pva=a->getVec();
Aux::scaleVec(&pva,fabs(std::cos(normalAngleA)));
//------if(pva.x!=pva.x||pva.y!=pva.y){
//    std::cout<<"ERRO!!!!!\n";
//    }
SDL_FPoint pvb=b->getVec();
Aux::scaleVec(&pvb,fabs(std::cos(normalAngleB)));
//-------if(pvb.x!=pvb.x||pvb.y!=pvb.y){
//    std::cout<<"ERRO!!!!!\n";
//    }
Aux::scaleVec(&pva,-1);
SDL_FPoint firstresult=GVector::add(pvb,pva);
float coeff=((ma*a->getElasticity())+(mb*b->getElasticity()))/(ma+mb);
float bigCoeff=(((ma*mb)/(ma+mb))*(1+coeff));

//---------            if(pva.x!=pva.x||pva.y!=pva.y){
//    std::cout<<"ERRO!!!!!\n";
//    }
Aux::scaleVec(&firstresult,bigCoeff);
float Jn=GVector::dotProduct(firstresult,n);
Aux::scaleVec(&directionA,Jn/ma);
Aux::scaleVec(&directionB,Jn/mb);
//the minus is implicit. Its directionA's vector symmetric
a->setVec(GVector::add(directionA,a->getVec()));
b->setVec(GVector::add(directionB,b->getVec()));

}

float PhysicsAux::gravForce(SDL_FPoint p1,SDL_FPoint p2,float m1,float m2){
float dist=Aux::calculateDistance(p1,p2);

return (m1*m2*10*PhysicsAux::GCONST)/(dist*dist);
}


float PhysicsAux::dragNeutralWind(float k,float airD,float speed){

return speed*speed*k*airD;
}


