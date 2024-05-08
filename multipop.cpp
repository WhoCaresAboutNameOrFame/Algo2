// #include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

int main(){
    stack <int> stk;
    int choice;
    int item;
    int limit;
    while(1){
        cout<<"Enter Choice: ";
        cin>>choice;
        switch(choice){
            case 0:
                exit(0);
            case 1:
                cout<<"Enter item: ";
                cin>>item;
                stk.push(item);
                break;
            case 2:
                cout<<"Enter limit: ";
                cin>>limit;
                while(!stk.empty() && limit>0){
                    cout<<stk.top()<<endl;
                    stk.pop();
                    limit--;
                }
                break;
            case 3:
                if(!stk.empty())
                    cout<<stk.top()<<endl;
                else cout<<-1<<endl;
                break;
            default:
                cout<<"Invalid Choice\n";
        }
    }
    return 0;
}