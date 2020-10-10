#include "Misc.h"

#include <fstream>
#include <iostream>
#include <math.h>

namespace DSP
{

void SaveSignal(std::string fileName, const TMB1 &signal)
{
	std::ofstream file("output\\" + fileName + ".bin", std::ios::out | std::ios::binary);
	file.write((char*)&signal, sizeof(TMB1) - sizeof(float*));
	file.write((char*)signal.buffer, signal.dataSize * sizeof(float));
	file.flush();
	file.close();
}

float GetXskzA(const TMB1& signal)
{
	const int M = signal.dataSize;
	const float divider = (float)(1) / (float)(M + 1);
	float sum = 0;
	
	for (int i = 0; i < M; i++)
	{
		sum += signal.buffer[i] * signal.buffer[i];
	}

	return sqrt(divider * sum);
}

float GetXskzB(const TMB1& signal)
{
	const int M = signal.dataSize;
	const float divider = (float)(1) / (float)(M + 1);
	float sum = 0;
	float sum2 = 0;

	for (int i = 0; i < M; i++)
	{
		sum += signal.buffer[i];
		sum2 += signal.buffer[i] * signal.buffer[i];
	}

	return sqrt(divider * sum2 - (divider * sum) * (divider * sum));
}

float GetAFourier1(const TMB1& signal, float phi)
{
	constexpr float PI = 3.14159265358979323846;

	const int M = signal.dataSize;
	const float f = (float)1 / (float)M;
	const float aFourierMultiplyer = (float)2 / (float)M;
	float sumA = 0;
	float sumB = 0;

	for (int i = 0; i < M; i++)
	{
		sumA += signal.buffer[i] * std::cos(2 * PI * f * i);
		sumA += signal.buffer[i] * std::sin(2 * PI * f * i);
	}

	float a1 = sumA * aFourierMultiplyer;
	float b1 = sumB * aFourierMultiplyer;

	return sqrt(a1 * a1 + b1 * b1);
}

}