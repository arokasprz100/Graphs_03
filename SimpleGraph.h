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
	SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation);


	/// This function prints graph informations to specified by argument place
	/// It can be for example file or standard output 
	void PrintGraph(std::ostream& placeToPrint) const ;


	void PrintWeightMatrix(std::ostream& placeToPrint) const;

	/// Function returning character that describes current graph representation
	/// It can be a, l or i, depending on representation.
	char GetRepresentation() const;


	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na macierz sąsiedztwa. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToAdjacencyMatrix();

	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na listę sąsiedztwa. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToAdjacencyList();


	// Funkcja generujaca graf losowy G(n, l) o zadanej liczbie wierzcholkow oraz gestosci. Jeśli drugi argument jest liczba
	// ujemna zamieniamy ja na dodatnia, jesli jest mniejszy od 1 traktujemy go jako gestosc (jaka czesc maksymalnej liczby
	// krawedzi ma sie znalezc w grafie), jesli wiekszy od 1 traktujemy go jako ilosc krawedzi.
	void GenerateRandomGraphBasedOnDensity(int verticesNumber, double density);


	unsigned FindMaxConnectedComponent();

	// Funkcja generujaca losowy graf spojny, o zadanej liczbie wierzcholkow i krawedzi podanej przez uzytkownika. Generujemy graf dopoki nie
	// wygenerujemy grafu spojnego.
	void GenerateConsistentRandomGraph(int numberOfVertices, int numberOfEdges);


	// Algorytm Dijkstry. Posiadamy dwa zbiory, kosztow i wierzcholkow nie przetworzonych. W kazdym kroku wybiera sie wierzcholek
	// nie odwiedzony o najmniejszym koszcie. Funckja przyjmuje dwa parametry: pierwszy informujacy o miejscu rozpoczecia algorytmu,
	// a drugi to wskaźnik do wektora odleglosci w ktorym bedziemy zapisywac odleglosci od zadanego wierzcholka. W zadaniu 3 (wskaznik rozny od 0)
	// nie wypisujemy zadnej informacji na ekran, jedynie zapisujemy odleglosci do wektora odelglosci.
	void Dijkstra(int vertice, std::vector <int>* distanceVector = 0);

	// Funkcja pomocnicza do znalezenia kolejnego wierzcholka o minimalnym koszcie. Wierzcholek ten nie mogl byc przetworzony.
	int FindMinimalDistance(int distances[], bool sptSet[]);


	// Funkcja tworzaca macierz odleglosci pomiedzy wszystkimi parami wierzcholkow na tym grafie. Wykorzystuje algorytm Dijkstry dla kazdego
	// wierzcholka i wypisuje macierz odleglosci na ekran.
	void CreateDistanceMatrix();


	void FindGraphCenter();


	void FindGraphMinimaxCenter();


private:

	// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Odczutej kolejno numer sasiada i zgodnie z jego numerem zapisuje go w macierzy na odowiedniej pozycji.
	void ChangeAdjacencyListToAdjacencyMatrix();

	// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Przepisuje kolejno numery sasiadujacych wiercholkow. Usuwa na koncu pola w macierzy zawierajace wartosc 0.
	void ChangeAdjacencyMatrixToAdjacencyList();


	/// Vector of vectors containing stored graph reperesentation
	std::vector< std::vector <int> > m_storedRepresentation;

	/// Macierz zawierajaca wagi krawedzi
	std::vector< std::vector <int> > m_weightMatrix;

	/// Macierz zawierajaca odleglosci pomiedzy kazda para wierzcholkow
	std::vector< std::vector <int> > m_distanceMatrix;

	/// Field representing type of stored graph representation
	/// It should be equal to one of following characters:
	/// - a - adjacency matrix
	/// - l - adjacency list
	char m_representation;


};


#endif
