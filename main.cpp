/* 
 * File:   main.cpp
 * Author: Agustin
 *
 * Created on 11 February 2015, 23:58
 */

#include <cstdlib>
#include "sequence_hash.hpp"
#include "seq_pointer.hpp"
#include "prefixSpan.hpp"
#include "helperFunctions.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#define dataType int
#define container set<dataType>
#define bit16 65535

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {
    sequence_hash test;
    cout<<"Test Created"<<'\n';
    test = test.assemble(3);
    cout<<"Test Append 1"<<'\n';
    test = test.assemble(15);
    cout<<"Test Assemble 1"<<'\n';
    test = test.append(14);
    cout<<"Test Append 2"<<'\n';
    test = test.assemble(9);
    cout<<"Test Assemble 2"<<'\n';
    cout<<test.getSize()<<'\n';
    cout<<test<<'\n';
    seq_pointer p1 = test.begin();
    cout<<*p1<<'\n';
    ++p1;
    cout<<*p1<<'\n';
    ++p1;
    cout<<*p1<<'\n';
    p1.__dump__();
    ++p1; ++p1;
    seq_pointer p2 = (test.end());
    cout<<"p1 == p2: "<<(p1==p2)<<'\n';
    cout<<"p1 != p2: "<<(p1!=p2)<<'\n';
    seq_pointer p3 = test.begin();
    (p3.proyect(14)).__dump__();
    cout<<(p3.proyect(14)).null();
    seq_pointer p4 = p3;
    cout<<(p4.proyect(14)).null();
    return 0;
}

