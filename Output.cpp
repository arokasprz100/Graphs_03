#include "Output.h"
#include <iostream>
#include <cstdlib>

Output::Output():
	m_fileName("") {}



void Output::SaveToFile(GraphStorage& toSave)
{
	SetName();
	OpenFile();
	m_outputFile<<toSave->GetRepresentation()<<std::endl<<std::endl;
	toSave->PrintGraph(m_outputFile);

	m_outputFile.close();
}

void Output::SetName()
{
	std::cout<<"You are going to save graph to file. \nPlease enter file name: ";
	std::cin>>m_fileName;
}

void Output::OpenFile()
{
	m_outputFile.open(m_fileName);
	if (!m_outputFile.is_open())
	{
		std::cerr<<"Could not open output file. Aborting."<<std::endl;
		exit(-1);
	}
}
