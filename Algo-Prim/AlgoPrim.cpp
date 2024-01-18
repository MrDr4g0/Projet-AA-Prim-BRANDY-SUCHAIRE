// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"

#include <fstream>

edgeM AlgoPrim::minEdge(const OurList<edgeM>& edgeMList, const OurList<bool>& isInTree)
{
    unsigned int min = std::numeric_limits<unsigned int>::max();
    edgeM res{};

    for (size_t i = 0; i < edgeMList.getSize(); ++i) {
        unsigned int vNum = edgeMList[i].n_vertex;
        unsigned int vDist = edgeMList[i].distance;

        if (isInTree[vNum-1] == false && vDist < min) {
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
    size_t graphSize = graphM.getSize();

    OurList<edgeM> finalTree(graphSize);
    OurList<edgeM> pile(graphSize);
    OurList<bool> inTree(graphSize,false); // init tab false

    VertexM origin = graphM[originM-1];
    OurList<unsigned int> originNeighbor = origin.getNeigborsDistance();

    edgeM originTree = { 0,originM,0 };
    inTree[originM - 1] = true;
    finalTree.insert_back(originTree);

    for (size_t i = 0; i < graphSize; ++i) {
        if (originNeighbor[i] != std::numeric_limits<unsigned int>::max()) {
            edgeM e = {originM, static_cast<unsigned int>(i)+1 , originNeighbor[i]};
            //std::cout << "Debug : (" << e.parent << ","<< e.n_vertex << ","<< e.distance << ")" << std::endl;
            pile.insert_back(e);
        }
    }

    for (size_t s = 0; s < graphSize - 1; ++s) {

        edgeM choosenOne = minEdge(pile, inTree);
        //std::cout << "Debug choosenOne : (" << choosenOne.parent << "," << choosenOne.n_vertex << "," << choosenOne.distance << ")" << std::endl;
        inTree[choosenOne.n_vertex-1] = true;
        finalTree.insert_back(choosenOne);

        VertexM currentV = graphM[choosenOne.n_vertex-1];
        OurList<unsigned int> vNeighbor = currentV.getNeigborsDistance();

        for (size_t i = 0; i < graphSize; ++i) {
            if (vNeighbor[i] != std::numeric_limits<unsigned int>::max()) {
                edgeM e = { choosenOne.n_vertex,static_cast<unsigned int>(i)+1, vNeighbor[i]};
                //std::cout << "Debug : (" << e.parent << "," << e.n_vertex << "," << e.distance << ")" << std::endl;
                pile.insert_back(e);
            }
        }


    }
    //Complexity o(n2)

    if (file == "") {
        //res in console
         //(x -> p : c)

        for (size_t i = 0; i < finalTree.getSize(); ++i) {
            if (finalTree[i].parent == 0) {
                std::cout << "(_ -> " << finalTree[i].n_vertex << " : _)" << std::endl;
            }
            else {
                std::cout << "(" << finalTree[i].parent << " -> " << finalTree[i].n_vertex << " : " << finalTree[i].distance << ")" << std::endl;
            }
            
        }

    }
    else {
        //res in file
    }
}
void AlgoPrim::setOriginM(unsigned int vertex)
{
    originM = vertex;
}
OurList<VertexM> AlgoPrim::getGraphM()
{
    return graphM;
}
;
