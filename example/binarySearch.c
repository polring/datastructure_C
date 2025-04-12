#include <stdio.h>
#define error -10000000
int binarySearch(int *arr,int data,int left,int right){
    int mid = (left+right)/2;
    if(left>right){
        return error;
    }
    if(arr[mid]<data){
        return binarySearch(arr,data,mid+1,right);
    }
    else if(arr[mid]>data){
        return binarySearch(arr,data,left,mid-1);
    }
    else{
        return mid;
    }

}
int BinarySearch(int *arr,int data,int left,int right){
    int mid = (left+right)/2;
    while(left<=right){
        mid = (left+right)/2;
        int a = 3;
        if(arr[mid]==data){
            return mid;
        }
        else if(arr[mid]<data){
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
        return error;
    
}



int main(){
    int arr[4] = {1,2,3,4};
    printf("%d\n",BinarySearch(arr,5,0,3));
}