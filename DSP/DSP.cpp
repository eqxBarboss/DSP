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
	//
	Generator::AllocateBufferAndInitSignalData(*signal, 4);
	signal->buffer[0] = 4;
	signal->buffer[1] = 3;
	signal->buffer[2] = 1;
	signal->buffer[3] = 6;
	//

	Generator::SetMinAndMax(*signal);
	std::stringstream fileNameStream;
	fileNameStream << std::fixed << std::setprecision(3) << "Signal 1";
	SaveSignal(fileNameStream.str(), *signal);

	auto signal1 = new TMB1();
	CopySignal(*signal, signal1);

	for (int i = 0; i < signal->dataSize; i++)
	{
		for (int j = 50; j <= 70; j++)
		{
			signal1->buffer[i] = -signal1->buffer[i];
		}
	}

	//
	Generator::AllocateBufferAndInitSignalData(*signal1, 3);
	signal1->buffer[0] = 5;
	signal1->buffer[1] = 2;
	signal1->buffer[2] = 3;
	//

	Generator::SetMinAndMax(*signal1);
	std::stringstream fileNameStream1;
	fileNameStream1 << std::fixed << std::setprecision(3) << "Signal 2";
	SaveSignal(fileNameStream1.str(), *signal1);

	auto r = new TMB1();
	int signalSize = signal->dataSize + signal1->dataSize - 1;
	Generator::AllocateBufferAndInitSignalData(*r, signalSize);

	for (int i = 0; i < signalSize; i++)
	{
		for (int k = 0; k <= i; k++)
		{
			float val = signal->buffer[(k + i) % signal->dataSize];
			if (k < signal1->dataSize) val *= signal1->buffer[k];
			else val = 0;
			r->buffer[i] += val;
		}
	}

	Generator::SetMinAndMax(*r);
	std::stringstream fileNameStreamR;
	fileNameStreamR << std::fixed << std::setprecision(3) << "R";
	SaveSignal(fileNameStreamR.str(), *r);
}