/*
Module : SortedArray.H
Purpose: Interface for an MFC template class which provides sorting and ordered insertion
         derived from the MFC class CArray
Created: PJN / 25-12-1999
History: PJN / 12-01-2000 Fixed a stack overflow in CSortedArray::Sort
         PJN / 21-02-2000 Fixed a number of problems in CSortedArray::Find
         PJN / 22-02-2000 Fixed a problem in CSortedArray::Find when there are no items in the array
         PJN / 29-02-2000 Fixed a problem in CSortedArray::Sort when there are no items in the array

Copyright (c) 1999 - 2000 by PJ Naughter.  
All rights reserved.

*/


////////////////////////////////// Macros ///////////////////////////

#ifndef __SORTEDARRAY_H__
#define __SORTEDARRAY_H__

#ifndef __AFXTEMPL_H__
#include <afxtempl.h> 
#pragma message("To avoid this message, please put afxtempl.h in your PCH")
#endif



/////////////////////////// Classes /////////////////////////////////

//Class which implements sorting for its parent class CArray


template<class TYPE, class ARG_TYPE>
class CSortedArray : public CArray<TYPE, ARG_TYPE>
{
public:
//Constructors / Destructors
  CSortedArray();

//Typedefs
  typedef int COMPARE_FUNCTION(ARG_TYPE element1, ARG_TYPE element2); 
  typedef COMPARE_FUNCTION* LPCOMPARE_FUNCTION;

//Methods
  int  OrderedInsert(ARG_TYPE newElement, int nCount=1);
  void Sort(int nLowIndex=0, int nHighIndex=-1);
  int  Find(ARG_TYPE element, int nLowIndex=0, int nHighIndex=-1);
  void SetCompareFunction(LPCOMPARE_FUNCTION lpfnCompareFunction) { m_lpfnCompareFunction = lpfnCompareFunction; };
  LPCOMPARE_FUNCTION GetCompareFunction() const { return m_lpfnCompareFunction; };

protected:
  LPCOMPARE_FUNCTION m_lpfnCompareFunction;
  void swap(ARG_TYPE element1, ARG_TYPE element2);
};


template<class TYPE, class ARG_TYPE>
CSortedArray<TYPE, ARG_TYPE>::CSortedArray()
{
  m_lpfnCompareFunction = NULL; 
}

template<class TYPE, class ARG_TYPE>
void CSortedArray<TYPE, ARG_TYPE>::swap(ARG_TYPE element1, ARG_TYPE element2)
{
  TYPE temp = element1;
  element1 = element2;
  element2 = temp;
}

template<class TYPE, class ARG_TYPE>
int CSortedArray<TYPE, ARG_TYPE>::OrderedInsert(ARG_TYPE newElement, int nCount)
{
  ASSERT(m_lpfnCompareFunction != NULL); //Did you forget to call SetCompareFunction prior to calling this function

  int nLowIndex = 0;
  int nHighIndex = GetUpperBound();

  //if there are no elements in the array then just insert it at the begining
  if (nHighIndex == -1)
  {
    InsertAt(0, newElement, nCount);
    return 0;
  }

  //do a binary chop to find the location where the element should be inserted
  int nInsertIndex = -1;
  do
  {
    int nCompareLow = m_lpfnCompareFunction(newElement, ElementAt(nLowIndex));
    int nCompareHigh = m_lpfnCompareFunction(newElement, ElementAt(nHighIndex));  
    if (nCompareLow <= 0)
      nInsertIndex = nLowIndex;
    else if (nCompareHigh == 0)
      nInsertIndex = nHighIndex;
    else if (nCompareHigh == 1)
      nInsertIndex = nHighIndex+1;
    else
    {
      ASSERT(nLowIndex < nHighIndex);

      int nCompareIndex;
      if (nHighIndex == (nLowIndex+2))
        nCompareIndex = nLowIndex+1;
      else
        nCompareIndex = ((nHighIndex - nLowIndex)/2) + nLowIndex;

      int nCompare = m_lpfnCompareFunction(newElement, ElementAt(nCompareIndex));
      switch (nCompare)
      {
        case -1:
        {
          if ((nHighIndex - nLowIndex) == 1)
            nHighIndex = nLowIndex;
          else
            nLowIndex = nCompareIndex;
          break;
        }
        case 0:
        {
          nInsertIndex = nCompareIndex;
          break;
        }
        case 1:
        {
          if ((nHighIndex - nLowIndex) == 1)
            nLowIndex = nHighIndex;
          else
            nHighIndex = nCompareIndex;
          break;
        }
        default:
        {
          ASSERT(FALSE); //Your compare function has been coded incorrectly. It should
                         //return -1, 0 or 1 similiar to the way the C Runtime function
                         //"qsort" works
          break;
        }
      }
    }
  }
  while (nInsertIndex == -1);
  
  //Do the actual insert
  InsertAt(nInsertIndex, newElement, nCount);
  return nInsertIndex;
}

