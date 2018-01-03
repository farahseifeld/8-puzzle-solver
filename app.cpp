//ASSIGNMENT 6 210
//HABIBA GAMAL 900151007
//MAYADA ELGHAMRY 900152853
//FARAH SEIF EL-DIN 900160195

#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "PQ.h"
using namespace std;

void readFile(string filename, int ** & board,int&size);
bool equal2D(int ** a, int ** b, int n);
E boardify(int ** b, int n, int cg);
void moves(int ** a, const int n, int ** &up, int ** &down, int** &left, int ** &right);
void getNeighbours(E current, vector <E> &neighbours, int n);
void print(E b, int n);
void solveBoard(int ** b, int n);

bool isFound(vector <E> v, E b, int n);

int main()
{
	int ** board;
	int n;
	
	string filename;
	cout << "Enter file name with puzzle:" << endl;
	cin >> filename;
	//fill initial board with values from file
	readFile(filename, board,n);
	
	//prints the sequence to solve the board
	solveBoard(board, n);

	

	system("pause");
	return 0;
}

//reads input file and returns 2D array with initial board
void readFile(string filename, int ** & board,int&size)
{
	ifstream inp;
	inp.open(filename.c_str());
	if (!inp.is_open())
		cout << "error opening input file" << endl;
	else
	{
		int N;
		//read size of board
		inp >> N;
		int temp;
		board = new int*[N];
		//initialize 2D array
		for (int i = 0; i < N; ++i)
			board[i] = new int[N];

		//read input from file to fill 2D array
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
			{
				inp >> temp;
				board[i][j] = temp;
			}
		size = N;
	}
	inp.close();
}



//get 2D array (board) and calculate the manhattan distance
//and return it in a struct of type E
E boardify(int ** b, int n, int cg) {

	int h = 0;


	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) {
			if (b[i][j] != 0) {
				//get i and j of the value in the goal board
				int ig = (b[i][j] - 1) / n;
				int jg = (b[i][j] - 1) % n;
				//find the difference between the i and j of the current board and the goal board
				//add that to the manhattan distance h
				h += (abs(ig - i) + abs(jg - j));
			}

		}

	//create object of type E and initialize its g,h,sum,and arr
	E board;
	board.g = cg;
	board.h = h;
	board.sum = board.g + board.h;
	board.arr = b;

	//return the board as an object of type E
	return board;


}

void moves(int ** a, const int n, int ** &up, int ** &down, int** &left, int ** &right) 
{
	//calculate the neighbors of the board a
	up = new int*[n];
	down = new int*[n];
	right = new int*[n];
	left = new int*[n];
	//initialize the 2D dynamic arrays
	for (int i = 0; i < n; i++) 
	{
		up[i] = new int[n];
		down[i] = new int[n];
		right[i] = new int[n];
		left[i] = new int[n];
	}

	//copy 2D array a to up,down,right,left
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
		{
			up[i][j] = a[i][j];
			down[i][j] = a[i][j];
			right[i][j] = a[i][j];
			left[i][j] = a[i][j];
		}

	//swap the position with value=0 (blank space) with its adjacent cells
	//either left, right, up or down depending on the position of 0
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
		{
			if (a[i][j] == 0) 
			{
				if (i < n - 1) //swap 0 and the element below it
					swap(down[i][j], down[i + 1][j]);
				if (i > 0) //swap 0 and the element above it
					swap(up[i][j], up[i - 1][j]);
				if (j>0) //swap 0 and the element to its right
					swap(right[i][j], right[i][j - 1]);
				if (j<n - 1) //swap 0 and the element to its left
					swap(left[i][j], left[i][j + 1]);
			}

		}


}

//takes the search node current, and returns a vector with all its neighbouring boards
void getNeighbours(E current, vector <E> &neighbours, int n) {
	
	neighbours.clear();


	int ** up, ** down, ** left, ** right;
	//get the 2D arrays with the possible moves
	moves(current.arr, n, up, down, left, right);

	//check that the 2D arrays with possible moves are not the same as the search node (current)
	if (!equal2D(current.arr, up, n)) {
		//if they are not the same then we turn this 2D array into a struct of type E
		//and add it to the neighbours vector
		neighbours.push_back(boardify(up, n, current.g));
		neighbours[neighbours.size() - 1].g++;
		neighbours[neighbours.size() - 1].sum = neighbours[neighbours.size() - 1].g + neighbours[neighbours.size() - 1].h;
	}
	//repeat above for all arrays with possible moves
	if (!equal2D(current.arr, down, n)) {
		neighbours.push_back(boardify(down, n, current.g));
		neighbours[neighbours.size() - 1].g++;
		neighbours[neighbours.size() - 1].sum = neighbours[neighbours.size() - 1].g + neighbours[neighbours.size() - 1].h;
	}
	if (!equal2D(current.arr, left, n)) {
		neighbours.push_back(boardify(left, n, current.g));
		neighbours[neighbours.size() - 1].g++;
		neighbours[neighbours.size() - 1].sum = neighbours[neighbours.size() - 1].g + neighbours[neighbours.size() - 1].h;
	}
	if (!equal2D(current.arr, right, n)) {
		neighbours.push_back(boardify(right, n, current.g));
		neighbours[neighbours.size() - 1].g++;
		neighbours[neighbours.size() - 1].sum = neighbours[neighbours.size() - 1].g + neighbours[neighbours.size() - 1].h;
	}

}

//checks if 2 2D dynamic arrays are equal
bool equal2D(int ** a, int ** b, int n) 
{

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] != b[i][j])
				return false;
	return true;
}

//prints the 2D array in a struct of type E
void print(E b, int n)
{
	cout << "------------------------" << endl;
	//cout << b.g << "    " << b.h << "    " << b.sum << endl;

	//print 2D array
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << b.arr[i][j] << "    ";
		cout <<endl;
	}
	cout << "------------------------" << endl;
	cout << endl << endl;
}

//solves the board
void solveBoard(int ** board, int n) {

	//vector with search node neighbors
	vector <E> nei;
	E b, tmp;
	bool equal = false;
	//turn the board 2D array into a struct of type E
	b = boardify(board, n, 0);
	//create PQ q
	PQ q(board, n);
	int cnt = 0;
	E parent;
	vector <E> visited;
	while (!equal)
	{
		
		cout << "STEP " << cnt << endl;

		//gets predecessor
		parent = b;

		//removes the board with the minimum sum from the PQ
		b = q.remove();
		//displays this board because it will be part of the solution
		print(b, n);
		//empty PQ because it has definite size and we do not want to exceed it
		while (!q.isEmpty()) {
			tmp = q.remove();
			visited.push_back(tmp);
		}

		//if search node has h=0 then we reached the goal board, so we exit the while loop
		if (b.h == 0) 
			equal = true;
			
		

		//get the neighbors of the search node board
		getNeighbours(b, nei, n);

		//inserts the neighbors into the PQ
		for (int i = 0; i < nei.size(); i++)
		{
			if(!equal2D(nei[i].arr,parent.arr,n) )
				//&& !isFound(visited,nei[i],n))
			//if(!equal2D(nei[i].arr,visited[j].arr,n))
				
			q.insert(nei[i]); //only insert neighbor if it does not equal the predecessor board

		}
		cnt++;
	}

}

bool isFound(vector <E> v, E b, int n) {
	for (int i = 0; i < v.size(); i++)
		if (equal2D(b.arr, v[i].arr, n))
			return true;
	return false;
}