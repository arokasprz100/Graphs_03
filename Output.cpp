#include "Output.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

void SaveToFile(SimpleGraph& toSave)
{
	std::string m_fileName;
	std::ofstream m_outputFile;
	std::cout<<"You are going to save graph to file. \nPlease enter file name: ";
	std::cin>>m_fileName;
	m_outputFile.open(m_fileName);
	m_outputFile<<"w"<<std::endl<<std::endl;
	toSave.PrintWeightMatrix(m_outputFile);

	m_outputFile.close();
}

