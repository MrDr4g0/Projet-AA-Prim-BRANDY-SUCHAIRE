// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"
#include <iostream>
#include <fstream>

AlgoPrim::AlgoPrim() : graphL(0), graphM(0),originL(0), originM(0)
{
}
void AlgoPrim::convertFileGraphM(std::string file)
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
            OurList<edge> neigbhors;

            // Je ne parcours pas de la bonne manière

            while (inputFile >> neighborVertex && neighborVertex != 0) {
                
                // Check the distance
                if (!(inputFile >> distance)) {
                    std::cerr << "Error reading distance for vertex " << vertexNumber << std::endl;
                    break;
                }
                
                // add neighbors
                edge neighbor{ distance, neighborVertex };
                neigbhors.insert_back(neighbor);
                
                // 
                for (int i = 0; i < graph.getSize(); i++) {
                    if (graph[i].getValue() == neighborVertex) {
                        graph[i].AddNeighbor(vertexNumber, distance);
                    }
                }
            }

            VertexL vertex(vertexNumber, neigbhors);

            

            // Add Vertex
            graph.insert_back(vertex);

            for (int j = 0; j < graph.getSize(); j++) {
                VertexL cvertex = graph[j];
                cvertex.getValue();
                OurList neigbhorss = cvertex.getNeighbors();
            }
        }

        graphL = graph;

        // TEST
        /*for (int i = 0; i < graphL.getSize(); i++) {
            std::cout <<graphL[i]<<std::endl;
        }*/
    }
}
void AlgoPrim::executePrimForL(std::string outputFile , int start)
{    
    // Collect size of graph
    size_t graphSize = graphL.getSize();

    // create an empty tree
    OurList<VertexL> finalTree(graphSize);

    // create tree of visited vertex
    OurList<bool> inTree(graphSize, false);

    // create an attribut for check if is connexe
    bool isConnex = true;

    // I choose my start point
    for (int i = 0; i < graphSize; i++) {
        if (start == graphL[i].getValue()) // My vertex exist
        {
            inTree[i] = true; // set start to visited 

            finalTree.insert_back(graphL[i].getValue()); // add the start to the final Tree

            unsigned int lesscost;
            unsigned int father;
            unsigned int child;

            // graphSize is the number of steps of the algorithm
            for (int j = 0; j < graphSize; j++) {
                lesscost = UINT_MAX;
                // check each vertex of the tree
                for (int k = 0; k < finalTree.getSize(); k++) {
                    // for each neighbors
                    for (int l = 0; l < graphL[finalTree[k].getValue()-1].getNeighbors().getSize(); l++) {
                        //Verify the most less cost and also if its not visited
                        if (graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_cost < lesscost && !inTree[graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_value-1]) {
                            lesscost = graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_cost;
                            child = graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_value;

                            father = graphL[finalTree[k].getValue()-1].getValue();
                        }
                    }
                }

                if (lesscost != UINT_MAX) {
                    // add the next vertex and the edge
                    VertexL newVertex(child);
                            
                    newVertex.AddNeighbor(father, lesscost);

                    for (int i = 0; i < finalTree.getSize(); i++) {
                         if (finalTree[i].getValue() == father) {
                             finalTree[i].AddNeighbor(child, lesscost);
                         }
                    }

                    finalTree.insert_back(newVertex);

                    inTree[child - 1] = true;
                }
                else {
                    // Dire que c'est pas connexe
                    isConnex = false;
                }
            }
            
            for (int i = 0; i < finalTree.getSize(); i++) {
                std::cout << finalTree[i] << std::endl;
            }

            break;
        }
    }

    // print my final tree
    for (size_t i = 0; i < finalTree.getSize(); i++) {
        if (i == 0) {
            std::cout << "(" << finalTree[i].getValue() << " -> _ : _)" << std::endl;
        }
        else if(i > 0){
            std::cout << "(" << finalTree[i].getValue() << " -> " << finalTree[i].getNeighbors()[0].v_value << " : " << finalTree[i].getCost(finalTree[i].getValue()) << ")" << std::endl;
        }
    }
};
