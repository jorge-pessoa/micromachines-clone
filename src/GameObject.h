//
//  GameObject.h
//  CGProj
//

#ifndef __CGProj__GameObject__
#define __CGProj__GameObject__

#include "Common.h"
#include "Entity.h"
#include "Vector3.h"
#include "Material.h"
#include "LightSource.h"
#include "Texture.h"

class Butter;
class Orange;
class Cheerio;
class Car;
class LightSource;

class GameObject : public Entity {
protected:
    Vector3 _rotation,
			_init_rotation,
			_init_scale,
			_scale;
    GLdouble _rotangle,
			 _init_rotangle;
	GLboolean _hasParent,
			  _draw;
	Material _material;
	Texture _texture;
	GLboolean _hasmaterial,
			  _light_on,
			  _hastexture;
		
	std::vector<GameObject*> _childs;
 	std::vector<LightSource*> _lights;
	GameObject* _parent;
	
	
	void setParent(GameObject* gobj);
    
public:
    GLboolean _hascollider;
    GLdouble _collisionradius;
	GameObject();
    GameObject(GLdouble posx, GLdouble posy, GLdouble posz,
		GLdouble rotangle = 0, GLdouble rotx = 0, GLdouble roty = 0, GLdouble rotz = 0,
		GLdouble scalex = 1, GLdouble scaley = 1, GLdouble scalez = 1);
	~GameObject();

	virtual void draw();
	virtual void render();
	virtual void update(GLdouble delta_t);

	void addChild(GameObject* gobj);
	void applyTransform();

	void addLight(LightSource* light);
	void toggleLights();

    virtual void reset();
    virtual void reset(GLint _lives);

	virtual void collide(GameObject* obj);
	virtual void collideWith(GameObject* obj);
	virtual void collideWith(Butter* obj);
	virtual void collideWith(Orange* obj);
	virtual void collideWith(Cheerio* obj);
    virtual void collideWith(Car* obj);
    void setMaterial(float amb[4], float diff[4], float spec[4], float shine);
    void setRotation(GLfloat rot, GLfloat x, GLfloat y, GLfloat z);
    void setScale(GLfloat x, GLfloat y, GLfloat z);
    void setInitRotation(GLfloat rotangle, GLfloat x, GLfloat y, GLfloat z);
    void setInitScale(GLfloat x, GLfloat y, GLfloat z);
    
};
#endif /* defined(__CGProj__GameObject__) */
