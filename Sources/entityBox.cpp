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
#include "../Includes/physEngine.h"
#include "../Includes/EntityMgmnt.h"
#include "../Includes/entityBox.h"


EntityBox::EntityBox(float maxSpeed,float maxSize,float ammount,float maxMass,float airDensity,float maxcharge){
this->entList= {};
engine=NULL;
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

std::cout<<"Initializing arena\n";

this->arena= EntityManagement::parseCollider(DEFAULT_COLLIDER_PATH);
if(this->arena){
std::cout<<"Done!\n";
}
else{
std::cerr<<"Error loading arena. Exiting...(Code 6)\n";
exit(-1);
}
std::cout<<"Starting to populate the simulation....\n";
std::thread populatingWorker(&EntityBox::populateEntityList,this,ammount);
populatingWorker.detach();

this->worldMassParticle=new Entity(Aux::randColor(),WORLDX,WORLDY,WORLDRADIUS*2,WORLDRADIUS*2,1,WORLDMASS,1,0);


}

void EntityBox::attentionEveryone(){

std::list<Entity*>::iterator it;

        for (it = entList.begin(); it != entList.end();) {
                Entity * next= (*it);
        if(!arena->bodyIsInside(next->getBody())){
    std::cout<<"ERRO!!!!!\n";
    delete (*it);
    it=entList.erase(it);
    }
    else{
    ++it;

    }
}

}
void EntityBox::freezeEveryone(){

std::list<Entity*>::iterator it;

        for (it = entList.begin(); it != entList.end();++it) {
                Entity * next= (*it);
                next->setVec((SDL_FPoint){0.0f,0.0f});

    }

}
void EntityBox::teleportEntityList(float x, float y){
std::list<Entity*>::iterator it;

        for (it = entList.begin(); it != entList.end(); it++) {
                Entity * next= (*it);
                next->setPos((SDL_FPoint){x,y});

        }



}
void EntityBox::updateEntities(int collisions,int gravity,int drag,int electricity,float tx,float ty){

    if(engine){
    engine->handleMovements(collisions,gravity,drag,electricity);
    monitorGrenades();
    monitorMissiles(tx,ty);
    cleanGrenades();
    cleanMissiles();
    attentionEveryone();
    }
}
void EntityBox::render(SDL_Renderer* ren){


    this->arena->fullRender(ren);
    std::list<Entity*>::iterator it;
    for (it = this->entList.begin(); it != this->entList.end(); ++it) {
        (*it)->render(ren);
    }
    std::list<Grenade*>::iterator it3;
    for (it3 = this->grenadeList.begin(); it3 != this->grenadeList.end(); ++it3) {
        (*it3)->render(ren);
    }
    std::list<Missile*>::iterator it6;
    for (it6 = this->missileList.begin(); it6 != this->missileList.end(); ++it6) {
        (*it6)->render(ren);
    }


}
void EntityBox::cleanGrenades(){


    std::list<Grenade*>::iterator it;
    for (it = grenadeList.begin(); it != grenadeList.end();) {
        if(!(*it)->isActive()){
    delete (*it);
    it=grenadeList.erase(it);
    }
    else{
    ++it;

    }



}

}
void EntityBox::monitorGrenades(){
	std::list<Grenade*>::iterator it2;
	for(it2= grenadeList.begin();it2!= grenadeList.end();++it2){

		if((*it2)->blowingUp()){

			engine->doBlast<Entity>(entList,(*it2)->getCenter().x,(*it2)->getCenter().y,(*it2)->getForce());
		}
		(*it2)->update();
	}



}

void EntityBox::cleanMissiles(){

    std::list<Missile*>::iterator it;
    for (it = missileList.begin(); it != missileList.end();) {
        if(!(*it)->isActive()){
    delete (*it);
    it=missileList.erase(it);
    }
    else{
    ++it;

    }



}


}
void EntityBox::monitorMissiles(float tx,float ty){
	std::list<Missile*>::iterator it2;
	for(it2= missileList.begin();it2!= missileList.end();++it2){

		if((*it2)->blowingUp()){

			engine->doBlast<Entity>(entList,(*it2)->getCenter().x,(*it2)->getCenter().y,(*it2)->getForce());
		}
		(*it2)->update(tx,ty);
	}



}


