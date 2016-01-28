#include "edge.h"

Edge::Edge()
{
	number_ = -1;
	position_ = -1;
	link_ = nullptr;
}

Edge::Edge(int number, int position, char ch)
{
	number_ = number;
	position_ = position;
	weight_ = ch;
	link_ = nullptr;
}
