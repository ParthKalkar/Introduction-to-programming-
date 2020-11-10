#include <bits/stdc++.h>

using namespace std;

class Matrix
{

protected:
    int dimensions = 0;
    double **matrix;

public:

    Matrix(int n)
    {

        dimensions = n;
        createMatrix();

    }

    void createMatrix()
    {

        matrix = new double*[dimensions];

        for(int i = 0; i < dimensions; i++)
        {

            matrix[i] = new double[dimensions];

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

    }

    bool permutation(int column)
    {


        //Value in the main diagonal
        int value = matrix[column][column];
        //Flag to check if the value was changed
        bool flag = false;
        //Value to save the index of the row that has the maximun value of the column (If a value is bigger than the one in the main diagonal)
        int rowIndex = 0;


        for(int i = 0; i < dimensions; i++)
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

        if(toDelete != 0)
        {

            //Row of the value to delete
            double *toDeleteRow = matrix[row];

            //Value of the pivot
            double pivot = matrix[column][column];
            //Temp row of the pivot
            double *pivotRow = new double[dimensions];

            //Get scalar to multiply by the pivot row
            double ratio = toDelete/pivot;

            //Copy values from pivot row to temp row
            for(int i = 0; i < dimensions; i++)
            {

                pivotRow[i] = matrix[column][i];

            }

            //Pivot row by scalar
            for(int i = 0; i < dimensions; i++)
            {

                toDeleteRow[i] = toDeleteRow[i] - (pivotRow[i]*ratio);

            }

            return true;
        }

        return false;
    }

    bool checkIfAllZeros(int column)
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

    double getDeterminant()
    {
        double result = 1;

        for(int i = 0; i < dimensions;i++)
        {

            result *= matrix[i][i];

        }

        return result;

    }

};


int main(int argc, char** argv) {


    cout << fixed << setprecision(2);

    //Dimensions of the matrix
    int n = 0;
    cin >> n;

    Matrix aMatrix(n);
    aMatrix.fillMatrix();

    int stepCount = 1;
    for(int column = 0; column < n; column++)
    {

        if(aMatrix.checkIfAllZeros(column) == true)
        {
            continue;
        }
        if(aMatrix.permutation(column)== true)
        {
            cout << "step #"<< stepCount<< ": permutation" <<endl;
            aMatrix.printMatrix();
        }

        int row = column+1;
        while(row < n)
        {

            if(aMatrix.deleteWithPivot(row,column) == true)
            {

                cout << "step #"<< stepCount<< ": elimination" <<endl;
                aMatrix.printMatrix();
                stepCount++;

            }

            row++;
        }

    }


    cout << "result:" << endl << aMatrix.getDeterminant();

    return 0;
}

