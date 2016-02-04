#include"dfa.h"
#include<string>
#include<iostream>
#include<stack>
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
	int i = 0, j = 0;
	char ch, cl;
	strcpy(regexPost_, "\0");
	std::stack<char> *value = new std::stack<char>();
	while (!value->empty())
	{
		value->pop();
	}
	ch = regex_[i];
	value->push('#');
	while (ch != '\0')
	{
		if (ch == '(')
		{
			value->push(ch);
			ch = regex_[++i];
		}
		else if (ch == ')')
		{
			while (value->top() != '(')
			{
				regexPost_[j++] = value->top();
				value->pop();
			}
			value->pop();
			ch = regex_[++i];
		}
		else if (ch=='|'||ch=='*'||ch=='.')
		{
			cl = value->top();
			while (precedence(cl) >= precedence(ch))
			{
				regexPost_[j++] = cl;
				value->pop();
				cl = value->top();
			}
			value->push(ch);
			ch = regex_[++i];
		}
		else 
		{
			regexPost_[j++] = ch;
			ch = regex_[++i];
		}
	}
	ch = value->top();
	value->pop();
	while (ch == '|' || ch == '*' || ch == '.')
	{
		regexPost_[j++] = ch;
		ch = value->top();
		value->pop();
	}
	regexPost_[j] = '\0';
	while (!value->empty())
	{
		value->pop();
	}
	std::cout << "Transform regexPost :" << regexPost_ << std::endl << "String length :" << strlen(regexPost_) << std::endl;
}
void DFA::getEdgeNumber()
{
	int i = 0, j;
	edgeNumber_ = 0;
	while (regexPost_[i] != '\0')
	{
		if (regexPost_[i] == '.' || regexPost_[i] == '|' || regexPost_[i] == '*')
		{
			i++;
			continue;
		}
		for (j = 0; j != edgeNumber_; j++)
		{
			if (regexPost_[i] == edgeNum_[j])
			{
				break;
			}
		}
		if (j == edgeNumber_)
		{
			edgeNum_[edgeNumber_] = regexPost_[i];
			edgeNumber_++;
		}
		i++;
	}
	edgeNum_[edgeNumber_] = '\0';
	std::cout << "get char list:" << std::endl;
	for (i = 0; i != edgeNumber_; i++)
	{
		std::cout << edgeNum_[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "char numbers: " << edgeNumber_ << std::endl;
}

void DFA::match()
{
}


