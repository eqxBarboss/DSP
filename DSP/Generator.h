#pragma once

#include <memory>
#include <vector>

#include "Misc.h"

namespace DSP
{

constexpr float PI = 3.14159265358979323846;

class Generator
{
public:
	static std::unique_ptr<TMB1> GenerateHarmonicSignal(int N, float A, float phi, float f);
	static std::unique_ptr<TMB1> GeneratePolyHarmonicSignal(int k, int N, std::vector<float> A, std::vector<float> phi, std::vector<float> f);

	static inline void AllocateBufferAndInitSignalData(TMB1& signal, int N)
	{
		signal.buffer = static_cast<float*>(malloc(sizeof(float) * N));
		memset(signal.buffer, 0, sizeof(float) * N);
		signal.dataSize = N;
		signal.totalTime = 1;
		SetSignature(signal);
	}

	static inline void SetSignature(TMB1& signal)
	{
		signal.signature[0] = 'T';
		signal.signature[1] = 'M';
		signal.signature[2] = 'B';
		signal.signature[3] = '1';
	}

	static inline void SetMinAndMax(TMB1& signal)
	{
		float min = signal.buffer[0];
		float max = signal.buffer[0];

		for (int i = 0; i < signal.dataSize; i++)
		{
			if (signal.buffer[i] < min)
			{
				min = signal.buffer[i];
			}
			if (signal.buffer[i] > max)
			{
				max = signal.buffer[i];
			}
		}

		signal.minValue = min;
		signal.maxValue = max;
	}
};

}
