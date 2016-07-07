// Environment: Dev-C++
#include <iostream>

using namespace std;

class BSTNode { // construct a class BSTNode as the node of the BST.
    friend class BST;

public:

    int exp; // exponent of the node.
    double coef; // coefficient of the node.
    BSTNode* left; // left child of the node.
    BSTNode* right; // right chold of the node.

    BSTNode() { // default constructor.
        exp = -1;
        coef = 0;
        left = NULL;
        right = NULL;
    }

    BSTNode(const BSTNode& a){ // copy constructor.
        exp = a.exp;
        coef = a.coef;
        left = a.left;
        right = a.right;
    }

    BSTNode(int e, double c){
        exp = e;
        coef = c;
        left = NULL;
        right = NULL;
    }

    ~BSTNode(){ //destructor.
    }

};

class BST{ // to form a Binary Search Tree.

public:
    BSTNode* root;

    BST(){ // constructor
        root = NULL;
    }

    ~BST(){ // destructor
        if(root){
            DeleteTree(root);
            return;
        }
        else{
            return;
        }
    }

    void DeleteTree(BSTNode* current){ // helper function to delete a BST.
        if(current->left){
            DeleteTree(current->left);
        }
        if(current->right){
            DeleteTree(current->right);
        }
        Delete(current);
    }

    BSTNode* Search(const int n) { // to search a node with exponent n.
        BSTNode* t = root; // starting from the root.
        while (t) {
            if (n == t->exp) {
                return t; // found
            }
            t = (n > t->exp) ? t->right : t->left; // or travel to the next node.
        }
        return NULL; // not found.
    }

    void Insert(const int e, const double c) { // insert the node with exponent e and coefficient c.

        BSTNode *t = root, *p = 0;
        while (t) {
            if (e == t->exp) { // duplicate key
                t->coef = e;
                return; // just update element
            }
            p = t;  // remember the parent of next t
            t = (e > t->exp) ? t->right : t->left;
        }
        t = new BSTNode(e,c); // insert a node
        if (root) { // tree not empty
            if (e < p->exp) p->left = t;
            else p->right = t;
        }
        else root = t;
    }

    //delete the node

    BSTNode* FindParent(BSTNode* a){ // helper function to find the parent of a node.
        BSTNode* current = root; // start from the root.
        while(current){
            if(current->left == a || current->right == a){
                return current; // found
            }
            current = (a->exp > current->exp) ? current->right : current->left;
        }
    }

    BSTNode* FindBiggest(BSTNode*a){ // helper function to find the rightmost node of left subtree.
        BSTNode* current = a->left; // move to the left child first.
        while(current->right){
            current = current->right; // keep moving to the right.
        }
        return current;
    }


    void Delete(BSTNode* a){ // the main function to delete a node.
        if(a->left == NULL && a->right == NULL){ // case 1: a is a leaf node.
            if(a == root){
                root = NULL;
            }
            else{
                BSTNode* parent = FindParent(a);
                if(parent->left == a){
                    parent->left = NULL;
                }
                else{
                    parent->right = NULL;
                }
            }
            delete a;
        }
        else if(a->left == NULL || a->right == NULL){ // case 2: a has only one child, then let its child replace it.
            if(a == root){
                if(a->left!=NULL){
                    root = a->left;
                }
                else{
                    root = a->right;
                }
            }
            else{
                BSTNode* parent = FindParent(a);
                if(a->left != NULL){
                    if(parent->right == a){
                        parent->right = a->left;
                    }
                    else if(parent->left == a){
                        parent->left = a->left;
                    }
                }
                else{
                    if(parent->right == a){
                        parent->right = a->right;
                    }
                    else if(parent->left == a){
                        parent->left = a->right;
                    }
                }
            }
            delete a;
        }
        else{ // case 3: a has two children.
            if(a == root){
                BSTNode* biggest = FindBiggest(a); // get the rightmost node of its left subtree.
                root->exp = biggest->exp;
                root->coef = biggest->coef;
                Delete(biggest);
            }
            else{
                BSTNode* biggest = FindBiggest(a); // find the rightmost node of the left subtree.
                a->exp = biggest->exp; // and replace a with it.
                a->coef = biggest->coef;
                Delete(biggest);
            }
        }
    }
};

class PolyBST :public BST{ // struct a polynomial using BST.

    friend ostream& operator<<(ostream &, const PolyBST&);

public:

    PolyBST():BST(){ // constructor

    }

    ~PolyBST(){ // destructor

    }

    PolyBST(const PolyBST& a){ // copy constructor
        *(this) = a;
    }

    void setTerm(int exponent,double coefficient){ // set the exponent and the coefficient of the term.
        if(Search(exponent) != NULL){ // the term exists.
            if(coefficient != 0) {
                Search(exponent)-> coef = coefficient; // update the term.
            }
            else{
                Delete(Search(exponent));
            }
        }
        else{ // the term doesn't exist.
            if(coefficient != 0){
                Insert(exponent, coefficient); // insert the term.
            }
        }
    }


    // Print

    BSTNode* exp_max(BSTNode* current){ // helper function to get the max exponent of the polynomial.
        while(current->right){ //travel to the rightmost node of the BST.
            current = current->right;
        }
        return current;
    }

