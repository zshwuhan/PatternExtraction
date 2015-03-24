/* 
 * File:   sequence_hash.hpp
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
 */

#include "sequence_hash.hpp"
#include "seq_pointer_hash.hpp"
#include "helperFunctions_hash.hpp"
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

using namespace std;



ostream &operator << (ostream &osin, container hashmap){
    if (hashmap.size()==0) return osin;
    if (hashmap.size()==1){
        osin<<((hashmap.begin())->first)<<':'<<(hashmap.begin()->second);}
    else {
        osin<<'(';
        container::iterator beg, forward, endoru;
        beg = hashmap.begin(); 
        forward = hashmap.begin(); 
        endoru = hashmap.end();
        if (beg!=endoru){
            ++forward;
            while(forward!=endoru){
                osin<<((*beg).first)<<':'<<(((*beg).second));
                osin<<",";
                ++forward;
                ++beg;
            }
        }osin<<((*beg).first)<<':'<<(((*beg).second));  
        
        osin<<')';
    }
    return osin;
}

ostream &operator << (ostream &osin, sequence_hash &seq){
    vector<container> iterable = seq.elements;
    vector<container>::iterator beg, forward, endoru;
    beg = iterable.begin(); forward = iterable.begin(); endoru = iterable.end();
    if (beg==endoru) return osin;
    ++forward;
    while(forward!=endoru){
        osin<<*beg<<", ";
        ++forward;
        ++beg;
    }osin<<*beg;
    return osin;
}

sequence_hash::sequence_hash(){
    vector <container> copy;
    this->elements = copy;
    this->size=0;
    this->tailMax = 0;
}

sequence_hash::sequence_hash(vector <container> input) {
    vector <container> copy = input;
    this->elements = copy;
    this->size = copy.size();
        vector <classType> keys;
    if (!input.empty()){    
        for(unordered_map<classType,dataType>::iterator it = elements.rbegin()->begin(); it != elements.rbegin()->end(); ++it) {
            keys.push_back(it->first);}
                vector <classType>::iterator iter;
        iter = max_element(keys.begin(), keys.end());
                if (keys.begin() != keys.end())
            tailMax = *iter;
        else tailMax = 0;
    }else tailMax=0;
    }

sequence_hash::sequence_hash(const sequence_hash& orig) {
    this->elements = orig.elements;
    this->size = orig.size;
    this->tailMax = orig.tailMax;
}

sequence_hash::~sequence_hash() {
}

sequence_hash sequence_hash::append(classType var, dataType item){
    container element; 
    element.emplace(var, item);
        sequence_hash ritorno (this->elements);
        (ritorno.elements).push_back(element);
    ritorno.size = ritorno.size + 1;
    ritorno.tailMax = var;
    return ritorno;
}
sequence_hash sequence_hash::assemble(classType var, dataType item){
    sequence_hash ritorno (this->elements);
    if (((ritorno.elements).rbegin())==((ritorno.elements).rend())){
        return (ritorno.append(var, item));}
    (*((ritorno.elements).rbegin())).emplace(var, item);
    ritorno.tailMax = (ritorno.tailMax>var)?ritorno.tailMax:var;
    return ritorno;
}

//Better way to handle empty set is required
container sequence_hash::tail(){
	if (elements.rbegin()!=elements.rend()){
		container ritorno = (*(elements.rbegin()));
		return ritorno;
	}
	container empty;
	return empty;
}

seq_pointer_hash sequence_hash::begin(){
    return seq_pointer_hash(const_cast<sequence_hash *> (this), elements.begin(), elements.end());
}

seq_pointer_hash sequence_hash::end(){
    return seq_pointer_hash(const_cast<sequence_hash *> (this), elements.end(), elements.end());
}

int sequence_hash::empty(){
    return (size==0);
}

pairSet sequence_hash::itemList(){
    pairSet listing;
    vector<container>::iterator vStart, vEnd; vStart=elements.begin(); vEnd=elements.end();
    while(vStart!=vEnd){
        listing.insert(vStart->begin(), vStart->end());
        ++vStart;
    }return listing;
}
//______________________________________________________________________________________
//______________________________________________________________________________________
//______________________________________________________________________________________
//_________________________________________PARAMETRISED_________________________________
//______________________________________________________________________________________
//______________________________________________________________________________________

sequence_hash sequence_hash_parser::append(classType var, dataType item){
    container element; 
    element.emplace(var, item);
	sequence_hash_parser ritorno = *this;
	//PASS OVER CHILD ATTRIBUTES
	ritorno.evaluator = evaluator;
	ritorno.tokenSet = tokenSet;
	ritorno.validity = validity;
	//___________________________
	(ritorno.elements).push_back(element);
    ritorno.size = ritorno.size + 1;
    ritorno.tailMax = var;
	//VALIDITY OPERATIONS
	if(!validity){
		ritorno.tokenSet[convert(make_pair(var, item))]=true;
		ritorno.tokenSet[convert(make_pair(var, 0))]=true;
		ritorno.validity = ritorno.evaluator.eval(ritorno.tokenSet);
	}
	//___________________________
    return ritorno;
}

sequence_hash sequence_hash_parser::assemble(classType var, dataType item){
    sequence_hash_parser ritorno = *this;
	//PASS OVER CHILD ATTRIBUTES
	ritorno.evaluator = evaluator;
	ritorno.tokenSet = tokenSet;
	ritorno.validity = validity;
	//___________________________
    if (((ritorno.elements).rbegin())==((ritorno.elements).rend())){
        return (ritorno.append(var, item));}
    (*((ritorno.elements).rbegin())).emplace(var, item);
    ritorno.tailMax = (ritorno.tailMax>var)?ritorno.tailMax:var;
	//VALIDITY OPERATIONS
	if(!validity){
		ritorno.tokenSet[convert(make_pair(var, item))]=true;
		ritorno.tokenSet[convert(make_pair(var, 0))]=true;
		ritorno.validity = ritorno.evaluator.eval(ritorno.tokenSet);
	}
	//___________________________
    return ritorno;
}

sequence_hash_parser::sequence_hash_parser(const sequence_hash_parser& orig) {
    this->elements = orig.elements;
    this->size = orig.size;
    this->tailMax = orig.tailMax;
	this->validity = orig.validity;
	this->evaluator = orig.evaluator;
	this->tokenSet = orig.tokenSet;
}