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
#include "../Includes/Gun.h"
#include "../Includes/Grenade.h"
#include "../Includes/GLauncher.h"
#include "../Includes/Missile.h"
#include "../Includes/MLauncher.h"
#include "../Includes/physicsAux.h"
#include "../Includes/EntityMgmnt.h"
#include "../Includes/physEngine.h"
#include "../Includes/entityBox.h"
#include "../Includes/arsenal.h"
#include "../Includes/InteractiveSim.h"

InteractiveSim::InteractiveSim(float maxSpeed,float maxSize,int ammount,float maxMass,float maxcharge){
init(maxSpeed,maxSize,ammount, maxMass,maxcharge);

}

InteractiveSim::InteractiveSim(){
init(DEFAULTENTMAXMASS,DEFAULTENTMAXSIZE,1000,DEFAULTENTMAXSPEED,DEFAULTENTMAXCHARGE);

}

int InteractiveSim::init(float maxSpeed,float maxSize,int ammount,float maxMass,float maxcharge){


std::cout<<"Initializing video\n";


if(!SDL_Init(SDL_INIT_EVERYTHING)){
std::cout<<"Done!\n";
}
else{
std::cerr<<"Error loading video. Exiting...(Code 1)\n";
return 1;
}
std::cout<<"Initializing window\n";

this->win= SDL_CreateWindow("ScrSaver",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_RESIZABLE);
if(this->win){
std::cout<<"Done!\n";
}
else{
std::cerr<<"Error loading window. Exiting...(Code 2)\n";
return 2;
}

std::cout<<"Initializing renderer\n";


this->ren=SDL_CreateRenderer(this->win,-1,SDL_RENDERER_ACCELERATED);
if(this->ren){
std::cout<<"Done!\n";
}
else{
std::cerr<<"Error loading window. Exiting...(Code 3)\n";
return 3;
}


std::cout<<"Initializing background\n";
this->bgr= SDL_CreateTexture(ren,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);

if(this->bgr){
std::cout<<"Done!\n";
}
else{
std::cerr<<"Error loading background. Exiting...(Code 4)\n";
return 4;
}
std::cout<<"Initializing entities\n";
this->ents= SDL_CreateTexture(ren,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);

if(this->ents){
std::cout<<"Done!\n";
}
else{
std::cerr<<"Error loading background. Exiting...(Code 5)\n";
return 5;
}


this->pause=0;
this->rendering=1;
this->selection=0;
this->collisions=0;
this->drag=0;
this->gravity=0;
this->electricity=0;

this->playground=new Arsenal(new EntityBox(maxSpeed,maxSize,ammount,maxMass,airDensity, maxcharge));
this->playground->getBox()->setPhysicsEngine(new PhysicsEngine(this->playground->getBox()));

}

InteractiveSim* InteractiveSim::parseGame(){



std::ifstream entSettingsRead(ENTSETTINGS_PATH);
float maxspeed,maxsize,maxmass,maxcharge,ammount;
    std::string dummy;
    while(dummy.rfind(COMMENTPREFIX, 0) == 0){

    std::getline(entSettingsRead,dummy);

    }

if(!entSettingsRead.is_open()){

std::cout<<"ERRO DE FICHEIRO A CARREGAR JOGO!!!!\n"<<ENTSETTINGS_PATH<<"\n";
return new InteractiveSim();

}
entSettingsRead>>maxspeed>>maxsize>>ammount>>maxmass>>maxcharge;
entSettingsRead.close();
return new InteractiveSim(maxspeed,maxsize,ammount,maxmass,maxcharge);







}

InteractiveSim* InteractiveSim::defaultGame(){
return new InteractiveSim();

}
void InteractiveSim::mainLoop(){
SDL_Event e;
SDL_bool quit=SDL_FALSE;
const Uint8* KEYS = SDL_GetKeyboardState(nullptr);

while(!quit){

int startTime= SDL_GetTicks();

    SDL_GetMouseState(&this->mouseX,&this->mouseY);

    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT){

        quit=SDL_TRUE;


        }
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
	if(KEYS[SDL_SCANCODE_Q]) {
    		
        	quit=SDL_TRUE;
	}
	else{
            	handleToggles(KEYS);
  	}
	}


    }
    handleContPresses(KEYS);

    handleEntities();
    if(this->rendering){
    doRendering();
    int endTime= SDL_GetTicks();

if((endTime-startTime)<((1/FRAMERATE)*1000)){

SDL_Delay(((1/FRAMERATE)*1000)-(endTime-startTime));
}


    }

}
}



