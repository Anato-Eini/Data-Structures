#pragma once

#include "AdjacencyList.h"

#include <algorithm>
#include <iterator>
#include <list>
#include <mutex>
#include <set>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>


namespace Graph
{

	template <typename V, typename E>
	AdjacencyList<V, E>::Vertex::Vertex(const V &name) : name(name)
	{
	}

	template <typename V, typename E>
	AdjacencyList<V, E>::Vertex::Vertex(const V &name, const std::list<E> &inEdges, const std::list<E> &outEdges) :
		name(name), inEdges(inEdges), outEdges(outEdges)
	{
	}

	template <typename V, typename E>
	AdjacencyList<V, E>::AdjacencyList() : list(new std::list<Vertex>()), sizeEdge(0)
	{
	}

	template <typename V, typename E>
	std::vector<V> *AdjacencyList<V, E>::vertices() const
	{
		std::vector<V> *vertices = new std::vector<V>();

		std::transform(list->begin(), list->end(), std::back_inserter(*vertices),
					   [](const Vertex &vertex) -> V { return vertex.name; });

		return vertices;
	}

	template <typename V, typename E>
	std::vector<E> *AdjacencyList<V, E>::edges() const
	{
		std::vector<E> *arr_edges = new std::vector<E>();

		std::for_each(list->begin(), list->end(), [&arr_edges](const Vertex &vertex) -> void
					  { arr_edges->insert(arr_edges->end(), vertex.outEdges.begin(), vertex.outEdges.end()); });

		return arr_edges;
	}

	template <typename V, typename E>
	std::vector<std::pair<V, V>> *AdjacencyList<V, E>::endVertices(const E &edge) const
	{
		std::mutex mutex;
		std::vector<std::pair<V, V>> *end_vertices = new std::vector<std::pair<V, V>>();

		size_t i = 0;
		size_t j = 0;

		// Destination thread
		std::thread threadIn(
			[this, &edge, &i, end_vertices, &mutex]() -> void
			{
				std::for_each(list->begin(), list->end(),
							  [this, &edge, &i, end_vertices, &mutex](const Vertex &v) -> void
							  {
								  const std::list<E> &cList = v.inEdges;
								  if (std::find(cList.begin(), cList.end(), edge) != cList.end())
								  {
									  std::lock_guard<std::mutex> lockGuard(mutex);
									  if (i++ == end_vertices->size())
										  end_vertices->emplace_back(std::make_pair(V(), v.name));
									  else
										  end_vertices->at(i - 1).first = v.name;
								  }
							  });
			});

		// Origin thread
		std::thread threadOut(
			[this, &edge, &j, end_vertices, &mutex]() -> void
			{
				std::for_each(list->begin(), list->end(),
							  [this, &edge, &j, end_vertices, &mutex](const Vertex &v) -> void
							  {
								  const std::list<E> &cList = v.outEdges;
								  if (std::find(cList.begin(), cList.end(), edge) != cList.end())
								  {
									  std::lock_guard<std::mutex> lockGuard(mutex);
									  if (j++ == end_vertices->size())
										  end_vertices->emplace_back(std::make_pair(V(), v.name));
									  else
										  end_vertices->at(j - 1).second = v.name;
								  }
							  });
			});

		threadIn.join();
		threadOut.join();

		return end_vertices;
	}

	template <typename V, typename E>
	std::vector<E> *AdjacencyList<V, E>::outgoingEdges(const V &vertex) const
	{
		std::vector<E> *outgoingEdges = new std::vector<E>();

		std::for_each(list->begin(), list->end(),
					  [outgoingEdges, &vertex](const Vertex &v) -> void
					  {
						  if (v.name == vertex)
							  outgoingEdges->insert(outgoingEdges->end(), v.outEdges.begin(), v.outEdges.end());
					  });

		return outgoingEdges;
	}

	template <typename V, typename E>
	std::vector<E> *AdjacencyList<V, E>::incomingEdges(const V &vertex) const
	{
		typename std::list<Vertex>::iterator it =
			std::find_if(list->begin(), list->end(), [&vertex](const Vertex &v) -> bool { return v.name == vertex; });

		if (it != list->end())
			return new std::vector<E>((*it).inEdges.begin(), (*it).inEdges.end());
		else
			throw std::logic_error("Vertex doesn't exist\n");
	}

	template <typename V, typename E>
	E AdjacencyList<V, E>::getEdge(const V &vertex1, const V &vertex2) const
	{
		typename std::list<Vertex>::iterator i_vertex_1 =
			std::find_if(list->begin(), list->end(), [&vertex1](const Vertex &v) -> bool { return v.name == vertex1; });
		typename std::list<Vertex>::iterator i_vertex_2 =
			std::find_if(list->begin(), list->end(), [&vertex2](const Vertex &v) -> bool { return v.name == vertex2; });

		if (i_vertex_1 != list->end() && i_vertex_2 != list->end())
		{
			std::list<E> &v1 = i_vertex_1->outEdges;
			std::list<E> &v2 = i_vertex_2->inEdges;

			for (const E &e : v2)
				if (std::find(v1.begin(), v1.end(), e) != v1.end())
					return e;
		}

		throw std::logic_error("Edge doesn't exist\n");
	}

	template <typename V, typename E>
	std::vector<V> *AdjacencyList<V, E>::opposite(const V &vertex) const
	{
		typename std::list<Vertex>::iterator it =
			std::find_if(list->begin(), list->end(), [&vertex](const Vertex &v) -> bool { return v.name == vertex; });

		if (it != list->end())
		{
			std::vector<V> *oppositeVertices = new std::vector<V>();
			std::set<E> outEdges(it->outEdges.begin(), it->outEdges.end());

			for (const Vertex &vertices : *list)
				for (const E &e : vertices.inEdges)
					if (outEdges.find(e) != outEdges.end())
						oppositeVertices->emplace_back(vertices.name);

			return oppositeVertices;
		}
		else
			throw std::logic_error("Vertex doesn't exist\n");
	}

