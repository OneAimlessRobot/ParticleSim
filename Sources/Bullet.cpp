#include <string>
#include <fstream>
#include <iostream>
#include "../Includes/IOSettings.h"
#include "../Includes/bulletSettings.h"
#include "../Includes/Bullet.h"

caliber caliber::defaultCaliber(){

    return (caliber){DEFAULTBULLETSIZE,DEFAULTBULLETM,DEFAULTBULLETE,0,DEFAULTBULLETQ};


}
//
