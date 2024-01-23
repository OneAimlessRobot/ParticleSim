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
#include "../Includes/container.h"
#include "../Includes/physEngine.h"
#include "../Includes/EntityMgmnt.h"
#include "../Includes/arsenal.h"


Arsenal::Arsenal(Container* cont){
this->cont=cont;

}
Arsenal::~Arsenal(){


}

void Arsenal::shootGuns(){

    std::list<Gun*>::iterator it;
    for (it = cont->getGunList().begin(); it != cont->getGunList().end(); ++it) {
    if(((*it)->canShoot())){

        cont->addEnt((*it)->shoot());
    }
    }
    std::list<GLauncher*>::iterator it2;
    for (it2= cont->getGLauncherList().begin(); it2 != cont->getGLauncherList().end(); ++it2) {
    if(((*it2)->canShoot())){

        cont->addGrenade((*it2)->shoot());
    }
    }
    std::list<MLauncher*>::iterator it3;
    for (it3= cont->getMLauncherList().begin(); it3 != cont->getMLauncherList().end(); ++it3) {
    if(((*it3)->canShoot())){

        cont->addMissile((*it3)->shoot());
    }
    }


}
void Arsenal::monitorGuns(float xtarget,float ytarget){

    std::list<Gun*>::iterator it;
    for (it = cont->getGunList().begin(); it != cont->getGunList().end(); ++it) {
    (*it)->setTarget(xtarget,ytarget);
    (*it)->updateGun();
    }

     std::list<GLauncher*>::iterator it2;
    for (it2 = cont->getGLauncherList().begin(); it2 != cont->getGLauncherList().end(); ++it2) {
    (*it2)->setTarget(xtarget,ytarget);
    (*it2)->updateGLauncher();
    }
     
	std::list<MLauncher*>::iterator it3;
    for (it3 = cont->getMLauncherList().begin(); it3 != cont->getMLauncherList().end(); ++it3) {
    (*it3)->setTarget(xtarget,ytarget);
    (*it3)->updateMLauncher();
    }



}
