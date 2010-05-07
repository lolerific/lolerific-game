import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from model import *
from inputsys import *
from gl import *

if sys.platform == 'win32' or sys.platform == 'win64':
    os.environ['SDL_VIDEO_CENTERED'] = '1'

pygame.init()

screen_size = (800, 600)

icon = pygame.Surface((1,1))
icon.set_alpha(0)
pygame.display.set_icon(icon)

surface = pygame.display.set_mode(screen_size, OPENGL|DOUBLEBUF)
    
def main():
    i = DefaultInputGrabber()
    obj = OBJ('untitled.obj')
    GL_Resize(screen_size)
    GL_Init()

    IS_SetInputTarget(i)
    while True:
        IS_GetInput()
        GL_Draw([obj])

if __name__ == '__main__':
    main()
    
