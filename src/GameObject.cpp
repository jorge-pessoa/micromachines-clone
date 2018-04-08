//
//  GameObject.cpp
//  CGProj
//

/*FIXME handle default collide comment*/

#include "GameObject.h"
#include "Logger.h"
#include "GameManager.h"


void GameObject::setParent(GameObject * gobj)
{
	_parent = gobj;
	_hasParent = true;
}

GameObject::GameObject()
{
	_hasParent = false;
    _rotangle = 0;
    _init_rotangle = _rotangle;
    _rotation.set(0, 0, 0);
    _init_rotation = _rotation;
    _scale.set(1, 1, 1);
	_draw = true;
    _init_scale = _scale;
    _hascollider = false;
    _collisionradius = 1;
    _hasmaterial = false;
	_light_on = false;
}


GameObject::GameObject(GLdouble posx, GLdouble posy, GLdouble posz,
                       GLdouble rotangle , GLdouble rotx, GLdouble roty, GLdouble rotz,
                       GLdouble scalex, GLdouble scaley, GLdouble scalez)
:Entity(posx,posy,posz)
{
    _rotangle = rotangle;
    _init_rotangle = _rotangle;
    _rotation.set(rotx, roty, rotz);
    _init_rotation = _rotation;
    _scale.set(scalex, scaley, scalez);
    _init_scale = _scale;
    _hascollider = false;
    _draw = true;
	if (scalex > scaley) {
		if (scalex > scalez)
			_collisionradius = scalex;
		else _collisionradius = scalez;
	}
	else if (scaley > scalez) {
		_collisionradius = scaley;
	}
	else if (scalez > scaley)
		_collisionradius = scalez;
	else _collisionradius = scalex;
	_light_on = true;
}

GameObject::~GameObject()
{
}

void GameObject::draw()
{
	if (_draw) {
		applyTransform();
		if (_hascollider == true && GameManager::getCurrentInstance()->wireframe()) {
			glColor4f(1, 0, 0, 0.5f);
			glutSolidSphere(_collisionradius*1.5, 8, 8);
		}
        if(_hasmaterial == true){
            _material.applyMaterial();
        }
		render();
	}
}

void GameObject::render()
{
}

void GameObject::update(GLdouble delta_t)
{

}

void GameObject::addChild(GameObject * gobj)
{
	_childs.push_back(gobj);
	gobj->setParent(this);
}

void GameObject::applyTransform()
{
	if (_hasParent == true && _parent != NULL) {
		_parent->applyTransform();
	}
	glTranslated(_position.getX(), _position.getY(), _position.getZ());
	glRotated(_rotangle, _rotation.getX(), _rotation.getY(), _rotation.getZ());
	glScaled(_scale.getX(), _scale.getY(), _scale.getX());
}

void GameObject::addLight(LightSource * light)
{
	_lights.push_back(light);
}

void GameObject::toggleLights()
{
	_light_on = !_light_on;
	for (std::vector<LightSource*>::iterator it = _lights.begin(); it != _lights.end(); ++it) {
		(*it)->setState(_light_on);
	}
}
 
void GameObject::reset()
{
    Entity::reset();
    _rotangle = _init_rotangle;
    _rotation = _init_rotation;
}

void GameObject::reset(GLint lives)
{
}

void GameObject::collide(GameObject* obj) 
{
	//Logger::printf("DEBUG: BOOP BOOP BOOP Something is very wrong in the GameObject, it seems to want to collide with someone, wonder how that happened! (Yes, this is the default collider)\n");
}

void GameObject::collideWith(GameObject* obj) 
{
}

void GameObject::collideWith(Butter * obj)
{
}

void GameObject::collideWith(Orange * obj)
{
}

void GameObject::collideWith(Cheerio * obj)
{
}

void GameObject::collideWith(Car * obj)
{
}

void GameObject::setMaterial(float amb[4], float diff[4], float spec[4], float shine)
{
    _hasmaterial = true;
    _material.setValues(amb, diff, spec, shine);
}

void GameObject::setRotation(GLfloat rot, GLfloat x, GLfloat y, GLfloat z)
{
    _rotation = Vector3(x,y,z);
    _rotangle = rot;
}

void GameObject::setScale(GLfloat x, GLfloat y, GLfloat z)
{
    _scale = Vector3(x,y,z);
}

void GameObject::setInitRotation(GLfloat rotangle, GLfloat x, GLfloat y, GLfloat z)
{
    _init_rotation = Vector3(x,y,z);
    _init_rotangle = rotangle;
}

void GameObject::setInitScale(GLfloat x, GLfloat y, GLfloat z)
{
    _init_scale = Vector3(x,y,z);
}
