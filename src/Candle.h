//
//  Candle.h
//  CGProj
//

#ifndef __CGProj__Candle__
#define __CGProj__Candle__

#include "Common.h"
#include "GameObject.h"
#include "Vector3.h"
#include "PointLight.h"
#include "GameManager.h"
#include "Material.h"

class Candle : public GameObject {
private:
	Material _material_lamp;
public:

	Candle();
	Candle(GLdouble posx, GLdouble posy, GLdouble posz);
	~Candle();

	void render();
};

#endif /* defined(__CGProj__Candle__) */
