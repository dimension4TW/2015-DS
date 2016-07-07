// Environment: Dev-C++
#include <iostream>
#include <stack>
#include <deque>
#include <list>

using namespace std;

class MyGraph{
public:

    list<int>* my_list;
    int* check_used; // to remember whether the number is used or not.
    int N; // the number of the vertices.
    int component; // number of the component.
    stack<int> mystack;
    deque<int> mydeque;

    MyGraph(int n ,int input[]) {


        N = n;
        component = 0;
        int input_counter = 0;
        my_list = new list<int>[N];
        check_used = new int[N];


        for(int i=0;i<N;i++){ // initialize the check_used function.
            check_used[i] = 0;
        }

        int **a = new int *[n]; // two dimension array to store the information of the matrix.
        for (int i = 0; i < n; i++) {
            a[i] = new int[n];
        }

        for (int i = 0; i < n; i++) { // to store the information in the matrix in the two dimension array.
            for (int j = 0; j < n; j++) {
                a[i][j] = input[input_counter++];
            }
        }

        for(int i=0;i<N;i++){ // store the information in the two dimension array in the adjacency-list.
            for(int j=0;j<N;j++){
                if(a[i][j] == 1) {
                    my_list[i].push_back(j);
                }
            }
        }

        for(int i=0;i<N;i++) {
            delete [] a[i];
        }
        delete [] a;

    }

    ~MyGraph() { // destructor

        delete [] check_used;
        delete [] my_list;
    }


    void CC(){ // function CC to find the connected components.
        for(int i=0;i<N;i++){ // initialize the check_used function.
            check_used[i] = 0;
        }

        for(int i=0;i<N;i++){
            //DFS(i); // call DFS or BFS function.
            BFS(i);
        }
    }

    void DFS(int I) {

        if (check_used[I] == 0) { // the number has not been used.
            cout << "Component#"<< ++component << ": "; // output the information about the component.
            mystack.push(I); // push to stack.
            while (!mystack.empty()) {
                int j = mystack.top();
                mystack.pop();
                if(check_used[j] == 0) cout << j << " "; // output the number at the top.
                check_used[j] = 1; // set the number to used.
                for (list<int>::iterator i = my_list[j].begin(); i!= my_list[j].end(); i++) {
                    if (check_used[*i] == 0) { // check if the vertex i is connected and has not been printed out.
                        mystack.push(*i); // push to stack.
                    }
                }
            }
            cout<<endl;
        }
    }

    void BFS(int I) {
        if (check_used[I] == 0) { // the number has not been used.
            cout << "Component#" << ++component << ": ";
            mydeque.push_back(I); // push it to the deque.
            while (!mydeque.empty()) {
                int j = mydeque.front();
                mydeque.pop_front();
                if(check_used[j] == 0) cout << j << " "; // output the number at the front.
                check_used[j] = 1; // set the number to used.
                for (list<int>::iterator i = my_list[j].begin(); i!= my_list[j].end(); i++) {
                    if (check_used[*i] == 0) { // check if the vertex i is connected and has not been printed out.
                        mydeque.push_back(*i); // push to deque.
                    }
                }
            }
            cout<<endl;
        }
    }
};
