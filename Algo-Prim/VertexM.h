#pragma once
#include "OurList.h"
class VertexM
{
	unsigned int v_number;
	OurList<unsigned int> neighbors_distance;

public:

	VertexM(unsigned int number, const OurList<unsigned int>& n_distance_list);

};

