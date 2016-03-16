#include "edge.h"

Edge::Edge()
{
	position1_ = -1;
	position2_ = -1;
	link_ = nullptr;
}

Edge::Edge(int number, int position, char ch)
{
	position1_ = number;
	position2_ = position;
	weight_ = ch;
	link_ = nullptr;
}
