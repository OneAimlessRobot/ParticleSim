#ifndef CAR_H
#define CAR_H

class Car:public Entity{
public:

class ForceFunction{
private:
std::map<float,float> dataPoints;

public:
ForceFunction(std::map<float,float> data);
static ForceFunction* defaultForceFunction();
float computePower(float rpm);

};
class Tyre{
private:

float grip,radius;
public:

static Tyre* defaultTyre();


};
class Transmission{
private:
std::vector<float> gearRatios;
float finalDrive;
public:

static Transmission* defaultTransmission();


};
class CarBody{
private:
float Car,frontalArea;
public:
static CarBody* defaultCarBody();


};
Car();
void accelerate();
void brake();
void update();
void getCurrentRPM();
void blowEngine();
~Car();

private:
ForceFunction* engine;
Tyre* tyreModel;
Transmission* transmission;
CarBody* shell;
std::vector<float> gearRatios;
std::string model,brand;





};
#endif
