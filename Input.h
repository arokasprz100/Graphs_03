#ifndef Input_h
#define Input_h

#include <fstream> // file handling
#include <string> // string handling

class GraphStorage;

class Input 
{
public:
	/// Basic constructor 
	/// It sets name of file to empty string
	Input();

	/// This function gets file name from user and checks if file exists
	/// If file does not exists (opened file is empty), then it asks user to try again
	void OpenFile();

	/// Parser that gets input from file and saves it 
	/// If file has a proper format it returns true
	/// Otherwise it returns false
	bool GetInputFromFile(GraphStorage& storage);

	/// Getter that return input file name stored in object that is an instance of this class
	std::string GetFileName() const;

	/// Getter that returns stored file 
	std::ifstream& GetFile();

private:
	/// Function that asks user to enter name of file that stores graph representation
	/// It saves the name in class field m_fileName
	void GetFileNameFromUser();

	/// Function that checks if file with name provided by user exists
	/// It returns true if it does, and false if it does not 
	bool CheckIfFileExists();

	/// This field operates on given input file
	std::ifstream m_inputFile;

	/// This filed stores 
	std::string m_fileName;

};

#endif