#include "Generator.h"

#include <cmath>

namespace DSP
{

std::unique_ptr<TMB1> Generator::GenerateHarmonicSignal(int N, float A, float phi, float f)
{
	auto signal = std::make_unique<TMB1>();
	AllocateBufferAndInitSignalData(*signal, N);

	const float multiplier = 2 * PI * f / N;

	for (int i = 0; i < signal->dataSize; i++)
	{
		signal->buffer[i] = A * std::sin(multiplier * i + phi);
	}

	SetMinAndMax(*signal);

	return signal;
}

std::unique_ptr<TMB1> Generator::GeneratePolyHarmonicSignal(int k, int N, std::vector<float> A, std::vector<float> phi, std::vector<float> f)
{
	auto signal = std::make_unique<TMB1>();
	AllocateBufferAndInitSignalData(*signal, N);

	for (int i = 0; i < k; i++)
	{
		std::unique_ptr<TMB1> harmonic = GenerateHarmonicSignal(N, A[i], phi[i], f[i]);
		for (int j = 0; j < harmonic->dataSize; j++)
		{
			signal->buffer[j] += harmonic->buffer[j];
		}
	}

	SetMinAndMax(*signal);
	return signal;
}

}