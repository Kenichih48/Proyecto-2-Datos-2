#ifndef GENETICPUZZLE_MATRIX_H_H
#define GENETICPUZZLE_MATRIX_H_H

#include <iostream>

#include "MatrixNodeBP.h"

using namespace std;

template <class T>
class MatrixGP
{
public:
    MatrixGP(int, int);
    ~MatrixGP();

    MatrixNodeBP<T>* getFirst();
    int getRows();
    int getCols();

    void setRows(int);
    void setCols(int);

    MatrixNodeBP<T>* getNodePos(int, int);
    MatrixNodeBP<T>* getNodeData(MatrixGP<T>*, T);

    void setNode(int, int, T);

    void printMatrix();

private:
    MatrixNodeBP<T> *first;

    int cols;
    int rows;
};

///Constructor per paramater
template <typename T>
MatrixGP<T>::MatrixGP(int rows_, int cols_)
{
    MatrixGP::rows = rows_;
    MatrixGP::cols = cols_;

    MatrixNodeBP<T> *previousRow = nullptr;

    for(int i = 0; i < rows; ++i)
    {
        MatrixNodeBP<T>* columnNode = new MatrixNodeBP<T>();
        MatrixNodeBP<T>* current = columnNode;

        if(previousRow != nullptr)
        {
            columnNode->setUp(previousRow);
            previousRow->setDown(columnNode);
            previousRow = previousRow->getRight();
        }

        if(i == 0)
            MatrixGP::first = columnNode;

        for(int j = 1; j < cols_; ++j)
        {
            MatrixNodeBP<T> * rowNode = new MatrixNodeBP<T>();
            rowNode->setLeft(current);
            current->setRight(rowNode);

            if(previousRow != nullptr){
                rowNode->setUp(previousRow);
                previousRow->setDown(rowNode);
                previousRow = previousRow->getRight();
            }
            current = rowNode;
        }
        previousRow = columnNode;
    }
}

///Gets the first node of the matrix
template <typename T>
MatrixNodeBP<T>* MatrixGP<T>::getFirst()
{
    return MatrixGP::first;
}

///Gets the number of rows of the matrix
template <typename T>
int MatrixGP<T>::getRows()
{
    return MatrixGP::rows;
}

///Gets the number of columns of the matrix
template <typename T>
int MatrixGP<T>::getCols()
{
    return MatrixGP::cols;
}

///Sets the number of rows of a matrix
template <typename T>
void MatrixGP<T>::setRows(int rows_)
{
    MatrixGP::rows = rows_;
}

///Sets the number of rows of a matrix
template <typename T>
void MatrixGP<T>::setCols(int cols_)
{
    MatrixGP::cols = cols_;
}

///Gets a node of the matrix by position
template <typename T>
MatrixNodeBP<T>* MatrixGP<T>::getNodePos(int row, int column)
{
    if(row < rows && column < cols){
        MatrixNodeBP<T>* node = first;

        for (int i = 0; i < row; ++i) {
            node = node->getDown();
        }
        for (int j = 0; j < column; ++j) {
            node = node->getRight();
        }

        return node;
    } else {
        return nullptr;
    }
}


///Gets a node of the matrix by data
template <typename T>
MatrixNodeBP<T>* MatrixGP<T>::getNodeData(MatrixGP<T>* matrix, T data_)
{
    for(int i = 0; i < matrix->getRows(); i++)
    {
        for(int j = 0; j < matrix->getCols(); j++)
        {
            MatrixNodeBP<int>* node = matrix->getNodePos(i, j);
            if(node->getData() == data_)
                return node;
        }
    }
}

///Sets a node in the matrix
template <typename T>
void MatrixGP<T>::setNode(int row, int column, T data_)
{
    if(column < cols && row < rows){
        MatrixNodeBP<T> *node = first;

        for (int i = 0; i < row; ++i) {
            node = node->getDown();
        }

        for (int j = 0; j < column; ++j) {
            node = node->getRight();
        }

        node->setData(data_);
    }
}

///Print the matrix
template <typename T>
void MatrixGP<T>::printMatrix()
{
    MatrixNodeBP<T>* currentColumn = first;

    for(int i = 0; i < rows; i++) {
        currentColumn->print();
        MatrixNodeBP<T>* currentRow = currentColumn->getRight();

        for(int j = 0; j < cols - 1; ++j) {
            currentRow->print();
            currentRow = currentRow->getRight();
        }
        cout << endl;
        currentColumn = currentColumn->getDown();
    }
}

///Deconstructor
template<typename T>
MatrixGP<T>::~MatrixGP() = default;

#endif //GENETICPUZZLE_MATRIX_H_H
