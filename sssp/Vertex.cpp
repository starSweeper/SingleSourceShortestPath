#include<iostream>
#include"Vertex.h"


void Vertex::setUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov(int value) {
	upperBoundOnTheWeightOfTheShortestPathFromSourcesTov = value;
}
int Vertex::getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov() {
	return upperBoundOnTheWeightOfTheShortestPathFromSourcesTov;
}
void Vertex::bakePie(Vertex* value) {
	pie = value;
}
Vertex* Vertex::eatPie() {
	return pie;
}
void Vertex::setVertexCharacter(char character) {
	vertexCharacter = character;
}
char Vertex::getVertexCharacter() {
	return vertexCharacter;
}