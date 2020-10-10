#include <iostream>
#include <string> 
#include <memory>
#include <iomanip>
#include <sstream>
#include <vector>

#include "Misc.h"
#include "Generator.h"

using namespace DSP;

int main()
{
	// VARIANT 5

	// 2.1
	{
		const float A = 1;
		const float f = 1;
		const float phi = 0;
		const int N = 2048;
		const int doubleN = N * 2;
		const int K = (float)(3 * N) / (float)4;

		std::vector<float> xskzA;
		std::vector<float> xskzB;
		std::vector<float> aFourier1;

		for (int M = K; M <= doubleN; M++)
		{
			std::unique_ptr<TMB1> signal = Generator::GenerateHarmonicSignal(N, M, 1, phi, 1);
			xskzA.push_back(0.707 - GetXskzA(*signal.get()));
			xskzB.push_back(0.707 - GetXskzB(*signal.get()));
			aFourier1.push_back(1 - GetAFourier1(*signal.get(), 0));
		}

		TMB1 signalXskzA;
		TMB1 signalXskzB;
		TMB1 signalAFourier1;
		Generator::AllocateBufferAndInitSignalData(signalXskzA, xskzA.size());
		Generator::AllocateBufferAndInitSignalData(signalXskzB, xskzB.size());
		Generator::AllocateBufferAndInitSignalData(signalAFourier1, aFourier1.size());
		signalXskzA.totalTime = xskzA.size();
		signalXskzB.totalTime = xskzB.size();
		signalAFourier1.totalTime = aFourier1.size();

		for (int i = 0; i < xskzA.size(); i++) signalXskzA.buffer[i] = xskzA[i];
		for (int i = 0; i < xskzB.size(); i++) signalXskzB.buffer[i] = xskzB[i];
		for (int i = 0; i < aFourier1.size(); i++) signalAFourier1.buffer[i] = aFourier1[i];

		Generator::SetMinAndMax(signalXskzA);
		Generator::SetMinAndMax(signalXskzB);
		Generator::SetMinAndMax(signalAFourier1);

		std::stringstream fileNameStream;
		fileNameStream << std::fixed << std::setprecision(3) << "2.1 xskzA";
		SaveSignal(fileNameStream.str(), signalXskzA);

		std::stringstream fileNameStream1;
		fileNameStream1 << std::fixed << std::setprecision(3) << "2.1 xskzB";
		SaveSignal(fileNameStream1.str(), signalXskzB);

		std::stringstream fileNameStream2;
		fileNameStream2 << std::fixed << std::setprecision(3) << "2.1 signalAFourier1";
		SaveSignal(fileNameStream2.str(), signalAFourier1);
	}

	// 2.2
	{
		const float A = 1;
		const float f = 1;
		const float phi = PI / 8;
		const int N = 2048;
		const int doubleN = N * 2;
		const int K = (float)(3 * N) / (float)4;

		std::vector<float> xskzA;
		std::vector<float> xskzB;
		std::vector<float> aFourier1;

		for (int M = K; M <= doubleN; M++)
		{
			std::unique_ptr<TMB1> signal = Generator::GenerateHarmonicSignal(N, M, 1, phi, 1);
			xskzA.push_back(0.707 - GetXskzA(*signal.get()));
			xskzB.push_back(0.707 - GetXskzB(*signal.get()));
			aFourier1.push_back(1 - GetAFourier1(*signal.get(), 0));
		}

		TMB1 signalXskzA;
		TMB1 signalXskzB;
		TMB1 signalAFourier1;
		Generator::AllocateBufferAndInitSignalData(signalXskzA, xskzA.size());
		Generator::AllocateBufferAndInitSignalData(signalXskzB, xskzB.size());
		Generator::AllocateBufferAndInitSignalData(signalAFourier1, aFourier1.size());
		signalXskzA.totalTime = xskzA.size();
		signalXskzB.totalTime = xskzB.size();
		signalAFourier1.totalTime = aFourier1.size();

		for (int i = 0; i < xskzA.size(); i++) signalXskzA.buffer[i] = xskzA[i];
		for (int i = 0; i < xskzB.size(); i++) signalXskzB.buffer[i] = xskzB[i];
		for (int i = 0; i < aFourier1.size(); i++) signalAFourier1.buffer[i] = aFourier1[i];

		Generator::SetMinAndMax(signalXskzA);
		Generator::SetMinAndMax(signalXskzB);
		Generator::SetMinAndMax(signalAFourier1);

		std::stringstream fileNameStream;
		fileNameStream << std::fixed << std::setprecision(3) << "2.2 xskzA";
		SaveSignal(fileNameStream.str(), signalXskzA);

		std::stringstream fileNameStream1;
		fileNameStream1 << std::fixed << std::setprecision(3) << "2.2 xskzB";
		SaveSignal(fileNameStream1.str(), signalXskzB);

		std::stringstream fileNameStream2;
		fileNameStream2 << std::fixed << std::setprecision(3) << "2.2 signalAFourier1";
		SaveSignal(fileNameStream2.str(), signalAFourier1);
	}
}