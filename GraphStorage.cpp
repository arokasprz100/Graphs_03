#include "GraphStorage.h"

GraphStorage::GraphStorage():
	m_storedGraph(nullptr) {}


void GraphStorage::AddGraphToStorage(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation)
{
	m_storedGraph = new SimpleGraph(inputFromFile, typeOfRepresentation);
}


SimpleGraph* GraphStorage::operator-> ()
{
	return m_storedGraph;
}

GraphStorage::~GraphStorage()
{
	if (m_storedGraph!=nullptr)
		delete m_storedGraph;
}


