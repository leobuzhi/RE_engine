#include<iostream>
#include "dfa.h"
int main()
{
	DFA dfa_test;
	dfa_test.inputRegex();
	dfa_test.insertNode();
	dfa_test.regexToPost();
	dfa_test.getEdgeNumber();
	dfa_test.thompson();
	dfa_test.inputString();
	dfa_test.match();
	return 0;
}
