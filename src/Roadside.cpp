//
//  Roadside.cpp
//  CGproj
//

#include "Roadside.h"
#include "Logger.h"
#include "Cheerio.h"
#include "GameManager.h"

#define CHEERIOS_RATE 14

Roadside::Roadside()
{
	StaticObject();

	_scale =2.8f;
    init();
}

Roadside::Roadside(GLdouble posx, GLdouble posy, GLdouble posz,
             GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
             GLdouble scalex, GLdouble scaley, GLdouble scalez)
:StaticObject(posx, posy, posz,
              rotangle, rotx, roty, rotz,
              scalex, scaley, scalez)
{
	_scale = 2.4f;
	init();
}

Roadside::~Roadside()
{
}

void Roadside::init()
{
    Vector3* p0 = new Vector3(-10,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(0,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(0,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(10,0,-10);
    _control_points.push_back(*p0);
    
    p0 = new Vector3(10,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(20,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(20,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(20,0,5);
    _control_points.push_back(*p0);
    
    p0 = new Vector3(20,0,5);
    _control_points.push_back(*p0);
    p0 = new Vector3(15,0,20);
    _control_points.push_back(*p0);
    p0 = new Vector3(5,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(0,0,5);
    _control_points.push_back(*p0);
    
    p0 = new Vector3(0,0,5);
    _control_points.push_back(*p0);
    p0 = new Vector3(0,0,10);
    _control_points.push_back(*p0);
    p0 = new Vector3(0,0,10);
    _control_points.push_back(*p0);
    p0 = new Vector3(-10,0,10);
    _control_points.push_back(*p0);
    
    p0 = new Vector3(-10,0,10);
    _control_points.push_back(*p0);
    p0 = new Vector3(-20,0,10);
    _control_points.push_back(*p0);
    p0 = new Vector3(-20,0,-10);
    _control_points.push_back(*p0);
    p0 = new Vector3(-10,0,-10);
    _control_points.push_back(*p0);
    
    drawBezierPath();
    calculatePerpendicularPoints();
    
}

void Roadside::render()
{
    /*for(int i = 0; i < _spawnedCheerios.size()-1; i++)
    {
        spawnCheerio(_inside[i].getX()*2, _inside[i].getZ()*2);
        spawnCheerio(_outside[i].getX()*2, _outside[i].getZ()*2);
    }*/
    
}

void Roadside::spawnCheerio(double x, double z)
{
    glColor3f(1, 1, 0.4);
    glPushMatrix();
        glTranslatef(x, -0.6, z);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glScalef(0.5,0.5,0.5);
        glutSolidTorus(0.4,0.9,12,12);
    glPopMatrix();
}

Vector3 Roadside::calculateBezierPoint(float t,Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3)
{
    float u = (1-t);
    float tt = t*t;
    float uu = u*u;
    float uuu = uu * u;
    float ttt = tt * t;
    Vector3 p = *new Vector3();
    p = p0 * uuu; //first term
    p = p + (p1 * (3 * uu * t)); //second term
    p = p + (p2 * (3 * u * tt)); //third term
    p = p + (p3 * ttt); //fourth term
    
    return p;
}


void Roadside::drawBezierPath()
{
	int max = CHEERIOS_RATE;
	GameObject* cheerio;
    for(int i = 0; i < _control_points.size() - 3; i+=4)
    {
        Vector3 p0 = _control_points[i];
        Vector3 p1 = _control_points[i + 1];
        Vector3 p2 = _control_points[i + 2];
        Vector3 p3 = _control_points[i + 3];
        
        if(i == 0) //Only do this for the first endpoint. When i != 0, this coincides with the end point of the previous segment
        {
            _spawned_cheerios.push_back(calculateBezierPoint(0, p0, p1, p2, p3));
        }
        
        for(int j = 1; j <= max; j++)
        {
            float t = j / (float) max;
           _spawned_cheerios.push_back(calculateBezierPoint(t, p0, p1, p2, p3));
        }
    }
}

void Roadside::calculatePerpendicularPoints()
{
    double angle1, angle2;
    float pi = M_PI;
	Vector3 normal;
	GameObject* cheerio;
    for(int i = 0; i < _spawned_cheerios.size(); i++)
    {
        if (i == 0)
        {
            angle1 = (atan2(_spawned_cheerios[i+1].getX()-_spawned_cheerios[_spawned_cheerios.size()-1].getX(), _spawned_cheerios[i+1].getZ()-_spawned_cheerios[_spawned_cheerios.size()-1].getZ()) + pi/2);
            
            angle2 = (atan2(_spawned_cheerios[i+1].getX()-_spawned_cheerios[_spawned_cheerios.size()-1].getX(), _spawned_cheerios[i+1].getZ()-_spawned_cheerios[_spawned_cheerios.size()-1].getZ()) - pi/2);
            //SPAWN CHEERIO
            normal = Vector3(_spawned_cheerios[i].getX()+2*sin(angle1),0,_spawned_cheerios[i].getZ()+2*cos(angle1));
			cheerio = new Cheerio(normal._x*_scale, -1.60, normal._z*_scale);
			GameManager::getCurrentInstance()->addGameObject(cheerio);
			addChild(cheerio);
			//SPAWN CHEERIO
			normal = Vector3(_spawned_cheerios[i].getX()+2*sin(angle2),0,_spawned_cheerios[i].getZ()+2*cos(angle2));
            cheerio = new Cheerio(normal._x*_scale, -1.60, normal._z*_scale);
			GameManager::getCurrentInstance()->addGameObject(cheerio);
			addChild(cheerio);
		}
		else if (i == (_spawned_cheerios.size()-1)) {
        
			angle1 = (atan2(_spawned_cheerios[0].getX()-_spawned_cheerios[i-1].getX(), _spawned_cheerios[0].getZ()-_spawned_cheerios[i-1].getZ()) + pi/2);
        
			angle2 = (atan2(_spawned_cheerios[0].getX()-_spawned_cheerios[i-1].getX(), _spawned_cheerios[0].getZ()-_spawned_cheerios[i-1].getZ()) - pi/2);
			//SPAWN CHEERIO
			normal = Vector3(_spawned_cheerios[i].getX()+2*sin(angle1),0,_spawned_cheerios[i].getZ()+2*cos(angle1));
			cheerio = new Cheerio(normal._x*_scale, -1.60, normal._z*_scale);
			GameManager::getCurrentInstance()->addGameObject(cheerio);
			addChild(cheerio);
			//SPAWN CHEERIO
			normal = Vector3(_spawned_cheerios[i].getX()+2*sin(angle2),0,_spawned_cheerios[i].getZ()+2*cos(angle2));
			cheerio = new Cheerio(normal._x*_scale, -1.60, normal._z*_scale);
			GameManager::getCurrentInstance()->addGameObject(cheerio);
			addChild(cheerio);
		}
		else {
			angle1 = (atan2(_spawned_cheerios[i + 1].getX() - _spawned_cheerios[i - 1].getX(), _spawned_cheerios[i + 1].getZ() - _spawned_cheerios[i - 1].getZ()) + pi / 2);

			angle2 = (atan2(_spawned_cheerios[i + 1].getX() - _spawned_cheerios[i - 1].getX(), _spawned_cheerios[i + 1].getZ() - _spawned_cheerios[i - 1].getZ()) - pi / 2);
			//SPAWN CHEERIO
			normal = Vector3(_spawned_cheerios[i].getX() + 2 * sin(angle1), 0, _spawned_cheerios[i].getZ() + 2 * cos(angle1));
			cheerio = new Cheerio(normal._x*_scale, -1.60, normal._z*_scale);
			GameManager::getCurrentInstance()->addGameObject(cheerio);
			addChild(cheerio);
			//SPAWN CHEERIO
			normal = Vector3(_spawned_cheerios[i].getX() + 2 * sin(angle2), 0, _spawned_cheerios[i].getZ() + 2 * cos(angle2));
			cheerio = new Cheerio(normal._x*_scale, -1.60, normal._z*_scale);
			GameManager::getCurrentInstance()->addGameObject(cheerio);
			addChild(cheerio);
		}
    }
}

void Roadside::update(GLdouble delta_t)
{
	//_position.set(_position._x + delta_t / 200.0, _position._y, _position._z + delta_t / 200.0);
}
