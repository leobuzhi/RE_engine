#ifndef VERTEX_H_
#define VERTEX_H_
#include "edge.h"
class Vertex {
public:
	Vertex();
	Vertex(int number);
	friend class AdjacentTable;
	friend class DFA;
private:
	int		number_;
	Vertex*		next_;
	Edge*		out_;
};
#endif 
