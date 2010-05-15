#include <math.h>
#include "gamedef.h"
#include "mathlib.h"

vec_t VectorLength(vec3_t v)
{
	int		i;
	float	length;

	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += v[i]*v[i];
	length = sqrt(length);

	return length;
}

void VectorNormalize (vec3_t v)
{
	float	length, ilength;

	length = VectorLength(v);

	if (length)
	{
		ilength = 1/length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}
}

void VectorInverse(vec3_t v)
{
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}

void VectorOrigin(vec3_t v)
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

gboolean VectorNear(vec3_t a, vec3_t b, float tollerance, gboolean including)
{
	if(including)
	{
		if((a[0]-b[0]>=tollerance||a[0]+b[0]>=tollerance)||
			(a[1]-b[1]>=tollerance||a[1]+b[1]>=tollerance)||
			(a[2]-b[2]>=tollerance||a[2]+b[2]>=tollerance))
			return gtrue;
	}
	else
	{
		if((a[0]-b[0]>tollerance||a[0]+b[0]>tollerance)||
			(a[1]-b[1]>tollerance||a[1]+b[1]>tollerance)||
			(a[2]-b[2]>tollerance||a[2]+b[2]>tollerance))
			return gtrue;
	}
	return gfalse;
}