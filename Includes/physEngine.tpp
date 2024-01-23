#include <utility>
#include <set>

template <typename T>  void PhysicsEngine::handleCollisionsWithArena(std::list<T*>& ents){


  typename std::list<T*>::iterator it;
    for (it = ents.begin(); it != ents.end(); ++it) {
        T *current= (*it);
        SDL_FRect currBody=current->getBody();
        if(cont->getArena()->whereIsColliding(currBody)>0){
	
    SDL_FPoint vec=current->getVec();
    
//    std::cout<<current->getPos().x<<" , "<<current->getPos().y<<"\n";
        int where=cont->getArena()->whereIsColliding(currBody);
            current->bounce();
            PhysicsAux::separateEntityFromCollider(current,cont->getArena(),where);
    if (where==1) {
        GVector::Reflect(&vec, new GVector(-1.0f, 0.0f));
    } else if (where==2) {

        GVector::Reflect(&vec, new GVector(1.0f, 0.0f));

    } else if (where==3) {

        GVector::Reflect(&vec, new GVector(0.0f, -1.0f));
    } else if (where==4) {

        GVector::Reflect(&vec, new GVector(0.0f, 1.0f));
    }
        current->setVec(vec);

        //Problema com colisões diagonais (qual eixo de reflexão escolher?)
    }

current->translate();
        

}
}
template <typename T>
void PhysicsEngine::handleInterparticleCollisions(std::list<T*>& ents) {
    typename std::list<T*>::iterator it, it2, endOfSecond;
    std::set<std::pair<T*, T*>> processedPairs;

    for (it = ents.begin(); it != ents.end(); ++it) {
        endOfSecond = ents.end();
        endOfSecond--;

        T *current = (*it);

        for (it2 = it; it2 != endOfSecond;) {
	    ++it2;
            T *current2 = *(it2);

            // Check if the pair has already been processed
            std::pair<T*, T*> currentPair(current, current2);
            std::pair<T*, T*> reversedPair(current2, current);

            if ((processedPairs.find(currentPair) == processedPairs.end() &&
                processedPairs.find(reversedPair) == processedPairs.end())) {

                if (Entity::areTouching(current, current2)) {
                        PhysicsAux::separateEntities(current, current2);
			PhysicsAux::rebound(current, current2);
                }

                // Mark the pair as processed
                processedPairs.insert(currentPair);
                processedPairs.insert(reversedPair);
            }
        }
    }
}
/*template <typename T>

void PhysicsEngine::handleInterparticleCollisions(std::list<T*>& ents){


    typename std::list<T*>::iterator it,it2,endOfSecond;
    for (it = ents.begin(); it != ents.end(); ++it) {
        endOfSecond=ents.end();
        endOfSecond--;
        T *current= (*it);

    for (it2=it; it2 !=endOfSecond;) {
        ++it2;
        T *current2= *(it2);
        if(Entity::areTouching(current,current2)){


            PhysicsAux::rebound(current,current2);
            PhysicsAux::separateEntities(current,current2);

        }

    }



}
}
*/
template <typename T>
void PhysicsEngine::deleteFreaks(std::list<T*>& ents){


    typename std::list<T*>::iterator it;
    for (it = ents.begin(); it != ents.end();) {
        SDL_FPoint v= (*it)->getVec(),p=(*it)->getPos();
        if(v.x!=v.x||v.y!=v.y||p.x!=p.x||p.y!=p.y){
    std::cout<<"ERRO!!!!!\n";
    delete (*it);
    it=ents.erase(it);
    }
    else{
    ++it;

    }



}
}
template <typename T>
void PhysicsEngine::handleInterparticleGravity(std::list<T*>& ents){

    typename std::list<T*>::iterator it,it2,endOfSecond;
    for (it = ents.begin(); it != ents.end(); ++it) {
        endOfSecond=ents.end();
        endOfSecond--;
        T *current= (*it);

    for (it2=it; it2 !=endOfSecond;) {
        ++it2;
        T *current2= *(it2);
        PhysicsAux::accelerateEntity((current2),PhysicsAux::gravVector(current->getCenter(),current2->getCenter(),current->getMass(),current2->getMass()));
        PhysicsAux::accelerateEntity((current),PhysicsAux::gravVector(current2->getCenter(),current->getCenter(),current->getMass(),current2->getMass()));

    }



}
}

