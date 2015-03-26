/* 
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Applied Artificial Intelligence and Pattern Recognition Research Group (GRPIAA)
 *
 */

#ifndef PARSERTREE_HPP
#define	PARSERTREE_HPP

#include <unordered_map>
#include <stack>
#include <iostream>

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

using namespace std;
//Deletion Structures Missing
class parserTree;

class token{
	friend class parserTree;
	public:
		virtual bool eval(unordered_map<hashConv, bool>)=0;
		virtual void print()=0;
	protected:
		token *parent;
		token *right;
		token *left;
};

class hashConvToken: public token{
	friend class parserTree;
	public:
		bool eval(unordered_map<hashConv, bool> guide){return guide[content];};
		void print(){cout<<(content>>16)<<':'<<((content<<16)>>16);}
	private:
		hashConvToken(){}
		hashConvToken(hashConv item){content = item;}
		hashConv content;
};

class operatorToken: public token{
	friend class parserTree;
	public:
		bool eval(unordered_map<hashConv, bool> guide);
		void print(){cout<<'(';left->print();cout<<content;right->print();cout<<')';}
	private:
		operatorToken(){}
		operatorToken(char item){content = item;}
		char content;

};

class parserTree{
	public:
		void operator <<(hashConv);
		void operator <<(char);
		bool eval(unordered_map<hashConv, bool>);
		void print(){if(tokenStack.size())tokenStack.top()->print();cout<<'\n';}
	private:
		stack<token*> tokenStack;
};

parserTree shuntingYard(string exp);

#endif	/* HELPERFUNCTIONS_HPP */
