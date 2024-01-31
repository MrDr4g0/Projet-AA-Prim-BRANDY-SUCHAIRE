// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"

#include <fstream>
#include <chrono>

edge AlgoPrim::minEdge(const OurList<edge>& edgeList, const OurList<bool>& isInTree)
{
    unsigned int min = std::numeric_limits<unsigned int>::max();
    edge res{};

    for (size_t i = 0; i < edgeList.getSize(); ++i) {
        unsigned int vNum = edgeList[i].n_vertex;
        unsigned int vDist = edgeList[i].distance;

        if (isInTree[vNum-1] == false && vDist < min) {
            min = vDist;
            res = edgeList[i];
        }
    }

    return res;
}


AlgoPrim::AlgoPrim() : graphL(0), graphM(0),originL(0),originM(0)
{
}

void AlgoPrim::convertFileGraphL(std::string file)
{
    std::ifstream inputFile(file);


    if (!inputFile.is_open())
        std::cout << "File cannot open : " << file << std::endl;
    else
    {
        // Read the number of vertices
        int numVertices;
        inputFile >> numVertices;

        // Creating a graph with the same number of vertices
        OurList<VertexL> graph(numVertices);

        // Read vertex data
        for (int i = 0; i < numVertices; ++i) {

            unsigned int vertexNumber;
            inputFile >> vertexNumber;

            // Read neighbors and distances
            unsigned int neighborVertex, distance;
            OurList<edgeL> neigbhors;

            // Je ne parcours pas de la bonne manière

            while (inputFile >> neighborVertex && neighborVertex != 0) {

                // Check the distance
                if (!(inputFile >> distance)) {
                    std::cerr << "Error reading distance for vertex " << vertexNumber << std::endl;
                    break;
                }

                // add neighbors
                edgeL neighbor{ distance, neighborVertex };
                neigbhors.insert_back(neighbor);

                // 
                for (size_t i = 0; i < graph.getSize(); i++) {
                    if (graph[i].getValue() == neighborVertex) {
                        graph[i].AddNeighbor(vertexNumber, distance);
                    }
                }
            }

            VertexL vertex(vertexNumber, neigbhors);



            // Add Vertex
            graph.insert_back(vertex);

            for (size_t j = 0; j < graph.getSize(); j++) {
                VertexL cvertex = graph[j];
                cvertex.getValue();
                OurList<edgeL> neigbhorss = cvertex.getNeighbors();
            }
        }

        graphL = graph;
    }
}