    void Print(BSTNode* CurrentNode, int max)const{ // main function of printing out the polynomial.
        if(CurrentNode != NULL){
            Print(CurrentNode->right, max); // inorder traversal.
            if(CurrentNode->coef<0){
                cout<<" - ";
                if(CurrentNode->exp != 0){
                    cout<<(CurrentNode->coef)*(-1)<<"*x^"<<CurrentNode->exp;
                }
                else{ // only print the coefficient of the node while the exp is zero.
                    cout<<(CurrentNode->coef)*(-1);
                }
            }
            else{
                if(CurrentNode->exp != max) { // print out the "+" if the node is not the first term of the polynomial.
                    cout << " + ";
                }
                if(CurrentNode->exp != 0){
                    cout<<CurrentNode->coef<<"*x^"<<CurrentNode->exp;
                }
                else{
                    cout<<CurrentNode->coef; // only print the coefficient of the node while the exp is zero.
                }
            }
            Print(CurrentNode->left, max);
        }
    }

    // Add

    void Add(const BSTNode* current){ // main function of adding two polynomial.
        if(current != NULL) {
            Add(current->left);
            Add(current->right);

            BSTNode* currentNode = Search(current->exp);
            if(currentNode != NULL){ // check whether the term exist.
                currentNode->coef += current->coef; // update the term.
                if(currentNode->coef == 0){ // delete the node if its coefficient is zero.
                    Delete(currentNode);
                }
            }
            else{
                setTerm(current->exp,current->coef); // set the new node.
            }
        }
    }
    PolyBST operator + (const PolyBST& a){ // operator "+" overloading.
        PolyBST re;
        re.Copy(*this);
        re.Add(a.root); // call the add function.
        return re;
    }

    //time function for (polynomial * polynomial)

    PolyBST operator * (const PolyBST& a){ // operator "*" overloading.
        PolyBST re;
        re.Time_Travel(this->root,a.root); // call the Time function.
        return re;
    }

    void Time_Travel(const BSTNode* current_a, const BSTNode* current_b){ // travel function for time function.
        if(current_a != NULL){
            Time_Travel(current_a->left,current_b);
            Time_Travel(current_a->right,current_b);
            Time(current_a,current_b); // call the time function.
        }
    }

    void Time(const BSTNode* current_a, const BSTNode* current_b){ // the main function of time operation

        if(current_b != NULL){
            Time(current_a,current_b->left);
            Time(current_a,current_b->right);
            int new_exp = current_a->exp + current_b->exp;
            double new_coef = current_a->coef * current_b->coef;
            BSTNode* currentNode = Search(new_exp); // check whether the term exist.
            if(currentNode != NULL){ // check whether the term exist.
                currentNode->coef += new_coef; // update the term.
                if(currentNode->coef == 0){ // delete the node if its coefficient is zero.
                    Delete(currentNode);
                }
            }
            else{
                setTerm(new_exp,new_coef); // set the new term.
            }
        }
    }

    //time function for (polynomial * constant)

    PolyBST operator* (const double n){ // operator "*" overloading.
        PolyBST re;
        re.Copy(*this);
        re.Time(re.root,n); // call the time function.
        return re;
    }

    void Time(BSTNode* current, const double n){ // main function of Time operation.
        if(current != NULL){ // travel to all the nodes of a PolyBST.
            Time(current->left,n);
            Time(current->right,n);
            current->coef *= n; // update the term.
        }
    }

    // Subtraction

    void Sub(const BSTNode* current){ // main function of subtraction operation.
        if(current != NULL) {
            Sub(current->left);
            Sub(current->right);
            BSTNode *currentNode = Search(current->exp);
            if (currentNode != NULL) { // check whether the term exist.
                currentNode->coef -= current->coef; // update the term.
                if (currentNode->coef == 0) { // delete the node if its coefficient is zero.
                    Delete(currentNode);
                }
            }
            else {
                setTerm(current->exp, (current->coef) * (-1)); // set the new term.
            }
        }
    }
    PolyBST operator - (const PolyBST& a){ // operator "-" overloading.
        PolyBST re;
        re.Copy(*this);
        re.Sub(a.root); // call the Sub to do the subtraction.
        return re;
    }


    // Equation

    void Copy(const PolyBST& OriginPoly){ // driver of the copy function.
        root = Copy(OriginPoly.root);
    }

    BSTNode* Copy(BSTNode* OriginNode){ // workhorse of the copy function.
        if(OriginNode != NULL){
            BSTNode *re = new BSTNode;
            re -> exp = OriginNode->exp;
            re -> coef = OriginNode->coef;
            re->left = Copy(OriginNode->left);
            re -> right = Copy(OriginNode->right);
            return re;
        }
        else{
            return NULL;
        }
    }

    PolyBST &operator = (const PolyBST& a){ // operator "=" overloading.
        this->Copy(a); // call the Copy to do the copying.
        return *this ;
    }

};

ostream &operator <<(ostream& out,const PolyBST& T){ // operator "=" overloading.
    if(T.root != NULL){ // the polyBST is not empty.
        PolyBST re;
        re.Copy(T);
        int max = re.exp_max(re.root)->exp; // get the max exp of the polyBST to handle the sign of the first term.
        T.Print(T.root,max); // call Print to output the result.
    }
    else{
        out<<"0"; // output 0 if the polyBST is empty.
    }
    return out;
}