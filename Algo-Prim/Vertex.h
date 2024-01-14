#pragma once
#include "OurList.h"
struct edge
{
	unsigned int n_vertex; // neighboring vertex
	unsigned int distance; // distance between current vertex and the neighbor

};

class Vertex
{
	unsigned int val;
	OurList<edge> neighbors;

public:

	Vertex(unsigned int number);
	Vertex(unsigned int number, const OurList<edge>& initialNeighbors);

};

