#ifndef ENT_MGMNT_H
#define ENT_MGMNT_H
namespace EntityManagement{
template <typename T>
void clearList(std::list<T*>& l);

Gun* parseGun(std::string filePath);
Collider* parseCollider(std::string filePath);
caliber parseCaliber(std::string filePath);
void printGunInfo(std::string filePath);
void printColliderInfo(std::string filePath);
void printCaliberInfo(std::string filePath);

}
#include "EntityMgmnt.tpp"
#endif
