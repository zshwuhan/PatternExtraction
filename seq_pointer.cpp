/* 
 * File:   seq_pointer.cpp
 * Author: Agustin
 * 
 * Created on 22 February 2015, 14:05
 */
#include <iostream>
#include "seq_pointer.hpp"
#include <algorithm>
#define dataType int
#define container set<dataType>

seq_pointer::seq_pointer():source(NULL){
}

seq_pointer::seq_pointer(sequence_hash * seq, container::iterator iter, container::iterator ender, int ind):source(seq){
    wildcard = false;
    current = iter;
    end = ender;
    index = ind;
}

seq_pointer::seq_pointer(const seq_pointer& orig):source(orig.source){
    wildcard = orig.wildcard;
    current = orig.current;
    end = orig.end;
    index = orig.index;
}

seq_pointer::~seq_pointer() {
}

int seq_pointer::operator ==(seq_pointer &dest){
    return current==dest.current;
}

int seq_pointer::operator !=(seq_pointer &dest){
    return current!=dest.current;
}

seq_pointer seq_pointer::operator ++ (){
    ++current;
    if(current==end && index!=(source->getSize()-1)){
        index = ++index;
        current=(*source).elements[index].begin();
        end=(*source).elements[index].end();
        wildcard=false;
    }return *this;
}

dataType seq_pointer::operator *(){
    return (*current);
}

void seq_pointer::__dump__(){
    cout<<"{Index: "<<index<<" Current: "<<*current<<" Wildcard: "<< wildcard <<"}\n";
    return;
}

void seq_pointer::jump(container::iterator dest){
    current = dest;
    return;
}

void seq_pointer::skip(){
    if (index < source->getSize()){
        index = ++index;
        current=(*source).elements[index].begin();
        end=(*source).elements[index].end();
        wildcard=false;
    }else{
        current = end;
        wildcard=false;
    }return;
}

void seq_pointer::reset(){
    current = (source->elements)[index].begin(); 
    wildcard = false; 
    return;
}

//lower_bound from algorithm with later comparison for find
seq_pointer seq_pointer::proyect(dataType appending){
    seq_pointer result = (*this);
    if (result.getWildcard())result.skip();
    seq_pointer trueEnd = source->end();
    container::iterator ritorno;
    while(result != trueEnd){
        ritorno=lower_bound(result.current, result.end, appending);
        if (ritorno!=result.end && *ritorno==appending){
            result.jump(ritorno);
            result.wildcard = true;
            ++result;
            break;
        }
        result.skip();
    }return result;
}

int match(seq_pointer &advanceable, seq_pointer &iterable){
    container::iterator start = advanceable.current;
    container::iterator finish = advanceable.end;
    container::iterator match = iterable.current;
    container::iterator goal = iterable.end;
    if (match==goal) return 1;
    while(start!=finish){
        if (*start == *match) match++;
        if (match==goal){ 
            advanceable.jump(start);
            ++advanceable;
            return 1;
            }
        ++start;
    }{advanceable.skip();return 0;}
}

seq_pointer seq_pointer::proyect(dataType appending, sequence_hash &prefix){
    seq_pointer result = (*this);
    seq_pointer trueEnd = source->end();
    container::iterator ritorno;
    //simple case if we already have wildcarded
    if (result.getWildcard()){
        ritorno=lower_bound(result.current, result.end, appending);
        if (ritorno!=result.end && *ritorno==appending){
            result.jump(ritorno);
            result.wildcard = true;
            ++result;
        }
        result.skip();
    }else{//not so simple case if we haven't
    //Substring match is what's left
        sequence_hash nPrefix = prefix.append(appending);
        seq_pointer prefIter = prefix.tail_pointer();
        seq_pointer prefEnd = prefix.tail_pointer();
        prefEnd.skip();
        while(result != trueEnd && prefIter != prefEnd){
            match(result, prefIter);
        }
    }return result;
}