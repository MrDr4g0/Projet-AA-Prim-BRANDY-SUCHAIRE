// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"

#include <fstream>
#include <chrono>

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
        std::cerr << "Error File Converter : Can't open the file." << std::endl;
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

                if (neighbor < 0 || neighbor > numberVertices) {
                    std::cerr << "Vertex out of bound : " << neighbor << std::endl;
                    break;
                }

                if (!(inputFile >> distance)) {
                    std::cerr << "Error reading distance for vertex " << vertexNumber << std::endl;
                    break;
                }

                neighborsDistance[neighbor-1] = distance;
                
                if (neighbor <= i+1) {
                    graph[neighbor - 1].getNeigborsDistance()[i] = distance;
                }
                
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
    //Debut de l'algo
    std::chrono::high_resolution_clock::time_point startClock = std::chrono::high_resolution_clock::now();


    //
    bool isDone = false;
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

    while (!isDone) {
        edgeM choosenOne = minEdge(pile, inTree);
        //std::cout << "Debug choosenOne : (" << choosenOne.parent << "," << choosenOne.n_vertex << "," << choosenOne.distance << ")" << std::endl;

        if (choosenOne == edgeM{}) {
            isDone = true;
        }
        else {
            inTree[choosenOne.n_vertex - 1] = true;
            finalTree.insert_back(choosenOne);

            VertexM currentV = graphM[choosenOne.n_vertex - 1];
            OurList<unsigned int> vNeighbor = currentV.getNeigborsDistance();

            for (size_t i = 0; i < graphSize; ++i) {
                if (vNeighbor[i] != std::numeric_limits<unsigned int>::max()) {
                    edgeM e = { choosenOne.n_vertex,static_cast<unsigned int>(i) + 1, vNeighbor[i] };
                    //std::cout << "Debug : (" << e.parent << "," << e.n_vertex << "," << e.distance << ")" << std::endl;
                    pile.insert_back(e);
                }
            }
        }

    }

    //Complexity o(n2)
    std::chrono::high_resolution_clock::time_point endClock = std::chrono::high_resolution_clock::now();
    //Total time
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(endClock - startClock);

    bool isConnected = true;
    for (size_t j = 0; j < inTree.getSize(); ++j) {
        if (!inTree[j]) {
            isConnected = false;
        }
    }

    if (file == "") {
        //res in console
         //(x -> p : c)

        isConnected ? std::cout << "LE GRAPHE EST CONNEXE" << std::endl << std::endl : std::cout << "LE GRAPHE N'EST PAS CONNEXE" << std::endl << std::endl;

        std::cout << "L'arbre couvrant a partir de : " << originM << std::endl;

        for (size_t i = 0; i < finalTree.getSize(); ++i) {
            if (finalTree[i].parent == 0) {
                std::cout << "("<< finalTree[i].n_vertex <<" -> _ : _)" << std::endl;
            }
            else {
                std::cout << "(" << finalTree[i].n_vertex << " -> " << finalTree[i].parent << " : " << finalTree[i].distance << ")" << std::endl;
            }
            
        }

        std::cout << std::endl << "Temps d'execution de l'algorithme de Prim sur une matrice d'adjacence est de : " << duration.count() << " micros" << std::endl;

    }
    else {
        std::ofstream outputFile(file,std::ios::out);
        if (!outputFile.is_open()) {
            std::cerr << "Error Prim Execution : Can't open the output file." << std::endl;
        }
        else {
            outputFile << "PrimM" << std::endl << std::endl;

            isConnected ? outputFile << "LE GRAPHE EST CONNEXE" << std::endl << std::endl : outputFile << "LE GRAPHE N'EST PAS CONNEXE" << std::endl << std::endl;

            outputFile << "L'arbre couvrant a partir de : " << originM << std::endl;

            for (size_t i = 0; i < finalTree.getSize(); ++i) {
                if (finalTree[i].parent == 0) {
                    outputFile << "(" << finalTree[i].n_vertex << " -> _ : _)" << std::endl;
                }
                else {
                    outputFile << "(" << finalTree[i].n_vertex << " -> " << finalTree[i].parent << " : " << finalTree[i].distance << ")" << std::endl;
                }

            }

            outputFile << std::endl << "Temps d'execution de l'algorithme de Prim sur une matrice d'adjacence est de : " << duration.count() << " micros" << std::endl;

            outputFile.close();
        }
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
