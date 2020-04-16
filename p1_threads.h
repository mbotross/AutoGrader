#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <math.h>
#include "p1_process.h"
#include "mergesort.h"
#include <vector>
#include <cstdlib>

using namespace std;
struct thread_args{
  vector<double>*A;
  vector<long>*B;
  int lower_limit;
  int upper_limit;
};
void makethread(int num_threads ,vector <long> studentID, vector <double> Grade, string file_name);
void merge_thread(int num_threads,int change, int threadchunk);
double Average(vector<double> Grade);
double Median(vector <double> Grade);
double S_D(vector <double> Grade);
void file_write1(string file_name, double SD, double average, double median);
void file_write2(string file_name,vector<long> studentID,vector<double>Grade);

#endif
