
#include <random>
#include <cmath>
#include <ctime>
#include "../Includes/auxFuncs.h"
typedef struct gameState{


int pause,homing,orbit;

}gameState;
float Aux::getRandomFloat(float min, float max) {
    std::random_device rd;                          // Obtain a random seed from the hardware
    std::mt19937 eng(rd());                         // Seed the generator
    std::uniform_real_distribution<float> distr(min, max); // Define the range

    return distr(eng);                              // Generate and return a random float
}

 float Aux::calculateDistance(SDL_FPoint p1,  SDL_FPoint p2){
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

Uint8 Aux::getRandomChar() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<Uint8> distr(0, 255); // Define the range


    return distr(rng);
}
float Aux::getRectArea(SDL_FRect rect){

    return rect.w*rect.h;
}
SDL_Color Aux::randColor(){

    Uint8 r=getRandomChar();
    Uint8 g= getRandomChar();
    Uint8 b= getRandomChar();
    Uint8 a= 255;
    return (SDL_Color){r,g,b,a};
}


constexpr float FLOAT_EPSILON = 0.01f;

bool Aux::AreFRectsEqual(const SDL_FRect& rect1, const SDL_FRect& rect2) {
    return (std::abs(rect1.x - rect2.x) < FLOAT_EPSILON) &&
           (std::abs(rect1.y - rect2.y) < FLOAT_EPSILON) &&
           (std::abs(rect1.w - rect2.w) < FLOAT_EPSILON) &&
           (std::abs(rect1.h - rect2.h) < FLOAT_EPSILON);
}

SDL_FPoint Aux::makeUnitVector(SDL_FPoint origin, SDL_FPoint head){


    float dx= head.x-origin.x;
    float dy= head.y-origin.y;

    float udx=std::cos(std::atan2(dy,dx));
    float udy=std::sin(std::atan2(dy,dx));

    return (SDL_FPoint){udx,udy};



}
void Aux::scaleVec(SDL_FPoint* vec,float scalar){

    float dx= vec->x;
    float dy= vec->y;
    dx*=scalar;
    dy*=scalar;
    vec->x=dx;
    vec->y=dy;

}
