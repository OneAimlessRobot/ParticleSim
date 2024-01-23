#ifndef ENTITYBOX_H
#define ENTITYBOX_H
class EntityBox{
private:
float maxSpeed, maxSize, ammount,maxMass, airDensity,maxcharge;
int genCount,thetime;

public:

PhysicsEngine* engine;
Collider* arena;
std::list<Grenade*> grenadeList;
std::list<Missile*> missileList;
std::list<Entity*> entList;
Entity* worldMassParticle;


EntityBox(float maxSpeed,float maxSize,float ammount,float maxMass,float airDensity,float macharge);
~EntityBox();
void attentionEveryone();
void freezeEveryone();
void teleportEntityList(float x, float y);

void render(SDL_Renderer* ren);
void updateEntities(int collisions,int gravity,int drag,int electricity,float tx, float ty);

void cleanGrenades();
void monitorGrenades();
void cleanMissiles();
void monitorMissiles(float tx,float ty);

void generationHandling();
void makeSelection();
void populateEntityList(int ammount);
void printSpeedsAndPos();

void addEnt(float x,float y);

std::list<Grenade*>& getGrenadeList();
std::list<Missile*>& getMissileList();
std::list<Entity*>& getEntityList();
Entity* getEarthParticle();
Collider* getArena();

void addEnt(Entity* ent);
void addGrenade(Grenade* gren);
void addMissile(Missile* miss);

void orbit(float x,float y);
void homming(float x,float y);
void blast(float x,float y);

void printBox();
float getTotalEnergy();

void destroyEntities();

void setPhysicsEngine(PhysicsEngine* engine);
};
#endif
