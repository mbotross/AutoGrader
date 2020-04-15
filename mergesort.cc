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
  mergesort(temp->A,temp->B,temp->lower_limit,temp->upper_limit-1);
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
  cout<<"here";

  int i=low;
  int j=mid+1;
  int k=0;
  double tmp[high-low+1];
  long tmp2[high-low+1];
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
    (*A)[i]=tmp[i-low];
    (*B)[i]=tmp2[i-low];



  }

}




/* eof */
