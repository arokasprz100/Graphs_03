#ifndef GraphStorage_h
#define GraphStorage_h

#include "Input.h"
#include "SimpleGraph.h"

class GraphStorage
{
public:
	/// Constructor. Appart from initialising m_storedGraph with nullptr, it does nothing
	GraphStorage();

	/// Function adding graph specified by inputFromFile to storage. It uses new to allocate memory
	/// for the graph - also it calls SimpleGraph constructor.
	void AddGraphToStorage(std::vector<std::vector<int>> inputFromFile,  char typeOfRepresentation);

	/// Overloaded -> operator. It allows user to access stored graph methods directly by this class
	SimpleGraph* operator-> ();

	/// Destructor. Frees memory allocated for stored graph representation
	/// It makes memory leaks less likely to happen.
	~GraphStorage();
private:
	SimpleGraph* m_storedGraph;
};

#endif