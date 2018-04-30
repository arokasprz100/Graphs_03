#include "Input.h"
#include "GraphStorage.h"
#include <iostream>
#include <vector>
#include <sstream>

Input::Input():
	m_fileName ("") {}



void Input::OpenFile()
{
	do 
	{
		GetFileNameFromUser();
		m_inputFile.open(m_fileName.c_str());
		if (!CheckIfFileExists())
			std::cout<<"Wrong file name. Try again."<<std::endl;
		else break;

	} while (true);


}


std::string Input::GetFileName() const
{
	return m_fileName;
}

std::ifstream& Input::GetFile() 
{
	return m_inputFile;
}


void Input::GetFileNameFromUser()
{
	std::cout<<"Please enter a proper name of a file with a graph representation: ";
	std::cin>>m_fileName;
}


bool Input::CheckIfFileExists()
{
	if (!m_inputFile.is_open())
		return false;
	return true;
}


/// TODO: Arek: clean code 
bool Input::GetInputFromFile(GraphStorage& storage)
{
	char fileType;
	m_inputFile >> fileType;
	std::cout<<fileType<<std::endl;
	if (fileType != 'l' and fileType != 'i' and fileType != 'a')
		return false;
	std::vector<std::vector<int>> input;
	std::string lineFromFile = "";
	for (int i=0; i<2; ++i)
		getline(m_inputFile, lineFromFile);
	
	int lineNumber = 0;
	while (std::getline(m_inputFile, lineFromFile))
	{
		if (lineFromFile=="" or lineFromFile=="\n")
			break;

		input.emplace_back();

		std::stringstream stream(lineFromFile);
		while (true)
		{
			int value;
			stream>>value;
			if(!stream)
      			break;
      		input.at(lineNumber).push_back(value);

		}

		lineNumber++;
		
	}

	storage.AddGraphToStorage(input, fileType);
	m_inputFile.close();

	return true;
	
}