void InteractiveSim::handleEntities(){

    if(!this->pause){
    
    playground->getBox()->updateEntities(collisions,gravity,drag,electricity,this->mouseX*1.0f,this->mouseY*1.0f);
    playground->monitorGuns((float)this->mouseX,(float)this->mouseY);
    if(this->selection){
    playground->getBox()->generationHandling();
    }
    }
    

}
void InteractiveSim::doRendering(){

    SDL_SetRenderDrawColor(this->ren,this->bgrclr.r,this->bgrclr.g,this->bgrclr.b,this->bgrclr.a);
    SDL_SetRenderTarget(ren,bgr);
    SDL_RenderClear(ren);
    SDL_SetRenderTarget(ren,ents);
    SDL_RenderCopy(ren,bgr,NULL,NULL);
    playground->render(ren);
    SDL_SetRenderTarget(ren,NULL);
    SDL_RenderCopy(ren,ents,NULL,NULL);
    SDL_RenderPresent(ren);

}
void InteractiveSim::handleContPresses(const Uint8*KEYS){
    if(KEYS[SDL_SCANCODE_LEFT]) {
        std::thread orbitWorker(&EntityBox::orbit,this->playground->getBox(),mouseX*1.0,mouseY*1.0);
        orbitWorker.detach();
    }
    if(KEYS[SDL_SCANCODE_RIGHT]) {

        std::thread hommingWorker(&EntityBox::homming,this->playground->getBox(),this->mouseX*1.0,this->mouseY*1.0);
        hommingWorker.detach();
    }
    if(KEYS[SDL_SCANCODE_M]) {
        std::thread blastingWorker(&EntityBox::blast,this->playground->getBox(),this->mouseX*1.0,this->mouseY*1.0);
        blastingWorker.detach();
    }
    if(KEYS[SDL_SCANCODE_DOWN]) {
        std::thread shootingWorker(&Arsenal::shootGuns,this->playground);
        shootingWorker.detach();
    //std::cout<<"Mouse (X,Y): ("<<this->mouseX<<" , "<<this->mouseY<<")\n";
}

    if(KEYS[SDL_SCANCODE_ESCAPE]) {
    }
}

void InteractiveSim::printSimVarsAndStats(){

    std::cout<<"============================Variaveis de teclado:============================================\n";
    std::cout<<"Gravidade ativa?: "<<this->gravity<<"\n";
    std::cout<<"Atrito do ar ativo?: "<<this->drag<<"\n";
    std::cout<<"Colisões ativas?: "<<this->collisions<<"\n";
    std::cout<<"Eletricidade ativa?: "<<this->electricity<<"\n";
    playground->getBox()->printBox();

}

void InteractiveSim::printKeyboardHelp(){


    std::cout<<"=============================Comandos de Spawning=============================================\n";
    std::cout<<"Arma: G\n";
    std::cout<<"Particula: S\n";
    std::cout<<"Lança granadas: V\n";
    std::cout<<"Lança misseis: X\n";
    std::cout<<"Disparar armas disponiveis: DOWNARROW\n";
    std::cout<<"Apagar objetos: D\n";
    std::cout<<"============================Comandos de efeitos:============================================\n";
    std::cout<<"Toggle Gravity: E\n";
    std::cout<<"Make explosion around mouse: M\n";
    std::cout<<"Toggle collisions: C\n";
    std::cout<<"Toggle electricity: W\n";
    std::cout<<"Toggle gravity around mouse: LEFTARROW\n";
    std::cout<<"Puxar particulas: RIGHTARROW\n";
    std::cout<<"Toggle pause: P\n";
    std::cout<<"Toggle selection mode: N\n";
    std::cout<<"Toggle rendering: R\n";
    std::cout<<"Freeze entities: B\n";
    std::cout<<"============================Comandos de feedback:============================================\n";
    std::cout<<"Mostrar energia total: J\n";
    std::cout<<"Mostrar estado de todas as particulas: UPARROW\n";
    std::cout<<"Mostrar ajuda: H\n";
    std::cout<<"Mostrar estado da simulaçao: T\n";
    std::cout<<"Informaçoes do ambiente: F\n";



}
void InteractiveSim::handleToggles(const Uint8*KEYS){

    if(KEYS[SDL_SCANCODE_UP]) {
        /*std::thread printing(&InteractiveSim::printSpeedsAndPos,this);
        printing.detach();
    	*/
	playground->getBox()->printSpeedsAndPos();
	}
    if(KEYS[SDL_SCANCODE_P]) {
    if(this->pause){
        this->pause=SDL_FALSE;
    }
    else{
        this->pause=SDL_TRUE;
    }
    }
    if(KEYS[SDL_SCANCODE_J]) {
        playground->getBox()->getTotalEnergy();
//        std::thread showEnergy(&InteractiveSim::getTotalEnergy,this);
//        showEnergy.detach();
    }
    if(KEYS[SDL_SCANCODE_S]) {
    playground->getBox()->addEnt(this->mouseX*1.0f,this->mouseY*1.0f);
    }
    if(KEYS[SDL_SCANCODE_R]) {
    if(this->rendering){
        this->rendering=SDL_FALSE;
    }
    else{
        this->rendering=SDL_TRUE;
    }
    }

    if(KEYS[SDL_SCANCODE_A]) {
    if(this->drag){
        this->drag=SDL_FALSE;
    }
    else{
        this->drag=SDL_TRUE;
    }
    }

    if(KEYS[SDL_SCANCODE_E]) {
    if(this->gravity){
        this->gravity=SDL_FALSE;
    }
    else{
        this->gravity=SDL_TRUE;
    }
    }
    if(KEYS[SDL_SCANCODE_C]) {
    if(this->collisions){
        this->collisions=SDL_FALSE;
    }
    else{
        this->collisions=SDL_TRUE;
    }
    }
    if(KEYS[SDL_SCANCODE_N]) {
    if(this->selection){
        this->selection=SDL_FALSE;
    }
    else{
        this->selection=SDL_TRUE;
    }
    }
    if(KEYS[SDL_SCANCODE_G]) {
        std::thread newGun(&InteractiveSim::processGunChoice,this,this->mouseX*1.0f,this->mouseY*1.0f);
        newGun.detach();

    }

    if(KEYS[SDL_SCANCODE_T]) {
        std::thread statsWorker(&InteractiveSim::printSimVarsAndStats,this);
        statsWorker.detach();

    }

    if(KEYS[SDL_SCANCODE_H]) {
        std::thread helpMenuWorker(&InteractiveSim::printKeyboardHelp,this);
        helpMenuWorker.detach();

    }

    if(KEYS[SDL_SCANCODE_V]) {

        playground->spawnGLauncher(this->mouseX*1.0f,this->mouseY*1.0f);

    }
    if(KEYS[SDL_SCANCODE_X]) {

        playground->spawnMLauncher(this->mouseX*1.0f,this->mouseY*1.0f);

    }
    if(KEYS[SDL_SCANCODE_D]) {

        processDeletion();

    }

    if(KEYS[SDL_SCANCODE_F]) {

        std::thread arenaInfo(&EntityManagement::printColliderInfo,DEFAULT_COLLIDER_PATH);
        arenaInfo.detach();

    }
    if(KEYS[SDL_SCANCODE_B]) {

     	playground->getBox()->freezeEveryone();
	
    }
    if(KEYS[SDL_SCANCODE_W]) {
	
    if(this->electricity){
        this->electricity=SDL_FALSE;
    }
    else{
        this->electricity=SDL_TRUE;
    }
     
    }
}

