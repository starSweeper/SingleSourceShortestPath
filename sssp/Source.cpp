/*
Single Source Shortest Path program

Based of Bellman-Ford, Initialize-Single-Source, and Relax pseudo code in text book.

ASSUMPTION: That since the assignment tells us to use Dijkstra's, but we actually have a choice, 
the assignment description needs to be updated, and using a minimum spanning tree is not required.
*/

#include<iostream>
#include<fstream>
#include<string>
#include"Vertex.h"

using namespace std;

const int TOINFINITYANDBEYOND = 9999; //I tried using std::numeric_limits<int>::max(), but when you add anything to that if becomes a negative number and messes up the whole thing.

int processFile(string, int[][50], Vertex[]); //Opens the file, gets graph information and closes the file
bool bellmanFord(int[][50], Vertex&,  Vertex[], int);
void initializeSingleSource(int[][50], Vertex&, Vertex[], int);
void relax(Vertex&, Vertex&, int);
void printResults(Vertex, Vertex, Vertex[], int);
void getPath(Vertex, Vertex);

int main(int argc, char *argv[]) {
	int graph[50][50];
	int vertexCount = 0;
	Vertex vertexList[50];
	Vertex source, destination;
	source.setVertexCharacter(*argv[2]);
	destination.setVertexCharacter(*argv[3]);

	vertexCount = processFile(argv[1], graph, vertexList);
	bool results = bellmanFord(graph, source, vertexList, vertexCount);
	printResults(source, destination, vertexList, vertexCount);

	int i = 0;
}

int processFile(string filePath, int graph[][50], Vertex vertexList[]) {
	ifstream inputFile;
	int vertexCount = 1;
	char temp;

	inputFile.open(filePath);

	inputFile >> temp; //Read in the a
	vertexList[0].setVertexCharacter(temp);
	inputFile >> temp;
	while (temp != 'a') {
		vertexList[vertexCount].setVertexCharacter(temp);
		vertexCount++;
		inputFile >> temp;
	}

	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			inputFile >> graph[i][j];
		}
		inputFile >> temp;
	}

	inputFile.close();

	return vertexCount;
}

bool bellmanFord(int graph[][50], Vertex &source, Vertex vertexList[], int size) {
	//INITIALIZE-SINGLE-SOURCE(G,S)
	initializeSingleSource(graph, source, vertexList, size);
	
	//for i = 1 to |G.V| - 1
	for (int i = 1; i < size - 1; i++) {
		//for each edge(u,v) that is an element in the graph
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				if (graph[j][k] != -1) {
					//RELAX(u,v,w)
					relax(vertexList[j], vertexList[k], graph[j][k]);
				}
			}
		}
	}
	
	//For each edge (u,v) that is an element in the graph
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (graph[i][j] != -1) {
				//if v.d > u.d + w(u,v)
				if (vertexList[j].getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() > (vertexList[i].getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() + graph[i][j])) {
					//return FALSE
					return false;
				}
			}
		}
	} 

	//Return TRUE
	return true;
}

void initializeSingleSource(int graph[][50], Vertex &source, Vertex vertexList[], int size) {
	Vertex *pointerToNull = NULL;
	
	//For each vertex v that is an element in the graph
	for (int i = 0; i < size; i++) {
		if (vertexList[i].getVertexCharacter() == source.getVertexCharacter()) {
			vertexList[i].setUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov(0);
			vertexList[i].bakePie(pointerToNull);
			//vertexList[i].path.sortedAdd(vertexList[i].getVertexCharacter());
			source = vertexList[i];
		}
		else {
			//v.d = infinity
			vertexList[i].setUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov(TOINFINITYANDBEYOND);
			//v.pi = NIL
			vertexList[i].bakePie(pointerToNull);
			//vertexList[i].path.sortedAdd(vertexList[i].getVertexCharacter());
			//vertexList[i].path.sortedAdd(source.getVertexCharacter());
		}
		
	}
		
	//s.d = 0;
	//source.setUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov(0);
}

void relax(Vertex &edgeVertex1, Vertex &edgeVertex2, int weight) {
	//if v.d > u.d + w(u,v)
	if (edgeVertex2.getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() > (edgeVertex1.getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() + weight)) {
		//v.d = u.d + w(u,v)
		edgeVertex2.setUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov((edgeVertex1.getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() + weight));
		//v.pi = u
		edgeVertex2.bakePie(&edgeVertex1);
	//	edgeVertex2.path.sortedAdd(edgeVertex1.getVertexCharacter());
	//	edgeVertex1.path.sortedAdd(edgeVertex2.getVertexCharacter());
	}
}

void printResults(Vertex source, Vertex destinationVertex, Vertex vertexList[], int size) {

		for (int i = 0; i < size; i++) {
			if (vertexList[i].getVertexCharacter() == destinationVertex.getVertexCharacter()) {
				destinationVertex = vertexList[i];
			}
		}

		char shortestPathBetweenSourceAndDestination[50];
		int pathLength = destinationVertex.path.getAllElements(shortestPathBetweenSourceAndDestination);

		cout << "From " << source.getVertexCharacter() << " to " << destinationVertex.getVertexCharacter() << ": ";
		cout << destinationVertex.getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() << endl;

		getPath(destinationVertex, source);
}

void getPath(Vertex pathNode, Vertex source) {
	Vertex nextNode = pathNode;

	do {
		//pathNode.path.sortedAdd(nextNode.getVertexCharacter());
		pathNode.path.addToHead(nextNode.getVertexCharacter());
		nextNode = *nextNode.eatPie();

	} while (nextNode.eatPie() != source.eatPie());
	//pathNode.path.sortedAdd(nextNode.getVertexCharacter());
	pathNode.path.addToHead(nextNode.getVertexCharacter());

	char allNodes[50];
	int numOfNodes = pathNode.path.getAllElements(allNodes);

	cout << "Shortest path: (";
	for (int i = numOfNodes - 1; i > 0; i--) {
		cout << pathNode.path.getElement(i) << " -> ";
	}
	cout << pathNode.path.getElement(0) << ")" << endl;
}