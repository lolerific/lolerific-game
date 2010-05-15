#include "gamedef.h"

typedef float vec_t;
typedef vec_t vec3_t[3];
extern vec3_t origin;

#define DotProduct(x,y)       (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define VectorSubtract(a,b,c) c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2]
#define VectorAdd(a,b,c)      c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2]
#define VectorMultiply(a,b,c) c[0]=a[0]*b[0];c[1]=a[1]*b[1];c[2]=a[2]*b[2]
#define VectorCopy(a,b)       b[0]=a[0];b[1]=a[1];b[2]=a[2]
#define VectorScale(a,b,s)    b[0]=a[0]*s;b[1]=a[1]*s;b[2]=a[2]*s
#define VectorEqual(a,b)      (a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2])

vec_t VectorLength(vec3_t v);
void  VectorNormalize(vec3_t v);
void  VectorInverse(vec3_t v);
void  VectorOrigin(vec3_t v);
gboolean VectorNear(vec3_t a, vec3_t b, float tollerance, gboolean including);