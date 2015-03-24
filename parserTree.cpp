#include "parserTree.hpp"
#include "helperFunctions_hash.hpp"
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
using namespace std;

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

parserTree shuntingYard(string exp){
	unordered_map<char, char> conversionTable;
	conversionTable[')']='(';
	conversionTable[']']='[';
	conversionTable['}']='{';

	stringstream parsing(exp);
	string empty = "";
	parserTree output;
	stack <char> operatorStack;
	dataType low;
	classType high;
	char temp='w';
	while(parsing.peek() != -1){
		if (parsing.peek()<='9' && parsing.peek()>='0'){
			parsing>>high;
			parsing.ignore();
			if(parsing.peek()=='X' || parsing.peek()=='x'){low=0;parsing.ignore();}
			else{parsing>>low;}
			output<<convert(make_pair(high, low));
		}else{
			parsing>>temp;
			if( temp!=')' && temp!=']' && temp!='}' ){
				operatorStack.push(temp);
			}else{
				while(operatorStack.top()!=conversionTable[temp]){output<<operatorStack.top();operatorStack.pop();}
				operatorStack.pop();
			}
		}
	}while(!operatorStack.empty()){output<<operatorStack.top(); operatorStack.pop();}
	return output;
}

bool operatorToken::eval(unordered_map<hashConv, bool> guide){
	if (content=='&' || content=='^')return right->eval(guide) && left->eval(guide);
	if (content=='|' || content=='v')return right->eval(guide) || left->eval(guide);
	return 0;
	}

void parserTree::operator <<(hashConv value){
	hashConvToken * token = new hashConvToken(value);
	tokenStack.push(token);
	return;
}

void parserTree::operator <<(char value){
	token *right;
	token *left;
	right = tokenStack.top(); tokenStack.pop();
	left = tokenStack.top(); tokenStack.pop();
	operatorToken *op = new operatorToken(value);
	op->right = right;
	op->left = left;
	right->parent = op;
	left->parent = op;
	tokenStack.push(op);
	return;
}

bool parserTree::eval(unordered_map<hashConv, bool> input){
	if (!tokenStack.size()) return true;
	token *base;
	base = tokenStack.top();
	return base->eval(input);
}