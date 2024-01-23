
#ifndef GUN_H
#define GUN_H
#define RELOAD_TIME_SECS 1.0
#define UPDATE_RATE (1000*RELOAD_TIME_SECS*FRAMERATE)
class Gun: public Entity{

private:

float barrelLen,force,spreadMaxAngle,recoilFactor;
int capacity,currAmmo,reloadTime,shootCounter,reloadCounter,existenceTime,shootperiod,muzzleFlashPeriod;
caliber bulletType;
GVector* shootVec;
int inCooldown();
int getReloadTime();
float getBarrelLength();
float getRecoilFactor();
float getTilt();
void reload();
public:

Gun(SDL_Color clr,float x, float y, float w, float h,float e,float m,float Car,float charge,float force,float recoilFactor,float barrelLen,float spreadIndex,int capacity,int reloadTime,int shootperiod);
int isEmpty();
void setTarget(float x,float y);
void setCaliber(caliber bType);
caliber getCaliber();
void updateGun();
int canShoot();
Entity* shoot();
void render(SDL_Renderer* ren);
float getShootingForce();
void setShootVec(SDL_FPoint newVec);
SDL_FPoint getShootVec();
static Gun* randGun(float width, float height,float maxMass,float maxSize,float maxSpeed,int capacity,float force);
static Gun* defaultGun();
SDL_FPoint getPos();
~Gun();



};
#endif
