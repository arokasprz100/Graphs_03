#include "Main.h"

int main()
{
	std::cout<<"In this program, You can do the following things:"<<std::endl;
	std::cout<<" 1. Generate random connected graph with weights assigned to its edges."<<std::endl;
	std::cout<<" 2. Use Dijkstra's Shortest Path Algorithm on graph like this."<<std::endl;
	std::cout<<" 3. Get distance matrix."<<std::endl;
	std::cout<<" 4. Get graph center and minimaxx graph center."<<std::endl;
	std::cout<<" 5. Get MST."<<std::endl<<std::endl;

	std::cout<<"You will now generate random connected graph."<<std::endl;
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
	std::cout<<"Your generated graph:"<<std::endl;
	graph.PrintGraph(std::cout);
	std::cout<<std::endl<<std::endl;
	std::cout<<"With weights:"<<std::endl;
	graph.PrintWeightMatrix(std::cout);
	std::cout<<std::endl<<std::endl;

	while (true)
	{
		std::cout<<"Dijkstra's SPA - choose vertex (type q to stop):"<<std::endl;
		int vertex;
		std::cin>>vertex;
		if(!std::cin)
		{
    		std::cin.clear();
    		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    		break;
    	}
    	graph.Dijkstra(vertex);
	}
	std::cout<<std::endl<<std::endl;

	graph.CreateDistanceMatrix();
	std::cout<<std::endl<<std::endl;

	std::cout<<"Graph center: "<<std::endl;
	graph.FindGraphCenter();
	std::cout<<std::endl<<std::endl;

	std::cout<<"Graph minimax center: "<<std::endl;
	graph.FindGraphMinimaxCenter();
	std::cout<<std::endl<<std::endl;

	std::cout<<"Prim algorithm: "<<std::endl;
	graph.Prim();
	std::cout<<std::endl<<std::endl;

	SaveToFile(graph);
	
	return 0;
}
