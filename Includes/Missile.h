#ifndef MISSILE_H
#define MISSILE_H

class Missile:public Entity{
private:

float chargeForce;
float targetx, targety;
int timer,currTime,active,explosionDuration,explosionHappening,speed;
void deactivate();
public:

Missile(float x,float y,float chargeForce,int explosionDuration,int timer,float tx,float ty,float speed);

static Missile* defaultMissile();

void update(float tx,float ty);
int blowingUp();
int isActive();
void render(SDL_Renderer* ren);
float getForce();
~Missile();


};

#endif
