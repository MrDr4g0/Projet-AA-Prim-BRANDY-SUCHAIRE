#pragma once
#include <string>
#include "VertexL.h"
#include "VertexM.h"

struct treeM {
	unsigned int vertexParent;
	unsigned int vertex;
	unsigned int distance;
};

struct edgeM
{
	unsigned int n_vertex; // neighboring vertex
	unsigned int distance; // distance between current vertex and the neighbor

};


class AlgoPrim {

	OurList<VertexL> graphL;
	OurList<VertexM> graphM;

	VertexL originL;
	unsigned int originM;

public:

	AlgoPrim();

	void convertFileGraphM(std::string file);
	void convertFileGraphL(std::string file);

	void executePrimForM(std::string file = "");

	OurList<VertexM> getGraphM();

};