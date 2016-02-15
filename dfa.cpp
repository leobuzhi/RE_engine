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
	std::stack<char>  value;
	while (!value.empty())
	{
		value.pop();
	}
	ch = regex_[i];
	value.push('#');
	while (ch != '\0')
	{
		if (ch == '(')
		{
			value.push(ch);
			ch = regex_[++i];
		}
		else if (ch == ')')
		{
			while (value.top() != '(')
			{
				regexPost_[j++] = value.top();
				value.pop();
			}
			value.pop();
			ch = regex_[++i];
		}
		else if (ch=='|'||ch=='*'||ch=='.')
		{
			cl = value.top();
			while (precedence(cl) >= precedence(ch))
			{
				regexPost_[j++] = cl;
				value.pop();
				cl = value.top();
			}
			value.push(ch);
			ch = regex_[++i];
		}
		else 
		{
			regexPost_[j++] = ch;
			ch = regex_[++i];
		}
	}
	ch = value.top();
	value.pop();
	while (ch == '|' || ch == '*' || ch == '.')
	{
		regexPost_[j++] = ch;
		ch = value.top();
		value.pop();
	}
	regexPost_[j] = '\0';
	while (!value.empty())
	{
		value.pop();
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

void DFA::thompson()
{
	int i, j;
	char ch;
	int s1, s2;
	std::stack<int> states;
	while (!states.empty())
	{
		states.pop();
	}
	if (strlen(regexPost_) < 1)
	{
		std::cout << "No regex expression find." << std::endl;
		exit(1);
	}
	i = 1, j = 0;
	ch = regexPost_[j];
	while (ch != '\0')
	{
		if (ch == '.')
		{
			s2 = states.top();
			states.pop();
			int value1 = states.top();
			states.pop();
			int value2 = states.top();
			states.pop();
			NFATable->insertEdgeByValue(value2, value1, '~');
			states.push(s1);
			states.push(s2);
		}
		else if (ch == '*')
		{
			s2 = states.top();
			states.pop();
			s1 = states.top();
			states.pop();
			NFATable->insertVertex(i);
			NFATable->insertVertex(i+1);
			NFATable->insertEdgeByValue(i, i + 1, '~');
			NFATable->insertEdgeByValue(s2, s1, '~');
			NFATable->insertEdgeByValue(i, s1, '~');
			NFATable->insertEdgeByValue(s2, i + 1, '~');
			s1 = i;
			s2 = i + 1;
			states.push(s1);
			states.push(s2);
			i += 2;
		}
		else if (ch == '|')
		{
			s2 = states.top();
			states.pop();
			int value1 = states.top();
			states.pop();
			int value2 = states.top();
			states.pop();
			s1 = states.top();
			states.pop();
			NFATable->insertVertex(i);
			NFATable->insertVertex(i + 1);
			NFATable->insertEdgeByValue(i, s1, '~');
			NFATable->insertEdgeByValue(i, value1, '~');
			NFATable->insertEdgeByValue(value2, i + 1, '~');
			NFATable->insertEdgeByValue(s2, i + 1, '~');
			s1 = i;
			s2 = i + 1;
			states.push(s1);
			states.push(s2);
			i += 2;
		}
		else
		{
			NFATable->insertVertex(i);
			NFATable->insertVertex(i + 1);
			NFATable->insertEdgeByValue(i, i + 1, ch);
			s1 = i;
			s2 = i + 1;
			states.push(s1);
			states.push(s2);
			i += 2;
		}
		j++;
		ch = regexPost_[j];
	}
	s2 = states.top();
	states.pop();
	s1 = states.top();
	states.pop();
	NFAStatesNumber_ = s2 + 1;
}

void initNFANode(int(*a)[100])
{
	for (int i = 0; i <= 100; i++)
	{
		for (int j = 0; j <= 100; j++)
		{
			a[i][j] = 0;
		}
	}
}

int judge(int states, int jud[][100])
{
	int i, j, sum;
	i = 2;
	while (jud[i][0])
	{
		sum = 0;
		j = 0;
		while (jud[i][j])
		{
			if (jud[states][j] == jud[i][j])
				sum++;
			j++;
		}
		if (sum == j)
			return i;
		i++;
	}
	return states;
}

void setAcceptStates(int *states)
{
	for (int i = 0; i <= 500; i++)
	{
		states[i] = 0;
	}
}

void DFA::NFAToDFA()
{
	int states;
	int update = 0;
	int vertexNode[1001] = { 0 };
	std::stack<int> DFAStates;
	std::stack<int> NFANode;
	int allNFANodes[100][100];
	initNFANode(allNFANodes);
	int pointer = 0;
	int edgeNums = NFATable->edgeNums_;
	for (int i = 0; i != edgeNums; i++)
		vertexNode[i] = 0;
	states = 1;
	DFATable->insertVertex(1);
	for (int i = 0; i != edgeNumber_; i++)
	{
		char weight = edgeNum_[i];
		Vertex *p = new Vertex;
		p = NFATable->startVertex_;
		for (int j = 0; j != states; j++)
			p = p->next_;
		if (p->out_->link_ == nullptr)
		{
			if (p->out_->weight_ == weight&&vertexNode[p->out_->position2_] == 0)
				NFANode.push(p->out_->position2_);
			vertexNode[p->out_->position2_] = 1;
		}
		if (p->out_->link_ != nullptr)
		{
			if (p->out_->weight_ == weight&&vertexNode[p->out_->position2_] == 0)
				NFANode.push(p->out_->position2_);
			vertexNode[p->out_->position2_] = 1;
			Edge *link = p->out_->link_;
			while (link != nullptr)
			{
				if (p->out_->weight_ == weight&&vertexNode[p->out_->position2_] == 0)
					NFANode.push(p->out_->position2_);
				vertexNode[p->out_->position2_] = 1;
				link = link->link_;
			}
		}
		if (NFANode.empty())
			continue;
		states++;
		DFAStates.push(states);
		while (!NFANode.empty())
		{
			int top = NFANode.top();
			NFANode.pop();
			allNFANodes[states][pointer] = top;
			pointer++;
			p = NFATable->startVertex_;
			for (int j = 0; j != top; j++)
				p = p->next_;
			if (p->out_&&p->out_->link_ == nullptr)
			{
				if (p->out_->weight_ == '~'&&vertexNode[p->out_->position2_] == 0)
					NFANode.push(p->out_->position2_);
				vertexNode[p->out_->position2_] = 1;
			}
			else if(p->out_)
			{
				if (p->out_->weight_ == '~'&&vertexNode[p->out_->position2_] == 0)
					NFANode.push(p->out_->position2_);
				vertexNode[p->out_->position2_] = 1;
				Edge *linkNode = p->out_->link_;
				while (linkNode != nullptr)
				{
					if (linkNode->weight_ == '~'&&vertexNode[linkNode->position2_] == 0)
						NFANode.push(linkNode->position2_);
					vertexNode[p->out_->position2_] = 1;
					linkNode = linkNode->link_;
				}
			}
		}
		DFATable->insertVertex(states);
		DFATable->insertEdgeByValue(1, states, edgeNum_[i]);
	}
	
	while (!DFAStates.empty())
	{
		DFAStatesNumber_ = DFAStates.top();
		DFAStates.pop();
		for (int j = 0; j != edgeNumber_; j++)
		{
			int i = 0;
			char weight = edgeNum_[j];
			while (allNFANodes[NFAStatesNumber_][i] != 0)
			{
				int vertexNode[1001] = { 0 };
				Vertex *p = new Vertex;
				p = NFATable->startVertex_;
				for (int k = 0; k != allNFANodes[NFAStatesNumber_][i]; k++)
					p = p->next_;
				i++;
				if (p->out_ == nullptr)
					continue;
				if (p->out_->link_ == nullptr)
				{
					if (p->out_->weight_ == weight&&vertexNode[p->out_->position2_] == 0)
						NFANode.push(p->out_->position2_);
					vertexNode[p->out_->position2_] = 1;
				}
				if (p->out_->link_ != nullptr)
				{
					if (p->out_->weight_ == weight&&vertexNode[p->out_->position2_] == 0)
						NFANode.push(p->out_->position2_);
					Edge *link = p->out_->link_;
					while (link != nullptr)
					{
						if (p->out_->weight_ == weight&&vertexNode[p->out_->position2_] == 0)
							NFANode.push(p->out_->position2_);
						vertexNode[p->out_->position2_] = 1;
						link = link->link_;
					}
				}
				if (NFANode.empty())
					continue;
				states++;
				pointer = 0;
				while (!NFANode.empty())
				{
					int top = NFANode.top();
					NFANode.pop();
					allNFANodes[states][pointer] = top;
					pointer++;
					p = NFATable->startVertex_;
					for (int j = 0; j != top; j++)
						p = p->next_;
					if (p->out_&&p->out_->link_ == nullptr)
					{
						if (p->out_->weight_ == '~'&&vertexNode[p->out_->position2_] == 0)
							NFANode.push(p->out_->position2_);
						vertexNode[p->out_->position2_] = 1;
					}
					else if (p->out_)
					{
						if (p->out_->weight_ == '~'&&vertexNode[p->out_->position2_] == 0)
							NFANode.push(p->out_->position2_);
						vertexNode[p->out_->position2_] = 1;
						Edge *linkNode = p->out_->link_;
						while (linkNode != nullptr)
						{
							if (linkNode->weight_ == '~'&&vertexNode[linkNode->position2_] == 0)
								NFANode.push(linkNode->position2_);
							vertexNode[p->out_->position2_] = 1;
							linkNode = linkNode->link_;
						}
					}
				}
				int sign = states;
				states = judge(states, allNFANodes);
				if (sign == states)
				{
					DFATable->insertVertex(states);
					DFAStates.push(states);
				}
				DFATable->insertEdgeByValue(NFAStatesNumber_, states, edgeNum_[j]);
				states = sign;
			}
		}
	}
	NFAStatesNumber_ = states;
	DFAStatesNumber_ = DFATable->vertexNums_ - 1;

	DFATable->startVertex_ = DFATable->startVertex_->next_;
	NFATable->startVertex_ = NFATable->startVertex_->next_;

	setAcceptStates(NFAAcceptStates);
	setAcceptStates(DFAAcceptStates);

	Vertex *p = NFATable->startVertex_;
	int vertexNums = NFATable->vertexNums_;
	for (int i = 1; i != vertexNums; i++)
	{
		if (p->out_ == nullptr)
			NFAAcceptStates[i] = i;
		p = p->next_;
	}
	for (int i = 2; i <= states; i++)
	{
		int vertexNums = NFATable->vertexNums_;
		for (int j = 0; j != vertexNums; j++)
		{
			int k = 0;
			while (allNFANodes[i][k] != 0)
			{
				for (int n = 0; vertexNums; n++)
				{
					if (NFAAcceptStates[n] == allNFANodes[i][k])
						NFAAcceptStates[i] = i;
				}
				k++;
			}
		}
	}
	int tag;
	for (int i = 0; i <= states; i++)
	{
		if (DFAAcceptStates[i] != 0)
			tag = judge(DFAAcceptStates[i], allNFANodes);
		if (tag != DFAAcceptStates[i])
			DFAAcceptStates[i] = 0;
	}
}

void DFA::match()
{
}


