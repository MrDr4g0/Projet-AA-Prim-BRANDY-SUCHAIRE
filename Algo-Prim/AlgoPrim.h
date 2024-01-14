#pragma once
#include <string>
#include "VertexL.h"
#include "VertexM.h"

class AlgoPrim {

	OurList<VertexL> graphL;
	OurList<VertexM> graphM;

public:

	void convertFileGraphM(std::string file);
	void convertFileGraphL(std::string file);

};