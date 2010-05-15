#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "gl_draw.h"
#include "gamedef.h"
#include "mathlib.h"

vec3_t rot;

int GL_DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f,0.0f,-5.0f);

    glRotatef(rot[0],1.0f,0.0f,0.0f);
    glRotatef(rot[1],0.0f,1.0f,0.0f);
    glRotatef(rot[2],0.0f,0.0f,1.0f);

    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glColor3f( 1.0f, 0.0f, 0.0f );
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glColor3f( 0.0f, 0.0f, 1.0f );
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glColor3f( 0.0f, 0.0f, 0.0f );
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glColor3f( 1.0f, 1.0f, 1.0f );
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    rot[0] += 0.3f;
    rot[1] += 0.2f;
    rot[2] += 0.4f;

    return TRUE;
}