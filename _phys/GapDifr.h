#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Parametrs.h"

class GapDifr
{
public:
	GapDifr(double _lamda, double _width, double _screenDistance, double _electrofield) : lamda(_lamda), width(_width), screenDistance(_screenDistance), electrofield(_electrofield) {};
	virtual void CountField(sf::Image& image) const = 0;
	double lamda = 0;
	double width = 0;
	double screenDistance = 0;
	double electrofield = 0;
};

class GapGeometric : public GapDifr
{
public:
	GapGeometric(double _lamda, double _width, double _screenDistance, double _electrofield) :GapDifr(_lamda, _width, _screenDistance, _electrofield) {};
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				if (abs(calibrateCenter(i)) <= width * 5)
				{
					image.setPixel(i, j, sf::Color(electrofield, 0, 0));
				}
			}
		}
	}
};

class GapGeomFrenel : public GapDifr
{
public:
	GapGeomFrenel(double _lamda, double _width, double _screenDistance, double _electrofield) :GapDifr(_lamda, _width, _screenDistance, _electrofield) {};
	double parametr = sqrt(lamda * screenDistance) / width;
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			double difrParam = (PI * width / lamda) * (abs(calibrateCenter(i))) / (10 * screenDistance);
			//double koef = 10 * (abs(calibrateCenter(i)) / 10) / width;
			double intensivityDifr = 0;
			double intensivityGeom = 0;
			
			if (abs(calibrateCenter(i)) <= width * 5)
			{
				intensivityGeom = electrofield;
				intensivityDifr = electrofield * sin(difrParam) * sin(difrParam);
			}
			double sumIntensivity = intensivityDifr * (parametr - 0.25) * 5 +  intensivityGeom * (0.45 - parametr) * 5;
			if (sumIntensivity > 255)
			{
				sumIntensivity = 255;
			}
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				//std::cout << sumIntensivity << std::endl;
				image.setPixel(i, j, sf::Color(sumIntensivity, 0, 0));
			}
		}
	}
};

class GapFrenel : public GapDifr
{
public:
	GapFrenel(double _lamda, double _width, double _screenDistance, double _electrofield) :GapDifr(_lamda, _width, _screenDistance, _electrofield) {};
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			double difrParam = (PI * width / lamda) * (abs(calibrateCenter(i))) / (10 * screenDistance);
			double intensivity = 0;
			if (abs(calibrateCenter(i)) <= width * 5)
			{
				intensivity =  electrofield * sin(difrParam) * sin(difrParam);
			}
			if (intensivity > 255)
			{
				intensivity = 255;
			}
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				//std::cout << intensivity << std::endl;
				image.setPixel(i, j, sf::Color(intensivity, 0, 0));
			}
		}
	}
};

class GapFrenelFraungof : public GapDifr
{
public:
	GapFrenelFraungof(double _lamda, double _width, double _screenDistance, double _electrofield) :GapDifr(_lamda, _width, _screenDistance, _electrofield) {};
	double parametr = sqrt(lamda * screenDistance) / width;
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			double difrParam = (PI * width / lamda) * (abs(calibrateCenter(i))) / (10 * screenDistance);
			//double koef = 10 * (abs(calibrateCenter(i)) / 10) / width;
			double intensivityFrenel = 0;
			double intensivityFraung = 0;

			if (abs(calibrateCenter(i)) <= width * 5)
			{
				intensivityFrenel =  electrofield * sin(difrParam) * sin(difrParam);;
				intensivityFraung =  electrofield * sinc(difrParam) * sinc(difrParam);
			}
			double sumIntensivity = intensivityFraung * (parametr - 0.6) * 10 + intensivityFrenel * (0.7 - parametr) * 10;
			if (sumIntensivity > 255)
			{
				sumIntensivity = 255;
			}
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				//std::cout << sumIntensivity << std::endl;
				image.setPixel(i, j, sf::Color(sumIntensivity, 0, 0));
			}
		}
	}
};


class GapFraungof : public GapDifr
{
public:
	GapFraungof(double _lamda, double _width, double _screenDistance, double _electrofield) :GapDifr(_lamda, _width, _screenDistance, _electrofield) {};
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			double difrParam = (PI * width / lamda) * (abs(calibrateCenter(i))) / (10 * screenDistance);
			double intensivity =  electrofield * sinc(difrParam) * sinc(difrParam);
			if (intensivity > 255)
			{
				intensivity = 255;
			}
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				//std::cout << intensivity << std::endl;
				image.setPixel(i, j, sf::Color(intensivity, 0, 0));
			}
		}
	}
};

void Draw(const GapDifr& field, sf::Image& image)
{
	image.create(WINDOWSIZE, WINDOWSIZE, sf::Color::Black);
	field.CountField(image);
}