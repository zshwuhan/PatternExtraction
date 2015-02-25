/* 
 * File:   helperFunctions.cpp
 * Author: Agustin
 * 
 * Created on 24 February 2015, 13:55
 */

#include "helperFunctions.hpp"
#include <string>
#include "sequence_hash.hpp"
#include <vector>
#include <iostream>
#include <sstream>

sequence_hash sequencer(string input){
    sequence_hash output;
    bool assembleMode = false;
    int low, high, net;
    stringstream inputStreamed(input);
    while(inputStreamed){
        if(inputStreamed.peek()=='('){
            inputStreamed.ignore();
            inputStreamed>>high;
            inputStreamed.ignore();
            inputStreamed>>low;
            net = low | (high<<16);
            output = output.append(net);
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
                net = low | (high<<16);
                output = output.assemble(net);
            }else{
                inputStreamed>>high;
                inputStreamed.ignore();
                inputStreamed>>low;
                net = low | (high<<16);
                output = output.append(net);
            }
        }else{
            inputStreamed.ignore();
        }
    }
    return output;
}

vector <sequence_hash> massSequencer(iostream input){
    vector <sequence_hash> output;
    while(input){
        string temp;
        getline(input, temp);
        sequence_hash helper;
        helper = sequencer(temp);
        output.push_back(helper);
    }
    return output;
}
