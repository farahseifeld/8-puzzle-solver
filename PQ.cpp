//ASSIGNMENT 6 210
//HABIBA GAMAL 900151007
//MAYADA ELGHAMRY 900152853
//FARAH SEIF EL-DIN 900160195

#include <iostream>

using namespace std;

//Constructor
PQ::PQ(int **bArray, int n)
{
	size = 0;
	a = new E[6];
	N = 0;
	itemMin = -32767; // Minimum Heap
	a[0].sum = itemMin;

	E initial;
	//Allocate memory for board 2D array
	initial.arr = new int *[n];
	for (int i = 0; i < n; i++)
		initial.arr[i] = new int[n];

	//Prepare initial element to be inserted in the heap
	//Copy received array to initial element array
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			initial.arr[i][j] = bArray[i][j];

	initial.g = 0;
	initial.h = findH(initial, n);
	initial.sum = initial.h + initial.g;

	cout << endl << "Initial" << endl;
	displayBorad(initial, n);

	insert(initial);
}

//Destructor
PQ::~PQ()
{
	//TODO
	//Write the code of the destructor
	E tmp;
	while (!isEmpty())
		tmp = remove();
	delete tmp.arr;
	delete a;
};

// Insert element (v) in the heap and adjust heap
void PQ::insert(E v)
{
	N++;
	a[N] = v;
	upheap(N);
	size++;
}
void PQ::upheap(int k)
{
	E v = a[k];
	while (a[k / 2].sum >= v.sum)
	{
		a[k] = a[k / 2];   k = k / 2;
	}
	a[k] = v;
}

// remove and return top of the heap, then adjust heap
E PQ::remove()
{
	size--;
	E v = a[1];
	a[1] = a[N--]; downheap(1);
	return v;
}
void PQ::downheap(int k)
{
	int j = 2 * k;     E v = a[k];
	while (j <= N) {
		if ((j < N) && (a[j].sum > a[j + 1].sum)) j++;
		if (v.sum <= a[j].sum) break;
		a[j / 2] = a[j];     j *= 2;
	}
	a[j / 2] = v;
}

//Display a board
void PQ::displayBorad(E b, int n)
{
	cout << "========" << endl << "g " << " " << "h " << " " << "c " << endl;
	cout << b.g << "  " << b.h << "  " << b.sum << endl << "--------" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << b.arr[i][j] << "  ";
		cout << endl;
	}
	cout << "=========" << endl << endl;
}



//find sum of all distances
int PQ::findH(E b, int n)
{
	
	int h = 0;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) {
			if (b.arr[i][j] != 0) {
				int ig = (b.arr[i][j] - 1) / n;
				int jg = (b.arr[i][j] - 1) % n;
				h += (abs(ig - i) + abs(jg - j));
			}

		}
	return h;
}
bool PQ::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}