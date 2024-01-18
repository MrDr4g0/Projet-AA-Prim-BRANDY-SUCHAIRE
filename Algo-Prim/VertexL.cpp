#include "pch.h"
#include "VertexL.h"

VertexL::VertexL()
{
}

VertexL::~VertexL()
{
	// A MODIF
}

VertexL::VertexL(unsigned int number) : v_number(number)
{
}

VertexL::VertexL(unsigned int number, OurList<edge> neighbors) : v_number(number), v_neighbors(neighbors)
{
}

VertexL::VertexL(unsigned int number, const OurList<edge>& initialNeighbors) : v_number(number), v_neighbors(initialNeighbors)
{
}

void VertexL::AddNeighbor(unsigned int value, unsigned int cost)
{
	edge newNeighbor{cost, value};
	v_neighbors.insert_back(newNeighbor);
}

OurList<edge> VertexL::getNeighbors()
{
	return v_neighbors;
}

std::ostream& operator<<(std::ostream& out, const VertexL& obj)
{
	out << obj.v_number << std::endl;
	return out;
}
