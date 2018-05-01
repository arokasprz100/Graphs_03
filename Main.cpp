/// Compile with -std=C++11 enabled

#include "Main.h"

int main()
{
	SimpleGraph graph;
	graph.GenerateConsistentRandomGraph();
	
	graph.Dijkstra(0);
	
	return 0;
}
