/* 
 * File:   seq_pointer.hpp
 * Author: Agustin
 *
 * Created on 22 February 2015, 14:05
 */

#ifndef SEQ_POINTER_HPP
#define	SEQ_POINTER_HPP

#include <map>
#include <bitset>
#include <vector>
#include <set>
#include "sequence_hash.hpp"
using namespace std;
#define dataType int
#define container set<dataType>

class sequence_hash;

class seq_pointer {
    friend int match(seq_pointer &, seq_pointer &);
public:
    seq_pointer();
    seq_pointer(sequence_hash *, container::iterator, container::iterator, int=0);
    
    seq_pointer(const seq_pointer& orig);
    seq_pointer operator ++ ();
    dataType operator *();
    int operator ==(seq_pointer &);
    int operator !=(seq_pointer &);
    void skip();
    void reset();
    bool getWildcard(){return wildcard;}
    bool null(){return current==end;}
    bool matched(){return lastMatch;}
    seq_pointer proyect(dataType);
    seq_pointer proyect(dataType, sequence_hash &);
    virtual ~seq_pointer();
    void __dump__();
private:
    bool lastMatch;
    bool wildcard;
    container::iterator current;
    container::iterator end;
    int index;
    sequence_hash * source;
    
    void jump(container::iterator);
};

#endif	/* SEQ_POINTER_HPP */

