#include "Escalamiento.h"

Escalamiento::Escalamiento(float x, float y)
{
	cols = 3;
	rows = 3;
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, 0);
	}

	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = 1;
}