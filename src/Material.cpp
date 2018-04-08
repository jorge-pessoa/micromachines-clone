//
//  Material.cpp
//  CGProj
//

#include "Material.h"

Material::Material()
{
}

Material::Material(GLfloat amb[4], GLfloat diff[4], GLfloat spec[4], GLfloat shine)
{
    this->setValues(amb, diff, spec, shine);
}

Material::~Material()
{
}

void Material::applyMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shine);
}

void Material::setValues(GLfloat amb[4], GLfloat diff[4], GLfloat spec[4], GLfloat shine)
{
    _amb[0] = amb[0];
    _amb[1] = amb[1];
    _amb[2] = amb[2];
    _amb[3] = amb[3];
    _diff[0] = diff[0];
    _diff[1] = diff[1];
    _diff[2] = diff[2];
    _diff[3] = diff[3];
    _spec[0] = spec[0];
    _spec[1] = spec[1];
    _spec[2] = spec[2];
    _spec[3] = spec[3];
    _shine = shine;
}