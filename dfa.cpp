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
	delete regex_;
	delete regexPost_;
	NFATable->clear();
	DFATable->clear();
}

void DFA::inputRegex()
{
	std::cout << "Input regex expression:" << std::endl;
	std::cin >> regex_;
}

int DFA::precedence(char symbol)
{
	int priority_;
	switch (symbol)
	{
	case '|':priority_ = 1; break;
	case '.':priority_ = 2; break;
	case '*':priority_ = 3; break;
	default:priority_ = 0; break;
	}
	return priority_;
}

void DFA::insertNode()
{
}

void DFA::regexToPost()
{
}
