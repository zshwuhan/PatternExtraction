/* 
 * File:   sequence_hash.cpp
 * Author: Agustin
 * 
 * Created on 12 February 2015, 00:00
 */

#include "sequence_hash.hpp"
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include "seq_pointer.hpp"
#define dataType int
#define container set<dataType>

using namespace std;



ostream &operator << (ostream &osin, container hashmap){
    if (hashmap.size()==0) return osin;
    if (hashmap.size()==1){
        osin<<((*(hashmap.begin()))>>16)<<':'<<(((*(hashmap.begin()))<<16)>>16);}
    else {
        osin<<'(';
        container::iterator beg, forward, endoru;
        beg = hashmap.begin(); 
        forward = hashmap.begin(); 
        endoru = hashmap.end();
        if (beg!=endoru){
            ++forward;
            while(forward!=endoru){
                osin<<((*beg)>>16)<<':'<<(((*beg)<<16)>>16);
                osin<<",";
                ++forward;
                ++beg;
            }
        }osin<<((*beg)>>16)<<':'<<(((*beg)<<16)>>16);  
        
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
}

sequence_hash::sequence_hash(vector <container> input) {
    vector <container> copy = input;
    this->elements = copy;
    this->size = copy.size();
}

sequence_hash::sequence_hash(const sequence_hash& orig) {
    this->elements = orig.elements;
    this->size = orig.size;
}

sequence_hash::~sequence_hash() {
}

//sequence_hash sequence_hash::proyection(int item);
//sequence_hash sequence_hash::proyection(int item, sequence_hash prefix);

sequence_hash sequence_hash::append(int item){
    container element; 
    element.insert(item);
    sequence_hash ritorno (this->elements);
    (ritorno.elements).push_back(element);
    ritorno.size = ritorno.size + 1;
    return ritorno;
}
sequence_hash sequence_hash::assemble(int item){
    sequence_hash ritorno (this->elements);
    if (((ritorno.elements).rbegin())==((ritorno.elements).rend())){
        return (ritorno.append(item));}
    (*((ritorno.elements).rbegin())).insert(item);
    return ritorno;
}

container sequence_hash::tail(){
    container ritorno = (*(elements.rbegin()));
    return ritorno;
};

seq_pointer sequence_hash::begin(){
    return seq_pointer(const_cast<sequence_hash *> (this), elements.begin()->begin(), elements.begin()->end());
}

seq_pointer sequence_hash::end(){
    return seq_pointer(const_cast<sequence_hash *> (this), elements.rbegin()->end(), elements.rbegin()->end(), (this->getSize()) -1);
}

seq_pointer sequence_hash::tail_pointer(){
    seq_pointer p1 (const_cast<sequence_hash *> (this), tail().begin(), tail().end(), this->getSize()-1); 
    return p1;
}

int sequence_hash::empty(){
    return (size==0);
}