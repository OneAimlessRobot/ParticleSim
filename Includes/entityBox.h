#ifndef ENTITYBOX_H
#define ENTITYBOX_H
class EntityBox{
private:
float maxSpeed, maxSize, ammount,maxMass, airDensity,maxcharge;
int genCount,thetime;
Container* cont;
public:



EntityBox(float maxSpeed,float maxSize,float ammount,float maxMass,float airDensity,float macharge,Container* cont);
~EntityBox();
void attentionEveryone();
void freezeEveryone();
void teleportEntityList(float x, float y);

void updateEntities(int collisions,int gravity,int drag,int electricity,float tx, float ty);
void updateEntities();

void generationHandling(float selectQuality);
void makeSelection(float selectQuality);


void addEnt(float x,float y);



void printBox();

};
#endif
