#ifndef MLAUNCHER_H
#define MLAUNCHER_H

class MLauncher :public Entity{
private:

float barrelLen,force,spreadMaxAngle,recoilFactor;
int capacity,currAmmo,reloadTime,shootCounter,reloadCounter,existenceTime,shootperiod;

GVector* shootVec;
int inCooldown();
int getReloadTime();
float getBarrelLength();
float getRecoilFactor();
float getTilt();
void reload();

public:
MLauncher(SDL_Color clr,float x, float y, float w, float h,float e,float m,float Car,float charge,float force,float recoilFactor,float barrelLen,float spreadIndex,int capacity,int reloadTime,int shootperiod);

int isEmpty();
void setTarget(float x,float y);
void updateMLauncher();
int canShoot();
Missile* shoot();
void render(SDL_Renderer* ren);
float getShootingForce();
void setShootVec(SDL_FPoint newVec);
SDL_FPoint getShootVec();
static MLauncher* randMLauncher(float width, float height,float maxMass,float maxSize,float maxSpeed,int capacity,float force);
static MLauncher* defaultMLauncher();
SDL_FPoint getPos();
~MLauncher();

};


#endif

