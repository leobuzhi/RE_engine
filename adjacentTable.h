#ifndef ADJACENTABLE_H_
#define ADJACENTABLE_H_
#include "vertex.h"
class AdjacentTable {
public:
	AdjacentTable();
	~AdjacentTable();
	void		setValue(int value,int pos);
	void		insertVertex(int value);
	void		insertEdgeByPos(int v1,int v2,char weight);
	void		insertEdgeByValue(int value1, int value2, char weight);
	void		removeAllEdges();
	void		clear();
	void		outPutNFA();
	int*		closure(int* t);
	int*		move(int* t, char ch);
	int		getPosByValue(int value) const;
	int		getValueByPos(int pos) const;
	char		getWeightByValue(int v1,int v2) const;
	char		getWeightByPos(int value1, int value2) const;

private:
	Vertex*		startVertex_;
	int		vertexNum_;
	int		edgeNum_;
};
#endif 