template <typename T>
void PhysicsEngine::handleInterparticleElectricity(std::list<T*>& ents){

    typename std::list<T*>::iterator it,it2,endOfSecond;
    for (it = ents.begin(); it != ents.end(); ++it) {
        endOfSecond=ents.end();
        endOfSecond--;
        T *current= (*it);

    for (it2=it; it2 !=endOfSecond;) {
        ++it2;
        T *current2= *(it2);
        PhysicsAux::accelerateEntity((current2),PhysicsAux::electricVector(current->getCenter(),current2->getCenter(),current->getCharge(),current2->getCharge()));
        PhysicsAux::accelerateEntity((current),PhysicsAux::electricVector(current2->getCenter(),current->getCenter(),current->getCharge(),current2->getCharge()));

    }



}
}
template <typename T>
void PhysicsEngine::handleGroundGravity(std::list<T*>& ents){


    typename std::list<T*>::iterator it;
    for (it = ents.begin(); it != ents.end(); ++it) {
        T *current= (*it);
        PhysicsAux::accelerateEntity((cont->getEarthParticle()),PhysicsAux::gravVector(current->getCenter(),cont->getEarthParticle()->getCenter(),current->getMass(),cont->getEarthParticle()->getMass()));
        PhysicsAux::accelerateEntity((current),PhysicsAux::gravVector(cont->getEarthParticle()->getCenter(),current->getCenter(),current->getMass(),cont->getEarthParticle()->getMass()));



}


}
template <typename T>
void PhysicsEngine::doBlast(std::list<T*>& entList,float x, float y,float intensity){


    typename std::list<T*>::iterator it;
    for (it = entList.begin(); it != entList.end(); ++it) {
    SDL_FPoint master=(SDL_FPoint){x,y},
                slave=(*it)->getPos();
        SDL_FPoint forceVec=PhysicsAux::blastVector(master,slave,intensity);

        PhysicsAux::accelerateEntity((*it),forceVec);
}

}
template <typename T>
void PhysicsEngine::orbit(std::list<T*>& entList,float x, float y){


    typename std::list<Entity*>::iterator it;
    for (it = entList.begin(); it != entList.end(); ++it) {
    SDL_FPoint master=(SDL_FPoint){x,y},
                slave=(*it)->getPos();
        SDL_FPoint forceVec=PhysicsAux::gravVector(master,slave,1000000,(*it)->getMass());
        PhysicsAux::accelerateEntity((*it),forceVec);

}

}
template <typename T>
void PhysicsEngine::homming(std::list<T*>& entList,float x, float y){

    typename std::list<T*>::iterator it;
    for (it = entList.begin(); it != entList.end(); ++it) {
    SDL_FPoint master=(SDL_FPoint){x,y},
                slave=(*it)->getPos();
        SDL_FPoint newVec=Aux::makeUnitVector(slave,master);
        Aux::scaleVec(&newVec,homingSpeed);

        (*it)->setVec(newVec);


}
}

template <typename T>

float PhysicsEngine::getAverageSpeed(std::list<T*>& entList){
    float speedSum=0;
    int totalBodies=0;
        typename std::list<T*>::iterator it;
            for (it = entList.begin(); it != entList.end(); ++it) {

                speedSum+=GVector::getNorm((*it)->getVec());
                totalBodies++;

        }
        return speedSum/totalBodies;

}


template <typename T>
float PhysicsEngine::getAverageQuality(std::list<T*>& entList){
    float qualitySum=0;
    int totalBodies=0;
        typename std::list<T*>::iterator it;
            for (it =entList.begin(); it != entList.end(); ++it) {

                qualitySum+=(*it)->getQuality();
                totalBodies++;

        }
        return qualitySum/totalBodies;
}
template <typename T>
float PhysicsEngine::getTotalEnergy(std::list<T*>& entList){
    float energySum=0;
        typename std::list<T*>::iterator it;
            for (it = entList.begin(); it != entList.end(); ++it) {

                energySum+=(*it)->getTotalEnergy();

        }
        std::cout<<"Energia total: "<<energySum<<"\n";
        return energySum;
}

template <typename T>
void PhysicsEngine::handleDrag(std::list<T*>& entList){


    typename std::list<T*>::iterator it;
    for (it = entList.begin(); it != entList.end(); ++it) {

        SDL_FPoint dragVec=PhysicsAux::dragNeutralWindVector((*it)->getVec(),(*it)->getDragConstant(),cont->getArena()->getAirDensity());
        PhysicsAux::accelerateEntity((*it),dragVec);


}



}
