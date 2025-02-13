#pragma once
//#include "..\..\..\Documents\Laba3Sem3\IDictionary.h"

#include <queue>
#include <limits>
#include "Route.h"
#include "HashTable.h"

template <class T>
class Edge
{
private:
	T  to;
	T  from;
	int weight;
	template <class T>
   friend std::ostream& operator << (std::ostream& out, const Edge<T>& edge);
public:
	Edge() {}
	Edge(T  From, T To, int Weight)
	{
		to = To;
		from = From;
		weight = Weight;
	}

	const int GetWeight() const
	{
		return weight;
	}
	const T GetFrom() const
	{
		return from;
	}
	const T GetTo() const
	{
		return to;
	}

	
	void SetWeight(const int newWeight)
	{
		weight = newWeight;
	}
};

template <class T>
std::ostream& operator << (std::ostream& out, const Edge<T>& edge)
{
	out << edge.from <<" "<<edge.to<<" "<<edge.weight<<std::endl;
	return out;
}


template <class T>
struct Vertex 
{
	T id;
	T value;
	ArraySequence<Edge<T>> edges;

	Vertex() : id(T()), value() {}
	Vertex(T key) : id(key), value() {}
	Vertex(T key, T value) : id(key), value(value) {}
};

template <class T>
std::ostream& operator << (std::ostream& out, const Vertex<T>& vertex)
{
	out << vertex.id;
	return out;
}
//Можно хранить все ребра в вершине, можно генерировать граф в интерфейсе (по количеству вершин и количеству ребер)
template <typename T>
class Graph
{
private:

	HashTable<T, Vertex<T>> vertices;

	//std::string nextAutoId = 0;


public:
	ArraySequence<Edge<T>> GetEdges(const T& id);

	bool FindVertex(const T& id)
	{
		auto ptr = vertices.FindElement(id);
		if (ptr != nullptr) return true;
		return false;
	}


	T GetVertexById(const T& id)
	{
		auto ptr = vertices.FindElement(id);
		if (ptr == nullptr) return T();
		return ptr->second.value;
	}

	
	void AddVertex(const T& id, const T& value)
	{
		Vertex<T> new_vertex(id, value);
		vertices.Add(id, new_vertex);
	}

    void AddEdge(const T& from, const T& to, int weight)
    {
		if (from == to)
		{
			throw std::logic_error("vertices have the same keys!");
		}
		auto* fromVertex = vertices.FindElement(from);
		auto* toVertex = vertices.FindElement(to);

		if (fromVertex == nullptr || toVertex == nullptr)
		{
			throw std::logic_error("vertex not found!");
		}

		Edge<T> edge(from, to, weight);
		
		(fromVertex->second).edges.Append(edge);
		
		(toVertex->second).edges.Append(edge);

    }

	void AddVertex(const T& id)
	{
		Vertex<T> new_vertex(id);
		vertices.Add(id, new_vertex);
	}


	void DeleteVertex(const T& id)
	{
		auto* nodeToRemove = vertices.FindElement(id);
		if (nodeToRemove == nullptr) 
		{
			throw std::runtime_error("vertex not found!");
		}

		while (nodeToRemove->second.edges.GetLength() != 0)
		{
			DeleteEdge((nodeToRemove->second).edges.Get(0).GetFrom(), (nodeToRemove->second).edges.Get(0).GetTo());
		}

		//DeleteEdges(id);
		vertices.Delete(id);
	}


	void SetVertexData(const T& id, T newData)
	{
		auto* nodePtr = vertices.FindElement(id);
		if (nodePtr != nullptr)
		{
			nodePtr->second.value = newData;
		}
		else 
		{
			throw std::runtime_error("vertex not found!");
		}
	}

	void SetWeight(const T& from, const T& to, int newWeight)
	{
		auto* startVertex = vertices.FindElement(from);
		auto* endVertex = vertices.FindElement(to);

		if (startVertex == nullptr || endVertex == nullptr)
		{
			throw std::logic_error("vertex not found!");
		}

		for (int i = 0; i < startVertex->second.edges.GetLength(); ++i)
		{
			if (startVertex->second.edges.Get(i).GetTo() == to)
			{
				startVertex->second.edges.Get(i).SetWeight(newWeight);
			}
		}

		for (int i = 0; i < endVertex->second.edges.GetLength(); ++i)
		{
			if (endVertex->second.edges.Get(i).GetFrom() == from)
			{
				endVertex->second.edges.Get(i).SetWeight(newWeight);
			}
		}
	}


	void DeleteEdge(const T& from, const T& to)
	{
		//std::cout << from << " " << to<<std::endl;
		if (from == to)
		{
			throw std::logic_error("vertices are the same!");
		}

		auto* sourceVertex = vertices.FindElement(from);
		if (sourceVertex == nullptr)
		{
			throw std::logic_error("source node not found!");
		}

		auto* targetVertex = vertices.FindElement(to);
		if (targetVertex == nullptr)
		{
			throw std::logic_error("target node not found!");
		}

		bool edgeFoundSource = false;
		bool edgeFoundTarget = false;


		for (int i = 0; i < sourceVertex->second.edges.GetLength(); ++i)
		{
			if ((sourceVertex->second.edges.Get(i).GetFrom() == from && sourceVertex->second.edges.Get(i).GetTo() == to)) 
			{
				sourceVertex->second.edges.Delete(i);
				edgeFoundSource = true;
				break;
			}
			
		}

		for (int i = 0; i < targetVertex->second.edges.GetLength(); ++i)
		{
			if ((targetVertex->second.edges.Get(i).GetFrom() == from && targetVertex->second.edges.Get(i).GetTo() == to))
			{
				targetVertex->second.edges.Delete(i);
				edgeFoundTarget = true;
				break;
			}
			
		}
		
		if (!edgeFoundSource || !edgeFoundTarget)
		{
			throw std::runtime_error("edge not found");
		}

		
	}

