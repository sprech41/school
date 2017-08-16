/******************
 *File: MMheap.cpp
 *Project: Project 4
 *Author: Jacob Sprecher
 *Date: 4/17/2016
 *Email: sprech1@umbc.edu
 *
 *This file contains implementation of all MMHeap functions. It creates and
 *maintains a min-max heap.
 ***********************/
#ifndef MMHEAP_CPP
#define MMHEAP_CPP
#include "MMheap.h"
//#include "MyException.h"
using namespace std;

template <class T>
MMheap<T>::MMheap()
{
  m_size = 0;
}

template <class T>
int MMheap<T>::size()
{
  m_size = heap.size();
  return m_size;
}

template <class T>
void MMheap<T>::dump()
{
  if (size() == 0)
    throw MyException("ERROR: Heap is empty.");

  else
  //Print heap information
  cout << "----- heap dump -----" << endl;
  cout << "Size = " << size() << endl;
  cout << "Minimum = " << getMin() << endl;
  cout << "Maximum = " << getMax() << endl;
  if (int(log2(heap.size())) % 2 == 1)
    cout << "Last level is max level" << endl;
  else
    cout << "Last level is min level" << endl;

  //Print all elements of the heap
  for (unsigned int i = 0; i < heap.size(); i++)
    {
      cout << "H[" << i << "] = " << heap[i] << endl;
    }
}

template <class T>
void MMheap<T>::bubbleUp(int index)
{
  //If we're already at the root, return
  if (index == 0)
    return;
 
  //find parent and grandparent indices
  unsigned int parent = (index - 1) / 2;
  unsigned int grandparent = (index - 3) / 4;
  
  //If the index is at the max level
  if (int(log2(index + 1)) % 2 == 1)
    {
      //Is it on the wrong level?
      if (heap[index].data < heap[parent].data)
	{
	  //Swap the index with its parent
	  swap(heap[index].data,heap[parent].data);
	  
	  //recurse
	  bubbleUp(parent);
	}

      //If its on the right level
      else
	{
	  //if the parent is the root, there is no grandparent. Stop there.
	  if (parent == 0)
	    return;

	  //if the index's data is not greater than the parent and less than the grandparent, swap with the grandparent
	  if (!((heap[index].data > heap[parent].data) && (heap[index].data < heap[grandparent].data)))
	    {
	      swap(heap[index].data, heap[grandparent].data);

	      //recurse
	      bubbleUp(grandparent);
	    }
	}
    }
  
  //if the index is at the min level
  else
    {
      //Is it on the wrong level?
      if (heap[index].data > heap[parent].data)
        {
          //Swap the index with its parent
          swap(heap[index].data,heap[parent].data);

          //recurse
          bubbleUp(parent);
        }

      //If its on the right level
      else
        {
          //if the parent is the root, there is no grandparent. Stop there.
          if (parent == 0)
	      return;

          //if the index's data is not less than the parent and greater than the grandparent, swap with the grandparent
          if (!((heap[index].data < heap[parent].data) && (heap[index].data > heap[grandparent].data)))
            {
              swap(heap[index].data, heap[grandparent].data);

              //recurse
              bubbleUp(grandparent);
            }
        }
    }
}

