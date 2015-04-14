/* 
 * File:   sequence_hash.hpp
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
 */

#ifndef PARSERTREE_HPP
#define	PARSERTREE_HPP

#include <unordered_map>
#include <stack>

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
	protected:
		token *parent;
		token *right;
		token *left;
};

class hashConvToken: public token{
	friend class parserTree;
	public:
		bool eval(unordered_map<hashConv, bool> guide){return guide[content];};
	private:
		hashConvToken(){}
		hashConvToken(hashConv item){content = item;}
		hashConv content;
};

class operatorToken: public token{
	friend class parserTree;
	public:
		bool eval(unordered_map<hashConv, bool> guide);
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
	private:
		stack<token*> tokenStack;
};

parserTree shuntingYard(string exp);

#endif	/* HELPERFUNCTIONS_HPP */

