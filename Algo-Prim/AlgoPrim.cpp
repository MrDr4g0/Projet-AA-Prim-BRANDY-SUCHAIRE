// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"

#include <fstream>

edgeM AlgoPrim::minEdge(const OurList<edgeM>& edgeMList, const OurList<bool>& isInTree)
{
    unsigned int min = std::numeric_limits<unsigned int>::max();
    edgeM res;

    for (size_t i = 0; i < edgeMList.getSize(); ++i) {
        unsigned int vNum = edgeMList[i].n_vertex;
        unsigned int vDist = edgeMList[i].distance;

        if (isInTree[vNum] == false && vDist < min) {
            min = vDist;
            res = edgeMList[i];
        }
    }

    return res;
}

AlgoPrim::AlgoPrim() : graphL(0), graphM(0),originL(0),originM(0)
{
}
void AlgoPrim::convertFileGraphM(std::string file)
{
	std::ifstream inputFile(file);
    if (!inputFile.is_open()) {
        std::cerr << "convertFileGraphM Error : Can't open the file." << std::endl;
    }
    else {

        unsigned int numberVertices;
        inputFile >> numberVertices;

        OurList<VertexM> graph(numberVertices);

        for (unsigned int i = 0; i < numberVertices; ++i) {

            //Current Vertex
            unsigned int vertexNumber;
            inputFile >> vertexNumber;

            OurList<unsigned int> neighborsDistance(numberVertices, std::numeric_limits<unsigned int>::max());

            //Neighboring Vertex & distance;
            unsigned int neighbor;
            unsigned int distance;

            while (inputFile >> neighbor && neighbor != 0) {

                if (!(inputFile >> distance)) {
                    std::cerr << "Error reading distance for vertex " << vertexNumber << std::endl;
                    break;
                }
                neighborsDistance[neighbor-1] = distance;
            }

            VertexM vertex(vertexNumber, neighborsDistance);
            graph.insert_back(vertex);
        }

        graphM = graph;

        inputFile.close();
    }

}
void AlgoPrim::executePrimForM(std::string file)
{
    //(x -> p : c)
    size_t graphSize = graphM.getSize();

    OurList<treeM> finalTree(graphSize);
    OurList<edgeM> pile(graphSize);
    OurList<bool> inTree(graphSize,false); // init tab false

    VertexM origin = graphM[originM];
    OurList<unsigned int> originNeighbor = origin.getNeigborsDistance();

    for (size_t i = 0; i < graphSize; ++i) {
        if (originNeighbor[i] != std::numeric_limits<unsigned int>::max()) {
            edgeM e = { i,originNeighbor[i] };
            pile.insert_back(e);
        }
    }
    //Complexity o(n)

    for (size_t s = 0; s < graphSize - 1; ++s) {

        edgeM choosenOne = minEdge(pile, inTree);


    }
    //Complexity o(n)

    //tree originTree = {0,,}

    if (file == "") {
        //res in console
    }
    else {
        //res in file
    }
}
OurList<VertexM> AlgoPrim::getGraphM()
{
    return graphM;
}
;
