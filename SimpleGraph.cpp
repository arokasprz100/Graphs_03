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


void SimpleGraph::GenerateConsistentRandomGraph(int numberOfVertices, int numberOfEdges)
{
	GenerateRandomGraphBasedOnDensity(numberOfVertices, numberOfEdges);

	while(FindMaxConnectedComponent() != 1)
	{
		GenerateRandomGraphBasedOnDensity(numberOfVertices, numberOfEdges);
	}

	PrintGraph(std::cout);
	std::cout<<"\n\n";

	PrintWeightMatrix(std::cout);
	std::cout<<"\n\n";
}

