#include <cstdlib>
#include "prefixSpan_hash.hpp"
#include "prefixSpan_hash_parameterized.hpp"
#include "sequence_hash.hpp"
#include "seq_pointer_hash.hpp"
#include "helperFunctions_hash.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

using namespace std;

#include <ctime>
#include <chrono>

void demo();
void parameterized(int, ifstream &, vector <sequence_hash> &, int);
void unparameterized(int, ifstream &, vector <sequence_hash> &);

int main(int argc, char** argv) {
    if (argc < 2){
        demo();
    }else{
        ifstream file;
        file.open(argv[1]);
        if (!file){cout<<"Filed failed to open."; return 0;}
        int threshold = atoi(argv[2]);
        string check = argv[2];
        vector <sequence_hash> seqDatabase;
        seqDatabase = massSequencer(file);
        if (check.find('%') != (unsigned int)(-1)) threshold = (int)((((float)threshold)/100.00)*seqDatabase.size());
		cerr<<"Starting Excecution of PrefixSpan\n";
        if (argc==3) unparameterized(threshold, file, seqDatabase);
		if (argc==4) parameterized(threshold, file, seqDatabase, atoi(argv[3]));
    }
    return 0;   
}

void manageTime(int elapsed){
    if (elapsed<2000000){
        cout<<"Excecution Time: "<<elapsed/1000<<'.'<<elapsed%1000<<"ms\n";
    }else if(elapsed<120000000){
        cout<<"Excecution Time: "<<elapsed/1000000<<'.'<<(elapsed/1000)%1000<<"s\n";
    }else if(elapsed<3600000000){
        cout<<"Excecution Time: "<<elapsed/60000000<<'.'<<(elapsed/1000000)%1000<<"m\n";
    }else{
        cout<<"Excecution Time: "<<elapsed/3600000000<<'.'<<(elapsed/60000000)%60<<"h\n";
    }
    return;
}

void parameterized(int threshold, ifstream &file, vector <sequence_hash> &seqDatabase, int parameter){
    auto start = std::chrono::steady_clock::now();
    prefixSpanParameterized(threshold, seqDatabase, parameter);      
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    manageTime(elapsed.count());
    return;
}

void unparameterized(int threshold, ifstream &file, vector <sequence_hash> &seqDatabase){
    auto start = std::chrono::steady_clock::now();
    prefixSpan(threshold, seqDatabase);      
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    manageTime(elapsed.count());
    return;
}

void demo(){
    cout<<"DEMO: \n";
    string s1 = "1:1,(1:1,2:2,3:3),(1:1,3:3),4:4,(3:3,6:6)";
    string s2 = "(1:1,4:4),3:3,(2:2,3:3),(1:1,5:5)";
    string s3 = "(5:5,6:6),(1:1,2:2),(4:4,6:6),3:3,2:2";
    string s4 = "5:5,7:7,(1:1,6:6),3:3,2:2,3:3";
    string hell = "(1:1,2:2,3:3,4:4,5:5)";
    vector <sequence_hash> seqDatabase;
    sequence_hash p1 = sequencer(s1);
    sequence_hash p2 = sequencer(s2);
    sequence_hash p3 = sequencer(s3);
    sequence_hash p4 = sequencer(s4);
    sequence_hash TEST = sequencer(hell);
    cout<<p1<<'\n'<<p2<<'\n'<<p3<<'\n'<<p4<<'\n'<<TEST<<'\n';
    cout<<p1.begin().proyect(6,6,TEST).null()<<'\n';
    cout<<p2.begin().proyect(6,6,TEST).null()<<'\n';
    cout<<p3.begin().proyect(6,6,TEST).null()<<'\n';
    cout<<p4.begin().proyect(6,6,TEST).null()<<'\n';
    seqDatabase.push_back(p1);
    seqDatabase.push_back(p2);
    seqDatabase.push_back(p3);
    seqDatabase.push_back(p4);
    cout<<"Prefix Span Test:\n";
    prefixSpan(2, seqDatabase);
}