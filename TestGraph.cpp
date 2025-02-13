#include "Graph.h"
#include <cassert>
//#include <string>

void assertRouteEqual(const Route<std::string>& expected, const Route<std::string>& actual, const std::string& message)
{
    if (expected.GetLength() != actual.GetLength())
    {
        std::cerr << "Assertion Failed: " << message << ". Expected length: " << expected.GetLength() << ", Actual length: " << actual.GetLength() << "\n";
        assert(false);
    }
    for (int i = 0; i < expected.GetLength(); ++i)
    {
        if (expected.Get(i) != actual.Get(i))
        {
            std::cerr << "Assertion Failed: " << message << ". Expected path: ";
            assert(false);
        }
    }
}

void assertStringEqual(const std::string& expected, const std::string& actual, const std::string& message) 
{
    if (expected != actual)
    {
        std::cerr << "Assertion Failed: " << message << ". Expected: \"" << expected << "\", Actual: \"" << actual << "\"\n";
        assert(false);
    }
}



void testGraphGetVertexById() 
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    assertStringEqual("Node A", graph.GetVertexById("A"), "GetVertexById Failed");
    std::cout << "test DirectedGraph GetVertexById passed" << std::endl;
}

void testGraphAddVertex() 
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    auto keys = graph.GetVertexById("A");
    assert(keys == "Node A");
    std::cout << "test DirectedGraph AddVertex WithId passed" << std::endl;
}


void testGraphAddEdge() 
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    graph.AddVertex("B", "Node B");
    graph.AddEdge("A", "B", 5);
    ArraySequence<Edge<std::string>> edges = graph.GetEdges("A");
    std::cout << edges.GetLength();
    assert(edges.GetLength() == 1);
    assert(edges.Get(0).GetTo() == "B");
    assert(edges.Get(0).GetWeight() == 5);
    std::cout << "test DirectedGraph AddEdge passed" << std::endl;
}


void testGraphDeleteVertex() 
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    graph.AddVertex("B", "Node B");
    graph.AddEdge("A", "B", 5);
   
    graph.DeleteVertex("A");
    auto keys2 = graph.GetVertexById("A");
    assert(keys2 == std::string());
    std::cout << "test DirectedGraph DeleteVertex passed" << std::endl;
}


void testGraphSetNodeData()
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    graph.SetVertexData("A", "New Node A");
    assertStringEqual("New Node A", graph.GetVertexById("A"), "SetNodeData Failed");
    std::cout << "test DirectedGraph SetNodeData passed" << std::endl;
}


void testGraphDeleteEdge() 
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    graph.AddVertex("B", "Node B");
    graph.AddEdge("A", "B", 5);
    ArraySequence<Edge<std::string>> edges = graph.GetEdges("A");
    assert(edges.GetLength() == 1);
    graph.DeleteEdge("A", "B");
    ArraySequence<Edge<std::string>> edges2 = graph.GetEdges("A");
    assert(edges2.GetLength() == 0);
    std::cout << "test DirectedGraph DeleteEdge passed" << std::endl;
}



void testGraphFindMaxBandwidthPath() 
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    graph.AddVertex("B", "Node B");
    graph.AddVertex("C", "Node C");
    graph.AddVertex("D", "Node D");
    graph.AddEdge("A", "B", 3);
    graph.AddEdge("A", "C", 5);
    graph.AddEdge("B", "D", 4);
    graph.AddEdge("C", "D", 2);

    std::pair<Route<std::string>, int> result = graph.FindMaxBandwidthPath("A", "D");
    assert(result.second == 3);
    Route<std::string> expected_path;
    expected_path.Add("A");
    expected_path.Add("B");
    expected_path.Add("D");

    assertRouteEqual(expected_path, result.first, "Incorrect path in FindMaxBandwidthPath");

    Graph<std::string> graph2;
    graph2.AddVertex("A", "Node A");
    graph2.AddVertex("B", "Node B");
    graph2.AddEdge("A", "B", 1);

    std::pair<Route<std::string>, int> result2 = graph2.FindMaxBandwidthPath("A", "B");
    assert(result2.second == 1);
    Route<std::string> expected_path2;
    expected_path2.Add("A");
    expected_path2.Add("B");

    assertRouteEqual(expected_path2, result2.first, "Incorrect path in FindMaxBandwidthPath");

    std::cout << "test FindMaxBandwidthPath passed" << std::endl;

}

void testGraphFindShortestRoute()
{
    Graph<std::string> graph;
    graph.AddVertex("A", "Node A");
    graph.AddVertex("B", "Node B");
    graph.AddVertex("C", "Node C");
    graph.AddVertex("D", "Node D");
    graph.AddEdge("A", "B", 1);
    graph.AddEdge("A", "C", 4);
    graph.AddEdge("B", "C", 2);
    graph.AddEdge("B", "D", 5);
    graph.AddEdge("C", "D", 1);


    Route<std::string> shortestPath = graph.FindShortestRoute("A", "D");
    Route<std::string> expected_path;
    expected_path.Add("A");
    expected_path.Add("B");
    expected_path.Add("C");
    expected_path.Add("D");
    assertRouteEqual(expected_path, shortestPath, "Incorrect shortest path");

    Graph<std::string> graph2;
    graph2.AddVertex("A", "Node A");
    graph2.AddVertex("B", "Node B");
    graph2.AddEdge("A", "B", 1);
    Route<std::string> shortestPath2 = graph2.FindShortestRoute("A", "B");
    Route<std::string> expected_path2;
    expected_path2.Add("A");
    expected_path2.Add("B");
    assertRouteEqual(expected_path2, shortestPath2, "Incorrect shortest path");

    std::cout << "test DirectedGraph FindShortestRoute passed" << std::endl;

}