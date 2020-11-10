//GAUSS ELIMINATION

#include <bits/stdc++.h>

using namespace std;

class Matrix
{

protected:
    int dimensions = 0;
    double **matrix;
    double **iMatrix;

public:

    Matrix(int n)
    {

        dimensions = n;
        createMatrix();
        createIdentityMatrix();

    }

    void createMatrix()
    {

        matrix = new double*[dimensions];

        for(int i = 0; i < dimensions; i++)
        {

            matrix[i] = new double[dimensions];

        }

    }

    void createIdentityMatrix()
    {
        iMatrix = new double*[dimensions];

        for(int i = 0; i < dimensions; i++)
        {

            iMatrix[i] = new double[dimensions];

        }

        for(int i = 0; i < dimensions; i++)
        {

            for(int j = 0; j < dimensions; j++)
            {

                if(i == j)
                {
                    iMatrix[i][j] = 1;
                }
                else
                {
                    iMatrix[i][j] = 0;
                }

            }

        }

    }

    void fillMatrix() {

        for (int i = 0; i < dimensions; i++)
        {

            for (int j = 0; j < dimensions; j++)
            {

                double value = 0;
                cin >> value;
                matrix[i][j] = value;

            }

        }

    }

    void printMatrix() {

        for (int i = 0; i < dimensions; i++) {

            for (int j = 0; j < dimensions; j++) {

                if (j == dimensions - 1) {
                    cout << matrix[i][j];
                } else {
                    cout << matrix[i][j] << " ";
                }

            }

            cout << "\n";

        }

    }

    void swapRow(int row1, int row2)
    {

        double *tempMatrix = new double[dimensions];

        tempMatrix = matrix[row1];
        matrix[row1] = matrix[row2];
        matrix[row2] = tempMatrix;


        double *tempIdentity = new double[dimensions];

        tempIdentity = iMatrix[row1];
        iMatrix[row1] = iMatrix[row2];
        iMatrix[row2] = tempIdentity;

    }

    bool permutation(int column)
    {
        //Value in the main diagonal
        int value = matrix[column][column];
        //Flag to check if the value was changed
        bool flag = false;
        //Value to save the index of the row that has the maximun value of the column (If a value is bigger than the one in the main diagonal)
        int rowIndex = 0;

        for(int i = column+1; i < dimensions; i++)
        {
            //If a value in the column is greater, value changes, row index changes and flag is true
            if(abs(matrix[i][column]) > abs(value))
            {
                value = matrix[i][column];
                rowIndex = i;
                flag = true;
            }
        }

        //If a value was greater, we swap the rows and return true
        if(flag == true)
        {
            swapRow(column,rowIndex);
            return true;
        }
        //Otherwise, nothing happens
        else
        {
            return false;
        }

    }

    bool deleteWithPivot(int row, int column)
    {

         //Value to delete
        double toDelete = matrix[row][column];

//        if(toDelete != 0)
//        {

            //Row of the value to delete
            double *toDeleteRow = matrix[row];

            //Row in the identity Matrix of the value to delete
            double *iToDeleteRow = iMatrix[row];


            //Value of the pivot
            double pivot = matrix[column][column];
            //Temp row of the pivot
            double *pivotRow = new double[dimensions];

            //Temp row of the identity matrix
            double *pivotIdentityRow = new double[dimensions];


            //Get scalar to multiply by the pivot row
            double ratio = toDelete/pivot;

            //Copy values from pivot row to temp row
            for(int i = 0; i < dimensions; i++)
            {

                pivotRow[i] = matrix[column][i];
                pivotIdentityRow[i] = iMatrix[column][i];
            }

            //Pivot row by scalar
            for(int i = 0; i < dimensions; i++)
            {

                toDeleteRow[i] = toDeleteRow[i] - (pivotRow[i]*ratio);

                iToDeleteRow[i] = iToDeleteRow[i] -(pivotIdentityRow[i]*ratio);

            }

            return true;
        //}

        //return false;
    }

