#ifndef _READIN_DATA_H
#define _READIN_DATA_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <algorithm>
#include <cmath>
 #include <ctime> 
using namespace std;

class readindata{

public:

	int numOfTuple;
	int numOfAttr;
	vector<string> attrName;
	vector<vector<string>> attrVal;
	int *numOfTar;               //target attr 's  value
	int targetAttr;
	vector<int> remainAttr;
	vector<vector<string>> data;
	vector<vector<double>> numdata;   
	vector<vector<double>> output;


	readindata(string dataCon);    //data control file
	readindata();
	void printData(bool d=false);          //d= true      print detail data
	//void printCount(); 
	void shuffleData();
	void getNumData();
	int targetA(){return targetAttr;}
	vector<vector<string>> attrV(){return attrVal;}
	vector<vector<string>> getData(){return data;}
	vector<string> attrN(){return attrName;}

	void count(vector<string> t,int attr,int *num);
	int * counts(int attr);

	double entropy();

	vector<readindata> vsplit(int attr);        //virtually split tree by attribute (don't have data),just for compute entropy
	double infoGain(int attr);                     //get the information gain
	int bestAttr();

	vector<readindata> split(int attr);       //really split

	vector<readindata> divide(int c);             //60% training set, 30% validation set, 10% test set(10 fold), c=0,1,2....9

}
;


#endif 