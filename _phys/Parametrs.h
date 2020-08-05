#pragma once
#include <cmath>

double INCREMENT = 0.05;
int WINDOWSIZE = 900;
double PI = 3.14;

int calibrateCenter(int pixelpos)
{
	return pixelpos - WINDOWSIZE / 2;
}

double sinc(double par)
{
	if (par == 0)
		return 1;
	return (sin(par) / par);
}