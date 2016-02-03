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
	int i = 0, j, len;
	len = strlen(regex_);
	int length = len;
	len--;
	while (len--)
	{
		if(((regex_[i]!='('&&regex_[i]!='.'&&regex_[i]!='|')||
			regex_[i]==')'||regex_[i]=='*')&&
			(regex_[i+1]!=')'&&regex_[i+1]!='.'&&regex_[i+1]!='|'&&regex_[i+1]!='*'))
		{
			for (j = length; j > i; j--)
			{
				regex_[j + 1] = regex_[j];
			}
			regex_[i + 1] = '.';
			length++;
			regex_[length] = '\0';
			i++;
		}
	}
}

void DFA::regexToPost()
{
}

void DFA::match()
{
}

void DFA::regexToPost()
{
}
