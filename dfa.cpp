#include"dfa.h"
#include<string>
#include<iostream>
DFA::DFA()
{
	regex_ = new char[256];
	regexPost_ = new char[256];
	edgeNum_ = new char[256];
	edgeNumber_ = 0;
	DFAStatesNumber_ = 0;
	NFAStatesNumber_ = 0;
	NFATable = new AdjacentTable();
	DFATable = new AdjacentTable();
}

DFA::~DFA()
{
}

void DFA::inputRegex()
{
	std::cout << "Input regex expression:" << std::endl;
	std::cin >> regex_;
}
