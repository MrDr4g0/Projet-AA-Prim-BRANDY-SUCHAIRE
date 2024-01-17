#pragma once
#include "OurList.h"

struct edge
{
	unsigned int n_vertex; // neighboring vertex
	unsigned int distance; // distance between current vertex and the neighbor

};

class VertexL
{
	unsigned int v_number;
	OurList<edge> neighbors;

public:

	VertexL();
	VertexL(unsigned int number);
	VertexL(unsigned int number, const OurList<edge>& initialNeighbors);

};

