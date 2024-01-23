#include <thread>
#include <list>
#include <fstream>
#include <vector>
#include "../Includes/resourcePaths.h"
#include "../Includes/allSettings.h"
#include <SDL2/SDL.h>
#include <random>
#include <cmath>
#include <iostream>
#include "../Includes/auxFuncs.h"
#include "../Includes/Collider.h"
#include "../Includes/GVector.h"
#include "../Includes/Bullet.h"
#include "../Includes/Entity.h"
#include "../Includes/Grenade.h"
#include "../Includes/Missile.h"
#include "../Includes/Gun.h"
#include "../Includes/GLauncher.h"
#include "../Includes/MLauncher.h"
#include "../Includes/physicsAux.h"
#include "../Includes/physEngine.h"
#include "../Includes/EntityMgmnt.h"
#include "../Includes/entityBox.h"
#include "../Includes/arsenal.h"


Arsenal::Arsenal(EntityBox* box){
this->box=box;

}
Arsenal::~Arsenal(){

 destroyGuns();
 delete box;

}


void Arsenal::spawnGLauncher(float x, float y){

    GLauncher*gLauncher=GLauncher::defaultGLauncher();
    gLauncher->setPos((SDL_FPoint){x,y});
    gLauncherList.emplace(gLauncherList.begin(),gLauncher);


}
void Arsenal::spawnMLauncher(float x, float y){

    MLauncher*mLauncher=MLauncher::defaultMLauncher();
    mLauncher->setPos((SDL_FPoint){x,y});
    mLauncherList.emplace(mLauncherList.begin(),mLauncher);


}
void Arsenal::spawnGun(std::string filePath,float x, float y,caliber bType){

    Gun* gun=EntityManagement::parseGun(filePath);
    gun->setPos((SDL_FPoint){x,y});
    gun->setCaliber(bType);
    gunList.emplace(gunList.begin(),gun);


}
void Arsenal::shootGuns(){

    std::list<Gun*>::iterator it;
    for (it = gunList.begin(); it != gunList.end(); ++it) {
    if(((*it)->canShoot())){

        box->addEnt((*it)->shoot());
    }
    }
    std::list<GLauncher*>::iterator it2;
    for (it2= gLauncherList.begin(); it2 != gLauncherList.end(); ++it2) {
    if(((*it2)->canShoot())){

        box->addGrenade((*it2)->shoot());
    }
    }
    std::list<MLauncher*>::iterator it3;
    for (it3= mLauncherList.begin(); it3 != mLauncherList.end(); ++it3) {
    if(((*it3)->canShoot())){

        box->addMissile((*it3)->shoot());
    }
    }


}
void Arsenal::monitorGuns(float xtarget,float ytarget){

    std::list<Gun*>::iterator it;
    for (it = gunList.begin(); it != gunList.end(); ++it) {
    (*it)->setTarget(xtarget,ytarget);
    (*it)->updateGun();
    }

     std::list<GLauncher*>::iterator it2;
    for (it2 = gLauncherList.begin(); it2 != gLauncherList.end(); ++it2) {
    (*it2)->setTarget(xtarget,ytarget);
    (*it2)->updateGLauncher();
    }
     
	std::list<MLauncher*>::iterator it3;
    for (it3 = mLauncherList.begin(); it3 != mLauncherList.end(); ++it3) {
    (*it3)->setTarget(xtarget,ytarget);
    (*it3)->updateMLauncher();
    }



}
void Arsenal::render(SDL_Renderer* ren){

    box->render(ren);
    std::list<Gun*>::iterator it2;
    for (it2 = this->gunList.begin(); it2 != this->gunList.end(); ++it2) {
        (*it2)->render(ren);
    }
    std::list<GLauncher*>::iterator it4;
    for (it4 = this->gLauncherList.begin(); it4 != this->gLauncherList.end(); ++it4) {
        (*it4)->render(ren);
    }
    std::list<MLauncher*>::iterator it5;
    for (it5 = this->mLauncherList.begin(); it5 != this->mLauncherList.end(); ++it5) {
        (*it5)->render(ren);
    }

}
void Arsenal::destroyGuns(){

    EntityManagement::clearList<Gun>(this->gunList);
    EntityManagement::clearList<GLauncher>(this->gLauncherList);
    EntityManagement::clearList<MLauncher>(this->mLauncherList);



}
EntityBox* Arsenal::getBox(){

	return this->box;


}
