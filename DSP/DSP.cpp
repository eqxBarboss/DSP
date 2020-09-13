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

	// 1.a
	{
		const float A = 7;
		const float f = 5;
		const float phi[] = { PI, 0, PI / 3, PI / 6, PI / 2 };

		for (const auto value : phi)
		{
			std::unique_ptr<TMB1> signal = Generator::GenerateHarmonicSignal(2048, A, value, f);
			std::stringstream fileNameStream;
			fileNameStream << std::fixed << std::setprecision(3) << "1.a A=" << A << " phi=" << value << " f=" << f;
			SaveSignal(fileNameStream.str(), *signal);
		}
	}

	// 1.b
	{
		const float A = 5;
		const float phi = 3 * PI / 4;
		const float f[] = { 1, 5, 11, 6, 3 };

		for (const auto value : f)
		{
			std::unique_ptr<TMB1> signal = Generator::GenerateHarmonicSignal(2048, A, phi, value);
			std::stringstream fileNameStream;
			fileNameStream << std::fixed << std::setprecision(3) << "1.b A=" << A << " phi=" << phi << " f=" << value;
			SaveSignal(fileNameStream.str(), *signal);
		}
	}

	// 1.c
	{
		const float f = 3;
		const float phi = 3 * PI / 4;
		const float A[] = { 4, 5, 3, 1, 7 };

		for (const auto value : A)
		{
			std::unique_ptr<TMB1> signal = Generator::GenerateHarmonicSignal(2048, value, phi, f);
			std::stringstream fileNameStream;
			fileNameStream << std::fixed << std::setprecision(3) << "1.c A=" << value << " phi=" << phi << " f=" << f;
			SaveSignal(fileNameStream.str(), *signal);
		}
	}

	// 2
	{
		std::vector<float> A = { 9, 9, 9, 9, 9 };
		std::vector<float> f = { 1, 2, 3, 4, 5 };
		std::vector<float> phi = { PI / 2, 0, PI / 4, PI / 3, PI / 6 };

		std::unique_ptr<TMB1> signal = Generator::GeneratePolyHarmonicSignal(5, 2048, A, phi, f);
		SaveSignal("2", *signal);
	}

	// 3
	{
		std::vector<float> A = { 9, 9, 9, 9, 9 };
		std::vector<float> f = { 1, 2, 3, 4, 5 };
		std::vector<float> phi = { PI / 2, 0, PI / 4, PI / 3, PI / 6 };
		std::vector<float> deltaA = { 10, 5, 3, 6, 7 };
		std::vector<float> deltaF = { 19, 19, 19, 19, 19 };
		std::vector<float> deltaPhi = { 3, 5, 10, 7, 6 };

		std::unique_ptr<TMB1> signal = Generator::GeneratePolyHarmonicSignalWithLinearInterpolation(5, 2048, A, phi, f, deltaA, deltaPhi, deltaF);
		SaveSignal("3", *signal);
	}
}