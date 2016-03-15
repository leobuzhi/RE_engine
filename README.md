RE_engine



Author:  leobuzhi
Email:   leobuzhi@gmail.com
A simple Regular Expression engine
OS:					
	Linux,*nix
Process:				
	Re->NFA->DFA
Algorithm:
	Re->NFA	
	Thompson algorithm		
	NFA->DFA			
	Subset Construction Method
Example:				
	re:ab(b|c)a*			
	string:dabbd success  		
	result:abb   success		
	string:qabcaaaaa		
	result:abcaaaaa   success		
	string:sabaaaaa			
	result:      failure
Lincense:				
	MIT

