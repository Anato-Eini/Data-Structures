# Graph ADT

* _addEdge (name, weight, vertex1, vertex2)_: Add edge with its name, weight and its two vertices


* _addVertex (name)_: Add vertex with its name


* _containEdge (edge)_: Returns a boolean if an edge is present or not;


* _containVertex (vertex)_:Returns a boolean value if a vertex is present or not;


* <i>numVertices ( )</i>: Returns the number of vertices of the graph.


* <i>vertices ( )</i>: Returns an iteration of all the vertices of the graph.


* <i>numEdges ( )</i>: Returns the number of edges of the graph.


* <i>edges ( )</i>: Returns an iteration of all the edges of the graph.


* <i>getEdge (u, v)</i>: Returns the edge from vertex u to vertex v, if one
exists; otherwise return null. For an undirected graph, there is no
difference between _getEdge (u, v)_ and _getEdge (v, u)_.


* <i>endVertices (e)</i>: Returns an array containing the two endpoint vertices
of edge e. If the graph is directed, the first vertex is the origin and the
second is the destination.

* <i>opposite (v, e)</i>: For edge e incident to vertex v, returns the other
vertex of the edge; an error occurs if e is not incident to v.

  
* <i>outDegree (v)</i>: Returns the number of outgoing edges from vertex v.


* <i>inDegree (v)</i>: Returns the number of incoming edges to vertex v. For
an undirected graph, this returns the same value as does
_outDegree (v)._


* _outgoingEdges (v)_: Returns an iteration of all outgoing edges from
vertex v.


* _incomingEdges (v)_: Returns an iteration of all incoming edges to
vertex v. For an undirected graph, this returns the same collection as
does _outgoingEdges (v)_.


**To showcase each core concepts of different strategies for implementing graphs, we'll implement them using 
undirected graph**