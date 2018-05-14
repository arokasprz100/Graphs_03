#include "SimpleGraph.h"
#include <algorithm>
#include <stack>


SimpleGraph::SimpleGraph()
{
}


SimpleGraph::SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation)
{
	m_storedRepresentation = inputFromFile;
	m_representation = typeOfRepresentation;
}


void SimpleGraph::PrintGraph(std::ostream& placeToPrint) const 
{
	for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
	{
		for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			placeToPrint<<m_storedRepresentation.at(i).at(j)<<" ";
		placeToPrint<<std::endl;
	}
}


void SimpleGraph::PrintWeightMatrix(std::ostream& placeToPrint) const 
{
	for (unsigned i = 0; i < m_weightMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_weightMatrix.at(i).size(); ++j)
			placeToPrint<<m_weightMatrix.at(i).at(j)<<" ";
		placeToPrint<<std::endl;
	}
}


char SimpleGraph::GetRepresentation() const
{
	return m_representation;
}


	
void SimpleGraph::ChangeAdjacencyListToAdjacencyMatrix()
{
	std::vector<std::vector<int>> adjacencyMatrix(m_storedRepresentation.size(), std::vector<int>(m_storedRepresentation.size(), 0));
	if(m_representation == 'l')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j] != 0)
				{
					adjacencyMatrix[i][m_storedRepresentation[i][j]-1] = 1;
				}
			}		
		}			
	}
	m_storedRepresentation=adjacencyMatrix;
	m_representation='a';
}

void SimpleGraph::ChangeAdjacencyMatrixToAdjacencyList()
{
	std::vector<std::vector<int>> adjacencyList(m_storedRepresentation.size(), std::vector<int>(m_storedRepresentation.size(), 0));
	int counter;
	if(m_representation == 'a'){
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			counter = 0;
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j] != 0)
				{
					adjacencyList[i][counter] = j+1;
					counter++;
				}
			}
		}
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			 for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(adjacencyList[i][j] == 0)
				{
					adjacencyList.at(i).erase(adjacencyList.at(i).begin()+j, adjacencyList.at(i).end());
					break;
				}
			}
		}
	}
	m_storedRepresentation=adjacencyList;
	m_representation='l';
}


int SimpleGraph::EdgesCounter() const
{
	int edges=0;
	if(m_representation=='l')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
			edges+=m_storedRepresentation.at(i).size();
		edges/=2;
	}
	if(m_representation=='a')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = i+1; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j]==1)
					edges++;
			}
		}
	}
	if(m_representation=='i')
		edges=m_storedRepresentation.at(0).size();
	return edges;
}


void SimpleGraph::ChangeToAdjacencyMatrix()
{
	if(m_representation=='l')
		ChangeAdjacencyListToAdjacencyMatrix();
	else if(m_representation=='a')
		std::cout<<"Graph is already represented by an adjacency matrix."<<std::endl;
}
	
void SimpleGraph::ChangeToAdjacencyList()
{
	if(m_representation=='l')
		std::cout<<"Graph is already represented by an adjacency list."<<std::endl;
	else if(m_representation=='a')
		ChangeAdjacencyMatrixToAdjacencyList();
}



void SimpleGraph::GenerateRandomGraphBasedOnProbability(int verticesNumber, int probability)
{
	srand (time(NULL));
	int randomNumber;
	bool randomize = true; 
	std::vector<std::vector<int>> adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
	std::vector<std::vector<int>> weightMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));

	if(!probability)
		randomize = false;

	if(randomize)
	{
		for (int i = 0; i < verticesNumber; ++i)
		{
			for (int j = i; j < verticesNumber; ++j)
			{
				randomNumber = rand() % 100 + 1;
				if((randomNumber <= probability) && (i != j))
				{
					int weight = rand() % 10 + 1;
					adjacencyMatrix[i][j] = 1;
					adjacencyMatrix[j][i] = 1;
					weightMatrix[i][j] = weight;
					weightMatrix[j][i] = weight;
				}
			}
		}
	}
	
	m_storedRepresentation=adjacencyMatrix;
	m_weightMatrix=weightMatrix;
	m_representation='a';
}


