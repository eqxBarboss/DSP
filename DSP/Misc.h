#pragma once

#include <string>

namespace DSP
{

constexpr float PI = 3.14159265358979323846;

#pragma pack(push, 1)
struct TMB1
{
	char signature[4];
	unsigned long channelCount;
	unsigned long samplePerChannel;
	unsigned long spectrumLineCount;
	unsigned long cutoffFrequency;
	float frequencyResolution;
	float timeForBlock;
	unsigned long totalTime;
	unsigned long blockCountUser;
	unsigned long dataSize; // In floats
	unsigned long blockCountSystem;
	float maxValue;
	float minValue;
	float *buffer;

	~TMB1()
	{
		free(buffer);
	}
};
#pragma pack(pop)

void SaveSignal(std::string fileName, const TMB1& signal);

float GetXskzA(const TMB1& signal);
float GetXskzB(const TMB1& signal);
float GetAFourier1(const TMB1& signal, float phi);

}