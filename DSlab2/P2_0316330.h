// Environment: Dev-C++

#include <iostream>
#include <stack>

using namespace std;

class term{ // To store the information we need while doing the permutation, we create a class called term.

public:
    int level;  //  level is to store which level we are perming the numbers.
    int X;  // X is to store the other swapped number.

    term(){
        level = 0;
        X = 0;
    }
    term(int n,int i){
        level = n;
        X = i;
    }
    void set(int n,int i){
        level = n;
        X = i;
    }
};

void non_recursive_perm(char *a, int x, int n)  //  a is the string that we want to perm, x is current level(begin) , n is the terminate level(end).
{
    stack<term> perm;   // we need a stack to store many information about swaps in levels, so we create a stack for term.

    term perm_term(x,x);
    perm.push(perm_term);   // we push the initial status into the stack.


    while(!perm.empty()) {  //  when the is not empty, we continue the perming process. The following program is to replace the recursion function call by using stack.

        while(perm.top().level < n) {   //  First, we generate the next state until we need to output the result of this branch.
            swap(a[perm.top().level], a[perm.top().X]);
            perm_term.set(perm.top().level + 1, perm.top().level + 1);  //  generate the next state.
            perm.push(perm_term);   // store the information in the stack.
        }

        if (perm.top().X == n) {    //  while the branch is in the terminate status, output the result of this branch.
            for (int f = 0; f <= n; f++) {
                cout << a[f];
            }
            cout << endl;
            perm.pop(); //  pop out the information that is used.
        }

        while(!perm.empty() && perm.top().X<=n){    // After we output the result of the branch, we have to swap the characters swapped during the process of perming the next terminate state of a branch.
            swap(a[perm.top().level],a[perm.top().X]);
            if(perm.top().X<n){ //  we have to continue this action until the original for loop is over, that is we are doing exactly the same thing as original codes.
                perm.top().X++;
                break;
            }
            else{
                perm.pop(); // after one for loop is over, we pop out its information.
            }
        }
    }
}
