#ifndef CONTAINER_H
#define CONTAINER_H

class Container{

private:

float maxSpeed, maxSize, ammount,maxMass, airDensity,maxcharge;

std::list<Gun*> gunList;
std::list<GLauncher*> gLauncherList;
std::list<MLauncher*> mLauncherList;


Collider* arena;
std::list<Grenade*> grenadeList;
std::list<Missile*> missileList;
std::list<Entity*> entList;
Entity* worldMassParticle;
public:
Container(float maxSpeed,float maxSize,float ammount,float maxMass,float airDensity,float maxcharge);
~Container();

std::list<Grenade*>& getGrenadeList();
std::list<Missile*>& getMissileList();
std::list<Entity*>& getEntityList();
std::list<Gun*>& getGunList();
std::list<MLauncher*>& getMLauncherList();
std::list<GLauncher*>& getGLauncherList();
Entity* getEarthParticle();
Collider* getArena();

void spawnGLauncher(float x, float y);

void populateEntityList(int ammount);
void spawnMLauncher(float x, float y);
void spawnGun(std::string filePath,float x, float y,caliber bType);

void render(SDL_Renderer* ren);
void addEnt(Entity* ent);
void addEnt(float x,float y);
void addGrenade(Grenade* gren);
void addMissile(Missile* miss);

void cleanGrenades();
void cleanMissiles();

void destroyEntities();
void destroyGuns();

};

#endif
