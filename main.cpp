#include "Includes/includes.h"
int main(int argc,char **argv){
InteractiveSim * mgr= InteractiveSim::parseGame();
mgr->mainLoop();
delete mgr;

return 0;
}
