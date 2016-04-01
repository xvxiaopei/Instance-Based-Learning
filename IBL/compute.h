#ifndef _COMPUTE_H
#define _COMPUTE_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include<assert.h>
#include <queue>
#include <set>   

#include "readindata.h"

using namespace std;

struct Pair{
	string targetValue;
	double dist;

	Pair(string V,double d)
	{
		targetValue=V;
		dist=d;
	}

};
bool operator<(Pair a,Pair b){
	return a.dist<b.dist;
}



class Compute{
private:
	static double dist1(vector<string> t1,vector<string> t2,int targetI )  //targetI is the index of target attr
	{
		if(t1.size()!=t2.size())

			cout<<" ERROR: compare two tuple with different number of attrs."<<endl;
			//assert(t1.size()==t2.size());

		double sum=0;
		for(int i=0;i<t1.size();i++)
		{
			if(i==targetI||mask.find(i)!=mask.end()) continue;
			if(t1[i]!=t2[i])sum+=2;
		}
		return sqrt(sum);
	}
public:
	static set<int> mask;

	static string KNN(vector<string> ins, readindata a,int k)
	{
		int targetI=a.targetAttr;
		priority_queue<Pair> q;
		if(k>a.data.size())k=a.data.size();
		int i=0;
		for(;i<k;i++){		
			double cur=dist1(ins,a.data[i],targetI);
			q.push(Pair(a.data[i][targetI],cur));
			//cout<<cur<<endl;

		}

		for(;i<a.data.size();i++){
			double max=q.top().dist;
			double cur=dist1(ins,a.data[i],targetI);
			//cout<<cur<<endl;
			if(max>cur) {
				q.pop();q.push(Pair(a.data[i][targetI],cur));
			}
		}

		double *vote =new double[a.attrVal[targetI].size()];
		for(int j=0;j<a.attrVal[targetI].size();j++) vote[j]=0;

		for(int i=0;i<k;i++)      //vote
		{
			Pair tmp=q.top();
			q.pop();
			bool c=false;
			for(int j=0;j<a.attrVal[targetI].size();j++)
			{
				if(tmp.targetValue==a.attrVal[targetI][j])
				{
					if(tmp.dist<0.000001)vote[j]+=1.0;
					else
					vote[j]+= 1.0/tmp.dist*tmp.dist; //distance weighted
					//cout<<1.0/tmp.dist*tmp.dist<<endl;
					c=true;
					break;
				}
			}
			assert(c);
		}

		double max=0;
		int maxIn=-1;
		for(int j=0;j<a.attrVal[targetI].size();j++) {
			if(vote[j]>max){
				maxIn=j;
				max=vote[j];
			}

		}

		return a.attrVal[targetI][maxIn];

	}


	static double acc(readindata test,readindata train,int k){
		int sum=0;
		for(int j=0;j<test.data.size();j++)
		{
			vector<string> t=test.data[j];
			//cout<<t[a.targetAttr]<<"  :  ";
			//cout<<Compute::KNN(t,div[0],k)<<endl;
			if(t[test.targetAttr]==Compute::KNN(t,train,k))sum+=1;

		}
		return (double)sum/test.data.size();

	}





};

set<int> Compute::mask;



#endif 