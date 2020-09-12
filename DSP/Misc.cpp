#include "Misc.h"

#include <fstream>
#include <iostream>

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

}