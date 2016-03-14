#include"adjacentTable.h"
#include<iostream>
AdjacentTable::AdjacentTable()
{
	vertexNums_ = 1;
	edgeNums_ = 0;
	startVertex_ = new Vertex();
}

AdjacentTable::~AdjacentTable()
{
	Vertex* p;
	Edge*   q;
	p = startVertex_;
	for (int i = 0; i != vertexNums_; i++)
	{
		q = p->out_;
		while (q)
		{
			p->out_ = q->link_;
			delete q;
			q = p->out_;
		}
		p = p->next_;
	}
}

int AdjacentTable::getValueByPos(int position) const 
{
	if (position >= 0 && position < vertexNums_)
	{
		Vertex *p = startVertex_;
		for (int i = 0; i != position; i++)
		{
			p = p->next_;
		}
		return p->number_;
	}
	return -1;
}

int AdjacentTable::getPosByValue(int value) const
{
	Vertex *p = startVertex_;
	for (int i = 0; i != vertexNums_; i++)
	{
		if (p->number_ == value)
			return i;
		p = p->next_;
	}
	return -1;
}

char AdjacentTable::getWeightByPos(int position1, int position2) const
{
	if (position1 >= 0 && position2 >= 0 && position1 < vertexNums_&&position2 < vertexNums_)
	{
		Vertex *p = startVertex_;
		for (int i = 0; i != position1; i++)
		{
			p = p->next_;
		}
		Edge *q = p->out_;
		while (q)
		{
			if (q->position2_ == position2)
				return q->weight_;
			q = q->link_;
		}
	}
	return '#';
}

char AdjacentTable::getWeightByValue(int value1, int value2)	const
{
	return getWeightByPos(getPosByValue(value1), getPosByValue(value2));
}

void AdjacentTable::setValue(int value,int position) 
{
	if (position < 0 || position >= vertexNums_)
	{
		std::cout << "Illegal setting(wrong position)." << std::endl;
		exit(1);
	}
	Vertex *p = startVertex_;
	for (int i = 0; i != position; i++)
	{
		p = p->next_;
	}
	p->number_ = value;
}

void AdjacentTable::insertVertex(int value)
{
	int position = getPosByValue(value);
	if (position >= 0 && position < vertexNums_)
	{
		std::cout << "Illegal setting(wrong value)." << std::endl;
		exit(1);
	}
	Vertex *p = startVertex_;
	while (p->next_)
		p=p->next_;
	Vertex *addVertex = new Vertex(value);
	p->next_ = addVertex;
	vertexNums_++;
}

void AdjacentTable::insertEdgeByPos(int position1_, int position2_, char weight)
{
	if (position1_ < 0 || position1_ >= vertexNums_ || position2_ < 0 || position2_ >= vertexNums_)
	{
		std::cout << "Illegal insert:the vertex doesn't exist." << std::endl;
		exit(1);
	}
	Vertex *p = startVertex_;
	for (int i = 0; i != position1_; i++)
	{
		p = p->next_;
	}
	Edge *q = p->out_;
	Edge *addEdge = new Edge(getValueByPos(position2_), position2_, weight);
	if (!q)
	{
		p->out_ = addEdge;
		edgeNums_++;
		return ;
	}
	while (q->position1_ != position2_&&q->link_)
	{
		q = q->link_;
	}
	if (q->position1_ == position2_)
	{
		std::cout << "Illegal insert:the vertex has existed." << std::endl;
		exit(1);
	}
	if (!q->link_)
	{
		q->link_ = addEdge;
		edgeNums_++;
	}
}

void AdjacentTable::insertEdgeByValue(int value1, int value2, char weight)
{
	insertEdgeByPos(getPosByValue(value1), getPosByValue(value2),weight);
}

void AdjacentTable::removeAllEdges()
{
	Vertex *p = startVertex_;
	for (int i = 0; i != vertexNums_; i++)
	{
		Edge *q = p->out_;
		while (q)
		{
			p->out_ = q->link_;
			delete q;
			q = p->out_;
		}
		p = p->next_;
		if (p == nullptr)
			break;
	}
	edgeNums_ = 0;
}

void AdjacentTable::clear()
{
	removeAllEdges();
	Vertex *p = startVertex_->next_;
	while (p)
	{
		startVertex_->next_ = p->next_;
		delete p;
		p = startVertex_->next_;
	}
	vertexNums_ = 1;
}
