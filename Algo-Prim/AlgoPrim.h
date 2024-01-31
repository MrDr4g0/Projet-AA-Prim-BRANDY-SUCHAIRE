#pragma once
#include <string>
#include "VertexL.h"
#include "VertexM.h"

struct edge
{
	unsigned int parent;
	unsigned int n_vertex; // neighboring vertex
	unsigned int distance; // distance between current vertex and the neighbor

	bool operator==(const edge& other) const {
		return parent == other.parent && n_vertex == other.n_vertex && distance == other.distance;
	}
};


class AlgoPrim {

	OurList<VertexL> graphL;
	OurList<VertexM> graphM;

	unsigned int originL;
	unsigned int originM;

	edge minEdge(const OurList<edge>& edgeList, const OurList<bool>& isInTree);

public:

	AlgoPrim();

	void convertFileGraphM(std::string file);
	void convertFileGraphL(std::string file);

	void executePrimForL(std::string outputFile,unsigned int start);
	void executePrimForM(std::string file = "");

	void setOriginM(unsigned int vertex);

	OurList<VertexM> getGraphM();

};