import pygame
from pygame.locals import *
import sys

inputs = []
current_input = None

def IS_SetInputTarget(target):
    global current_input
    current_input = target

class InputGrabber(object):
    def __init__(self):
        self.keys = []
        inputs.append(self)

    def grab(self):
        self.keys = pygame.key.get_pressed()

class DefaultInputGrabber(InputGrabber):
    def __init__(self):
        InputGrabber.__init__(self)

    def grab(self):
        InputGrabber.grab(self)
        if self.keys[K_ESCAPE]:
            pygame.quit()
            sys.exit()

def IS_GetInput():
    global current_input
    pygame.event.pump()
    key = pygame.key.get_pressed()
    current_input.grab()
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
