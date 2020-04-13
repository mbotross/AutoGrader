
#if !defined (INC_SORT_HH)
#define INC_SORT_HH

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "p1_threads.h"
using namespace std;

void *mergesort_thread(void *args);
void mergesort(vector<double> *A,vector<long>*B,int low, int high);
void merge(vector<double> *A,vector<long> *B, int low, int mid, int high);
void mySort (int N, vector<double> *A, vector<long> *B);


#endif

/* eof */
