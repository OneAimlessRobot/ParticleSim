
#ifndef G_VEC
#define G_VEC
class GVector {

private:
float x,y;

public:
    GVector(float x,float y);
    float getX();
    float getY();
    void setX(float newX);
    void setY(float newY);
    static float getNorm(SDL_FPoint point);
    SDL_FPoint getCoords();
    void setCoords(SDL_FPoint point);
    static void Reflect(SDL_FPoint* velocity, GVector* collisionNormal);
    static SDL_FPoint add(SDL_FPoint v1, SDL_FPoint v2);
    static float dotProduct(SDL_FPoint v1,SDL_FPoint v2);
    static float angleBetween(SDL_FPoint v1,SDL_FPoint v2);
    static SDL_FPoint tiltVector(SDL_FPoint v,float angle);
    ~GVector();





};
#endif