int InteractiveSim::processBulletChoice(caliber* bType){

std::string choice;
std::string path;
int whatToDo;
do{
std::cout<<"0- Para escolher um calibre\n";
std::cout<<"1- Para ver informaçoes de um calibre\n";
std::cout<<"2- Sair\n";

std::cin>>whatToDo;
if(!whatToDo){
	Resources::printMenu(Resources::generateBulletMenu());
    	std::cin>>choice;
        path=CALIBERS_PATH+choice;
        *bType=EntityManagement::parseCaliber(path);
    	std::cout<<bType->size<<" , "<<bType->mass<<",  "<<bType->e<<" , "<<bType->Car<<" \n";
        }
        else if(whatToDo==1){
        Resources::printMenu(Resources::generateBulletMenu());
    	std::cin>>choice;
        path=CALIBERS_PATH+choice;
        EntityManagement::printCaliberInfo(path);
        }
    }while(whatToDo==1);
return whatToDo;
}
void InteractiveSim::processDeletion(){
int choice;
std::cout<<"Queres apagar...\n";
Resources::printMenu(Resources::generateDeleteMenu());
std::cout<<"Outra- Ou nada?\n";
std::cin>>choice;
switch (choice){
    case 0:{
        playground->getBox()->destroyEntities();
        playground->destroyGuns();

    break;
    }
    case 1:{


        playground->destroyGuns();


    break;
    }
    case 2:{


        playground->getBox()->destroyEntities();


    break;
    }
    default:
    break;



}




}
void InteractiveSim::processGunChoice(float x,float y){

    std::string choice,path;
    int whatToDo;
    do{
std::cout<<"0- Spawnar uma arma\n";
std::cout<<"1- Ve informacoes de uma arma\n";
std::cout<<"2- Sair do menu\n";
    std::cin>>whatToDo;
        
	if(!whatToDo){
                Resources::printMenu(Resources::generateMenu(GUNMENU_PATH));
    		std::cin>>choice;
    		std::string extension=".gun";
    		path= GUNSPATH+choice+extension;
                caliber chosenCaliber;
                if(processBulletChoice(&chosenCaliber)==2){

				return;
		}
		playground->spawnGun(path,x,y,chosenCaliber);
                }
                else if(whatToDo==1){
                Resources::printMenu(Resources::generateMenu(GUNMENU_PATH));
    		std::cin>>choice;
    		std::string extension=".gun";
    		path= GUNSPATH+choice+extension;
                EntityManagement::printGunInfo(path);
                }

   }while(whatToDo==1);



}
InteractiveSim::~InteractiveSim(){


delete playground;
SDL_DestroyTexture(this->bgr);
SDL_DestroyTexture(this->ents);
SDL_DestroyRenderer(this->ren);
SDL_DestroyWindow(this->win);

SDL_Quit();
}

