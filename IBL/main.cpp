#include<iostream>
#include<vector>
#include<assert.h>
#include "compute.h"
#include "readindata.h"
using namespace std;

void IBL(string in,string out){
	ofstream myfile (out);
	myfile<<"Read in Control File from: "<<in<<"...";
	readindata a(in);
	myfile<<"Complete!"<<endl;
	a.shuffleData();     //randomly shuffle
	a.printData();
	int k=5;

	for(int i=0;i<10;i++)
	{        
		cout<<i<<" fold"<<endl;
		Compute::mask.clear();   //feature selection

		vector<readindata> div=a.divide(i);    //3 dataset :train 60%; validation 30%; test 10%
		//for(int i=0;i<div.size();i++)  div[i].printData();
		myfile<<"-----------------"<<i<<" th fold----------------------------------------\n";
		double acc= Compute::acc(div[1],div[0],k);
		myfile<<"With all features, acc = "<<acc<<endl;


		vector<int> remainFea;
		for(int i=0;i<a.numOfAttr;i++)
		{
			if(i==a.targetAttr) continue;
			remainFea.push_back(i);
		}
		
		
		double lastacc=acc;
		while(!remainFea.empty()){
			double maxacc=0;
			int leastIndex=-1;
			for(int i=0;i<remainFea.size();i++){
				Compute::mask.insert(remainFea[i]);
				acc= Compute::acc(div[1],div[0],k);
				myfile<<"If we dismiss feature "<<a.attrName[remainFea[i]]<<", acc = "<< acc<<endl;
				Compute::mask.erase(remainFea[i]);

				if(acc>maxacc){maxacc=acc;leastIndex=i;}
			}
			//cout<<maxacc<<endl;
			if(maxacc<lastacc) break;
			Compute::mask.insert(remainFea[leastIndex]);
			myfile<<"Eliminate Feature "<<a.attrName[remainFea[leastIndex]]<<endl<<endl;
			vector<int>::iterator it = remainFea.begin()+leastIndex;
			remainFea.erase(it);
			myfile<<"Now remain number of features :"<<remainFea.size()<<  "  and acc = "<<maxacc<<endl;
			myfile<<"Remain features: ";
			for(int i=0;i<remainFea.size();i++)
			{
				myfile<<a.attrName[remainFea[i]]<<", ";
			}
			myfile<<endl;
			lastacc=maxacc;
		}

		acc=Compute::acc(div[2],div[0],k);
		myfile<<endl<<"The test acc = "<<acc<<endl;
		myfile<<"--------------------------------------------------------------\n";



	}
	
	myfile.close();

}




int main(){
	srand(time(0));
	string in,out;

	int choose=5;
	switch (choose)
	{
		case 1:{in="./data/car/dataConforCar.txt";out="./data/car/output.txt";break;}
		case 2:{in="./data/nursery/dataConforNur.txt";out="./data/nursery/output.txt";break;} 
		case 3:{in="./data/blog/dataConforBlog.txt"; out="./data/blog/output.txt";break;}
		case 4:{in="./data/mush/dataConforMsh.txt";out="./data/mush/output.txt";break;}
		default:{in="./data/vote/dataConforVote.txt"; out="./data/vote/output.txt";break;}
	}


	IBL(in,out);

	cout<<"Hello World!";
		
}