/// Compile with -std=C++11 enabled

#include "Main.h"

int main()
{
	int numberOfVertices, numberOfEdges;
	std::cout<<"Enter number of vertices: ";
	std::cin>>numberOfVertices;
	std::cout<<"Enter number of edges: ";
	std::cin>>numberOfEdges;
	while(numberOfEdges < numberOfVertices-1)
	{
		std::cout<<"If you want to have consistent graph, enter larger number of edges: ";
		std::cin>>numberOfEdges;
	}

	SimpleGraph graph;
	graph.GenerateConsistentRandomGraph(numberOfVertices, numberOfEdges);
	

	return 0;
}
