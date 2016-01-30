#include"dfa.h"
#include<string>
#include<iostream>
DFA::DFA()
{

}

DFA::~DFA()
{
}

void DFA::inputRegex()
{
	std::cout << "Input regex expression:" << std::endl;
	std::cin >> regex_;
}
