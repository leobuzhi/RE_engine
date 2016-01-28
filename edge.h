#ifndef EDGE_H_
#define EDGE_H_
class Edge {
public:
	Edge();
	Edge(int number,int position,char weight);
	~Edge();

private:
	int		number_;
	int		position_;
	char		weight_;
	Edge*		link_;
};
#endif 