import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
import sys, os

class Console:
    def __init__(self):
        self.visible = False
        surf = pygame.image.load('data/console.bmp').convert_alpha()
        data = pygame.image.tostring(surf,"RGBA",True)
        self.texture = glGenTextures(1)
        glBindTexture(GL_TEXTURE_2D,self.texture)

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,surf.get_width(),surf.get_height(),0,GL_RGBA,GL_UNSIGNED_BYTE,data)
        glTexParameterf(paramtype,GL_TEXTURE_MIN_FILTER,GL_NEAREST)
        glTexParameterf(paramtype,GL_TEXTURE_MAG_FILTER,GL_NEAREST) 
        
    def draw(self):
        glViewport(*self.texture[1].get_rect())
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluOrtho2D(self.surf.get_rect()[0], \
                   self.surf.get_rect()[0]+self.surf.get_rect()[2], \
                   self.surf.get_rect()[1], \
                   self.surf.get_rect()[1]+self.surf.get_rect()[3])
        glBegin(GL_QUADS)        
        glTexCoord2f(-400.0, -300.0); glVertex2f(-400.0, -300.0)
        glTexCoord2f(400.0, -300.0); glVertex2f(400.0, -300.0)
        glTexCoord2f(400.0, 300.0); glVertex2f(400.0, 300.0)
        glTexCoord2f(-400.0, 300.0); glVertex2f(-400.0, 300.0)
        glEnd()
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity() 
        
    def write(self, message, arguments):
        for c in message:
            if c == '{':
                if message[message.find('{')-1] == '\\':
                    break
                else:
                    message.replace('{' + message[message.find('{')+1] + '}', arguments[int(message[message.find('{')+1])])

console = Console()
                
