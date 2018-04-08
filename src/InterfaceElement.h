//
//  InterfaceElement.hpp
//  CG
//
//  Created by Administrador on 24/11/15.
//  Copyright © 2015 Administrador. All rights reserved.
//

#ifndef InterfaceElement_h
#define InterfaceElement_h

#include <stdio.h>
#include "Common.h"
#include "Texture.h"

class InterfaceElement{
private:
    
    GLfloat     _x,
                _y,
                _sizex,
                _sizey;
    
    Texture     _texture;
    //GLuint      _textureid;
    
public:
    
    GLboolean   _active;
    
    InterfaceElement();
    ~InterfaceElement();
    InterfaceElement(GLfloat x,  GLfloat y, GLfloat sizex, GLfloat sizey);
    
    void moveTo(GLfloat x, GLfloat y);
    void resize(GLfloat sizex, GLfloat sizey);
    void setTexture(Texture& tex);
    void setTexture(char* pathtotexture);
    void render();
    
};

#endif /* InterfaceElement_h */
