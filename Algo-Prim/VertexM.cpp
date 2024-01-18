#include "pch.h"
#include "VertexM.h"

VertexM::VertexM()
{
}

VertexM::VertexM(unsigned int number) : v_number(0)
{
}

VertexM::VertexM(unsigned int number, const OurList<unsigned int>& n_distance) : v_number(number), neighbors_distance(n_distance)
{
}
