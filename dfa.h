#ifndef DFA_H_
#define DFA_H_
#include<string>
#include "adjacentTable.h"
class DFA {
public:
	DFA();
	~DFA();
	void			inputRegex();
	void			insertNode();
	void			regexToPost();
	void			match();
	void			inputString();
	void			getEdgeNumber();
	void			thompson();
	void			NFAToDFA();
	void			getAcceptState();
	int			precedence(char symbol);
	int			judgeVertex(char ch);
private:
	char*			regex_;
	char*			regexPost_;
	char*			edgeNum_;
	int			edgeNumber_;
	std::string		input_;
	std::string     	matchout_;
	int			NFAStatesNumber_;
	int			DFAStatesNumber_;
	int			NFAAcceptStates[500];
	int			DFAAcceptStates[500];
	int			NFANodeAll[100][100];
	AdjacentTable*		DFATable;
	AdjacentTable*		NFATable;
	char			DFAStates[101][101];
	int			miniDFAStates[101][101];
};
#endif 
