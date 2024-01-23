#ifndef INT_H
#define INT_H
class InteractiveSim{
private:
SDL_Window* win;
SDL_Renderer* ren;
SDL_Texture * bgr,*ents;
Container* cont;
EntityBox* box;
Arsenal* playground;
PhysicsEngine* engine;
SDL_Color bgrclr;
float maxSpeed, maxSize, ammount,maxMass, airDensity,maxcharge;
int genCount;
int thetime,mouseX,mouseY;

int pause,rendering,collisions,selection,gravity,drag,electricity;
void keyboard(SDL_Event event);
void generationHandling();


int processBulletChoice(caliber* caliber);

void processGunChoice(float x,float y);
void printGunMenu();

void printSimVarsAndStats();
void printKeyboardHelp();


void processDeletion();


void handleToggles(const Uint8* KEYS);
void handleContPresses(const Uint8* KEYS);
void doRendering();

void handleEntities();


public:
InteractiveSim(float maxSpeed,float maxSize,int ammount,float maxMass,float maxcharge);
InteractiveSim();
~InteractiveSim();
void mainLoop();
int init(float maxSpeed,float maxSize,int ammount,float maxMass,float maxcharge);
static InteractiveSim* parseGame();
static InteractiveSim* defaultGame();
};
#endif
