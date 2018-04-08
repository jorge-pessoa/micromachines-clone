//
//  InterfaceElement.cpp
//  CG
//
//  Created by Administrador on 24/11/15.
//  Copyright © 2015 Administrador. All rights reserved.
//

#include "InterfaceElement.h"

InterfaceElement::InterfaceElement()
{
}

InterfaceElement::~InterfaceElement()
{
}

InterfaceElement::InterfaceElement(GLfloat x, GLfloat y, GLfloat sizex, GLfloat sizey)
{
    _x = x;
    _y = y;
    _sizex = sizex;
    _sizey = sizey;
}

void InterfaceElement::moveTo(GLfloat x, GLfloat y)
{
    _x = x;
    _y = y;
}

void InterfaceElement::resize(GLfloat sizex, GLfloat sizey)
{
    _sizex = sizex;
    _sizey = sizey;
}

void InterfaceElement::setTexture(Texture& tex)
{
    _texture = tex;
}

void InterfaceElement::setTexture(char* pathtotexture)
{
    _texture.chooseImage(pathtotexture);
    _texture.generateTexture();
}

void InterfaceElement::render()
{
    
    _texture.bindTexture();
    glColor3f(0.8, 0.8, 0.8);
    if(_active){
        glPushMatrix();
        glTranslatef(_x, 2, _y);
        
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(0, 0, _sizey);
        
        glTexCoord2f(1,1);
        glVertex3f(_sizex, 0, _sizey);
        
        glTexCoord2f(1,0);
        glVertex3f(_sizex, 0, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glEnd();
        
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
}