void SimpleGraph::GenerateRandomGraphBasedOnDensity(int verticesNumber, double density)
{
	srand (time(NULL));
	std::vector<std::vector<int>> adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
	std::vector<std::vector<int>> weightMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));

	int maxEdges = verticesNumber*(verticesNumber-1)/2;
	if(density<0)
		density = -density;
	if (density<1)
	{
		for(int i=0; i<verticesNumber; i++)
		{
			for(int j=i+1; j<verticesNumber; j++)
			{
				double probability=(double)(std::rand()%(maxEdges+1))/(double)maxEdges;
				if(density>=probability)
				{
					int weight = rand() % 10 + 1;
					adjacencyMatrix[i][j] = 1;
					adjacencyMatrix[j][i] = 1;
					weightMatrix[i][j] = weight;
					weightMatrix[j][i] = weight;
				}
			}
		}
	}
	else
	{
		int edgesNumber=density;
		if (edgesNumber>maxEdges) 
			edgesNumber=maxEdges;
		while(edgesNumber>0)
		{
			for(int i=0; i<verticesNumber; i++)
			{
				for(int j=i+1; j<verticesNumber; j++)
				{
					double probability=(double)(std::rand()%(maxEdges+1))/(double)maxEdges;
					double rest=((double)maxEdges-edgesNumber)/(double)maxEdges;
					if(probability>=rest && adjacencyMatrix[i][j] == 0 && edgesNumber>0)
					{
						int weight = rand() % 10 + 1;
						adjacencyMatrix[i][j] = 1;
						adjacencyMatrix[j][i] = 1;
						weightMatrix[i][j] = weight;
						weightMatrix[j][i] = weight;
						edgesNumber--;
					}
				}
			}
		}
	}

	m_storedRepresentation=adjacencyMatrix;
	m_weightMatrix=weightMatrix;
	m_representation='a';
}


void SimpleGraph::RandomizeSimpleGraph()
{
	srand (time(NULL));
	int rand_a, rand_b, rand_c, rand_d;
	int temp_b, temp_d;
	int many_times = 1000;
	bool randomize;

	if(m_representation != 'l')
		ChangeToAdjacencyList();

	for(int i = 0; i < many_times; i++)
	{
		randomize = false;
		rand_a = rand() % m_storedRepresentation.size();        
		rand_c = rand() % m_storedRepresentation.size();
		
		
		if (m_storedRepresentation.at(rand_a).size() == 0 || m_storedRepresentation.at(rand_c).size() == 0)
			continue;
		
		rand_b = rand() % m_storedRepresentation.at(rand_a).size();
		rand_d = rand() % m_storedRepresentation.at(rand_c).size();
		temp_b = rand_b;
		temp_d = rand_d;
		rand_b = m_storedRepresentation[rand_a][rand_b];
		rand_d = m_storedRepresentation[rand_c][rand_d];
		rand_a += 1;
		rand_c += 1;


		if( (rand_a != rand_d) && (rand_b != rand_c) ) randomize = true;

		for(unsigned j = 0; j < m_storedRepresentation.at(rand_a-1).size(); j++)
		{
			if(m_storedRepresentation[rand_a-1][j] == rand_d) randomize = false;
		}

		for(unsigned j = 0; j < m_storedRepresentation.at(rand_b-1).size(); j++)
		{
			if(m_storedRepresentation[rand_b-1][j] == rand_c) randomize = false;
		}


		if(randomize)
		{
		 	m_storedRepresentation.at(rand_a-1).push_back(rand_d);
		 	m_storedRepresentation.at(rand_d-1).push_back(rand_a);
		 	m_storedRepresentation.at(rand_b-1).push_back(rand_c);
		 	m_storedRepresentation.at(rand_c-1).push_back(rand_b);
		
		 	m_storedRepresentation.at(rand_a-1).erase(m_storedRepresentation.at(rand_a-1).begin()+temp_b);
		 	m_storedRepresentation.at(rand_c-1).erase(m_storedRepresentation.at(rand_c-1).begin()+temp_d);
		 
		 	for(unsigned j = 0; j < m_storedRepresentation.at(rand_b-1).size(); j++)
		 	{
		 	 	if(m_storedRepresentation[rand_b-1][j] == rand_a)
		 	 		m_storedRepresentation.at(rand_b-1).erase(m_storedRepresentation.at(rand_b-1).begin()+j);
		 	}
		 	
		 	for(unsigned j = 0; j < m_storedRepresentation.at(rand_d-1).size(); j++)
		 	{
		 		if(m_storedRepresentation[rand_d-1][j] == rand_c)
		 			m_storedRepresentation.at(rand_d-1).erase(m_storedRepresentation.at(rand_d-1).begin()+j);
		 	}
		 	
			for(unsigned j = 0; j < m_storedRepresentation.size(); ++j)
			{
				std::sort(m_storedRepresentation.at(j).begin(), m_storedRepresentation.at(j).end(), [](const int a, const int b) {return a > b; });
			}


			m_weightMatrix[rand_a-1][rand_d-1]=m_weightMatrix[rand_a-1][rand_b-1];
			m_weightMatrix[rand_d-1][rand_a-1]=m_weightMatrix[rand_a-1][rand_b-1];
			m_weightMatrix[rand_c-1][rand_b-1]=m_weightMatrix[rand_c-1][rand_d-1];
			m_weightMatrix[rand_b-1][rand_c-1]=m_weightMatrix[rand_c-1][rand_d-1];
			m_weightMatrix[rand_a-1][rand_b-1]=0;
			m_weightMatrix[rand_b-1][rand_a-1]=0;
			m_weightMatrix[rand_c-1][rand_d-1]=0;
			m_weightMatrix[rand_d-1][rand_c-1]=0;
		 }
	}
	ChangeToAdjacencyMatrix();
}


