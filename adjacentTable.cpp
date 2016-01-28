#include"adjacentTable.h"

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

}

int AdjacentTable::getPosByValue(int value) const
{

}

char AdjacentTable::getWeightByPos(int value1,int value2) const
{

}

char AdjacentTable::getWeightByValue(int v1,int v2)	const
{

}

void AdjacentTable::setValue(int value,int position) 
{

}

void AdjacentTable::insertVertex(int value)
{

}

void AdjacentTable::insertEdgeByPos(int v1, int v2, char weight)
{

}

void AdjacentTable::insertEdgeByValue(int value1, int value2, char weight)
{

}

void AdjacentTable::removeAllEdges()
{

}

void AdjacentTable::clear()
{

}
