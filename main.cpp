//#include "Graph.h"
#include "TestAll.h"
//#include "HashTable.h"

int main()
{


    testDefaultConstructor();
    testPrepend();
    testAdd();
    testGet();
    testGetLength();
    testGraphGetVertexById();
  
    testGraphAddEdge();
    testGraphDeleteVertex();
    testGraphSetNodeData();
    testGraphDeleteEdge();
    testGraphFindMaxBandwidthPath();
    testGraphFindShortestRoute();
    
    testHashTableAddAndFind();
    testHashTableDelete();
    testHashTableSize();
    testHashTableEmpty();
    testHashTableRehashing();
    testHashTableKeys();
    testHashTableDeleteWithKeys();

    testHashTableAddAndFind();
    testHashTableDelete();
    testHashTableSize();
    testHashTableEmpty();
    testHashTableRehashing();
    testHashTableKeys();
    testHashTableDeleteWithKeys();

    HashTable<int, char> hash;
    hash.Add(5, 'c');
    hash.Delete(5);
    Graph<std::string> gr;
    gr.AddVertex("A");
    gr.AddVertex("B");
    gr.AddVertex("C");
 //   gr.AddVertex("D");

    gr.AddEdge("A", "B", 5);
    gr.AddEdge("B", "C", 10);
    gr.AddEdge("C", "B", 2);
   // gr.AddEdge("A", "C", 13);
   // gr.AddEdge("D", "B", 2);

   // gr.DeleteVertex("B");
    //gr.SetWeight("A", "C", 1);
    auto res = gr.FindMaxBandwidthPath("A", "C");
   // auto res1 = gr.FindShortestRoute("A", "C");

    std::cout << res.first << res.second;
   // std::cout << gr.GetEdges("A");
}