    void printIdentity()
    {

        for (int i = 0; i < dimensions; i++) {

            for (int j = 0; j < dimensions; j++) {

                if (j == dimensions - 1) {
                    cout << iMatrix[i][j];
                } else {
                    cout << iMatrix[i][j] << " ";
                }

            }

            cout << "\n";

        }

    }

    bool checkIfAllZerosUnder(int column)
    {

        bool flag = true;

        int i = 1;

        while((column+i) < dimensions)
        {
            if(matrix[column+i][column] != 0)
            {
                flag = false;
            }

            i++;
        }

        return flag;

    }

    bool checkIfAllZerosAbove(int column)
    {

        bool flag = true;

        for(int i = 0; i < column; i++)
        {

            if(matrix[i][column] != 0)
            {
                flag = false;
            }

        }

        return flag;

    }

    double getDeterminant()
    {
        double result = 1;

        for(int i = 0; i < dimensions;i++)
        {

            result *= matrix[i][i];

        }

        return result;

    }

    void normalizeDiagonal()
    {

        for(int i = 0; i < dimensions; i++)
        {

            double denominator = matrix[i][i];

            for(int j = 0; j < dimensions; j++)
            {

                matrix[i][j] = matrix[i][j]/denominator;
                iMatrix[i][j] = iMatrix[i][j]/denominator;

            }

        }

    }

    void printInverse()
    {

        for(int i = 0; i < dimensions; i++)
        {
            for(int j = 0; j < dimensions; j++)
            {
                cout << matrix[i][j] << " ";
            }
            for(int k = 0; k < dimensions; k++)
            {

                if(k == (dimensions-1))
                {
                    cout << iMatrix[i][k];
                }
                else
                {
                    cout << iMatrix[i][k] << " ";
                }


            }

            cout << endl;

        }

    }

};


int main(int argc, char** argv) {


    cout << fixed << setprecision(2);

    //Dimensions of the matrix
      int n = 0;
      cin >> n;

    Matrix aMatrix(n);

    aMatrix.fillMatrix();

    cout<<"step #0: Augmented Matrix"<<endl;

    aMatrix.printInverse();

    cout<<"Direct way:"<<endl;

    int stepCount = 1;
    for(int column = 0; column < n; column++)
    {

//        if(aMatrix.checkIfAllZerosUnder(column) == true)
//        {
//            continue;
//        }

        if(aMatrix.permutation(column)== true)
        {
            cout << "step #"<< stepCount<< ": permutation" <<endl;
//            aMatrix.printMatrix();
//            aMatrix.printIdentity();
            aMatrix.printInverse();
        }

        int row = column+1;
        while(row < n)
        {

            if(aMatrix.deleteWithPivot(row,column) == true)
            {

                cout << "step #"<< stepCount<< ": elimination" <<endl;
//                aMatrix.printMatrix();
//                aMatrix.printIdentity();
                aMatrix.printInverse();
                stepCount++;

            }

            row++;
        }

    }

    cout << "Way back:"<<endl;

    for(int i = (n-1); i >= 0; i--)
    {

//        if(aMatrix.checkIfAllZerosAbove(i) == true)
//        {
//            continue;
//        }

        for(int j = (i-1); j >= 0; j--)
        {

            if(aMatrix.deleteWithPivot(j,i) == true)
            {

                cout << "step #"<< stepCount<< ": elimination" <<endl;
//                aMatrix.printMatrix();
//                aMatrix.printIdentity();
                aMatrix.printInverse();
                stepCount++;

            }

        }

    }

    aMatrix.normalizeDiagonal();
//    aMatrix.printMatrix();
//    aMatrix.printIdentity();
    cout<<"Diagonal normalization:"<<endl;
    aMatrix.printInverse();

    cout <<"result:" <<endl;
    aMatrix.printIdentity();


    return 0;
}

