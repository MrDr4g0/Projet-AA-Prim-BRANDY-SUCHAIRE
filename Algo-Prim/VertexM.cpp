#include "pch.h"
#include "VertexM.h"

VertexM::VertexM() : v_number(0),neighbors_distance(1)
{
}

VertexM::VertexM(unsigned int number) : v_number(number), neighbors_distance(1)
{
}

VertexM::VertexM(unsigned int number, const OurList<unsigned int>& n_distance) : v_number(number), neighbors_distance(n_distance)
{
}

std::ostream& operator<<(std::ostream& os, const VertexM& v)
{
	unsigned int bob = 4;
	v.neighbors_distance[bob];
	os << "number : " << v.v_number << " { ";
	for (size_t i = 0; i < v.neighbors_distance.getSize(); ++i) {

		os << v.neighbors_distance[i] << " ";

	}
	std::cout << " }";
	return os;
}
