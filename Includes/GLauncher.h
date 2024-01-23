#ifndef GLAUNCHER_H
#define GLAUNCHER_H

class GLauncher :public Entity{
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
GLauncher(SDL_Color clr,float x, float y, float w, float h,float e,float m,float Car,float charge,float force,float recoilFactor,float barrelLen,float spreadIndex,int capacity,int reloadTime,int shootperiod);

int isEmpty();
void setTarget(float x,float y);
void updateGLauncher();
int canShoot();
Grenade* shoot();
void render(SDL_Renderer* ren);
float getShootingForce();
void setShootVec(SDL_FPoint newVec);
SDL_FPoint getShootVec();
static GLauncher* randGLauncher(float width, float height,float maxMass,float maxSize,float maxSpeed,int capacity,float force);
static GLauncher* defaultGLauncher();
SDL_FPoint getPos();
~GLauncher();

};

#endif

