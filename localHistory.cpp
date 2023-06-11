#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include"smithCounter.h"
#include"localHistory.h"
using namespace std;

int main(int argc,char ** argv){
  localHistory local;
  vector<string> branchAddress;
  vector<string> actualPrediction;

  //This line read branch address and actual prediction from branch_trace.dat file
  local.readData(branchAddress,actualPrediction,argv[1]);
  //This simulates local history branch predictor
  local.localSimulation(branchAddress,actualPrediction,local);
  return 0;
}
//End of the program
