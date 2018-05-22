#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

typedef struct Edge{
    int weight;
    int beg, end;
} Edge;

int Find(int subset[], int i){
    if (subset[i] == 0)
        return i;
    return Find(subset, subset[i]);
}

void Union(int subset[], int x, int y){
    int p = Find(subset, x);
    int q = Find(subset, y);
    subset[p] = q;
}

bool compareWeights(const Edge &a, const Edge &b){
    return a.weight < b.weight;
}

 vector <Edge> Kruskal(unsigned int vertices, vector <Edge> adjacencyList){

    vector <Edge> spanningTree;

    sort(adjacencyList.begin(), adjacencyList.end(), compareWeights);

    int *X = new int[vertices+1];
    for(unsigned int i = 0; i <= vertices; i++){
        X[i] = 0;
    }

    int i = 0;
    int p = 0;
    int q = 0;

    while(spanningTree.size() < vertices-1){
        Edge *next = &adjacencyList[i];
        p = Find(X, next->beg);
        q = Find(X, next->end);
        if(p != q){
            spanningTree.push_back(*next);
            Union(X, p, q);
        }
        i++;
    }

    return spanningTree;

}


int main()
{
    fstream myFile;
    unsigned int vertices = 0;
    unsigned int edges = 0;
    string line;
    myFile.open("in.txt");
    myFile >> vertices >> edges;
    vector <Edge> adjacencyList;
        while (getline( myFile, line)){
            stringstream ss(line);
            Edge *e = new Edge();
            while(ss >> e->beg >> e->end >> e->weight){
                adjacencyList.push_back(*e);
            }
    }
    myFile.close();

    vector <Edge> spanningTree = Kruskal(vertices, adjacencyList);

    int weightSum = 0;
    myFile.open("out.txt", ofstream::out | ofstream::trunc);
    for(unsigned int i = 0; i < spanningTree.size(); i++){
        weightSum += spanningTree[i].weight;
    }

    myFile << weightSum << endl;
    myFile << spanningTree.size() << endl;
    for(unsigned int i = 0; i < spanningTree.size(); i++){
        myFile << spanningTree[i].beg << " " << spanningTree[i].end << endl;
    }

    myFile.close();

    return 0;
}
