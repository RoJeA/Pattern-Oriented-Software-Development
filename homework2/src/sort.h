#include<functional>
#include<algorithm>
#include<vector>

#ifndef SORT_H
#define SORT_H

class Sort{
public:
  Sort(std::vector<Shape*>* v):_v(v){}
  // The argument ** Accept comparison ** can accept lambda, function, and object
  void sortArea(function<bool (Shape *a,Shape *b)>AscendDescend)
  {
     std::sort(_v->begin(), _v->end(), AscendDescend);
  }

  void sortPerimeter(function<bool (Shape *a,Shape *b)>AscendDescend)
  {
    std::sort(_v->begin(), _v->end(), AscendDescend);
  }

  void sortSumOfSquares(function<bool (Shape *a,Shape *b)>AscendDescend)
  {
    std::sort(_v->begin(), _v->end(), AscendDescend);
  }

  int partition (function<bool (Shape *a,Shape *b)>CompFunc, int low, int high)
  {
    vector <Shape*> :: iterator pivot = (_v->begin())+high; // pivot
     int i = low-1;
    for(vector <Shape*> :: iterator j = (_v->begin())+low ; j != (_v->begin())+high; j++)
    {
      if(CompFunc(*j,*pivot))
      {
        i++;
        swap(_v->at(i),*j);
      }
    }
    i++;
    std::swap(_v->at(i), _v->at(high));
    return i;
  }

  void qsortProccess(function<bool (Shape *a, Shape *b)>CompQSort,int loo,int hii)
  {
    if(loo < hii)
    {
      int pivot=partition(CompQSort,loo,hii);
      qsortProccess(CompQSort,loo,pivot-1);
      qsortProccess(CompQSort,pivot+1,hii);
    }
  }

  void quickSort(function<bool (Shape *a, Shape *b)>CompQSort)
  {
    int loo = 0;
    int hii = std::distance(_v->begin(),_v->end())-1;
    qsortProccess(CompQSort,loo,hii);
  }

private:
  std::vector<Shape*>* _v;
};


bool areaAscendingComparison(Shape *a, Shape *b)
{
  return a->area() < b->area();
};
bool areaDescendingComparison(Shape *a, Shape *b)
{
  return a->area() > b->area();
};
bool perimeterAscendingComparison(Shape *a, Shape *b)
{
  return a->perimeter() < b->perimeter();
};
bool perimeterDescendingComparison(Shape *a, Shape *b)
{
  return a->perimeter() > b->perimeter();
};
bool sumOfSquaresAscendingComparison(Shape *a, Shape *b)
{
  return a->sumOfSquares() < b->sumOfSquares();
};
bool sumOfSquaresDescendingComparison(Shape *a, Shape *b)
{
  return a->sumOfSquares() > b->sumOfSquares();
};

//You should use following objects as parameter for Sort::sortArea(), Sort::sortPerimeter(), Sort::sortSumOfSquares(), Sort::quickSort()
//In the loop of the quickSort algorithm, use std::vector<Shape*>::Iterator to control your vector rather than index
class AscendingComparison
{
public:
  AscendingComparison(string typeOfAscend):_typeOfAscend(typeOfAscend){}
  bool operator()(Shape *a, Shape *b)
  {
      if(_typeOfAscend=="area")
      {
        return a->area() < b->area();
      }
      else if(_typeOfAscend=="perimeter")
      {
        return a->perimeter() < b->perimeter();
      }
      else if(_typeOfAscend=="sumOfSquares")
      {
        return a->sumOfSquares() < b->sumOfSquares();
      }
      else
      {
        exit(-1);
      }
  }
private:
  string _typeOfAscend;
};

class DescendingComparison
{
public:
  DescendingComparison(string typeOfDescend):_typeOfDescend(typeOfDescend){}
  bool operator()(Shape *a, Shape *b)
  {
    if(_typeOfDescend=="area")
    {
      return a->area() > b->area();
    }
    else if(_typeOfDescend=="perimeter")
    {
      return a->perimeter() > b->perimeter();
    }
    else if(_typeOfDescend=="sumOfSquares")
    {
      return a->sumOfSquares() > b->sumOfSquares();
    }
    else
    {
      exit(-1);
    }
  }
private:
string _typeOfDescend;

};

#endif
