#ifndef PHYSICS_H
#define PHYSICS_H
namespace PhysicsAux{

constexpr float GCONST=0.001;
constexpr float ECONST=0.001;
float getReboundSpeed(float initSpeed,float coeff);
void rebound(Entity* a,Entity *b);
float gravForce(SDL_FPoint p1,SDL_FPoint p2,float m1,float m2);
float electricForce(SDL_FPoint p1,SDL_FPoint p2,float q1,float q2);

float blastForce(SDL_FPoint p1,SDL_FPoint p2,float forceConst);

SDL_FPoint blastVector(SDL_FPoint p1,SDL_FPoint p2,float forceConst);
SDL_FPoint gravVector(SDL_FPoint p1,SDL_FPoint p2,float m1,float m2);
SDL_FPoint electricVector(SDL_FPoint p1,SDL_FPoint p2,float q1,float q2);

SDL_FPoint dragNeutralWindVector(SDL_FPoint vVec,float k, float airD);
SDL_FPoint getAccelVec(SDL_FPoint vec,float mass);

template <typename T>
void railAcceleration(T* ent,SDL_FPoint forceVec,float angle,float length);
void accelerateEntity(Entity* ent,SDL_FPoint forceVec);
float dragNeutralWind(float k, float airD,float speed);
void separateEntities(Entity* a,Entity *b);
void separateEntityFromCollider(Entity* a,Collider *col,int where);
void blastEnergy(SDL_FPoint p1,SDL_FPoint p2,float energyOut);
}
#include "physicsAux.tpp"
#endif
