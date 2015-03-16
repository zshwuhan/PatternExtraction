/* 
 * File:   seq_pointer.cpp
 * Author: Agustin
 * 
 * Created on 22 February 2015, 14:05
 */
//UNFINISHED
#include <iostream>
#include "seq_pointer_hash.hpp"
#include <algorithm>
#include <unordered_map>
#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

seq_pointer_hash::seq_pointer_hash():source(NULL){
}

seq_pointer_hash::seq_pointer_hash(sequence_hash * seq, vector<container>::iterator iter, vector<container>::iterator ender):source(seq){
    wildcard = false;
    current = iter;
    end = ender;
}

seq_pointer_hash::seq_pointer_hash(const seq_pointer_hash& orig):source(orig.source){
    wildcard = orig.wildcard;
    current = orig.current;
    end = orig.end;
}

seq_pointer_hash::~seq_pointer_hash() {
}

int seq_pointer_hash::operator ==(seq_pointer_hash &dest){
    return current==dest.current;
}

int seq_pointer_hash::operator !=(seq_pointer_hash &dest){
    return current!=dest.current;
}

void seq_pointer_hash::__dump__(){
    cout<<"{Elements: "<<" Wildcard: "<< wildcard << "}\n";
    return;
}

void seq_pointer_hash::skip(){
    if (current!=end)++current;
    wildcard=false;
    return;
}

//lower_bound from algorithm with later comparison for find
seq_pointer_hash seq_pointer_hash::proyect(classType varClass, dataType varData){
    seq_pointer_hash result = (*this);
    if (result.getWildcard())result.skip();
    seq_pointer_hash trueEnd = source->end();
    container::iterator ritorno;
    while(result.current != result.end){
        if( result.current->count(varClass) && (*(result.current))[varClass]==varData){
            result.wildcard = true;
            break;
        }
        result.skip();
    }return result;
}

int match(container &subseq, container &seq){
    container::iterator match = subseq.begin();
    container::iterator goal = subseq.end();
    while(match != goal){
        if (!(seq.count(match->first) && seq[match->first]==match->second)) return 0;
        ++match;
    }
    return 1;
}


//CLEAR UNCLEAN PATCHING
seq_pointer_hash seq_pointer_hash::proyect(classType varClass, dataType varData, sequence_hash &prefix){
    seq_pointer_hash result = (*this);
    vector<container>::iterator ritorno;
    //simple case if we already have wildcarded
    if (result.getWildcard()){
        if( result.current->count(varClass) && ( (*(result.current))[varClass] == varData )  ){
            result.wildcard = true;
            return result;
        }
        result.skip();
    }
        sequence_hash nPrefix = prefix.assemble(varClass, varData);
        container search =  nPrefix.tail();
        while(!result.null()){
            if (  match( search,(*(result.current)) )  ){result.wildcard = true; break;}
            result.skip();
        }//while(!result.null())result.skip();
    return result;
}