void AlgoPrim::executePrimForL(std::string outputFile,unsigned int start)
{
    // Start algo
    std::chrono::high_resolution_clock::time_point startClock = std::chrono::high_resolution_clock::now();

    // Collect size of graph
    size_t graphSize = graphL.getSize();

    // create an empty tree
    OurList<edge> finalTree(graphSize);

    // create tree of visited vertex
    OurList<bool> inTree(graphSize, false);

    // create a queue
    OurList<edge> pile(graphSize);

    // is the tree done ?
    bool isDone = false;

    // I choose my start point
    /*
    for (size_t i = 0; i < graphSize; i++) {
        if (start == graphL[i].getValue()) // My vertex exist
        {
            inTree[i] = true; // set start to visited 

            finalTree.insert_back(graphL[i].getValue()); // add the start to the final Tree

            unsigned int lesscost;
            unsigned int father;
            unsigned int child;

            // graphSize is the number of steps of the algorithm
            for (size_t j = 0; j < graphSize; j++) {
                lesscost = UINT_MAX;
                // check each vertex of the tree
                for (size_t k = 0; k < finalTree.getSize(); k++) {
                    // for each neighbors
                    for (size_t l = 0; l < graphL[finalTree[k].getValue() - 1].getNeighbors().getSize(); l++) {
                        //Verify the most less cost and also if its not visited
                        if (graphL[finalTree[k].getValue() - 1].getNeighbors()[l].v_cost < lesscost && !inTree[graphL[finalTree[k].getValue() - 1].getNeighbors()[l].v_value - 1]) {
                            lesscost = graphL[finalTree[k].getValue() - 1].getNeighbors()[l].v_cost;
                            child = graphL[finalTree[k].getValue() - 1].getNeighbors()[l].v_value;

                            father = graphL[finalTree[k].getValue() - 1].getValue();
                        }
                    }
                }

                if (lesscost != UINT_MAX) {
                    // add the next vertex and the edgeL
                    VertexL newVertex(child);

                    newVertex.AddNeighbor(father, lesscost);

                    for (size_t i = 0; i < finalTree.getSize(); i++) {
                        if (finalTree[i].getValue() == father) {
                            finalTree[i].AddNeighbor(child, lesscost);
                        }
                    }

                    finalTree.insert_back(newVertex);

                    inTree[child - 1] = true;
                }
            }
            break;
        }
    }
    */

    edge originTree = { 0,start,0 };
    inTree[start - 1] = true;
    finalTree.insert_back(originTree);

    VertexL originV = graphL[start - 1];

    for (size_t i = 0; i < originV.getNeighbors().getSize(); ++i) {
        edge e = { start, originV.getNeighbors()[i].v_value , originV.getNeighbors()[i].v_cost };
        pile.insert_back(e);
    }

    while(!isDone){
        edge bestEdge = minEdge(pile, inTree);

        if (bestEdge == edge{}) {
            isDone = true;
        }
        else {
            inTree[bestEdge.n_vertex - 1] = true;
            finalTree.insert_back(bestEdge);

            VertexL currentV = graphL[bestEdge.n_vertex - 1];
            OurList<edgeL> vNeighbor = currentV.getNeighbors();

            for (size_t i = 0; i < vNeighbor.getSize(); ++i) {
                edge e = { bestEdge.n_vertex,vNeighbor[i].v_value, vNeighbor[i].v_cost};
                pile.insert_back(e);        
            }
        }
    }


    // End algo
    std::chrono::high_resolution_clock::time_point endClock = std::chrono::high_resolution_clock::now();

    // Total time
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(endClock - startClock);


    // If the user want to write in a file
    std::ofstream output(outputFile, std::ios::out);

    // Check if graph is connexe 
    bool isConnex = true;
    for (size_t i = 0; i < inTree.getSize(); i++) {
        if (inTree[i] == false) {
            isConnex = false;
        }
    }

    // If its not specified
    if (outputFile == "")
    {
        // Check if its connexe
        isConnex ? std::cout << "LE GRAPHE EST CONNEXE" << std::endl << std::endl : std::cout << "LE GRAPHE N'EST PAS CONNEXE" << std::endl << std::endl;

        // print start point
        std::cout << "L'arbre couvrant a partir de : " << start << std::endl;

        // print my final tree
        for (size_t i = 0; i < finalTree.getSize(); i++) {
            if (i == 0) {
                std::cout << "(" << finalTree[i].n_vertex << " -> _ : _)" << std::endl;
            }
            else if (i > 0) {
                std::cout << "(" << finalTree[i].n_vertex << " -> " << finalTree[i].parent << " : " << finalTree[i].distance << ")" << std::endl;
            }
        }

        std::cout << std::endl << "Temps d'execution de l'algorithme de Prim sur les listes d'adjacence est de : " << duration.count() << " micros" << std::endl;

    }
    else {
        // Check if its connexe
        isConnex ? output << "LE GRAPHE EST CONNEXE" << std::endl << std::endl : output << "LE GRAPHE N'EST PAS CONNEXE" << std::endl << std::endl;

        // print start point
        output << "L'arbre couvrant a partir de : " << start << std::endl;

        // Write in the final tree
        for (size_t i = 0; i < finalTree.getSize(); i++) {
            if (i == 0) {
                output << "(" << finalTree[i].n_vertex << " -> _ : _)" << std::endl;
            }
            else if (i > 0) {
                output << "(" << finalTree[i].n_vertex << " -> " << finalTree[i].parent << " : " << finalTree[i].distance << ")" << std::endl;
            }
        }

        // Write execution time 
        output << std::endl << "Temps d'execution de l'algorithme de Prim sur les listes d'adjacence est de : " << duration.count() << " micros" << std::endl;
        output.close();


    }
};

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

    OurList<edge> finalTree(graphSize);
    OurList<edge> pile(graphSize);
    OurList<bool> inTree(graphSize,false); // init tab false

    VertexM origin = graphM[originM-1];
    OurList<unsigned int> originNeighbor = origin.getNeigborsDistance();

    edge originTree = { 0,originM,0 };
    inTree[originM - 1] = true;
    finalTree.insert_back(originTree);

    for (size_t i = 0; i < graphSize; ++i) {
        if (originNeighbor[i] != std::numeric_limits<unsigned int>::max()) {
            edge e = {originM, static_cast<unsigned int>(i)+1 , originNeighbor[i]};
            //std::cout << "Debug : (" << e.parent << ","<< e.n_vertex << ","<< e.distance << ")" << std::endl;
            pile.insert_back(e);
        }
    }

    while (!isDone) {
        edge choosenOne = minEdge(pile, inTree);
        //std::cout << "Debug choosenOne : (" << choosenOne.parent << "," << choosenOne.n_vertex << "," << choosenOne.distance << ")" << std::endl;

        if (choosenOne == edge{}) {
            isDone = true;
        }
        else {
            inTree[choosenOne.n_vertex - 1] = true;
            finalTree.insert_back(choosenOne);

            VertexM currentV = graphM[choosenOne.n_vertex - 1];
            OurList<unsigned int> vNeighbor = currentV.getNeigborsDistance();

            for (size_t i = 0; i < graphSize; ++i) {
                if (vNeighbor[i] != std::numeric_limits<unsigned int>::max()) {
                    edge e = { choosenOne.n_vertex,static_cast<unsigned int>(i) + 1, vNeighbor[i] };
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
