#include<iostream>
#include "dfa.h"
int main()
{
	std::cout << "input n :" << std::endl;
	int n;
	std::cin >> n;
	while (n--)
	{
		DFA dfa_test;
		dfa_test.inputRegex();
		dfa_test.insertNode();
		dfa_test.regexToPost();
		dfa_test.getEdgeNumber();
		dfa_test.thompson();
		dfa_test.NFAToDFA();
		dfa_test.inputString();
		dfa_test.match();
	}
	return 0;
}
