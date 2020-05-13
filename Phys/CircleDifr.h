#pragma once

#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Parametrs.h"

class Difraction
{
public:
	Difraction(double _lamda, double _radius, double _screenDistance, double _electrofield): lamda(_lamda), radius(_radius), screenDistance(_screenDistance), electrofield(_electrofield) {};
	virtual void CountField(sf::Image& image) const = 0;
	double lamda = 0;
	double radius = 0;
	double screenDistance = 0;
	double electrofield = 0;
};

class Geometric : public Difraction
{
public:
	Geometric(double _lamda, double _radius, double _screenDistance, double _electrofield) :Difraction(_lamda, _radius, _screenDistance, _electrofield) {};
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				if (calibrateCenter(i) * calibrateCenter(i) + calibrateCenter(j) * calibrateCenter(j) <= radius * radius * 100)
				{
					image.setPixel(i, j, sf::Color(electrofield, 0, 0));
				}
			}
		}
	}
};

class NonGeom : public Difraction
{
public:
	NonGeom(double _lamda, double _radius, double _screenDistance, double _electrofield) :Difraction(_lamda, _radius, _screenDistance, _electrofield) {};
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				double distanceToPoint = sqrt(screenDistance * screenDistance + calibrateCenter(i) * calibrateCenter(i) / 10 + calibrateCenter(j) * calibrateCenter(j) / 10);
				double frenelParam = 2 * PI * radius * radius / (4 * lamda * distanceToPoint);
				double intensivity = 4 * electrofield * sin(frenelParam) * sin(frenelParam) * sqrt(screenDistance / distanceToPoint);
				image.setPixel(i, j, sf::Color(intensivity, 0, 0));
			}
		}
	}
};


class SemiGeom : public Difraction
{
public:
	SemiGeom(double _lamda, double _radius, double _screenDistance, double _electrofield) :Difraction(_lamda, _radius, _screenDistance, _electrofield) {};
	double parametr = sqrt(lamda * screenDistance) / radius;
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				double distanceToPoint = sqrt(screenDistance * screenDistance + calibrateCenter(i) * calibrateCenter(i) / 10 + calibrateCenter(j) * calibrateCenter(j) / 10);
				double frenelParam = 2 * PI * radius * radius / (4 * lamda * distanceToPoint);
				double intensivityDifr = 4 * electrofield * sin(frenelParam) * sin(frenelParam) * sqrt(screenDistance / distanceToPoint);
				double intensivityGeom = 0;
				if (calibrateCenter(i) * calibrateCenter(i) + calibrateCenter(j) * calibrateCenter(j) <= radius * radius * 100)
				{
					intensivityGeom = electrofield;
				}
				double sumIntensivity = intensivityDifr * (parametr - 0.35) * 10 + intensivityGeom * (0.45 - parametr) * 10;
				image.setPixel(i, j, sf::Color(sumIntensivity, 0, 0));
			}
		}
	}
};

void Draw(const Difraction& field, sf::Image& image)
{
	image.create(WINDOWSIZE, WINDOWSIZE, sf::Color::Black);
	field.CountField(image);
}