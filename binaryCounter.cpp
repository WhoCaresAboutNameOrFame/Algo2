#include <iostream>
#include <vector>
using namespace std;

void increment(int A[], int k) {
    int i = 0;
    for (int j = k-1; j > -1; j--) {
        cout << A[j];
    }
    while (i < k && A[i] == 1){
        A[i] = 0;
        i += 1;
    }
    if (i < k) {
        A[i] = 1;
    }
    // for (int j = k-1; j > -1; j--) {
    //     cout << A[j];
    // }
    cout<<endl;
}

int main() {
    int k;
    cout << "Enter size of Array: "; // << endl;
    cin >> k;
    int A[k];
    for(int i=0; i<k; i++){
        A[i] = 0;
    }
    // vector<int> A(k, 0);
    for (int count = 0; count < (1 << k); count++) {
        increment(A,k);
    }
}
