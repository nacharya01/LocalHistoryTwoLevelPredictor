#ifndef LOCALHISTORY_H
#define LOCALHISTORY_H
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include"smithCounter.h"
using namespace std;

class localHistory: public smithCounter{
  //BHT has 4 entries
  private: string Bht[4];
  private: int size;
  //Defination of the constructor
  public: localHistory(){
    for( int i=0;i<4;i++) Bht[i]="0000";
    size=3;
  }
  public: void localSimulation(vector<string>, vector<string>,localHistory );
  public: int getSize();
};

int localHistory:: getSize(){
  return size;
}
//This function simulates as local history branch predictor
void localHistory:: localSimulation(vector<string>branchAddress, vector<string>actualPrediction,localHistory local){
  int indexBht,
      indexPht,
      notTaken=0,
      taken=0,
      takenCorrect=0,
      notTakenCorrect=0,
      totalBranches=0,instruction;
  //This loop go through every branch address and makes a prediction
  for(int i=0;i<branchAddress.size();i++){
    //Hasing done to do indexing
    std::string binary = std::bitset<16>(stoi(branchAddress[i])).to_string();
    instruction = atoi(binary.c_str());
    indexBht=(instruction/4) & 0x3;
    indexPht= (((instruction/4) << (getSize())) | (stoi(Bht[indexBht],0,2) & 0xF)) & 0x1F;
    if(local.getCounterValue()[indexPht]==0||local.getCounterValue()[indexPht]==1){
      //These 3 lines of codes are used to shift string left by  1
      reverse(Bht[indexBht].begin(),Bht[indexBht].begin()+1);
      reverse(Bht[indexBht].begin()+1,Bht[indexBht].end());
      reverse(Bht[indexBht].begin(),Bht[indexBht].end());
      //If the actual prediction is taken then increment counter value
      if(actualPrediction[i]=="T"){
        local.updateCounter(indexPht,1);
        Bht[indexBht][3]='1';
      }
      //if the actual prediction is not taken then decrement counter value
      else{
        local.updateCounter(indexPht,-1);
        Bht[indexBht][3]='0';
        notTakenCorrect++;
      }
    }
    //If the counter value is greater or equal to 2 predict as taken
    else{
      //These 3 lines of codes are used to shift string left by  1
      reverse(Bht[indexBht].begin(),Bht[indexBht].begin()+1);
      reverse(Bht[indexBht].begin()+1,Bht[indexBht].end());
      reverse(Bht[indexBht].begin(),Bht[indexBht].end());
      if(actualPrediction[i]=="T"){
        local.updateCounter(indexPht,1);
        //Inserting 1 as taken at last index of string  bhr
        Bht[indexBht][3]='1';
        takenCorrect++;
      }
      else{
        local.updateCounter(indexPht,-1);
        //Inserting 0 as not taken at last index of string  bhr
        Bht[indexBht][3]='0';
      }
    }
    totalBranches++;
    if(actualPrediction[i]=="T")taken++;
    if(actualPrediction[i]=="N")notTaken++;
  }
  //Printing out the results that we got from the loop
  cout<<endl<<endl<<"----Local History ----"<<endl<<endl;
  cout<<"Number of branches: "<<totalBranches<<endl;
  cout<<"Number of branches taken: "<<taken<<endl;
  cout<<"Number taken branches correctly predicted: "<<takenCorrect<<endl;
  cout<<"Number of branches not taken: "<<notTaken<<endl;
  cout<<"Number not taken branches correctly predicted: "<<notTakenCorrect<<endl;
  cout<<"Overall rate of correct predictions: "<<((takenCorrect+notTakenCorrect)/(float)totalBranches)*100.00<<"%"<<endl;
}
#endif
