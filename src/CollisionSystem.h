//
//  CollisionSystem.h
//  CGProj
//

#ifndef __CGProj__CollisionSystem__
#define __CGProj__CollisionSystem__

#include "Common.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Car.h"
#include "Orange.h"


class CollisionSystem {
    GLdouble _radius;
    GameObject * _obj;
public:
  
    CollisionSystem(GLdouble radius);
    ~CollisionSystem();
    void searchCollisions(std::vector<GameObject*>& objs, DynamicObject* target);
    GLboolean checkCollision(GameObject* obj1, GameObject* obj2);
    
};
#endif /* defined(__CGProj__CollisionSystem__) */

