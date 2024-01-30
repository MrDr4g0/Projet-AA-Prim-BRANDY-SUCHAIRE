#pragma once
#include "OurList.h"

class VertexL;

struct edge
{
	unsigned int v_cost; // 
	unsigned int v_value; //  
};

class VertexL
{
	unsigned int v_number;
	OurList<edge> v_neighbors; // adjacence list

public:
	VertexL();
	VertexL(unsigned int number);
	VertexL(unsigned int number, const OurList<edge>& initialNeighbors);
	void AddNeighbor(unsigned int value, unsigned int cost);
	OurList<edge> getNeighbors();
	friend std::ostream& operator<<(std::ostream& out, const VertexL& obj);
	VertexL& operator=(const VertexL& other);
	int getValue();
	int getCost(int value);
};
