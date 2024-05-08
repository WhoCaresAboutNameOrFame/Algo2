// Batcher's Odd Even Merge Sort

#include <iostream>
using namespace std;

void swap(int* i, int* j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

void compare(int* a, int i, int j){
    if(a[i] > a[j]){
        swap(&a[i], &a[j]);
    }
}

void oddEvenMerge(int* arr, int l, int n, int r){
    int m = r*2;
    if(m<n){
        oddEvenMerge(arr, l, n, m);
        oddEvenMerge(arr, l+r, n, m);
        for(int i=l+r; (i+r)<(l+n); i+=m)
            compare(arr, i, i+r);
    }
    else compare(arr, l, l+r);
}

void oddEvenMergeSort(int* arr, int l, int n){
    if(n>1){
        int m = n/2;
        oddEvenMergeSort(arr, l, m);
        oddEvenMergeSort(arr, l+m, m);
        oddEvenMerge(arr, l, n, 1);
    }
}

int main(){
    int size;
    cout<<"Enter the size of array (MUST BE IN POWER OF 2): ";
    cin>>size;
    int arr[size];

    for(int i=0; i<size; i++){
        cout<<"Enter element "<<(i+1)<<": ";
        cin>>arr[i];
    }

    cout<<"\nElements of array before sorting: ";
    for(int i=0; i<size; i++)
        cout<<arr[i]<<" ";

    cout<<"\n";
    oddEvenMergeSort(arr, 0, size);

    cout<<"\nElements of array after sorting: ";
    for(int i=0; i<size; i++)
        cout<<arr[i]<<" ";

    return 0;
}