	template <typename V, typename E>
	std::vector<E> *AdjacencyList<V, E>::unique_edge() const
	{
		std::set<E> edgeSet;
		std::vector<E> *unique_edges = new std::vector<E>();

		std::for_each(list->begin(), list->end(),
					  [&unique_edges, &edgeSet](const Vertex &v) -> void
					  {
						  std::for_each(v.outEdges.begin(), v.outEdges.end(),
										[&unique_edges, &edgeSet](const E &e) -> void
										{ unique_edges->emplace_back(e); });
					  });

		std::transform(edgeSet.begin(), edgeSet.end(), std::back_inserter(*unique_edges),
					   [](const E &e) -> E { return e; });

		return unique_edges;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &AdjacencyList<V, E>::addVertex(const V &vertex)
	{
		if (this->containVertex(vertex))
			throw std::logic_error(vertex + " vertex already exists\n");

		list->emplace_back(vertex, std::list<E>(), std::list<E>());

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &AdjacencyList<V, E>::add_directed_Edge(const E &edge, const V &vertex1, const V &vertex2)
	{
		typename std::list<Vertex>::iterator i_vertex_1 =
			std::find_if(list->begin(), list->end(), [&vertex1](const Vertex &v) -> bool { return v.name == vertex1; });
		typename std::list<Vertex>::iterator i_vertex_2 =
			std::find_if(list->begin(), list->end(), [&vertex2](const Vertex &v) -> bool { return v.name == vertex2; });


		if (i_vertex_1 != list->end() && i_vertex_2 != list->end())
		{
			i_vertex_1->outEdges.emplace_back(edge);
			i_vertex_2->inEdges.emplace_back(edge);

			return *this;
		}
		else
			throw std::logic_error("Vertex doesn't exist\n");
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &AdjacencyList<V, E>::add_bidirected_Edge(const E &edge, const V &vertex1, const V &vertex2)
	{
		add_directed_Edge(edge, vertex1, vertex2);
		add_directed_Edge(edge, vertex2, vertex1);

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &AdjacencyList<V, E>::removeVertex(const V &vertex)
	{
		list->remove_if([&vertex](const Vertex &v) -> bool { return v.name == vertex; });

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &AdjacencyList<V, E>::removeEdge(const E &edge)
	{
		std::for_each(list->begin(), list->end(),
					  [&edge](Vertex &v) -> void
					  {
						  v.inEdges.remove_if([&edge](const E &e) -> bool { return e == edge; });
						  v.outEdges.remove_if([&edge](const E &e) -> bool { return e == edge; });
					  });

		return *this;
	}

	template <typename V, typename E>
	bool AdjacencyList<V, E>::containEdge(const E &edge) const
	{
		for (const Vertex &v : *list)
			if (std::find(v.inEdges.begin(), v.inEdges.end(), edge) != v.inEdges.end() ||
				std::find(v.outEdges.begin(), v.outEdges.end(), edge) != v.outEdges.end())
				return true;

		return false;
	}

	template <typename V, typename E>
	bool AdjacencyList<V, E>::containVertex(const V &vertex) const
	{
		return std::find_if(list->begin(), list->end(),
							[&vertex](const Vertex &v) -> bool { return v.name == vertex; }) != list->end();
	}

	template <typename V, typename E>
	size_t AdjacencyList<V, E>::numVertices() const
	{
		return list->size();
	}

	template <typename V, typename E>
	size_t AdjacencyList<V, E>::numEdges() const
	{
		size_t numEdges = 0;

		for (const Vertex &v : *list)
			numEdges += v.outEdges.size();

		return numEdges;
	}

	template <typename V, typename E>
	size_t AdjacencyList<V, E>::outDegree(const V &vertex) const
	{
		typename std::list<Vertex>::iterator it =
			std::find_if(list->begin(), list->end(), [&vertex](const Vertex &v) -> bool { return v.name == vertex; });

		if (it != list->end())
			return it->outEdges.size();
		else
			throw std::logic_error("Vertex doesn't exist\n");
	}

	template <typename V, typename E>
	size_t AdjacencyList<V, E>::inDegree(const V &vertex) const
	{
		typename std::list<Vertex>::iterator it =
			std::find_if(list->begin(), list->end(), [&vertex](const Vertex &v) -> bool { return v.name == vertex; });

		if (it != list->end())
			return it->inEdges.size();
		else
			throw std::logic_error("Vertex doesn't exist\n");
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &AdjacencyList<V, E>::print(std::ostream &ostream)
	{
		bool isFirst = true;

		for (const Vertex &v : *list)
		{
			ostream << "Vertex: " << v.name << "\nVertex inEdges: ";
			for (const E &edge : v.inEdges)
			{
				if (isFirst)
				{
					ostream << " " << edge;
					isFirst = false;
				}
				else
					ostream << " -> " << edge;
			}

			isFirst = true;
			ostream << "\nVertex outEdges: ";
			for (const E &edge : v.outEdges)
			{
				if (isFirst)
				{
					ostream << " " << edge;
					isFirst = false;
				}
				else
					ostream << " -> " << edge;
			}
			isFirst = true;
			ostream << '\n';
		}
		return *this;
	}

	template <typename V, typename E>
	AdjacencyList<V, E>::~AdjacencyList()
	{
		delete list;
	}

} // namespace Graph
