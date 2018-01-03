//ASSIGNMENT 6 210
//HABIBA GAMAL 900151007
//MAYADA ELGHAMRY 900152853
//FARAH SEIF EL-DIN 900160195

#ifndef PQ_H
#define PQ_H

struct E 
{
	int g;
	int h;
	int sum;
	int **arr;
};

class PQ
{
  public:
	PQ(int **bArray, int n);
	~PQ();
	void insert(E);	// insert element into heap
	E remove();			// remove & return the top of the heap
	void displayBorad(E b, int n);
	bool isEmpty();
private:
   
	int findH(E b, int n); //find sum of all distances
	E *a;   //Heap array
	int N;	// index of last element in the array
	int itemMin; //Very small value at index 0
	void upheap(int k);
	void downheap(int k);
	int size;
};
#include "PQ.cpp"
#endif // PQ_H

