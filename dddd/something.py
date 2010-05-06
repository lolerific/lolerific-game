import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from model import *
import random
import os, sys

if sys.platform == 'win32' or sys.platform == 'win64':
    os.environ['SDL_VIDEO_CENTERED'] = '1'

pygame.init()

screen_size = (800, 600)

icon = pygame.Surface((1,1))
icon.set_alpha(0)
pygame.display.set_icon(icon)

surface = pygame.display.set_mode(screen_size, OPENGL|DOUBLEBUF)

def resize((width, height)):
    if height == 0:
        height = 1
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, 1.0*width/height, 0.1, 1000.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    
def init():
    glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)
    glEnable(GL_TEXTURE_2D)
    glShadeModel(GL_SMOOTH)
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_ALPHA_TEST)
    glDepthFunc(GL_LEQUAL)
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)
    glAlphaFunc(GL_NOTEQUAL,0.0)

def getinput():
    pygame.event.pump()
    key = pygame.key.get_pressed()
    for event in pygame.event.get():
        if event.type == QUIT or key[K_ESCAPE]:
            pygame.quit()
            sys.exit()
        

def draw(objects):
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    glTranslate(0, 0, -5)
    for obj in objects:
        glCallList(obj.gl_list)

    if console.visible:
        console.draw()
    pygame.display.flip()

def main():
    obj = OBJ('untitled.obj')
    resize(screen_size)
    init()

    while True:
        getinput()
        draw([obj])

if __name__ == '__main__':
    #try:
    main()
    #except Exception, e:
     #   print '%s: %s' % (e.__class__.__name__, e)
      #  raw_input('')
    
