//
//  Roadside.h
//  CGproj
//

#ifndef __CGproj__Roadside__
#define __CGproj__Roadside__

#include "Common.h"
#include "StaticObject.h"
#include "Vector3.h"
#include <vector>

class Roadside : public StaticObject {
private:
    std::vector<Vector3> _spawned_cheerios,
						 _control_points;
	GLdouble _scale;
public:
    Roadside();
    Roadside(GLdouble posx, GLdouble posy, GLdouble posz,
           GLdouble rotangle=0, GLdouble rotx=0, GLdouble roty=0, GLdouble rotz=0,
           GLdouble scalex=1, GLdouble scaley=1, GLdouble scalez=1);
    ~Roadside();

    void render();
    void init();
    void spawnCheerio(double x, double z);

    Vector3 calculateBezierPoint(float t,Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3);
    void drawBezierPath();
    void calculatePerpendicularPoints();

	void update(GLdouble delta_t);
};
    
#endif /* defined(__CGproj__Roadside__) */
