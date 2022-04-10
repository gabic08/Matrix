#include <iostream>
#include <math.h>
using namespace std;

class Matrix {
private:
    //The class Matrix it is represented in the form of an one-dimensional array
    int lines;
    int columns;
    double* matrix;

public:
    Matrix(int lines, int columns); //Constructor
    Matrix(const Matrix& mc); //Copy Constructor
    ~Matrix(); //Destructor

    //Returns the number of rows or columns, respectively
    int getNrLines()const;
    int getNrCols()const;

    //Set the value on line i, column j
    void setElement(int i, int j, double val);

    //Returns the value from line i, column j
    double getElement(int i, int j)const;

    void input(); //Gets the input of the matrix from the user
    void display(); //Displays the elements of the matrix

    //The elements on the main diagonal, respectively the secondary diagonal, are displayed
    void displayLeftDiag();
    void displayRightDiag();

    //The sum of the elements on the main diagonal, respectively the secondary diagonal are returned
    double sumLeftDiag();
    double sumRightDiag();

    //The functions for operator overloading
    Matrix operator + (Matrix mc);
    Matrix operator - (Matrix mc);
    Matrix operator * (Matrix mc);
    Matrix& operator = (const Matrix& mc);

};




Matrix::Matrix(int lines = 0, int columns = 0) {
    this->lines = lines;
    this->columns = columns;

    //Each element in the matrix is ​​initially assigned the value of 0
    this->matrix = new double[lines * columns];
    for (int i = 0; i < lines * columns; i++)
        this->matrix[i] = 0;
}


Matrix::Matrix(const Matrix& mc) {
    //Copies the elements from the received array as a parameter to the initial array
    this->lines = mc.lines;
    this->columns = mc.columns;
    this->matrix = new double[lines * columns];
    for (int i = 0; i < lines * columns; i++)
        this->matrix[i] = mc.matrix[i];
}


Matrix::~Matrix() {
    if (matrix != 0)
        delete[]matrix;
}

int Matrix::getNrLines()const {
    return lines;
}

int Matrix::getNrCols()const {
    return columns;
}



//In the following two functions, it is first checked whether the position received as a
//parameter is inside the matrix, and then it is set or returned, respectively
void Matrix::setElement(int i, int j, double val) {
    if (i >= 0 && i < lines && j >= 0 && j < columns)
        matrix[i * columns + j] = val;
}

double Matrix::getElement(int i, int j)const {
    if (i >= 0 && i < lines && j >= 0 && j < columns)
        return matrix[i * columns + j];
    else
        return 0;
}


void Matrix::input() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "[" << i << "][" << j << "] = ";
            cin >> matrix[i * columns + j];
        }
    }
    cout << endl;
}

void Matrix::display() {
    cout << endl;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++)
            cout << matrix[i * columns + j] << " ";
        cout << endl;
    }
}


//In the following four functions it is first checked whether the number of rows
//is equal to the number of columns to determine if the matrix is ​​square
//and then do the addition / display operations and return the results

double Matrix::sumLeftDiag() {
    int s = 0;
    if (lines == columns) {
        for (int i = 0; i < getNrLines(); i++)
            s += matrix[(i * getNrLines()) + i];
        return s;
    }
    else {
        cout << endl << "The matrix is not square which means it does not have an left diagonal";
        return 0;
    }

}


double Matrix::sumRightDiag() {
    int s = 0;
    if (lines == columns) {
        for (int i = 1; i <= getNrLines(); i++)
            s += matrix[(getNrLines() * i) - i];
        return s;
    }
    else {
        cout << endl << "The matrix is not square which means it does not have an right diagonal";
        return 0;
    }
}

void Matrix::displayLeftDiag() {
    if (lines == columns) {
        cout << endl << "The numbers from the left diagonal are: ";
        for (int i = 0; i < getNrLines(); i++)
            cout << matrix[(i * getNrLines()) + i] << " ";
        cout << " and their sum is: ";
        cout << Matrix::sumLeftDiag();
    }
    else {
        cout << endl << "The matrix is not square which means it does not have an left diagonal";
    }

}

