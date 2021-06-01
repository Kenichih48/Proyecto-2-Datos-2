#ifndef GENETICPUZZLE_MATRIXNODEBP_H
#define GENETICPUZZLE_MATRIXNODEBP_H

#include <iostream>

using namespace std;

template <class T>
class MatrixNodeBP
{
public:
    MatrixNodeBP();
    MatrixNodeBP(T);
    ~MatrixNodeBP();

    T getData();
    void setData(T);
    int getH();
    void setH(int);
    MatrixNodeBP<T>* getRight();
    void setRight(MatrixNodeBP<T>*);
    MatrixNodeBP<T>* getLeft();
    void setLeft(MatrixNodeBP<T>*);
    MatrixNodeBP<T>* getUp();
    void setUp(MatrixNodeBP<T>*);
    MatrixNodeBP<T>* getDown();
    void setDown(MatrixNodeBP<T>*);

    void print();

private:
    T data;
    int H;
    MatrixNodeBP<T>* right = nullptr;
    MatrixNodeBP<T>* left = nullptr;
    MatrixNodeBP<T>* up = nullptr;
    MatrixNodeBP<T>* down = nullptr;
};

///Default constructor
template <typename T>
MatrixNodeBP<T>::MatrixNodeBP() {}

///Constructor per parameter
template <typename T>
MatrixNodeBP<T>::MatrixNodeBP(T data_)
{
    data = data_;
}

///Gets the data of the node
template <typename T>
T MatrixNodeBP<T>::getData()
{
    return MatrixNodeBP::data;
}

///Sets the data of the node
template <typename T>
void MatrixNodeBP<T>::setData(T data_)
{
    MatrixNodeBP::data = data_;
}

///Gets the H of the node
template <typename T>
int MatrixNodeBP<T>::getH()
{
    return MatrixNodeBP::H;
}

///Sets the H of the node
template <typename T>
void MatrixNodeBP<T>::setH(int h)
{
    MatrixNodeBP::H = h;
}

///Gets the right node in matrix
template <typename T>
MatrixNodeBP<T>* MatrixNodeBP<T>::getRight()
{
    return MatrixNodeBP::right;
}

///Sets the right node in matrix
template <typename T>
void MatrixNodeBP<T>::setRight(MatrixNodeBP<T>* node)
{
    MatrixNodeBP::right = node;
}

///Gets the left node in matrix
template <typename T>
MatrixNodeBP<T>* MatrixNodeBP<T>::getLeft()
{
    return MatrixNodeBP::left;
}

///Sets the left node in matrix
template <typename T>
void MatrixNodeBP<T>::setLeft(MatrixNodeBP<T>* node)
{
    MatrixNodeBP::left = node;
}

///Gets the node above in matrix
template <typename T>
MatrixNodeBP<T>* MatrixNodeBP<T>::getUp()
{
    return MatrixNodeBP::up;
}

///Sets the node above in matrix
template <typename T>
void MatrixNodeBP<T>::setUp(MatrixNodeBP<T>* node)
{
    MatrixNodeBP::up = node;
}

///Gets the node below in matrix
template <typename T>
MatrixNodeBP<T>* MatrixNodeBP<T>::getDown()
{
    return MatrixNodeBP::down;
}

///Sets the node below in matrix
template <typename T>
void MatrixNodeBP<T>::setDown(MatrixNodeBP<T>* node)
{
    MatrixNodeBP::down = node;
}

///Prints the data of the node
template <typename T>
void MatrixNodeBP<T>::print()
{
    cout << data << " ";
}

///Deconstructor
template <typename T>
MatrixNodeBP<T>::~MatrixNodeBP() = default;

#endif //GENETICPUZZLE_MATRIXNODEBP_H
