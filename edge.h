#ifndef EDGE_H_
#define EDGE_H_
class Edge {
public:
	Edge();
	Edge(int number,int position,char weight);
	friend class AdjacentTable;
private:
	int		position1_;
	int		position2_;
	char		weight_;
	Edge*		link_;
};
#endif 
