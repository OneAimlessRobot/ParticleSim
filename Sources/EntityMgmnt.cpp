#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include "../Includes/allSettings.h"
#include <iterator>
#include <vector>
#include "SDL2/SDL.h"
#include "../Includes/Collider.h"
#include "../Includes/GVector.h"
#include "../Includes/auxFuncs.h"
#include "../Includes/Bullet.h"
#include "../Includes/Entity.h"
#include "../Includes/Gun.h"
#include "../Includes/EntityMgmnt.h"


Gun* EntityManagement::parseGun(std::string filePath){
std::ifstream gunRead(filePath);
float force, barrelLen,
            recoil,
            spread,
            reloadTime;
int capacity,
    shootperiod;
    std::string dummy;
    while(dummy.rfind(COMMENTPREFIX, 0) == 0){

    std::getline(gunRead,dummy);

    }

gunRead>>force>>barrelLen>>spread>>recoil>>reloadTime>>capacity>>shootperiod;
if(!gunRead.is_open()){

std::cout<<"ERRO DE FICHEIRO A CARREGAR FICHEIRO!!!!\n"<<filePath<<"\n";
return Gun::defaultGun();

}
gunRead>>force>>barrelLen>>spread>>recoil>>reloadTime>>capacity>>shootperiod;
gunRead.close();
return new Gun(Aux::randColor(),0,0,
            DEFAULTGUNW,
            DEFAULTGUNH,
            DEFAULTGUNE,
            DEFAULTGUNM,
            DEFAULTGUNCAR,
            DEFAULTGUNQ,
	    force,
            recoil,
            barrelLen,
            spread,
            capacity,
            reloadTime,
            shootperiod
            );






}
Collider* EntityManagement::parseCollider(std::string filePath){



std::ifstream colliderRead(filePath);
float x,y,width,height,thickness,airDensity;
int r,g,b,a;
if(!colliderRead.is_open()){

std::cout<<"ERRO DE FICHEIRO A CARREGAR COLLIDER!!!!\n"<<filePath<<"\n";
return Collider::defaultCollider();

}
std::string dummy;
    while(dummy.rfind(COMMENTPREFIX, 0) == 0){

    std::getline(colliderRead,dummy);

    }
colliderRead>>r>>g>>b>>a>>x>>y>>width>>height>>thickness>>airDensity;
colliderRead.close();
SDL_Color color=(SDL_Color){r,g,b,a};
return new Collider(color,x,y,width,height,thickness,airDensity);





}
caliber EntityManagement::parseCaliber(std::string filePath){
std::ifstream bulletReader(filePath);
float size,mass,e,Car;
if(!bulletReader.is_open()){

std::cout<<"ERRO DE FICHEIRO A CARREGAR ARMA!!!!\n"<<filePath<<"\n";
return caliber::defaultCaliber();


}
bulletReader>>size>>mass>>e>>Car;
bulletReader.close();
return (caliber){size,mass,e,Car,DEFAULTBULLETQ};



}

void EntityManagement::printGunInfo(std::string filePath){
std::ifstream gunRead(filePath);
float force, barrelLen,
            recoil,
            spread,
            reloadTime;
int capacity,
    shootperiod;
std::string dummy;
    while(dummy.rfind(COMMENTPREFIX, 0) == 0){

    std::getline(gunRead,dummy);

    }
gunRead>>force>>barrelLen>>spread>>recoil>>reloadTime>>capacity>>shootperiod;
gunRead.close();
std::cout<<"Características:\n";
std::cout<<"Força: "<<force<<"\n";
std::cout<<"Capacidade: "<<capacity<<"\n";
std::cout<<"spread: "<<spread<<"\n";
std::cout<<"recoil: "<<capacity<<"\n";
std::cout<<"Comprimento cano: "<<barrelLen<<"\n";
std::cout<<"Reloadtime: "<<reloadTime<<"\n";
std::cout<<"ShootCooldown: "<<shootperiod<<"\n";

}

void EntityManagement::printColliderInfo(std::string filePath){
std::ifstream colliderRead(filePath);
float x,y,width,height,thickness,airDensity;
int r,g,b,a;
if(!colliderRead.is_open()){

std::cout<<"ERRO DE FICHEIRO A CARREGAR COLLIDER!!!!\n"<<filePath<<"\n";
}
std::string dummy;
    while(dummy.rfind(COMMENTPREFIX, 0) == 0){

    std::getline(colliderRead,dummy);

    }
colliderRead>>r>>g>>b>>a>>x>>y>>width>>height>>thickness>>airDensity;
colliderRead.close();
std::cout<<"Cor: "<<r<<" "<<g<<" "<<b<<" "<<a<<"\n";
std::cout<<"Posiçao: "<<x<<" "<<x<<"\n";
std::cout<<"Dimensões: "<<width<<" "<<height<<"\n";
std::cout<<"Espessura: "<<thickness<<"\n";
std::cout<<"densidadedear: "<<airDensity<<"\n";





}

void EntityManagement::printCaliberInfo(std::string filePath){
std::ifstream bulletReader(filePath);
float size,mass,e,Car;
if(!bulletReader.is_open()){

std::cout<<"ERRO DE FICHEIRO A CARREGAR ARMA!!!!\n"<<filePath<<"\n";

}
std::string dummy;
    while(dummy.rfind(COMMENTPREFIX, 0) == 0){

    std::getline(bulletReader,dummy);

    }
bulletReader>>size>>mass>>e>>Car;
std::cout<<"Características:\n";
std::cout<<"Tamanho: "<<size<<"\n";
std::cout<<"Massa: "<<mass<<"\n";
std::cout<<"Coeficiente de restituiçao invertido: "<<e<<"\n";
std::cout<<"Coeficiente de atrito aerodinamico: "<<Car<<"\n";
bulletReader.close();


}

