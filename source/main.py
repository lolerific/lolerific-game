import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from model import *
from inputsys import *
from gl import *
from basentity import *
from entitycontroller import *

if sys.platform == 'win32' or sys.platform == 'win64':
    os.environ['SDL_VIDEO_CENTERED'] = '1'

pygame.init()

screen_size = (800, 600)

icon = pygame.Surface((1,1))
icon.set_alpha(0)
pygame.display.set_icon(icon)

surface = pygame.display.set_mode(screen_size, OPENGL|DOUBLEBUF)

entityController = EntityController()

class Test(BaseEntity):
    def __init__(self):
        BaseEntity.__init__(self)
        BaseEntity.setNextThink(self, entityController.curtime + 1.0)

    def think(self):
        print 'thunk'
        BaseEntity.setNextThink(self, entityController.curtime + 1.0)

linkEntityToClass('test', Test)

def main():
    obj = OBJ('untitled.obj')
    GL_Resize(screen_size)
    GL_Init()

    i = DefaultInputGrabber()
    IS_SetInputTarget(i)

    ent = createEntity('test', 'test1')

    entityController.startupEntities()
    while True:
        IS_GetInput()
        entityController.loop()
        GL_Draw([obj])

    entityController.end()

if __name__ == '__main__':
    main()
    
