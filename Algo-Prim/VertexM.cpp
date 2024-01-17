#include "pch.h"
#include "VertexM.h"

VertexM::VertexM(unsigned int number) : v_number(number), neighbors_distance(0)
{
}

VertexM::VertexM(unsigned int number, const OurList<unsigned int>& n_distance) : v_number(number), neighbors_distance(n_distance)
{
}
