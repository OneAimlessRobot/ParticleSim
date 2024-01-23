#include <thread>
#include <list>
#include <fstream>
#include <vector>
#include "../Includes/resourcePaths.h"
#include "../Includes/allSettings.h"
#include <SDL2/SDL.h>
#include <random>
#include <cmath>
#include <iostream>
#include "../Includes/auxFuncs.h"
#include "../Includes/Collider.h"
#include "../Includes/GVector.h"
#include "../Includes/Bullet.h"
#include "../Includes/Entity.h"
#include "../Includes/Grenade.h"
#include "../Includes/Missile.h"
#include "../Includes/Gun.h"
#include "../Includes/GLauncher.h"
#include "../Includes/MLauncher.h"
#include "../Includes/physicsAux.h"
#include "../Includes/container.h"
#include "../Includes/EntityMgmnt.h"
#include "../Includes/entityBox.h"


EntityBox::EntityBox(float maxSpeed,float maxSize,float ammount,float maxMass,float airDensity,float maxcharge,Container* cont){
this->maxSpeed=maxSpeed;
if(std::fabs(this->maxSpeed)==0){
    this->maxSpeed=0.00001f;
}

this->genCount=0;
this->maxSize=maxSize;
this->ammount=ammount;
this->maxMass=maxMass;
this->maxcharge=maxcharge;
this->airDensity=airDensity;
this->thetime=0;

this->cont=cont;

}

void EntityBox::attentionEveryone(){

std::list<Entity*>::iterator it;

        for (it = cont->getEntityList().begin(); it != cont->getEntityList().end();) {
                Entity * next= (*it);
        if(!cont->getArena()->bodyIsInside(next->getBody())){
    std::cout<<"ERRO!!!!!\n";
    delete (*it);
    it=cont->getEntityList().erase(it);
    }
    else{
    ++it;

    }
}

}
void EntityBox::freezeEveryone(){

std::list<Entity*>::iterator it;

        for (it = cont->getEntityList().begin(); it != cont->getEntityList().end();++it) {
                Entity * next= (*it);
                next->setVec((SDL_FPoint){0.0f,0.0f});

    }

}
void EntityBox::teleportEntityList(float x, float y){
std::list<Entity*>::iterator it;

        for (it = cont->getEntityList().begin(); it != cont->getEntityList().end(); it++) {
                Entity * next= (*it);
                next->setPos((SDL_FPoint){x,y});

        }



}
void EntityBox::updateEntities(){

    cont->cleanGrenades();
    cont->cleanMissiles();
    attentionEveryone();
}


void EntityBox::makeSelection(float selectQuality){
	 std::list<Entity*>::iterator it;
            for (it = cont->getEntityList().begin(); it != cont->getEntityList().end(); ) {

                if(GVector::getNorm((*it)->getVec())<selectQuality){
                    delete (*it);
                    it=cont->getEntityList().erase(it);

                }
                else{
                    it++;
                }


}
}

EntityBox::~EntityBox(){


}


void EntityBox::generationHandling(float selectQuality){

    this->thetime++;
if(this->thetime%addMoreInt==0){
    std::thread addWorker(&Container::populateEntityList,this->cont,howManyToAdd);
    addWorker.detach();
    }

    if(this->thetime%selectFrameInt==0){
    makeSelection(selectQuality);
    std::cout<<"Geraçao numero: "<<this->genCount<<"\n";
    this->genCount++;
    }


}
void EntityBox::printBox(){
    std::cout<<"=============================Variaveis de estado=============================================\n";
    std::cout<<"Quantidade de particulas na simulação: "<<this->cont->getEntityList().size()<<"\n";
    std::cout<<"============================Variaveis de configuraçao por ficheiro:==========================\n";
    std::cout<<"Massa maxima de particula: "<<this->maxMass<<"\n";
    std::cout<<"Velocidade maxima de particula: "<<this->maxSpeed<<"\n";
    std::cout<<"Tamanho maximo de particula: "<<this->maxSize<<"\n";
    std::cout<<"Carga eletrica maxima de particula (modulo): "<<this->maxcharge<<"\n";
    std::cout<<"Atrito do ar: "<<cont->getArena()->getAirDensity()<<"\n";

}

