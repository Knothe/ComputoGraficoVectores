#include "Rotacion.h"
#include <math.h>

Rotacion::Rotacion(float angle)
{
	cols = 3;
	rows = 3;
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, 0);
	}
	mat[0][0] = cos(angle);
	mat[0][1] = sin(angle);
	mat[1][0] = -sin(angle);
	mat[1][1] = cos(angle);
	mat[2][2] = 1;
}