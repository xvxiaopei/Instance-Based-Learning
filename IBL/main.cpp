#include<iostream>
#include<vector>
#include<assert.h>
#include "compute.h"
#include "readindata.h"
using namespace std;

void IBL(string in,string out,int k){
	ofstream myfile (out);
	myfile<<"Read in Control File from: "<<in<<"...";
	readindata a(in);
	myfile<<"Complete!"<<endl;
	a.shuffleData();     //randomly shuffle
	a.printData();


	for(int i=0;i<10;i++)
	{        
		cout<<i<<" fold"<<endl;
		Compute::mask.clear();   //feature selection

		vector<readindata> div=a.divide(i);    //3 dataset :train 60%; validation 30%; test 10%
		//for(int i=0;i<div.size();i++)  div[i].printData();

		cout<<"Divide done!"<<endl;
		myfile<<"-----------------"<<i<<" th fold----------------------------------------\n";
		double acc= Compute::acc(div[1],div[0],k);
		cout<<"With all features, acc = "<<acc<<endl;
		myfile<<"With all features, acc = "<<acc<<endl;


		vector<int> remainFea;
		for(int i=0;i<a.numOfAttr;i++)
		{
			if(i==a.targetAttr) continue;
			remainFea.push_back(i);
		}
		
		
		double lastacc=acc;
		while(!remainFea.empty()){
			if(lastacc==1) break;
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
			if(maxacc<=lastacc) break;
			Compute::mask.insert(remainFea[leastIndex]);
			myfile<<"Eliminate Feature "<<a.attrName[remainFea[leastIndex]]<<endl<<endl;
			vector<int>::iterator it = remainFea.begin()+leastIndex;
			remainFea.erase(it);
			cout<<"Now remain number of features :"<<remainFea.size()<<  "  and acc = "<<maxacc<<endl;
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
	
	cout<<"1.Car Evaluation Data Set (http://archive.ics.uci.edu/ml/datasets/Car+Evaluation)"<<endl;
    cout<<"2.Nursery Data Set (http://archive.ics.uci.edu/ml/datasets/Nursery)"<<endl;
	cout<<"3.BLOGGER Data Set (http://archive.ics.uci.edu/ml/datasets/BLOGGER#)"<<endl;
	cout<<"4.Mushroom Data Set (http://archive.ics.uci.edu/ml/datasets/Mushroom)"<<endl;
	cout<<"5.Congressional Voting Records Data Set(http://archive.ics.uci.edu/ml/datasets/Congressional+Voting+Records)"<<endl;
	cout<<"Please choose the dataset:";
	
	int choose=0;
	int k=1;
	cin>>choose;
	switch (choose)
	{
		case 1:{in="./data/car/dataConforCar.txt";out="./data/car/outputk_10.txt";break;}
		case 2:{in="./data/nursery/dataConforNur.txt";out="./data/nursery/outputk_10.txt";break;} 
		case 3:{in="./data/blog/dataConforBlog.txt"; out="./data/blog/outputk_10.txt";break;}
		case 4:{in="./data/mush/dataConforMsh.txt";out="./data/mush/outputk_10.txt";break;}
		default:{in="./data/vote/dataConforVote.txt"; out="./data/vote/outputk_10.txt";break;}
	}

	cout<<"Please enter the K: ";
	cin>>k;
	IBL(in,out,k);

		
}