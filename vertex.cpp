#include "vertex.h"

Vertex::Vertex()
{
	number_ = -1;
	next_ = nullptr;
	out_ = nullptr;
}

Vertex::Vertex(int number)
{
	number_ = number;
	next_ = nullptr;
	out_ = nullptr;
}