void EntityBox::makeSelection(){

      float selectQuality=engine->getAverageSpeed<Entity>(entList);
        std::list<Entity*>::iterator it;
            for (it = entList.begin(); it != entList.end(); ) {

                if(GVector::getNorm((*it)->getVec())<selectQuality){
                    delete (*it);
                    it=entList.erase(it);

                }
                else{
                    it++;
                }


}
}

void EntityBox::populateEntityList(int ammount){

for(int i =0;i<ammount;i++){

    entList.emplace(entList.begin(),Entity::randEnt(WIDTH,HEIGHT,this->maxMass,this->maxSize,this->maxSpeed,this->maxcharge));
}



}
void EntityBox::printSpeedsAndPos(){


    std::list<Entity*>::iterator it;
    for (it = entList.begin(); it != entList.end(); ++it) {
       std::cout<<"Posição: (x,y)= ("<<(*it)->getPos().x<<" , "<<(*it)->getPos().y<<")\n";
       std::cout<<"Velocidade: "<<GVector::getNorm((*it)->getVec())<<"\n";
       std::cout<<"Coeficientes: \n";
       std::cout<<"Elasticidade: "<<1-(*it)->getElasticity()<<"\n";
       std::cout<<"Massa: "<<(*it)->getMass()<<"\n";
       std::cout<<"Carga: "<<(*it)->getCharge()<<"\n";
       std::cout<<"Coeficiente de resis. do ar: "<<(*it)->getDragConstant()<<"\n";


}


}
void EntityBox::destroyEntities(){


    EntityManagement::clearList<Entity>(this->entList);
    EntityManagement::clearList<Grenade>(this->grenadeList);
    EntityManagement::clearList<Missile>(this->missileList);


}
EntityBox::~EntityBox(){
    destroyEntities();
    delete this->worldMassParticle;
    delete this->arena;



}

void EntityBox::orbit(float x,float y){

        engine->orbit<Entity>(this->entList,x,y);

}
void EntityBox::homming(float x,float y){


        engine->homming<Entity>(this->entList,x,y);

}
void EntityBox::blast(float x,float y){

    engine->doBlast<Entity>(this->entList,x,y,MAINBLASTFORCE);

}

void EntityBox::generationHandling(){

    this->thetime++;
if(this->thetime%addMoreInt==0){
    std::thread addWorker(&EntityBox::populateEntityList,this,howManyToAdd);
    addWorker.detach();
    }

    if(this->thetime%selectFrameInt==0){
    makeSelection();
    std::cout<<"Geraçao numero: "<<this->genCount<<"\n";
    this->genCount++;
    }


}
void EntityBox::printBox(){
    std::cout<<"=============================Variaveis de estado=============================================\n";
    std::cout<<"Quantidade de particulas na simulação: "<<this->entList.size()<<"\n";
    std::cout<<"============================Variaveis de configuraçao por ficheiro:==========================\n";
    std::cout<<"Massa maxima de particula: "<<this->maxMass<<"\n";
    std::cout<<"Velocidade maxima de particula: "<<this->maxSpeed<<"\n";
    std::cout<<"Tamanho maximo de particula: "<<this->maxSize<<"\n";
    std::cout<<"Carga eletrica maxima de particula (modulo): "<<this->maxcharge<<"\n";
    std::cout<<"Atrito do ar: "<<arena->getAirDensity()<<"\n";

}
void EntityBox::addEnt(float x, float y){
	
	Entity* ent=Entity::randEnt(WIDTH,HEIGHT,maxMass,maxSize,maxSpeed,maxcharge);
    	ent->setPos((SDL_FPoint){x,y});
	entList.emplace(entList.begin(),ent);

}

float EntityBox::getTotalEnergy(){

	return engine->getTotalEnergy<Entity>(this->entList);


}

void EntityBox::addEnt(Entity* ent){

	entList.emplace(entList.begin(),ent);
}
void EntityBox::addGrenade(Grenade* gren){

	grenadeList.emplace(grenadeList.begin(),gren);


}
void EntityBox::addMissile(Missile* miss){


	missileList.emplace(missileList.begin(),miss);

}


std::list<Grenade*>& EntityBox::getGrenadeList(){

	return grenadeList;

}
std::list<Missile*>& EntityBox::getMissileList(){

	return missileList;

}
std::list<Entity*>& EntityBox::getEntityList(){

	return entList;

}
Entity* EntityBox::getEarthParticle(){

	return worldMassParticle;

}
Collider* EntityBox::getArena(){

	return arena;
}

void EntityBox::setPhysicsEngine(PhysicsEngine* engine){

	this->engine=engine;
}

