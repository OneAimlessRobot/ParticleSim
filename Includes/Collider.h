#ifndef COL_H
#define COL_H

class Collider{
private:
SDL_FRect containedObject,top,bottom,left,right;
SDL_bool type;
float airDensity;
SDL_Color bodyColor;
public:
Collider(SDL_Color color,float x,float y,float w,float h,float thickness,float airDensity);
void fullRender(SDL_Renderer* ren);
void render(SDL_Renderer* ren);
SDL_FRect getColliderInsideData();
int whereIsColliding(SDL_FRect rect);
float getAirDensity();

static Collider* defaultCollider();
int bodyIsInside(SDL_FRect body);
SDL_FRect getInter(SDL_FRect body,int where);


};
#endif