template<class TYPE, class ARG_TYPE>
int CSortedArray<TYPE, ARG_TYPE>::Find(ARG_TYPE element, int nLowIndex, int nHighIndex)
{
  ASSERT(m_lpfnCompareFunction != NULL); //Did you forget to call SetCompareFunction prior to calling this function

  //If there are no items in the array, then return immediately
  if (GetSize() == 0)
    return -1;

  int left = nLowIndex;
  int right = nHighIndex;
  if (right == -1)
    right = GetUpperBound();
  ASSERT(left <= right);

  if (left == right) //Straight comparision fewer than 2 elements to search
  {
    BOOL bFound = (m_lpfnCompareFunction(ElementAt(left), element) == 0);
    if (bFound)
      return left;
    else
      return -1;
  }

  //do a binary chop to find the location where the element should be inserted
  int nFoundIndex = -1;
  while (nFoundIndex == -1 && left != right)
  {
    int nCompareIndex;
    if (right == (left+2))
      nCompareIndex = left+1;
    else
      nCompareIndex = ((right - left)/2) + left;

    int nCompare = m_lpfnCompareFunction(ElementAt(nCompareIndex), element);
    switch (nCompare)
    {
      case -1:
      {
        if ((right - left) == 1)
        {
          if (m_lpfnCompareFunction(ElementAt(right), element) == 0)
            nFoundIndex = right;
          else if (m_lpfnCompareFunction(ElementAt(left), element) == 0)
            nFoundIndex = left;
          else
            left = right;
        }
        else
          left = nCompareIndex;
        break;
      }
      case 0:
      {
        nFoundIndex = nCompareIndex;
        break;
      }
      case 1:
      {
        if ((right - left) == 1)
        {
          if (m_lpfnCompareFunction(ElementAt(right), element) == 0)
            nFoundIndex = right;
          else if (m_lpfnCompareFunction(ElementAt(left), element) == 0)
            nFoundIndex = left;
          else
            right = left;
        }
        else
          right = nCompareIndex;
        break;
      }
      default:
      {
        ASSERT(FALSE); //Your compare function has been coded incorrectly. It should
                       //return -1, 0 or 1 similiar to the way the C Runtime function
                       //"qsort" works
        break;
      }
    }
  }
  
  return nFoundIndex;
}



template<class TYPE, class ARG_TYPE>
void CSortedArray<TYPE, ARG_TYPE>::Sort(int nLowIndex, int nHighIndex)
{
  ASSERT(m_lpfnCompareFunction != NULL); //Did you forget to call SetCompareFunction prior to calling this function

  //If there are no items in the array, then return immediately
  if (GetSize() == 0)
    return;

  int left = nLowIndex;
  int right = nHighIndex;
  if (right == -1)
    right = GetUpperBound();

	if (right-left <= 0) //Do nothing if fewer than 2 elements are to be sorted
		return;

	// (not really needed, just to optimize)
	if (right-left == 1)  //Do a simple comparison if only 2 elements
	{
		if (m_lpfnCompareFunction(ElementAt(right), ElementAt(left)) == -1)
			swap(ElementAt(left), ElementAt(right));
		return;
	}

  swap(ElementAt(left), ElementAt((left+right)/2));      //move partition element to begining 
  int last = left;

  for (int i=left+1; i<=right; i++) //Partition
  {
    if (m_lpfnCompareFunction(ElementAt(i), ElementAt(left)) == -1)
      swap(ElementAt(++last), ElementAt(i));
  }

  swap(ElementAt(left), ElementAt(last)); //Restore partition element
  Sort(left, last-1);
  Sort(last+1, right);  
}

#endif //__SORTEDARRAY_H__
