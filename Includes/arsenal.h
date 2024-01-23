#ifndef ARSENAL_H
#define ARSENAL_H
class Arsenal{
private:
Container* cont;
public:
Arsenal(Container* cont);
~Arsenal();
void shootGuns();
void monitorGuns(float xtarget,float ytarget);
};

#endif
