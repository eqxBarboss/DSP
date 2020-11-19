#include <iostream>
#include <string> 
#include <memory>
#include <iomanip>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>

#include "Misc.h"
#include "Generator.h"

using namespace DSP;

void CopySignal(TMB1 from, TMB1* to)
{
	to->signature[0] = 'T';
	to->signature[1] = 'M';
	to->signature[2] = 'B';
	to->signature[3] = '1';
	to->buffer = static_cast<float*>(malloc(sizeof(float) * 2048));
	for (int i = 0; i < 2048; i++) to->buffer[i] = from.buffer[i];
	to->dataSize = 2048;
	to->totalTime = 1;
}

float middleOfThree(float a, float b, float c)
{
	// Checking for b 
	if ((a < b && b < c) || (c < b && b < a))
		return b;

	// Checking for a 
	else if ((b < a && a < c) || (c < a && a < b))
		return a;

	else
		return c;
}

int main()
{
	// VARIANT 5

	const float B1 = 100, B2 = 1;
	const float f = 1;
	const float phi = 0;

	std::unique_ptr<TMB1> signal = Generator::GenerateHarmonicSignal(2048, B1, phi, f);

	for (int i = 0; i < signal->dataSize; i++)
	{
		for (int j = 50; j <= 70; j++)
		{
			int multiplier = (std::rand() < (RAND_MAX / 2)) ? 1 : -1;
			signal->buffer[i] += multiplier * B2 * std::sin(2 * PI * i * j / 2048);
		}
	}

	Generator::SetMinAndMax(*signal);

	std::stringstream fileNameStream;
	fileNameStream << std::fixed << std::setprecision(3) << "Generated signal";
	SaveSignal(fileNameStream.str(), *signal);

	// Скользящее усреднение с окном 3

	auto signal1 = new TMB1();
	CopySignal(*signal, signal1);

	for (int i = 1; i < 2046; i++)
	{
		signal1->buffer[i] = middleOfThree(signal->buffer[i], signal->buffer[i - 1], signal->buffer[i + 1]);
	}

	Generator::SetMinAndMax(*signal1);

	std::stringstream fileNameStream1;
	fileNameStream1 << std::fixed << std::setprecision(3) << "Window 3";
	SaveSignal(fileNameStream1.str(), *signal1);

	// Медианная фильтрация с окном 7

	auto signal2 = new TMB1();
	CopySignal(*signal, signal2);

	for (int i = 3; i < 2044; i++)
	{
		std::vector<float> vec;
		for (int j = i - 3; j < i + 4; j++) vec.push_back(signal->buffer[j]);
		std::sort(vec.begin(), vec.end());
		float sum = 0;
		for (int j = i - 2; j < i + 3; j++) sum += signal->buffer[j];
		sum /= 5;
		signal2->buffer[i] = sum;
	}

	Generator::SetMinAndMax(*signal2);

	std::stringstream fileNameStream2;
	fileNameStream2 << std::fixed << std::setprecision(3) << "Median 7";
	SaveSignal(fileNameStream2.str(), *signal2);

	// Парабола 4 степени по 7 точкам

	auto signal3 = new TMB1();
	CopySignal(*signal, signal3);

	for (int i = 3; i < 2044; i++)
	{		
		signal3->buffer[i] = (5*signal->buffer[i -3] - 30 * signal->buffer[i - 2] + 75 * signal->buffer[i - 1] + 131 * signal->buffer[i] + 75 * signal->buffer[i + 1]
			- 30 * signal->buffer[i + 2] + 5 * signal->buffer[i + 3])/(float)231;
	}

	Generator::SetMinAndMax(*signal3);

	std::stringstream fileNameStream3;
	fileNameStream3 << std::fixed << std::setprecision(3) << "Parabola 4, 7 points";
	SaveSignal(fileNameStream3.str(), *signal3);
}