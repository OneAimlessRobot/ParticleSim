
template <typename T> void EntityManagement::clearList(std::list<T*>& l){



    typename std::list<T*>::iterator it;
    for (it = l.begin(); it != l.end(); ) {
            delete (*it);
            it=l.erase(it);
    }



}
