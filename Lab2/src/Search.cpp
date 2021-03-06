#include "Search.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <time.h>

using namespace std;


Search::Search(){
    FileType = 3;
    AlgorithmName = "DFS-Recursive";          // We set the first algorithm
    newBase = new DFS_recu();
    GraphName = "NULL";

    vector<double> temptable;
    for(int i = 0; i < 6; i++)
    temptable.push_back(0);

    for(int j = 0; j < 5; j++){
    ListSummaryTable.push_back(temptable);
    MatrixSummaryTable.push_back(temptable);
    }

}

void Search::Load(int ListOrMatrix,std::vector<std::vector<int>>& inputGraph, std::vector<std::vector<double>>& inputWeight, std::vector<std::vector<int>>& inputDistance){
    Graph = inputGraph;
    FileType = ListOrMatrix;
    WeightGraph = inputWeight;
    DistanceGraph = inputDistance;  // Load Graphes an Graph type
    
}



void Search::Execute(int src, int dest){
    BeginPoint = src;
    EndPoint = dest;
    
    if(FileType == 0){
        GraphName = "List";
        newBase->SetGraph(Graph);
        newBase->SetWeight(WeightGraph);               // Pass graphes to the SearchBase
        newBase->SetDistance(DistanceGraph);
        newBase->ImplementList(src, dest);
        //if(AlgorithmName == "DFS-Recursive"){
      //  newBase->FindCostOfPath();
      //  newBase->FindDistanceOfPath();
     //   }
     //   newBase->FillSummaryTable(ListSummaryTable, AlgorithmName);
    }
    else if(FileType == 1){
        GraphName = "Matrix";
        newBase->SetGraph(Graph);
        newBase->SetWeight(WeightGraph);
        newBase->SetDistance(DistanceGraph);
        newBase->ImplementMatrix(src, dest);       // We have an implementlist and an implementmatrix
      //  if(AlgorithmName == "DFS-Recursive"){
      //  newBase->FindCostOfPath();
      //  newBase->FindDistanceOfPath();
     //   }
      //  newBase->FillSummaryTable(MatrixSummaryTable, AlgorithmName); 
    }
    else{
        cout << "Error Occured On Execute..." << endl;
        exit(0);
    }
}


void Search::Display(){
    
}

void Search::Stats(){
    cout<< "=================STATS Data=================" << endl;
    cout << "Algorithm Name: " << AlgorithmName << endl;
    cout << "Graph Name(List or Matrix): " << GraphName << endl;
    cout << "Search from " << BeginPoint << " to " << EndPoint << endl;
    newBase->FindCostOfPath();
    newBase->FindDistanceOfPath();
    if(GraphName == "List")
    newBase->FillSummaryTable(ListSummaryTable, AlgorithmName);
    else
    newBase->FillSummaryTable(MatrixSummaryTable, AlgorithmName);
    
    newBase->PrintPathData();        // Show result to the screen
}


void Search::Save(){
    ofstream outfile("OutPutData.txt");
    if(!outfile){
        cout << "Error on OutputFile" << endl;
        exit(0);
    }
    outfile << "List" << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            outfile << ListSummaryTable.at(i).at(j)/100 << " ";   // Save list's normalized data
        }
        outfile << endl;
    }
    outfile << "\n" << endl;
    outfile << "Matrix" << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            outfile << MatrixSummaryTable.at(i).at(j)/100 << " ";     // Save matrix's normalized data
        }
        outfile << endl;
    }


    outfile.close();
}

void Search::Select(int SearchAl){
    switch (SearchAl)
    {
    case 0:{
        delete newBase;
        newBase = new Dijkstra();
        AlgorithmName = "Dijkstra";   // Use an integer to change algorith,
        break;
    }
    case 1:{
        delete newBase;               // Using delete to release the memory
        newBase = new A_star();
        AlgorithmName = "A_Star";
        break;
    }
    case 2:{
        delete newBase;
        newBase = new BFS_recu();
        AlgorithmName = "BFS-Recursive";
        break;
    }
    case 3:{
        delete newBase;
        newBase = new DFS_iter();
        AlgorithmName = "DFS-Iterative";
        break;
    }
    case 4:{
        delete newBase;
        newBase = new BFS_iter();
        AlgorithmName = "BFS-Iterative";
        break;
    }
    case 5:{
        delete newBase;
        newBase = new DFS_iter();
        AlgorithmName = "DFS-Recursive";
        break;
    }
    default:{
        cout << "error" << endl;
        AlgorithmName = "NULL";
        break;
    }
   }
}


Search::~Search()
{

}