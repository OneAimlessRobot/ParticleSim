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
#include "../Includes/EntityMgmnt.h"
#include "../Includes/container.h"



Container::Container(float maxSpeed,float maxSize,float ammount,float maxMass,float airDensity,float maxcharge){

this->entList= {};
this->maxSpeed=maxSpeed;
if(std::fabs(this->maxSpeed)==0){
    this->maxSpeed=0.00001f;
}

this->maxSize=maxSize;
this->ammount=ammount;
this->maxMass=maxMass;
this->maxcharge=maxcharge;
this->airDensity=airDensity;

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
std::thread populatingWorker(&Container::populateEntityList,this,ammount);
populatingWorker.detach();

this->worldMassParticle=new Entity(Aux::randColor(),WORLDX,WORLDY,WORLDRADIUS*2,WORLDRADIUS*2,1,WORLDMASS,1,0);




}

void Container::populateEntityList(int ammount){

for(int i =0;i<ammount;i++){

    addEnt(Entity::randEnt(WIDTH,HEIGHT,this->maxMass,this->maxSize,this->maxSpeed,this->maxcharge));
}



}

void Container::addGrenade(Grenade* gren){

	grenadeList.emplace(grenadeList.begin(),gren);


}
void Container::addMissile(Missile* miss){


	missileList.emplace(missileList.begin(),miss);

}



void Container::addEnt(Entity* ent){

	entList.emplace(entList.begin(),ent);
}


std::list<Grenade*>& Container::getGrenadeList(){

	return grenadeList;

}
std::list<Missile*>& Container::getMissileList(){

	return missileList;

}
std::list<Entity*>& Container::getEntityList(){

	return entList;

}


std::list<GLauncher*>& Container::getGLauncherList(){

	return gLauncherList;

}
std::list<MLauncher*>& Container::getMLauncherList(){

	return mLauncherList;

}
std::list<Gun*>& Container::getGunList(){

	return gunList;

}
Entity* Container::getEarthParticle(){

	return worldMassParticle;

}
Collider* Container::getArena(){

	return arena;
}


void Container::spawnGLauncher(float x, float y){

    GLauncher*gLauncher=GLauncher::defaultGLauncher();
    gLauncher->setPos((SDL_FPoint){x,y});
    gLauncherList.emplace(gLauncherList.begin(),gLauncher);


}
void Container::spawnMLauncher(float x, float y){

    MLauncher*mLauncher=MLauncher::defaultMLauncher();
    mLauncher->setPos((SDL_FPoint){x,y});
    mLauncherList.emplace(mLauncherList.begin(),mLauncher);


}
void Container::spawnGun(std::string filePath,float x, float y,caliber bType){

    Gun* gun=EntityManagement::parseGun(filePath);
    gun->setPos((SDL_FPoint){x,y});
    gun->setCaliber(bType);
    gunList.emplace(gunList.begin(),gun);


}



Container::~Container(){

destroyEntities();
destroyGuns();
delete worldMassParticle;
delete arena;
}
void Container::destroyGuns(){

    EntityManagement::clearList<Gun>(this->gunList);
    EntityManagement::clearList<GLauncher>(this->gLauncherList);
    EntityManagement::clearList<MLauncher>(this->mLauncherList);



}

void Container::destroyEntities(){


    EntityManagement::clearList<Entity>(this->entList);
    EntityManagement::clearList<Grenade>(this->grenadeList);
    EntityManagement::clearList<Missile>(this->missileList);


}
void Container::addEnt(float x, float y){
	
	Entity* ent=Entity::randEnt(WIDTH,HEIGHT,maxMass,maxSize,maxSpeed,maxcharge);
    	ent->setPos((SDL_FPoint){x,y});
	addEnt(ent);
}

void Container::render(SDL_Renderer* ren){


    this->arena->fullRender(ren);
    std::list<Entity*>::iterator it;
    for (it = this->getEntityList().begin(); it != this->getEntityList().end(); ++it) {
        (*it)->render(ren);
    }
    std::list<Grenade*>::iterator it3;
    for (it3 = this->getGrenadeList().begin(); it3 != this->getGrenadeList().end(); ++it3) {
        (*it3)->render(ren);
    }
    std::list<Missile*>::iterator it6;
    for (it6 = this->getMissileList().begin(); it6 != this->getMissileList().end(); ++it6) {
        (*it6)->render(ren);
    }
    std::list<Gun*>::iterator it2;
    for (it2 = this->getGunList().begin(); it2 != this->getGunList().end(); ++it2) {
        (*it2)->render(ren);
    }
    std::list<GLauncher*>::iterator it4;
    for (it4 = this->getGLauncherList().begin(); it4 != this->getGLauncherList().end(); ++it4) {
        (*it4)->render(ren);
    }
    std::list<MLauncher*>::iterator it5;
    for (it5 = this->getMLauncherList().begin(); it5 != this->getMLauncherList().end(); ++it5) {
        (*it5)->render(ren);
    }

}
void Container::cleanGrenades(){


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

void Container::cleanMissiles(){

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


