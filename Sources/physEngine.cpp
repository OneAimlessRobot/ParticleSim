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
#include "../Includes/physEngine.h"
#include "../Includes/EntityMgmnt.h"

PhysicsEngine::PhysicsEngine(Container*cont){

	this->cont=cont;

}

void PhysicsEngine::updateEntities(int collisions,int gravity,int drag,int electricity,float tx, float ty){

	handleMovements(collisions,gravity,drag,electricity);
	monitorGrenades();
	monitorMissiles(tx,ty);


}

void PhysicsEngine::handleCollisions(int collisionsEnabled){

    //broken. Maybe will fix
    if(collisionsEnabled){
    deleteFreaks<Entity>(cont->getEntityList());
    deleteFreaks<Grenade>(cont->getGrenadeList());
      handleInterparticleCollisions<Entity>(cont->getEntityList());
      handleInterparticleCollisions<Grenade>(cont->getGrenadeList());
      handleInterparticleCollisions<Missile>(cont->getMissileList());
    }

    deleteFreaks<Entity>(cont->getEntityList());
    deleteFreaks<Grenade>(cont->getGrenadeList());
    deleteFreaks<Missile>(cont->getMissileList());
     handleCollisionsWithArena<Entity>(cont->getEntityList());
    handleCollisionsWithArena<Grenade>(cont->getGrenadeList());
    handleCollisionsWithArena<Missile>(cont->getMissileList());

}
void PhysicsEngine::handleForces(int gravityEnabled,int dragEnabled,int electricity){
	
    if(gravityEnabled){
    deleteFreaks<Entity>(cont->getEntityList());
    deleteFreaks<Grenade>(cont->getGrenadeList());
    deleteFreaks<Missile>(cont->getMissileList());
      handleInterparticleGravity<Entity>(cont->getEntityList());
      handleInterparticleGravity<Grenade>(cont->getGrenadeList());
      handleInterparticleGravity<Missile>(cont->getMissileList());



    }
    if(dragEnabled){
    deleteFreaks<Entity>(cont->getEntityList());

    handleDrag<Entity>(cont->getEntityList());
    deleteFreaks<Grenade>(cont->getGrenadeList());
    handleDrag<Grenade>(cont->getGrenadeList());

    deleteFreaks<Missile>(cont->getMissileList());
    handleDrag<Missile>(cont->getMissileList());
    }
    if(gravityEnabled){
    deleteFreaks<Entity>(cont->getEntityList());

    handleGroundGravity<Entity>(cont->getEntityList());

    deleteFreaks<Grenade>(cont->getGrenadeList());
    handleGroundGravity<Grenade>(cont->getGrenadeList());
    deleteFreaks<Missile>(cont->getMissileList());
    handleGroundGravity<Missile>(cont->getMissileList());

    }
    if(electricity){
    deleteFreaks<Entity>(cont->getEntityList());
    deleteFreaks<Grenade>(cont->getGrenadeList());
    deleteFreaks<Missile>(cont->getMissileList());
      handleInterparticleElectricity<Entity>(cont->getEntityList());
      handleInterparticleElectricity<Grenade>(cont->getGrenadeList());
      handleInterparticleElectricity<Missile>(cont->getMissileList());

    }

}
void PhysicsEngine::handleMovements(int collisionsEnabled,int gravityEnabled,int dragEnabled,int electricity){

    handleForces(gravityEnabled,dragEnabled,electricity);

    handleCollisions(collisionsEnabled);



}
PhysicsEngine::~PhysicsEngine(){

}

void PhysicsEngine::printSpeedsAndPosEnts(){


    std::list<Entity*>::iterator it;
    for (it = cont->getEntityList().begin(); it != cont->getEntityList().end(); ++it) {
       std::cout<<"Posição: (x,y)= ("<<(*it)->getPos().x<<" , "<<(*it)->getPos().y<<")\n";
       std::cout<<"Velocidade: "<<GVector::getNorm((*it)->getVec())<<"\n";
       std::cout<<"Coeficientes: \n";
       std::cout<<"Elasticidade: "<<1-(*it)->getElasticity()<<"\n";
       std::cout<<"Massa: "<<(*it)->getMass()<<"\n";
       std::cout<<"Carga: "<<(*it)->getCharge()<<"\n";
       std::cout<<"Coeficiente de resis. do ar: "<<(*it)->getDragConstant()<<"\n";


}
	


}
float PhysicsEngine::getTotalEnergyEnts(){

	return getTotalEnergy<Entity>(this->cont->getEntityList());



}

void PhysicsEngine::monitorGrenades(){
	std::list<Grenade*>::iterator it2;
	for(it2= cont->getGrenadeList().begin();it2!= cont->getGrenadeList().end();++it2){

		if((*it2)->blowingUp()){

			doBlast<Entity>(cont->getEntityList(),(*it2)->getCenter().x,(*it2)->getCenter().y,(*it2)->getForce());
		}
		(*it2)->update();
	}



}
void PhysicsEngine::monitorMissiles(float tx,float ty){
	std::list<Missile*>::iterator it2;
	for(it2= cont->getMissileList().begin();it2!= cont->getMissileList().end();++it2){

		if((*it2)->blowingUp()){

			doBlast<Entity>(cont->getEntityList(),(*it2)->getCenter().x,(*it2)->getCenter().y,(*it2)->getForce());
		}
		(*it2)->update(tx,ty);
	}



}
