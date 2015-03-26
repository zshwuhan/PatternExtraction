/* 
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Applied Artificial Intelligence and Pattern Recognition Research Group (GRPIAA)
 *
 */

#include "helperFunctions_hash.hpp"
#include <string>
#include "sequence_hash.hpp"
#include <vector>
#include <iostream>
#include <sstream>

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

void vectorPrint(vector <sequence_hash> v){
    vector <sequence_hash>::iterator it1,it2;
    it1=v.begin(), it2=v.end();
    while(it1!=it2){
        cerr<<*it1;
        ++it1;
    }
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

hashConv convert(pair<classType, dataType> datum){
    return ((datum.first<<16)|datum.second);
}

pair<classType, dataType> deconvert(hashConv data){
    return make_pair((data>>16), (data<<16)>>16);
}

void sequencer(sequence_hash *trueOutput, string input, bool include){
    bool assembleMode = false;
    int low, high;
    stringstream inputStreamed(input);
	sequence_hash *output = trueOutput;
    while(inputStreamed){
        if(inputStreamed.peek()=='('){
            inputStreamed.ignore();
            inputStreamed>>high;
            inputStreamed.ignore();
            inputStreamed>>low;
			output = (output->append(high, low));
			assembleMode=true;
        }else if(inputStreamed.peek()==')'){
            assembleMode=false;
            inputStreamed.ignore();
        }else if(inputStreamed.peek()==','){
            inputStreamed.ignore();
        }else if(inputStreamed.peek()!=-1){
            if(assembleMode){
                inputStreamed>>high;
                inputStreamed.ignore();
                inputStreamed>>low;
				output = (output->assemble(high,low));
			}else{
                inputStreamed>>high;
                inputStreamed.ignore();
                inputStreamed>>low;
				output = (output->append(high, low));
            }
        }else{
            inputStreamed.ignore();
        }
    }//cerr<<"PREVIOUS TO EXIT: "<<output->valid()<<'\n';
	if (include){*((sequence_hash_parser *)trueOutput) = *((sequence_hash_parser *)output);/*cerr<<"TING!";*/}
	else{*trueOutput = *output;}
    return;
}
#include <fstream>

vector <sequence_hash> massSequencer(ifstream &input){
    vector <sequence_hash> output;
    while(input){
        string temp;
        getline(input, temp);
        sequence_hash *helper = new sequence_hash;
        sequencer(helper, temp);
        if (!helper->empty())output.push_back(*helper);
    }
    return output;
}

//NEED FIX FOR PARENT/CHILD PROBLEM
vector <sequence_hash> massSequencer(ifstream &input, char *cString, int &counter, parserTree &tree){
    vector <sequence_hash> output;
	string expression = cString;
	parserTree jormungand = shuntingYard(expression);
	tree.print();
	counter = 0;
    while(input){
        string temp;
        getline(input, temp);
        sequence_hash_parser *helper= new sequence_hash_parser(jormungand);
        sequencer(helper, temp, true);
        if (!helper->empty() && helper->valid()){output.push_back(*(sequence_hash *)helper);}
		++counter;
    }
	tree = jormungand;
    return output;
}
