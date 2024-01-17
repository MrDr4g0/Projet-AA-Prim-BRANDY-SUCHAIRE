#pragma once
#include "OurList.h"
#include <iostream>

class VertexM
{
	unsigned int v_number;
	OurList<unsigned int> neighbors_distance;

public:

	VertexM();
	VertexM(unsigned int number);
	VertexM(unsigned int number, const OurList<unsigned int>& n_distance_list);

	friend std::ostream& operator<<(std::ostream& os, const VertexM& v);

};

