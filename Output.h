#ifndef Output_h
#define Output_h

#include "GraphStorage.h"
#include <fstream>
#include <string>

class Output 
{
public:
	/// Basic constructor of Output object
	Output();

	/// Function that saves current graph representation to file
	/// It lets user choose file name
	void SaveToFile(GraphStorage& toSave);


private:
	/// Function that asks user for a output file name
	void SetName();

	/// Function that creates and opens output file, where graph will be saves
	void OpenFile();

	/// Field storing name of output file
	std::string m_fileName;

	/// Field for storing output file data
	std::ofstream m_outputFile;
};

#endif