template <class T>
void MMheap<T>::bubbleDown(int index)
{
  unsigned int leftChild = 2 * index + 1;
  unsigned int leftGrand = 4 * index + 3;
  unsigned int smallest = index;
  unsigned int largest = index;

  //If we're at the bottom level, no need to go further.
  if (leftChild >= heap.size())
    return;

  //if we're deleting max
  if (int(log2(index + 1)) % 2 == 1)
    {
      //check the children to see if any are larger than the largest.
      if (heap[leftChild].data > heap[largest].data)
        largest = leftChild;
      if (heap[leftChild + 1].data > heap[largest].data && leftChild + 1 != heap.size())
        largest = leftChild + 1;

      //check the grandchildren for the same thing while making sure not to go out of range
      for (unsigned int i = 0; i < 4 && leftGrand + i < heap.size(); ++i)
        {
          if (heap[leftGrand + i].data > heap[largest].data)
            largest = leftGrand + i;
        }

      //if after all that the original index was the largest, stop.
      if (index == largest)
        return;

      //swap
      swap(heap[index].data, heap[largest].data);

      //if we swapped with a grandchild, we have to keep going
      if (largest - leftChild > 1)
        {
          unsigned int parent = (largest - 1) / 2;
          if (heap[parent].data > heap[largest].data)
            swap(heap[parent].data, heap[largest].data);

          bubbleDown(largest);
        }
    }

  //if we're deleting min
  else
    {
      //check the children to see if any are smaller than the smallest.
      if (heap[leftChild].data < heap[smallest].data)
	smallest = leftChild;
      if (heap[leftChild + 1].data < heap[smallest].data && leftChild + 1 != heap.size())
        smallest = leftChild + 1;

      //check the grandchildren for the same thing while making sure not to go out of range
      for (unsigned int i = 0; i < 4 && leftGrand + i < heap.size(); ++i)
	{
	  if (heap[leftGrand + i].data < heap[smallest].data)
	    smallest = leftGrand + i;
	}
      
      //if after all that the original index was the smallest, stop.
      if (index == smallest)
	return;

      //swap
      swap(heap[index].data, heap[smallest].data);

      //if we swapped with a grandchild, we have to keep going
      if (smallest - leftChild > 1)
	{
	  unsigned int parent = (smallest - 1) / 2;
	  if (heap[parent].data < heap[smallest].data)
	    swap(heap[parent].data, heap[smallest].data);

	  bubbleDown(smallest);
	}
    }
}

template <class T>
void MMheap<T>::insert(T x)
{
  //Push the value at the end, then bubble up to maintain minmax structure
  entry temp;
  temp.data = x;
  heap.push_back(temp);
  bubbleUp(heap.size() - 1);
}

template <class T>
T MMheap<T>::getMin()
{
  if (size() == 0)
    throw MyException("ERROR: Heap is empty.");
  else
    return heap[0].data;
}

template <class T>
T MMheap<T>::getMax()
{
  if (size() == 0)
    throw MyException("ERROR: Heap is empty.");

  //If there's only one element, that's the max
  if (heap.size() == 1)
    {
      maxIndex = 0;
      return heap[0].data;
    }
  //If there are two elements, max is the child
  else if (heap.size() == 2)
    {
      maxIndex = 1;
      return heap[1].data;
    }
  //If there are more than 2 elements, max is the greatest of the two children.
  else
    {
      if (heap[1].data > heap[2].data)
	{
	  maxIndex = 1;
	  return heap[1].data;
	}
      else
	{
	  maxIndex = 2;
	  return heap[2].data;
	}
    }
}

template <class T>
T MMheap<T>::deleteMin()
{
  if (size() == 0)
    throw MyException("ERROR: Heap is empty.");

  //Save min to a temp location before deleting it so we can return it
  T temp = getMin();

  //If the heap is just the root, just pop it.
  if (heap.size() == 1)
    {
      heap.pop_back();
      return temp;
    }
  else
    {
      //Swap the min with the last element, bubble down
      swap(heap[0].data, heap[heap.size() - 1].data);
      heap.pop_back();
      bubbleDown(0);
      return temp;
    }
}

template <class T>
T MMheap<T>::deleteMax()
{
  if (size() == 0)
    throw MyException("ERROR: Heap is empty.");

  T temp = getMax();
  if (heap.size() == 1)
    {
      heap.pop_back();
      return temp;
    }
  else
    {
      swap(heap[maxIndex].data, heap[heap.size() - 1].data);
      heap.pop_back();
      bubbleDown(maxIndex);
      return temp;
    }
}
#endif
