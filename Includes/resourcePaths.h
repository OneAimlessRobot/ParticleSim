#ifndef RES_H
#define RES_H
//#define PROGRAMPATH std::string("/home/hubbo/oar-apps1-master/CPP/ParticleSim/")
#define PROGRAMPATHAUX
#define PROGRAMPATH std::string(PROGRAMPATHAUX)
#define MENU_PATH (PROGRAMPATH+std::string("resources/menus/"))

#define DELETEMENU_PATH (MENU_PATH+std::string("whatToDelete"))


#define ENTITIES_PATH (PROGRAMPATH+std::string("resources/entities/"))
#define COLLIDERS_PATH (ENTITIES_PATH+std::string("collider/"))


#define GUNMENU_PATH (MENU_PATH+std::string("gunMenu"))
#define GUNSPATH (PROGRAMPATH+std::string("resources/guns/"))
#define SRIFLE_PATH (PROGRAMPATH+std::string("resources/guns/sniperRifle.gun"))
#define ARIFLE_PATH (PROGRAMPATH+std::string("resources/guns/assaultRifle.gun"))
#define SMG_PATH (PROGRAMPATH+std::string("resources/guns/subMG.gun"))
#define PISTOL_PATH (PROGRAMPATH+std::string("resources/guns/pistol.gun"))



#define CALIBERMENU_PATH (MENU_PATH+std::string("bulletMenu"))
#define CALIBERS_PATH (PROGRAMPATH+std::string("resources/guns/calibers/"))
#define FIVEFIVESIX_PATH (CALIBERS_PATH +std::string("fivefivesix"))
#define FFORTYF_PATH (CALIBERS_PATH +std::string("fivefortyfive"))
#define SEVENSIXNINE_PATH (CALIBERS_PATH +std::string("sevensixnine"))
#define THREEOEIGHT_PATH (CALIBERS_PATH +std::string("threeoeight"))
#define FFTYBMG_PATH (CALIBERS_PATH +std::string("fiftybmg"))


#define CAR_MENU_PATH (MENU_PATH+std::string("carMenu"))
#define CARS_PATH (PROGRAMPATH+std::string("resources/cars/"))
#define TRANSMISSIONS_PATH (CARS_PATH+std::string("transmissions/"))
#define TYREMODELS_PATH (CARS_PATH+std::string("tyreModels/"))
#define ENGINES_PATH (CARS_PATH+std::string("engines/"))
#define BODY_MODELS_PATH (CARS_PATH+std::string("bodyModels/"))











#define ENTSETTINGS_PATH (ENTITIES_PATH+std::string("ents/defaultentsettings"))

#define DEFAULT_COLLIDER_PATH (COLLIDERS_PATH+std::string("defaultcollider"))

enum gunType {SRIFLE=0,ARIFLE=1,SMG=2,PISTOL=3};


enum caliberType {FFSIX=0,FFORTYF=1,SEVENSIXNINE=2,THREEOEIGHT=3,FFTYBMG=4};

namespace Resources{

std::vector<std::string> generateGunMenu();



std::vector<std::string> generateBulletMenu();

std::vector<std::string> generateMenu(std::string filePath);


std::vector<std::string> generateDeleteMenu();

void printMenu(std::vector<std::string> menu);

}



#endif
