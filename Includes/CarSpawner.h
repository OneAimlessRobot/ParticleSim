#ifndef CAR_SPAWN_H
#define CAR_SPAWN_H

class carSpawner{
public:
static Car::Transmission* loadTransmission(std::string filePath);

static Car::Tyre* loadTyre(std::string filePath);

static Car::ForceFunction* loadEngine(std::string filePath);

static Car* loadModel(std::string filePath);


};
#endif
