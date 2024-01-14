#include "pch.h"
#include "VertexL.h"

VertexL::VertexL(unsigned int number) : v_number(number), neighbors(0)
{
}

VertexL::VertexL(unsigned int number, const OurList<edge>& initialNeighbors) : v_number(number),neighbors(initialNeighbors)
{
}