void Matrix::displayRightDiag() {
    if (lines == columns) {
        cout << endl << "The numbers from the right diagonal are: ";
        for (int i = 1; i <= getNrLines(); i++)
            cout << matrix[(getNrLines() * i) - i] << " ";
        cout << " and their sum is: ";
        cout << Matrix::sumRightDiag();
    }
    else {
        cout << endl << "The matrix is not square which means it does not have an right diagonal";
    }
}


//A new matrix 'M' is ​​created that retains the sum of the two Matrices (the main matrix and the one received as a parameter),
//then M is returned
Matrix Matrix::operator + (Matrix mc) {

    Matrix M(mc.getNrLines(), mc.getNrCols());
    int n = mc.getNrLines();
    int m = mc.getNrCols();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            M.matrix[i * m + j] = this->matrix[i * m + j] + mc.matrix[i * m + j];
        }
    }
    return M;
}


Matrix Matrix::operator - (Matrix mc) {

    Matrix M(mc.getNrLines(), mc.getNrCols());
    int n = mc.getNrLines();
    int m = mc.getNrCols();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            M.matrix[i * m + j] = this->matrix[i * m + j] - mc.matrix[i * m + j];
        }
    }
    return M;
}


Matrix Matrix::operator * (Matrix mc) {
    Matrix M(mc.getNrLines(), mc.getNrCols());
    int n = mc.getNrLines();
    int m = mc.getNrCols();

    if (this->getNrCols() == mc.getNrLines()) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {

                M.matrix[i * m + j] = 0;
                for (int k = 0; k < columns; k++)
                    M.matrix[i * columns + j] = M.matrix[i * columns + j] + this->matrix[(i * columns) + k] * mc.matrix[j + (lines * k)];
            }

        return M;
    }

    else
        return 0;
}

//The elements in the main matrix are assigned the elements from the 'mc' matrix
Matrix& Matrix::operator = (const Matrix& mc) {
    int n = mc.getNrLines();
    int m = mc.getNrCols();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            this->matrix[i * m + j] = mc.matrix[i * m + j];
        }
    }
    return *this;
}


//In the main function, two Matrix objects are created and the functions in the class are applied to them
int main() {
    int lines, columns;
    cout << "Insert the number of lines: ";
    cin >> lines;
    cout << "Insert the number of columns: ";
    cin >> columns;

    Matrix a(lines, columns), b(lines, columns), c(lines, columns);
    cout << endl << "The number of lines is: " << a.getNrLines();
    cout << endl << "The number of columns is: " << a.getNrCols() << endl;



    cout << endl << "Insert the elements of the first matrix: " << endl;
    a.input();
    //I  give the third matrix the same elements as the first matrix
    //using the overloaded assignment operator
    c = a;



    //I used the Get function to display the element from line and column 0 and then
    //with the Set function I change the value of the element from line and column 0 to 100
    cout << endl << "The value from position 0, 0 is: " << a.getElement(0, 0) << endl;
    double val = 100;
    cout << "The value of 100 is set on position 0, 0 " << endl << endl;
    a.setElement(0, 0, val);


    cout << endl << endl << "Insert the elements of the second matrix: " << endl;
    b.input();

    cout << "The elements of the first matrix are: ";
    a.display();

    cout << endl << "The elements of the second matrix are: ";
    b.display();

    cout << endl << "The third matrix is equal with the first (before changing the first element) and its elements are: ";
    c.display();


    a.displayLeftDiag();
    b.displayRightDiag();

    cout << endl << endl << "Addition of matrices is: ";
    (a + b).display();

    cout << endl << "Subtraction of matrices is: ";
    (a - b).display();


    //The number of columns of the first Matrix must be equal to the number of rows of the second Matrix;
    //otherwise nothing will be displayed
    cout << endl << "Multiplication of matrices is: ";
    (a * b).display();

    return 0;
}