    std::pair<Route<T>, int> FindMaxBandwidthPath(const T& start, const T&  end);
    Route<T> FindShortestRoute(const T& start, const T& end);
};

template <typename T>
std::pair<Route<T>, int> Graph<T>::FindMaxBandwidthPath(const T& start, const T& end)
{
	std::queue<std::pair<Route<T>, int>> queue;
	Route<T> initialRoute;
	initialRoute.Add(start);
	queue.push({ initialRoute, std::numeric_limits<int>::max() });

	Route<T> maxBandwidthPath;
	int maxBandwidth = 0;

	while (!queue.empty())
	{
		std::pair<Route<T>, int> current = queue.front();
		queue.pop();

		Route<T> currentRoute = current.first;
		int currentMinBandwidth = current.second;

		T lastVertex = currentRoute.Get(currentRoute.GetLength() - 1);

		if (lastVertex == end)
		{
			if (currentMinBandwidth > maxBandwidth)
			{
				maxBandwidth = currentMinBandwidth;
				maxBandwidthPath = currentRoute;
			}
			continue;
		}


		auto vertexPtr = vertices.FindElement(lastVertex);
		if (vertexPtr == nullptr) continue;
		ArraySequence<Edge<T>> edges = vertexPtr->second.edges;
		for (int i = 0; i < edges.GetLength(); ++i)
		{
			Edge<T> edge = edges.Get(i);
			if (edge.GetFrom() == lastVertex) //исходящие
			{
				T neighbor = edge.GetTo();
				int weight = edge.GetWeight();

				Route<T> newRoute = currentRoute;
				newRoute.Add(neighbor);
				int newMinBandwidth = std::min(currentMinBandwidth, weight);
				queue.push({ newRoute, newMinBandwidth });
			}
		}
	}

	return { maxBandwidthPath, maxBandwidth };
}


template <typename T>
Route<T> Graph<T>::FindShortestRoute(const T& start, const T& end)
{
	ArraySequence<T> keys(vertices.Keys());

	const int infinity = std::numeric_limits<int>::max();

	int size = keys.GetLength();
	ArraySequence<int> distanceEstimates(size, infinity);
	ArraySequence<bool> visitedNodes(size, false);
	ArraySequence<T> previousNodes(size, T());

	int startIndex = -1;
	for (int i = 0; i < size; i++)
	{
		if (keys.Get(i) == start)
		{
			startIndex = i;
			break;
		}
	}
	if (startIndex == - 1)
	{
		return {};
	}

	distanceEstimates.Set(0, startIndex);


	for (int i = 0; i < size; ++i)
	{
		T currentKey;
		int  currentIndex = -1;
		for (int j = 0; j < size; ++j)
		{ //индекс текущей с нименьшим весом
			if (!visitedNodes.Get(j) && (currentIndex == -1 || distanceEstimates.Get(j) < distanceEstimates.Get(currentIndex)))
			{
				currentKey = keys.Get(j);
				currentIndex = j;

			}
		}

		if (distanceEstimates.Get(currentIndex) == infinity || currentKey == end)
		{
			break;
		}

		visitedNodes.Set(true, currentIndex);

		auto* currentVertex = vertices.FindElement(currentKey);
		if (currentVertex == nullptr)
		{
			continue;
		}

		ArraySequence<Edge<T>> Edges (currentVertex->second.edges);

		for (int j = 0; j < Edges.GetLength(); ++j)
		{
			int neighborIndex = -1;
			for (int k = 0; k < size; ++k)
			{
				if (keys.Get(k) == Edges.Get(j).GetTo())
				{
					neighborIndex = k;
					break;
				}
			}
			if (neighborIndex != -1)
			{
				if (distanceEstimates.Get(currentIndex) + Edges.Get(j).GetWeight() < distanceEstimates.Get(neighborIndex))
				{
					distanceEstimates.Set(distanceEstimates.Get(currentIndex) + Edges.Get(j).GetWeight(), neighborIndex);
					previousNodes.Set(currentKey, neighborIndex);
				}
			}
		}
	}

	int endIndex = -1;
	for (int i = 0; i < size; i++)
	{
		if (keys.Get(i) == end)
		{
			endIndex = i;
			break;
		}
	}

	if (distanceEstimates.Get(endIndex) == infinity)
	{
		return {};
	}

	Route<T> shortestPath;
	T current = end;
	while (current != T())
	{
		shortestPath.Prepend(current);
		int current_index = -1;
		for (int k = 0; k < size; ++k)
		{
			if (keys.Get(k) == current)
			{
				current_index = k;
				break;
			}
		}
		if (current_index != -1)
		{
			current = previousNodes.Get(current_index);
		}
		else
		{
			current = T();
		}
	}
	return shortestPath;
}


template <typename T>
ArraySequence<Edge<T>> Graph<T>::GetEdges(const T& id)
{
	auto vertexPtr = vertices.FindElement(id);
	if (vertexPtr == nullptr) throw std::runtime_error("vertex not found");
	ArraySequence<Edge<T>> allEdges(vertexPtr->second.edges);

	return allEdges;
}
