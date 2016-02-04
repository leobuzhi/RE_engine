#include<iostream>
#include "dfa.h"
int main()
{
	DFA dfa_test;
	dfa_test.inputRegex();
	dfa_test.insertNode();
	dfa_test.regexToPost();
	return 0;
}
