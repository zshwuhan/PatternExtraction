/* 
 * File:   sequence_hash.hpp
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
 */

using namespace std;
#include <cstring>
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

#define MAX_INT 500


#include <ctime>
#include <chrono>

ostream &operator << (ostream &osin, unordered_map<string, int> hashmap){
	unordered_map<string, int>::iterator forward, ending;
	forward = hashmap.begin(); 
	ending = hashmap.end();
	while(forward!=ending){
		osin<<forward->first<<": "<<forward->second<<'\n';
		++forward;
	}
    return osin;
}


void demo();
void parameterized(int, ifstream &, vector <sequence_hash> &, parserTree *, int, char**);
void unparameterized(int, ifstream &, vector <sequence_hash> &);

int main(int argc, char** argv) {
    if (argc < 2){
        demo();
    }else{
	//FILE OPERATIONS
        ifstream file;
        file.open(argv[1]);
        if (!file){cout<<"Filed failed to open."; return 0;}
	//FLAG CHECKING
        int threshold = atoi(argv[2]);
		int counter=0;
		cerr<<"Inputs Analyzed\n";
        string check = argv[2];
        vector <sequence_hash> seqDatabase;
		parserTree *jormungand = NULL;
	//CHECKING INCLUSION
		if (argc>3 && !strcmp(argv[3], "-include")){	
			string expression = argv[4];
			jormungand = new parserTree;
			*jormungand = shuntingYard(expression); 
			seqDatabase = massSequencer(file, jormungand, counter);
		}
        else{seqDatabase = massSequencer(file); counter = seqDatabase.size();}
	//CHECKING IF % OR RAW NUMBER FOR THRESHOLD
        if (check.find('%') != string::npos){
			threshold = (int)((((float)threshold)/100.00)*counter);}
		cerr<<"Starting Excecution of PrefixSpan\n";
        if (argc==3) unparameterized(threshold, file, seqDatabase);
		if (argc>3) parameterized(threshold, file, seqDatabase, jormungand, argc, argv);
    }
    return 0;   
}

#include <climits>
void parameterized(int threshold, ifstream &file, vector <sequence_hash> &seqDatabase, parserTree *tree, int argc, char** argv){
	unordered_map<string, int> options;
	//DEFAULT OPTIONS
	options["-minSseq"]=0;
	options["-maxSseq"]=MAX_INT;
	options["-minSize"]=0;
	options["-maxSize"]=MAX_INT;
	string inclusion = "-include";
	options["-includeFlag"] = 0;
	//OPTION PARSING
	for(int i = 3; i<argc ;++i){
		string option = argv[i];
		++i;
		if (option != inclusion){
			int value = (int) atoi(argv[i]);
			options[option] = value;
		}
		else {//REMINDER: PREPROCESSING IS DONE THROUGH OVERLOAD, POSTPROCESSING IS DONE THROUGH THE VALID ATTRIBUTE IN SEQUENCE_HASH
			string expression = argv[i];
			options["-includeFlag"]=1;		
		}
	}cerr<<"Options Set:\n"<<options<<"-threshold: "<<threshold<<'\n';
    auto start = std::chrono::steady_clock::now();
	prefixSpanParameterized(threshold, seqDatabase, options, tree);  
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
    sequence_hash p1; sequencer(p1, s1);
    sequence_hash p2; sequencer(p2, s2);
    sequence_hash p3; sequencer(p3, s3);
    sequence_hash p4; sequencer(p4, s4);
    sequence_hash TEST; sequencer(TEST, hell);
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