unsigned SimpleGraph::FindMaxConnectedComponent()
{
	char oldRepresentation = m_representation;
	ChangeToAdjacencyList();
	std::vector<unsigned> vertices (m_storedRepresentation.size(), 0);
	std::stack<unsigned> stackForVertices;
	unsigned currentConnectedComponent = 0;
	for (unsigned i = 0; i<vertices.size(); ++i)
	{
		if (vertices[i]>0)
			continue;

		currentConnectedComponent++;

		stackForVertices.push(i);
		vertices[i] = currentConnectedComponent;

		while (stackForVertices.empty() == false) /// DFS using stack
		{
			unsigned v = stackForVertices.top();
			stackForVertices.pop();
			for (unsigned j = 0; j<m_storedRepresentation.at(v).size(); ++j)
			{
				unsigned u = m_storedRepresentation.at(v).at(j) - 1;
				if (vertices.at(u)>0)
					continue;
				stackForVertices.push(u);
				vertices.at(u) = currentConnectedComponent;
			}
		}

	}

	if (oldRepresentation=='a')
		ChangeToAdjacencyMatrix();


	return currentConnectedComponent;
}


void SimpleGraph::GenerateConsistentRandomGraph()
{
	GenerateRandomGraphBasedOnDensity(6, 7);
	PrintGraph(std::cout);
	std::cout<<"\n\n";

	PrintWeightMatrix(std::cout);
	std::cout<<"\n\n";

	while(FindMaxConnectedComponent() != 1)
	{
		RandomizeSimpleGraph();
		std::cout<<"randomizacja"<<std::endl;
	}

	PrintGraph(std::cout);
	std::cout<<"\n\n";

	PrintWeightMatrix(std::cout);
	std::cout<<"\n\n";
}

void SimpleGraph::Dijkstra(int vertice)
{
	if(m_representation != 'a')
		ChangeToAdjacencyMatrix();

	int distances[m_storedRepresentation.size()];
	int predecessors[m_storedRepresentation.size()];
	bool visitedVertices[m_storedRepresentation.size()];

	for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
	{
		distances[i] = 999;
		predecessors[i] = -1;
		visitedVertices[i] = false;
	}

	distances[vertice] = 0;

	for (unsigned i = 0; i < m_storedRepresentation.size() - 1; ++i)
	{
		int indexToNextVertex = FindMinimalDistance(distances, visitedVertices);
		visitedVertices[indexToNextVertex] = true;

		for(unsigned j = 0; j < m_storedRepresentation.size(); ++j)
		{
			if(!visitedVertices[j] && m_weightMatrix[indexToNextVertex][j]
			&& distances[indexToNextVertex] != 999 
			&& distances[indexToNextVertex]+m_weightMatrix[indexToNextVertex][j] < distances[j])
			{
            	
            	distances[j] = distances[indexToNextVertex] + m_weightMatrix[indexToNextVertex][j];
            	predecessors[j] = indexToNextVertex;
            }
		}
	}


	std::cout<<"Predecessors Array"<<std::endl;

	for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
	{
		std::cout<< " "<< predecessors[i];
	}

	std::cout<<std::endl;

	std::cout<< "Vertex\tDistance  Path" <<std::endl;
    for (unsigned i = 0; i < m_storedRepresentation.size(); i++)
    {
    	std::cout<< i << '\t' << distances[i];
    	PrintDijkstraPath(predecessors, i);
    	std::cout<<std::endl;
    }	
}

int SimpleGraph::FindMinimalDistance(int distances[], bool visitedVertices[])
{
	int min = 999;
	int minIndex;

	for (unsigned i = 0; i < m_storedRepresentation.size() ; ++i)
	{
		if (distances[i] <= min && visitedVertices[i] == false)
		{
			minIndex = i;
			min = distances[i];
		}
	}

	return minIndex;
}

void SimpleGraph::PrintDijkstraPath(int predecessors[], int parentIndex)
{
    if (predecessors[parentIndex] == -1)
    	{
    		std::cout<<"	  "<<parentIndex<<" ";
    		return;
    	} 
 
    PrintDijkstraPath(predecessors, predecessors[parentIndex]);
    	std::cout<<parentIndex<< " ";
}
