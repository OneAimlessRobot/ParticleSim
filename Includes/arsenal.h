#ifndef ARSENAL_H
#define ARSENAL_H
class Arsenal{
private:
std::list<Gun*> gunList;
std::list<GLauncher*> gLauncherList;
std::list<MLauncher*> mLauncherList;
EntityBox* box;
public:
Arsenal(EntityBox* box);
~Arsenal();
void spawnGLauncher(float x, float y);
void spawnMLauncher(float x, float y);
void spawnGun(std::string filePath,float x, float y,caliber bType);
void shootGuns();
void render(SDL_Renderer* ren);
void monitorGuns(float xtarget,float ytarget);
void destroyGuns();
EntityBox* getBox();
};

#endif
