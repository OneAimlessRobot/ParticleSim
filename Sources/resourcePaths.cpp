#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../Includes/resourcePaths.h"

std::vector<std::string> Resources::generateGunMenu(){

std::vector<std::string> gunMenu={};
std::ifstream gunMenuReader(GUNMENU_PATH);
std::string line;
while(std::getline(gunMenuReader,line)){

    gunMenu.push_back(line);

}

return gunMenu;


}

std::vector<std::string> Resources::generateMenu(std::string filePath){

std::cout<<filePath<<"\n";
std::vector<std::string> menu={};
std::ifstream menuReader(filePath);
std::string line;
while(std::getline(menuReader,line)){

menu.push_back(line);

}

return menu;



}
std::vector<std::string> Resources::generateDeleteMenu(){

std::vector<std::string> deleteMenu={};
std::ifstream deleteMenuReader(DELETEMENU_PATH);
std::string line;
while(std::getline(deleteMenuReader,line)){

    deleteMenu.push_back(line);

}

return deleteMenu;


}


std::vector<std::string> Resources::generateBulletMenu(){

std::vector<std::string> bulletMenu={};
std::ifstream bulletMenuReader(CALIBERMENU_PATH);
std::string line;
while(std::getline(bulletMenuReader,line)){

    bulletMenu.push_back(line);

}

return bulletMenu;


}

void Resources::printMenu(std::vector<std::string> menu){


std::vector<std::string>::iterator it;
int number=0;
for(it=menu.begin();it!=menu.end();it++){

    std::cout<<number<<" - "<<(*it)<<"\n";
(number++);
}
std::cout<<"\n";

}

