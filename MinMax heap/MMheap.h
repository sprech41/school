/******************
 *File: MMheap.h
 *Project: Project 4
 *Author: Jacob Sprecher
 *Date: 4/17/2016
 *Email: sprech1@umbc.edu
 *
 *Contains prototypes for all MMHeap functions and data members
 ***********************/

#ifndef MMHEAP_H
#define MMHEAP_H
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "MyException.h"
using namespace std;

template <class T>
class MMheap
{
 public:
  //constructor
  MMheap();

  //-------------------------------------------------------
  // Name: size
  // PreCondition: N/A
  // PostCondition: Returns the size of the heap
  //---------------------------------------------------------
  int size();
  
  //-------------------------------------------------------
  // Name: dump
  // PreCondition: N/A
  // PostCondition: Prints the contents of the heap
  //---------------------------------------------------------
  void dump();

  //-------------------------------------------------------
  // Name: insert
  // PreCondition: x is a value with valid comparison operators
  // PostCondition: Inserts a new value into the heap
  //---------------------------------------------------------
  void insert(T x);

  //-------------------------------------------------------
  // Name: getMin
  // PreCondition: N/A
  // PostCondition: Returns the smallest value of the heap
  //---------------------------------------------------------
  T getMin();

  //-------------------------------------------------------
  // Name: getMax
  // PreCondition: N/A
  // PostCondition: Returns the largest value in the heap
  //---------------------------------------------------------
  T getMax();

  //-------------------------------------------------------
  // Name: deleteMin
  // PreCondition: N/A
  // PostCondition: Deletes and returns the smallest value in the heap
  //---------------------------------------------------------
  T deleteMin();

  //-------------------------------------------------------
  // Name: deleteMax
  // PreCondition: N/A
  // PostCondition: Deletes and returns the largest value in the heap
  //---------------------------------------------------------
  T deleteMax();

 private:
  
  struct entry
  {
    T data;
    
    friend ostream& operator<<(ostream& sout, const entry& e)
    {
      sout << e.data;
      return sout;
    }
  };

  //-------------------------------------------------------
  // Name: bubbleUp
  // PreCondition: index is valid in the heap
  // PostCondition: "heapifies" the heap upward
  //---------------------------------------------------------
  void bubbleUp(int index);

  //-------------------------------------------------------
  // Name: bubbleDown
  // PreCondition: index is valid in the heap
  // PostCondition: "heapifies" the heap downward
  //---------------------------------------------------------
  void bubbleDown(int index);

  //Size of the heap
  int m_size;

  //Remembers what the max's index is. Only used in deleteMax
  unsigned int maxIndex;

  //The heap represented as a vector
  vector<entry> heap;
};
#include "MMheap.cpp"
#endif
