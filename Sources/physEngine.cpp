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

PhysicsEngine::PhysicsEngine(EntityBox*box){

	this->box=box;

}


void PhysicsEngine::handleCollisions(int collisionsEnabled){

    //broken. Maybe will fix
    if(collisionsEnabled){
    deleteFreaks<Entity>(box->getEntityList());
    deleteFreaks<Grenade>(box->getGrenadeList());
      handleInterparticleCollisions<Entity>(box->getEntityList());
      handleInterparticleCollisions<Grenade>(box->getGrenadeList());
      handleInterparticleCollisions<Missile>(box->getMissileList());
    }

    deleteFreaks<Entity>(box->getEntityList());
    deleteFreaks<Grenade>(box->getGrenadeList());
    deleteFreaks<Missile>(box->getMissileList());
     handleCollisionsWithArena<Entity>(box->getEntityList());
    handleCollisionsWithArena<Grenade>(box->getGrenadeList());
    handleCollisionsWithArena<Missile>(box->getMissileList());

}
void PhysicsEngine::handleForces(int gravityEnabled,int dragEnabled,int electricity){
	
    if(gravityEnabled){
    deleteFreaks<Entity>(box->getEntityList());
    deleteFreaks<Grenade>(box->getGrenadeList());
    deleteFreaks<Missile>(box->getMissileList());
      handleInterparticleGravity<Entity>(box->getEntityList());
      handleInterparticleGravity<Grenade>(box->getGrenadeList());
      handleInterparticleGravity<Missile>(box->getMissileList());



    }
    if(dragEnabled){
    deleteFreaks<Entity>(box->getEntityList());

    handleDrag<Entity>(box->getEntityList());
    deleteFreaks<Grenade>(box->getGrenadeList());
    handleDrag<Grenade>(box->getGrenadeList());

    deleteFreaks<Missile>(box->getMissileList());
    handleDrag<Missile>(box->getMissileList());
    }
    if(gravityEnabled){
    deleteFreaks<Entity>(box->getEntityList());

    handleGroundGravity<Entity>(box->getEntityList());

    deleteFreaks<Grenade>(box->getGrenadeList());
    handleGroundGravity<Grenade>(box->getGrenadeList());
    deleteFreaks<Missile>(box->getMissileList());
    handleGroundGravity<Missile>(box->getMissileList());

    }
    if(electricity){
    deleteFreaks<Entity>(box->getEntityList());
    deleteFreaks<Grenade>(box->getGrenadeList());
    deleteFreaks<Missile>(box->getMissileList());
      handleInterparticleElectricity<Entity>(box->getEntityList());
      handleInterparticleElectricity<Grenade>(box->getGrenadeList());
      handleInterparticleElectricity<Missile>(box->getMissileList());

    }

}
void PhysicsEngine::handleMovements(int collisionsEnabled,int gravityEnabled,int dragEnabled,int electricity){

    handleForces(gravityEnabled,dragEnabled,electricity);

    handleCollisions(collisionsEnabled);



}
PhysicsEngine::~PhysicsEngine(){

}
