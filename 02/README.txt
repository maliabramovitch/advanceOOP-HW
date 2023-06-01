Malka Abramovitch
314723586 

class DriectedGraph<V-vertex, E-edge>:
	generic class for representing directed graph.
	implemented as Adjacency Matrix with deque<V,E>.
	fileds:
		- std::deque<std::deque<E>> graph - Adjacency Matrix
		- td::deque<V> vertex - for the order of the vertices in graph-> the edge- graph[i][j] == (vertex[i], vertex[j])
	
class Ship:
	class for holding the files data.
	there is no need for the big 5, because coping or moving the file data keeper makes no sence.
	sub structs:
		- OriginPort- for the firts line of the file.
		- DockingPort- for the other lines in the file.
	fileds:
		- OriginPort origin.
		- deque<DockingPort> dockingPort
		- unsigned int containersUnloaded - The amount of containers the ship left the port of origin with
		
class Time:
	for time calculating.
	
class BoggieLever:
	Implements the queries.
	fields:
		- std::string outFileName
		- DirectedGraph<std::string, int> containers
		- DirectedGraph<std::string, double> cruiseTime
		- std::deque<Ship> ships
	
class Terminal:
	for comunicating with the user.
	