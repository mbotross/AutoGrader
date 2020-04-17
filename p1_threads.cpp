#include "p1_threads.h"

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function
using namespace std;
std::vector<long> student_ID;
std::vector<double> grade;
void makethread(int num_threads ,vector<long> studentID, vector<double> Grade, string file_name){


	student_ID.clear();
	grade.clear();

		for(int i=0;i<studentID.size();i++){
	  	student_ID.push_back(studentID[i]);
		  grade.push_back(Grade[i]);
	}


	//threads creation

	pthread_t tid[num_threads];

	int threadchunk=grade.size()/num_threads;
	int lowerlimit=0;
	int upperlimit=threadchunk;

	for(int i=0;i<num_threads;i++){
		thread_args *args=new thread_args;
		if(i==num_threads-1 && upperlimit<grade.size()){
			upperlimit=grade.size();
		}

		args->A=&grade;
		args->B=&student_ID;
		args->lower_limit=lowerlimit;
		args->upper_limit=upperlimit;
		//call mergesort, with divided work based on number of threads
		pthread_create(&tid[i],NULL,mergesort_thread,(void *)args);
		//cout<<"lowerlimit"<<lowerlimit<<endl;
		//cout<<"upperlimit"<<upperlimit<<endl;
		lowerlimit=lowerlimit+threadchunk;
		upperlimit=upperlimit+threadchunk;

	}

	for(int i=0;i<num_threads;i++){
		pthread_join(tid[i],NULL);

	}


  //Merge threads together
 merge_thread(num_threads,1,threadchunk);



	double average=Average(grade);
	double median=Median(grade);
	double SD=S_D(grade);

	//write to file
	file_write1(file_name,SD,average,median);
	file_write2(file_name,student_ID,grade);
}

//after sorting

void merge_thread(int num_threads,int change,int threadchunk){

		for(int i=0;i<num_threads;i+=2){
		  int low=i*threadchunk*change;
			int high=(i+2)*threadchunk*change-1;
			//cout<<"low:"<<low<<endl;

			if(high>=grade.size()){
				high=grade.size()-1;
			}
			//cout<<"high"<<high<<endl;
			int middle=low+(threadchunk*change)-1;
			//cout<<"middle:"<<middle<<endl;

			merge(&grade,&student_ID,low,middle,high);

		}
		if(num_threads/2>=1){
				merge_thread(num_threads/2,change*2,threadchunk);
		}

}

double Average(vector<double> Grade){
	int size=Grade.size();
	double sum=0;
	for(int i=0;i<size;i++){
	    sum=sum+Grade[i];

	}
	double average=sum/size;
	return average;
}


double Median(vector<double> Grade){
	int size=Grade.size();
	int median=size/2;
	return Grade[median];

}

double S_D(vector <double> Grade){
	double average=Average(Grade);
	double square=0;
	for(int i=0;i<Grade.size();i++){
		square+=(Grade[i]-average)*(Grade[i]-average);

	}
	double SD=sqrt(square/Grade.size());
	return SD;
}


void file_write1(string file_name, double SD, double average, double median){

		string path="output/"+file_name+"_stats.csv";
		char file[path.size()+1];
		strcpy(file,path.c_str());
		ofstream myfile(file);
		myfile<<"Average,Median,Std. Dev"<<endl;
		myfile<<setprecision(3)<<fixed<<average<<",";
		myfile<<setprecision(3)<<fixed<<median<<",";
		myfile<<setprecision(3)<<fixed<<SD;

		myfile.close();


}

void file_write2(string file_name,vector<long> studentID,vector<double>Grade){

		string path="output/"+file_name+"_sorted.csv";
		char file[path.size()+1];
		strcpy(file,path.c_str());
		ofstream myfile(file);
		int rank=1;
		myfile<<"Rank,Student ID,Grade"<<endl;
		for(int i=Grade.size()-1;i>=0;i--){
				myfile<<rank<<","<<studentID[i]<<","<<setprecision(15)<<Grade[i]<<endl;
				rank++;


		}
		myfile.close();
}
