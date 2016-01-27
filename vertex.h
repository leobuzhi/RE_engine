#ifndef VERTEX_H_
#define VERTEX_H_
#include "edge.h"
class Vertex {
public:
	Vertex();
	Vertex(int number);
	~Vertex();
private:
	int		number_;
	Vertex*		next_;
	Edge*		out_;
};
#endif 
