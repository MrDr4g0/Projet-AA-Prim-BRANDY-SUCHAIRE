#include "pch.h"
#include "VertexL.h"

VertexL::VertexL() : v_number(0), v_neighbors()
{
}

VertexL::VertexL(unsigned int number) : v_number(number), v_neighbors()
{
}

VertexL::VertexL(unsigned int number, const OurList<edge>& initialNeighbors) : v_number(number), v_neighbors(initialNeighbors)
{
}

void VertexL::AddNeighbor(unsigned int value, unsigned int cost)
{
	edge newNeighbor{ cost, value };
	v_neighbors.insert_back(newNeighbor);
}

OurList<edge> VertexL::getNeighbors()
{
	return v_neighbors;
}

VertexL& VertexL::operator=(const VertexL& other)
{
	if (this != &other) {
		this->v_number = other.v_number;
		this->v_neighbors = other.v_neighbors;
	}
	return *this;
}

unsigned int VertexL::getValue()
{
	return v_number;
}

int VertexL::getCost(int value)
{
	return this->getNeighbors()[0].v_cost;
}

std::ostream& operator<<(std::ostream& out, const VertexL& obj)
{
	out << obj.v_number << std::endl;
	for (size_t i = 0; i < obj.v_neighbors.getSize(); i++) {
		out << "Valeur : " << obj.v_neighbors[i].v_value << std::endl;
		out << "Cout : " << obj.v_neighbors[i].v_cost << std::endl;
	}
	return out;
}
