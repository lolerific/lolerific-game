import pygame
from OpenGL.GL import *

def MTL(filename):
    contents = {}
    mtl = None
    for line in open(filename, 'r'):
        if line.startswith('#'): continue
        values = line.split()
        if not values: continue

        if values[0] == 'newmtl':
            mtl = contents[values[1]] = {}
        elif mtl is None:
            raise ValueError, 'mtl file doesn\'t start with newmtl stmt'
        elif values[0] == 'map_Kd':
            mtl[values[0]] = values[1]
            surface = pygame.image.load(mtl['map_Kd'])
            image = pygame.image.tostring(surface, 'RGBA', 1)
            ix, iy = surf.get_rect().size
            texid = mtl['texture_Kd'] = glGenTextures(1)
            glBindTexture(GL_TEXTURE_2D, texid)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            glTexParamereti(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ix, iy, 0, GL_RGBA, GL_UNSIGNED_BYTE, image)
        else:
            mtl[values[0]] = map(float, values[1:])
    return contents
            

class OBJ:
    def __init__(self, filename, swapyz=False):
        self.verts = []
        self.texcoords = []
        self.normals = []
        self.faces = []

        material = None
        for line in open(filename, 'r'):
            if line.startswith('#'): continue
            values = line.split()
            if not values: continue
            if values[0] == 'v':
                v = map(float, values[1:4])
                if swapyz:
                    v = v[0], v[2], v[1]
                self.verts.append(v)
            elif values[0] == 'vn':
                vn = map(float, values[1:4])
                if swapyz:
                    v = v[0], v[2], v[1]
                self.normals.append(v)
            elif values[0] == 'vt':
                self.texcoords.append(map(float, values[1:4]))
            elif values[0] in ('usemtl', 'usemat'):
                material = values[1]
            elif values[0] == 'mtllib':
                self.mtl = MTL(values[1])
            elif values[0] == 'f':
                face = []
                texcoords = []
                norms = []
                for v in values[1:]:
                    w = v.split('/')
                    face.append(int(w[0]))
                    if len(w) >= 2 and len(w[1]) > 0:
                        texcoords.append(int(w[1]))
                    else:
                        texcoords.append(0)
                    if len(w) >= 3 and len(w[2]) > 0:
                        norms.append(int(w[2]))
                    else:
                        norms.append(0)
                self.faces.append((face, norms, texcoords, material))

            self.gl_list = glGenLists(1)
            glNewList(self.gl_list, GL_COMPILE)
            glEnable(GL_TEXTURE_2D)
            glFrontFace(GL_CCW)
            for face in self.faces:
                verts, normals, texcoords, material = face
                mtl = self.mtl[material]

                if 'texture_Kd' in mtl:
                    glBindTexture(GL_TEXTURE_2D, mtl['texture_Kd'])
                else:
                    glColor(*mtl['Kd'])

                glBegin(GL_POLYGON)
                for i in range(len(verts)):
                    if normals[i] > 0:
                        glNormal3fv(self.normals[normals[i]-1])
                    if texcoords[i] > 0:
                        glTexCoord2fv(self.texcoords[texcoords[i]-1])
                    glVertex3fv(self.verts[verts[i]-1])
                glEnd()
            glDisable(GL_TEXTURE_2D)
            glEndList()
            
