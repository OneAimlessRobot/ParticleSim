#ifndef PHYSENGINE_H
#define PHYSENGINE_H


class EntityBox;

class PhysicsEngine{

private:
Container* cont;

public:

PhysicsEngine(Container* cont);
~PhysicsEngine();
void handleCollisions(int collisionsEnabled);
template <typename T>
void handleInterparticleCollisions(std::list<T*>& ents);
template <typename T>
void handleInterparticleGravity(std::list<T*>& ents);
template <typename T>
void handleInterparticleElectricity(std::list<T*>& ents);
template <typename T>
void deleteFreaks(std::list<T*>& ents);
template <typename T>
void handleGroundGravity(std::list<T*>& ents);
template <typename T>
void handleCollisionsWithArena(std::list<T*>& ents);
void handleForces(int gravityEnabled,int dragEnabled,int electricity);

void handleMovements(int collisionsEnabled,int gravityEnabled,int dragEnabled,int electricity);
template <typename T>
static void homming(std::list<T*>& entList,float x, float y);
template <typename T>
static void doBlast(std::list<T*>& entList,float x, float y,float intensity);
template <typename T>
static void orbit(std::list<T*>& entList,float x, float y);
template <typename T>
void handleDrag(std::list<T*>& entList);
template <typename T>
float getAverageSpeed(std::list<T*>& entList);
template <typename T>
float getAverageQuality(std::list<T*>& entList);
template <typename T>
float getTotalEnergy(std::list<T*>& entList);

void printSpeedsAndPosEnts();
float getTotalEnergyEnts();


void monitorGrenades();
void monitorMissiles(float tx,float ty);

void updateEntities(int collisions,int gravity,int drag,int electricity,float tx, float ty);


void hommingEnts(float x, float y);

void doBlastEnts(float x, float y,float intensity);

void orbitEnts(float x, float y);

};
#include "allSettings.h"
#include "physEngine.tpp"

#endif
