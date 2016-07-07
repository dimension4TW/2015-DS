#include <iostream>
#include <stdio.h>
#include <cstring>
#include "P3_0316330.h"

using namespace std;

int main()
{
    const char *a = "4 1 2 -1 3 -1 -1 -1 4";
    BT bt(a);
    bt.inorder();
    cout<<endl;
    bt.preorder();
    cout<<endl;
    bt.postorder();
    return 0;
}

