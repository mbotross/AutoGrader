#include "p1_process.h"

using namespace std;
vector<long> studentID;
vector<double> Grade;
void get_statistics(std::string class_name[], int num_processes, int num_threads) {

	// You need to create multiple processes here (each process
	// handles at least one file.)


	// Each process should use the sort function which you have defined
	// in the p1_threads.cpp for multithread sorting of the data.

	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.



	for(int i=0;i<num_processes;i++){
		int pid=fork();
		if(pid<0){
			cout<<"Error"<<endl;
			return;
		}

		else if(pid==0){
			printf("Child process is created. (pid: %d)\n",getpid());
			//call thread function, passsing in num of threads,and two arrays of ID and Grade
			if(i==num_processes-1 && num_processes<5){
				for(int i=num_processes-1;i<5;i++){
				file_process(class_name,i);

				makethread(num_threads,studentID,Grade,class_name[i]);

				}

			}
			else{
				file_process(class_name,i);
				makethread(num_threads,studentID,Grade,class_name[i]);
			}

			printf("Child process is terminated. (pid: %d)\n",getpid());
			exit(0);
		}

	}
	for(int i=0;i<num_processes;i++){

		int status;
		pid_t pid=wait(&status);


	}

 }


void file_process(std::string class_name[],int i){
	studentID.clear();
	Grade.clear();

	string lines;
	string filename;
	ifstream myfile;

	int k=0;


	filename="input/"+class_name[i]+".csv";
	char file[filename.size()+1];
//	cout<<filename<<endl;
	strcpy(file,filename.c_str());
	myfile.open(file);
	getline(myfile,lines);
	//split the ID from the grade
	while(!getline(myfile,lines).eof()){
		char line[lines.length()];
		strcpy(line,lines.c_str());
		char *token=strtok(line,",");

		string result[2];
		int j=0;

		while(token!=NULL){
			result[j]=token;
			token=strtok(NULL,",");
			// cout<<result[j]<<endl;
			j++;
		}
		studentID.push_back(atol(result[0].c_str()));
		//cout<<studentID[k]<<endl;
		Grade.push_back(atof(result[1].c_str()));


		k++;

	}

	myfile.close();



}
