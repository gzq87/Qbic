#pragma once

#define PI       3.14159265358979323846
#define EPSILON5	(1E-5)
#define EPSILON3 (1E-3)
#define DEG2RAD(d) ((d)*(PI/180.0))
#define RAD2DEG(r) ((r)*(180.0/PI))

enum AxisName
{
	AN_X,
	AN_Y,
	AN_Z
};