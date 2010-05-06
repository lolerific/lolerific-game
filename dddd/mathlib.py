from math import *

origin = [0,0,0]

def ML_VectorAdd(a, b, c, t=float):
    c[0] = t(a[0]+b[0])
    c[1] = t(a[1]+b[1])
    c[2] = t(a[2]+b[2])

def ML_VectorSubtract(a, b, c, t=float):
    c[0] = t(a[0]-b[0])
    c[1] = t(a[1]-b[1])
    c[2] = t(a[2]-b[2])

def ML_VectorMultiply(a, b, c, t=float):
    c[0] = t(a[0]*b[0])
    c[1] = t(a[1]*b[1])
    c[2] = t(a[2]*b[2])

def ML_VectorNear(a, b, tl, i=True):
    if i:
        if (a[0] - b[0] >= tl or a[0] + b[0] <= tl) or \
            (a[1] - b[1] >= tl or a[1] + b[1] <= tl) or \
            (a[2] - b[2] >= tl or a[2] + b[2] <= tl):
                return True
    else:
        if (a[0] - b[0] > tl or a[0] + b[0] < tl) or \
            (a[1] - b[1] > tl or a[1] + b[1] < tl) or \
            (a[2] - b[2] > tl or a[2] + b[2] < tl):
                return True
    return False

def ML_VectorColliding(a, b):
    return ML_VectorNear(a, b, 0)

def ML_VectorLength(a):
    return sqrt((a[0]^2)+(a[1]^2)+(a[2]^2))

def ML_VectorNormal(a):
    L = ML_VectorLength(a)
    a[0] = a[0] / L
    a[1] = a[1] / L
    a[2] = a[2] / L

def ML_VectorDot(a, b):
    return (a[0]*b[0])+(a[1]*b[1])+(a[2]*b[2])

def ML_VectorFacing(a, b):
    ML_VectorNormal(a)
    ML_VectorNormal(b)
    return degrees(acos(ML_VectorDot(a, b)))

def ML_RoundTo(n, r, t):
    return t(n+(r-n))
