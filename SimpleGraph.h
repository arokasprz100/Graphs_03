#ifndef SimpleGraph_h
#define SimpleGraph_h

#include <vector>
#include <iostream>
     
class SimpleGraph final  
{
public:

	SimpleGraph();


	/// Simple graph constructor. First argument represents input received from file that stores data 
	/// about graph. Second one represents type of representation - one of the following:
	/// - a - adjacency matrix
	/// - l - adjacency list
	/// - i - incidence matrix
	SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation);


	/// This function prints graph informations to specified by argument place
	/// It can be for example file or standard output 
	void PrintGraph(std::ostream& placeToPrint) const ;


	void PrintWeightMatrix(std::ostream& placeToPrint) const;


	char GetRepresentation() const;


	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na macierz sąsiedztwa. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToAdjacencyMatrix();

	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na listę sąsiedztwa. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToAdjacencyList();


	// Funkcja generujaca graf losowy G(n, p) o zadanej liczbie wierzcholkow oraz prawdopodobienstwa wystapienia kazdej z krawedzi. 
	// Drugi argument traktowany jest jako procent. Na podstawie losowanych liczb generuje się nowe polaczenia w grafie.
	void GenerateRandomGraphBasedOnProbability(int verticesNumber, int probability);

	void GenerateRandomGraphBasedOnDensity(int verticesNumber, double density);
	
	// Funkcja randomizuja ulozenie krawedzi w grafie. Zamienia krawedz a-b, c-d na a-d, b-c pozostajac przy tym grafem prostym.
	// Funkcja operuje na liscie sasiedztwa, sprawdza wpierw warunek czy zamiana nie zaburzy warunkow istnienia grafu prostego, 
	// nastepnie sprawdza czy juz odpowiednie krawedzie nie instnieja dla uprzednio wylosowanych czterech losowych krawedzi.
	// Dodaje do listy nowe krawedzie, usuwa stare powiazania i na koncu sortuje i zamienia reprezentache na macierz sasiedztwa.
	void RandomizeSimpleGraph();


	unsigned FindMaxConnectedComponent();


	void GenerateConsistentRandomGraph();
	
	// Algorytm Dijkstry. Posiadamy dwa zbiory, kosztow i wierzcholkow nie przetworzonych. W kazdym kroku wybiera sie wierzcholek
	// nie odwiedzony o najmniejszym koszcie. Funckja przyjmuje jeden parametr informujacy o miejscu rozpoczecia algorytmu. 
	void Dijkstra(int vertice);

	// Funkcja pomocnicza do znalezenia kolejnego wierzcholka o minimalnym koszcie. Wierzcholek ten nie mogl byc przetworzony.
	int FindMinimalDistance(int distances[], bool visitedVertices[]);
	
	// Funkcja pomocnicza do wypisania pelnej siezki od zrodla. Opiera sie na rekurencji.
	void PrintDijkstraPath(int predecessors[], int parentIndex);

private:

	// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Odczutej kolejno numer sasiada i zgodnie z jego numerem zapisuje go w macierzy na odowiedniej pozycji.
	void ChangeAdjacencyListToAdjacencyMatrix();

	// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Przepisuje kolejno numery sasiadujacych wiercholkow. Usuwa na koncu pola w macierzy zawierajace wartosc 0.
	void ChangeAdjacencyMatrixToAdjacencyList();


	/// This  function counts number of edges in a graph and returns it. 
	/// Works for every type of representation.
	int EdgesCounter() const;

	/// Vector of vectors containing stored graph reperesentation
	std::vector< std::vector <int> > m_storedRepresentation;

	std::vector< std::vector <int> > m_weightMatrix;

	/// Field representing type of stored graph representation
	/// It should be equal to one of following characters:
	/// - a - adjacency matrix
	/// - l - adjacency list
	/// - i - incidence matrix
	char m_representation;

};


#endif
