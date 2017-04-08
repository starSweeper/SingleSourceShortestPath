#pragma once
#include"SLList.h"

class Vertex {
private:
	int upperBoundOnTheWeightOfTheShortestPathFromSourcesTov;
	Vertex *pie;
	char vertexCharacter;
	

public:
	SLList path;

	void setUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov(int);
	int getUpperBoundOnTheWeightOfTheShortestPathFromSourcesTov();
	void bakePie(Vertex*); //setPie
	Vertex* eatPie(); //getPie
	void setVertexCharacter(char);
	char getVertexCharacter();
};