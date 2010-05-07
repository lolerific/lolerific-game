import pygame
from pygame.locals import *
import sys

def IS_GetInput():
    pygame.event.pump()
    key = pygame.key.get_pressed()
    for event in pygame.event.get():
        if event.type == QUIT or key[K_ESCAPE]:
            pygame.quit()
            sys.exit()
