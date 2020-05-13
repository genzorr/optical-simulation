#pragma once

#include <SFML/Graphics.hpp>
#include "FrenelC.h"
#include "FrenelS.h"
#include "Parametrs.h"

class EdgeDifraction
{
public:
	EdgeDifraction(double _lamda, double _screenDistance, double _electrofield) : lamda(_lamda), screenDistance(_screenDistance), electrofield(_electrofield) {};
	virtual void CountField(sf::Image& image) const = 0;
	double lamda = 0;
	double screenDistance = 0;
	double electrofield = 0;
};

class EdgeDifractionFrenel : public EdgeDifraction
{
public:
	EdgeDifractionFrenel(double _lamda, double _screenDistance, double _electrofield) :EdgeDifraction(_lamda, _screenDistance, _electrofield) {};
	void CountField(sf::Image& image)const override
	{
		for (int i = 0; i < WINDOWSIZE; ++i)
		{
			for (int j = 0; j < WINDOWSIZE; ++j)
			{
				double integrParam = abs(calibrateCenter(i)) * sqrt(PI / (lamda * screenDistance));
				integrParam /= 45;
				double paramC = Fresnel_Auxiliary_Cosine_Integral(integrParam) - 0.5;
				if (calibrateCenter(i) < -1)
				{
					paramC *= -1;
				}
				double paramS = Fresnel_Auxiliary_Sine_Integral(integrParam) - 0.5;
				if (calibrateCenter(i) < -1)
				{
					paramS *= -1;
				}
				double intensivity = electrofield  * (((paramC - 0.5) * (paramC - 0.5) + (paramS - 0.5) * (paramS - 0.5)));
				if (calibrateCenter(i) > 5)
				{
					intensivity += electrofield / 5 * sin(integrParam * integrParam * 4);
					intensivity *= 1 - 1.f * calibrateCenter(i) / WINDOWSIZE;
					if (j == 500)
					{
						std::cout << intensivity << std::endl;
					}
				}
				image.setPixel(i, j, sf::Color(intensivity, 0, 0));
			}
		}
	}
};


void Draw(const EdgeDifraction& field, sf::Image& image)
{
	image.create(WINDOWSIZE, WINDOWSIZE, sf::Color::Black);
	field.CountField(image);
}