#pragma once
#include "OurList.h"

class VertexL;

struct edgeL
{
	unsigned int v_cost; // dist
	unsigned int v_value; //  neigh
};

class VertexL
{
	unsigned int v_number;
	OurList<edgeL> v_neighbors; // adjacence list

public:
	VertexL();
	VertexL(unsigned int number);
	VertexL(unsigned int number, const OurList<edgeL>& initialNeighbors);
	void AddNeighbor(unsigned int value, unsigned int cost);
	OurList<edgeL> getNeighbors();
	friend std::ostream& operator<<(std::ostream& out, const VertexL& obj);
	VertexL& operator=(const VertexL& other);
	unsigned int getValue();
	int getCost(int value);
};
