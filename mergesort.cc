#include "mergesort.h"



//A: Grades
//B: Student ID
void mySort (int N, vector<double> *A,vector<long> *B)
{
  if(N==1){
    return;
  }
  mergesort(A,B,0,N-1);
}

void *mergesort_thread(void *args){

  struct thread_args *temp=(thread_args *)args;
  if(temp->lower_limit < temp->upper_limit-1){

    mergesort(temp->A,temp->B,temp->lower_limit,temp->upper_limit-1);

   }
}

void mergesort(vector<double> *A, vector<long> *B, int low, int high){


  if(low<high){
    // cout<<"low:"<<low<<endl;
    // cout<<"high:"<<high<<endl;
    int mid=(low+high)/2;
    mergesort(A,B,low,mid);
    mergesort(A,B,mid+1,high);
    merge(A,B,low,mid,high);
  }

}


void merge(vector<double> *A,vector<long> *B,  int low, int mid, int high){

  int i=low;
  int j=mid+1;
  int k=0;

  double *tmp=new double [high-low+1];
  long *tmp2=new long[high-low+1];
  while(i<=mid && j<=high){

    if((*A)[i]<=(*A)[j]){
      tmp[k]=(*A)[i];
      tmp2[k]=(*B)[i];

      i++;
    }
    else {
      tmp[k]=(*A)[j];
      tmp2[k]=(*B)[j];

      j++;

    }
    k++;

  }

  if(i>mid){
    while(j<=high){
      tmp[k]=(*A)[j];
      tmp2[k]=(*B)[j];

      j++;
      k++;

    }

  }
  else if(j>high){
    while(i<=mid){
      tmp[k]=(*A)[i];
      tmp2[k]=(*B)[i];
      i++;
      k++;

    }

  }

  for(int i=low;i<=high;i++){

    //cout<<k<<endl;
    (*A)[i]=tmp[i-low];
    (*B)[i]=tmp2[i-low];


  }

}

void merge2(vector<double>* A, vector<long>* B, int left, int middle, int right){
  cout<<"Im here";
  int i = 0;
  int j = 0;
  int k = 0;
  int left_length = middle - left + 1;
  int right_length = right - middle;
  double left_array[left_length];
  double right_array[right_length];
  long left_array2[left_length];
  long right_array2[right_length];

  /* copy values to left array */
  for (int i = 0; i < left_length; i ++) {
      left_array[i] = (*A)[left + i];
      left_array2[i] = (*B)[left + i];

  }

  /* copy values to right array */
  for (int j = 0; j < right_length; j ++) {
      right_array[j] = (*A)[middle + 1 + j];
      right_array2[j] = (*B)[middle + 1 + j];
  }

  i = 0;
  j = 0;
  /** chose from right and left arrays and copy */
  while (i < left_length && j < right_length) {
      if (left_array[i] <= right_array[j]) {
          (*A)[left + k] = left_array[i];
          (*B)[left + k] = left_array2[i];

          i ++;
      } else {
          (*A)[left + k] = right_array[j];
          (*B)[left + k] = right_array2[j];
          j ++;
      }
      k ++;
  }

  /* copy the remaining values to the array */
  while (i < left_length) {
      (*A)[left + k] = left_array[i];
      (*B)[left + k] = left_array2[i];
      k ++;
      i ++;
  }
  while (j < right_length) {
      (*A)[left + k] = right_array[j];
      (*B)[left + k] = right_array2[j];
      k ++;
      j ++;
  }
}



/* eof */
