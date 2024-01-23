#ifndef PHYSENGINE_H
#define PHYSENGINE_H

constexpr int selectFrameInt= 180;
constexpr int addMoreInt= 60;
constexpr int howManyToAdd= 5;
constexpr int homingSpeed= 5;

class EntityBox;

class PhysicsEngine{

private:
EntityBox* box;

public:

PhysicsEngine(EntityBox*box);
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
void homming(std::list<T*>& entList,float x, float y);
template <typename T>
void doBlast(std::list<T*>& entList,float x, float y,float intensity);
template <typename T>
void orbit(std::list<T*>& entList,float x, float y);
template <typename T>
void handleDrag(std::list<T*>& entList);
template <typename T>
float getAverageSpeed(std::list<T*>& entList);
template <typename T>
float getAverageQuality(std::list<T*>& entList);
template <typename T>
float getTotalEnergy(std::list<T*>& entList);

};
#include "physEngine.tpp"

#endif
