#include "Traslacion.h"

Traslacion::Traslacion(float x, float y)
{
	cols = 3;
	rows = 3;
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, 0);
	}
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[2][0] = x;
	mat[2][1] = y;
}

//knothe