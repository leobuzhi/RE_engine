# RE_engine
#Author:  leobuzhi
#Email:   leobuzhi@gmail.com


A simple Regular Expression engine


OS:
	Linux,*nix
Process:
	Re->NFA->DFA
Algorithm:
	Thompson algorithm
	Re->NFA
	NFA->DFA
	Subset Construction Method
Example:
	re:ab(b|c)a*
	string:dabbd success  
	result:abb   success
	string:qabcaaaaa
	result:abb   success
	string:sabaaaaa
	result:      failure
