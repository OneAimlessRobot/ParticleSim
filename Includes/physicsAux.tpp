template <typename T>
void PhysicsAux::railAcceleration(T* ent,SDL_FPoint forceVec,float angle,float length){

    float efficiency=std::cos(angle);
    float efficientComponentMagnitude= GVector::getNorm(forceVec)*efficiency;
    SDL_FPoint paralelToForce=Aux::makeUnitVector((SDL_FPoint){0,0},forceVec);
    float velocitySquared=(1/ent->getMass())*length*efficientComponentMagnitude;
    float velUpdate= std::sqrt(velocitySquared);
    Aux::scaleVec(&paralelToForce,velUpdate);
    accelerateEntity(ent,paralelToForce);





}
