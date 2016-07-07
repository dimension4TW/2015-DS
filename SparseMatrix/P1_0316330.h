// Environment: Dev-C++
using namespace std;

class MatrixTerm{

    friend class SparseMatrix;  // The basic class to store the factor of every term.
public:
    int row, col;
    double value;

    MatrixTerm(){
        row = 0;
        col = 0;
        value = 0;
    }

    MatrixTerm(int r, int c, int v){
        row = r;
        col = c;
        value = v;
    }
};

class SparseMatrix{


public:
    int rows, cols, terms, capacity;  // Rows to store the amount of the row, cols to store the amount of the col, terms to store the amount of terms, capacity stores the capacity of the SparseMatrix.
    MatrixTerm *smArray;    // Store an array of MatrixTerm to form a SparseMatrix.

    SparseMatrix(){ // Constructor, initializing.
        rows = 0;
        cols = 0;
        terms = 0;
        capacity = 1;
        smArray = new MatrixTerm[capacity];
    }

    SparseMatrix(const SparseMatrix &a){    // Copy constructor.

        rows = a.rows;
        cols = a.cols;
        terms = a.terms;
        capacity = a.capacity;
        smArray = new MatrixTerm[capacity];

        for(int i=0;i<terms;i++){
            smArray[i].row = a.smArray[i].row;
            smArray[i].col = a.smArray[i].col;
            smArray[i].value = a.smArray[i].value;
        }
    }

    ~SparseMatrix(){    // Destructor, delete the smArray we new earlier.
        delete smArray;
    }

    void SetTerms(const int *row, const int *column, const double *value, int n){   // n represents the amount of terms.
        delete [] smArray;  // Delete current smArray to new a new one.
        capacity = 2*n;
        smArray = new MatrixTerm[capacity];
        terms = n;
        int rowmax = row[0];    // use rowmax to store the highest power of x.
        int colmax = column[0]; //use colmax to store the highest power of y.
        for(int i=0;i<n;i++){

            smArray[i].row = row[i];
            smArray[i].col = column[i];
            smArray[i].value = value[i];
            if(row[i] > rowmax){    // To get the biggest power of x so far.
                rowmax = row[i];
            }
            if(column[i] > colmax){ //To get the biggest power of y so far.
                colmax = column[i];
            }
        }

        rows = rowmax;  // Store the power size of x in rows.
        cols = colmax;  // Store the power size of y in cols.
        for(int i=0;i<terms;i++){   //  Get rid of the terms that their value are zero.
            if(smArray[i].value == 0){
                if(i == terms-1){   // If the term are in the last position, just drop it.
                    terms--;
                    cols--;
                    rows--;
                }
                else{   // Otherwise use the last term to cover the current term.
                    smArray[i].row = smArray[terms-1].row;
                    smArray[i].col = smArray[terms-1].col;
                    smArray[i].value = smArray[terms-1].value;
                    terms--;
                    cols--;
                    rows--;
                }
            }
        }

        for(int i=0;i<terms-1;i++){ // Sort the terms by the power of x first then the power of y.
            for(int j=0;j<terms-1;j++){
                if(smArray[j].row < smArray[j+1].row){
                    MatrixTerm tmp;
                    tmp.col = smArray[j].col;
                    tmp.row = smArray[j].row;
                    tmp.value = smArray[j].value;
                    smArray[j].col = smArray[j+1].col;
                    smArray[j].row = smArray[j+1].row;
                    smArray[j].value = smArray[j+1].value;
                    smArray[j+1].col = tmp.col;
                    smArray[j+1].row = tmp.row;
                    smArray[j+1].value = tmp.value;
                }
            }
        }
    }


    SparseMatrix &operator =(const SparseMatrix& a){    // Operator "=" overload.
        delete [] smArray;
        rows = a.rows;
        cols = a.cols;
        terms = a.terms;
        capacity = a.capacity;
        smArray = new MatrixTerm[capacity];

        for(int i=0;i<terms;i++){
            smArray[i].row = a.smArray[i].row;
            smArray[i].col = a.smArray[i].col;
            smArray[i].value = a.smArray[i].value;
        }

        return *this;
    }

    SparseMatrix Add(SparseMatrix a){   // Add function.

        for (int i = 0; i < a.terms; i++) {
            bool flag = false;  // flag to check whether the term can add to an existing term.
            for (int j = 0; j < terms; j++) {
                if ((a.smArray[i].row == smArray[j].row) && (a.smArray[i].col == smArray[j].col)) {
                    smArray[j].value += a.smArray[i].value;
                    flag = true;
                    break;
                }
            }
            if (flag) { // If there is no existing term, add itself to the last position.
                continue;
            }
            else {
                terms++;
                cols++;
                rows++;
                smArray[terms - 1].row = a.smArray[i].row;
                smArray[terms - 1].col = a.smArray[i].col;
                smArray[terms - 1].value = a.smArray[i].value;
            }
        }
        for(int i=0;i<terms;i++){
            if(smArray[i].value == 0){  // Get rid of the terms that their value are zero.
                if(i == terms-1){   // If the term are in the last position, just drop it.
                    terms--;
                    cols--;
                    rows--;
                }
                else{  // Otherwise use the last term to cover the current term.
                    smArray[i].row = smArray[terms-1].row;
                    smArray[i].col = smArray[terms-1].col;
                    smArray[i].value = smArray[terms-1].value;
                    terms--;
                    cols--;
                    rows--;
                }
            }
        }


        for(int i=0;i<terms-1;i++){ // Sort the terms by the power of x first then the power of y.
            for(int j=0;j<terms-1;j++){
                if(smArray[j].row < smArray[j+1].row){
                    MatrixTerm tmp;
                    tmp.col = smArray[j].col;
                    tmp.row = smArray[j].row;
                    tmp.value = smArray[j].value;
                    smArray[j].col = smArray[j+1].col;
                    smArray[j].row = smArray[j+1].row;
                    smArray[j].value = smArray[j+1].value;
                    smArray[j+1].col = tmp.col;
                    smArray[j+1].row = tmp.row;
                    smArray[j+1].value = tmp.value;
                }
            }
        }

        SparseMatrix re(*this);
        return re;
    }
};

class SparsePoly2D: public SparseMatrix{

public:

    void Print(){   // Print function
        for(int i=0;i<terms;i++){
            cout<<"<"<<smArray[i].row<<","<<smArray[i].col<<","<<smArray[i].value<<">"<<endl;
        }
    }

    double Eval(double x, double y){    // Evaluation function, given the value of x and y.

        double re = 0;
        for(int i=0;i<terms;i++){
            double tmpx = 1;
            double tmpy =1;
            for(int j = 0;j<smArray[i].row;j++){
                tmpx *= x;
            }
            for(int j=0;j<smArray[i].col;j++){
                tmpy *= y;
            }
            re += (smArray[i].value * tmpx * tmpy);
        }
        return re;
    }

};