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
#include <string>
#include <sstream>
#include <fstream>
#define dataType int
#define container set<dataType>
#define bit16 65535

using namespace std;
/*
 * 
 */


int main(int argc, char** argv) {
    if (argc < 2){
        cout<<"DEMO: \n";
        string s1 = "(1:1,2:1,3:1),1:1,2:4,(1:2,2:3),1:1,(1:3,2:4)";
        string s2 = "(1:1,2:2),1:1,2:4,(1:2,2:3),1:1,(1:5,2:4)";
        string s3 = "1:2";
        vector <sequence_hash> seqDatabase;
        sequence_hash p1 = sequencer(s1);
        sequence_hash p2 = sequencer(s2);
        sequence_hash p3 = sequencer(s3);
        cout<<(p1.begin().proyect(131075)).matched()<<'\n';
        cout<<(p1.begin().proyect(65537).proyect(131075)).matched()<<'\n';

        seqDatabase.push_back(p1);
        seqDatabase.push_back(p2);
        cout<< seqDatabase[0] <<'\n';
        cout<< seqDatabase[1] <<'\n';
        cout<<"Prefix Span Test:\n";
        prefixSpan(2, seqDatabase);
    }else{
        ifstream file;
        file.open(argv[1]);
        if (!file){cout<<"Filed failed to open."; return 0;}
        vector <sequence_hash> seqDatabase;
        seqDatabase = massSequencer(file);
        int threshold = atoi(argv[2]);
        string check = argv[2];
        if (check.find('%') != (unsigned int)(-1)) threshold = (int)((((float)threshold)/100.00)*seqDatabase.size());
        prefixSpan(threshold, seqDatabase);        
    }
    return 0;
}

