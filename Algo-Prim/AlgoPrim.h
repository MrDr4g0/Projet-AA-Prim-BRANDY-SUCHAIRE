#pragma once
#include <string>
#include "VertexL.h"
#include "VertexM.h"

class AlgoPrim {

	OurList<VertexL> graphL;
	OurList<VertexM> graphM;

	VertexL originL;
	VertexM originM;

public:

	AlgoPrim();

	void convertFileGraphM(std::string file);
	void convertFileGraphL(std::string file);

	OurList<VertexM> getGraphM();

};