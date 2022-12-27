#pragma once
#pragma once
#include "graphics.h"
#include "stack.h"
#include <conio.h>
#define sizeOfSquare 45
#define SIZE 10000
#define sleep 1000

struct SQUARE {
	int x;
	int y;
	int number;

	SQUARE()
	{

	}

	SQUARE(int x, int y, int number)
	{
		this->x = x;
		this->y = y;
		this->number = number;
	}

	void Draw(int A)
	{
		char text[1000];
		sprintf_s(text, "%d\n", number);
		FrameRectangle(x, y, x + sizeOfSquare, y + sizeOfSquare, A);
		drawText(x, y, x + sizeOfSquare, y + sizeOfSquare, text);
	}
};

void StackToSquare(Stack S, SQUARE* left, SQUARE* right, int x, int y);

void ArrayToSquares(int arr[], int n, SQUARE squares[], int x, int y)
{
	for (int i = 0; i < n; i++)
	{
		squares[i] = SQUARE(x, y, arr[i]);
		x += sizeOfSquare + 5;
	}
}
void PrintArrayOfSquare(SQUARE s[], int n)
{
	for (int i = 0; i < n; i++)
		s[i].Draw(5);
}

void ComparisonCounting(int arr[], int n)
{
	int gap = sizeOfSquare / 2 + 5;

	SQUARE* squares = new SQUARE[n];
	ArrayToSquares(arr, n, squares, 100, 30);
	// khởi tạo mảng COUNT =  0
	int* COUNT = new int[n];
	for (int i = 0; i < n; i++)
		COUNT[i] = 0;
	// chuyển COUNT thành mảng square
	SQUARE* count = new SQUARE[n];
	ArrayToSquares(COUNT, n, count, 100, 150);

	int* result = new int[n];
	for (int i = 0; i < n; i++)
		result[i] = 0;
	SQUARE* RESULT = new SQUARE[n];
	ArrayToSquares(result, n, RESULT, 100, 300);


	char txt[100] = "COUNT";
	

	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[i] < arr[j])
			{
				count[j].number++;
				PrintArrayOfSquare(count, n);
				count[j].Draw(4);
				drawText(1,150, 46, 195, txt);
			}
			else
			{
				count[i].number++;
				PrintArrayOfSquare(count, n);
				count[i].Draw(4);
				drawText(1, 150, 46, 195, txt);
			}
			PrintArrayOfSquare(squares, n);
			arrow(squares[i].x + gap, squares[i].y + sizeOfSquare + 5);
			squares[i].Draw(2);
			squares[j].Draw(3);
			Sleep(sleep);
			cls();
		}
	}
	PrintArrayOfSquare(squares, n);
	PrintArrayOfSquare(count, n);
	for (int i = 0; i < n; i++)
	{
		int j = count[i].number;
		RESULT[j].number = arr[i];
		PrintArrayOfSquare(squares, n);
		squares[i].Draw(2);
		PrintArrayOfSquare(count, n);
		count[i].Draw(2);
		PrintArrayOfSquare(RESULT, n);
		RESULT[j].Draw(3);
		Sleep(sleep);
		cls();
	}
	PrintArrayOfSquare(RESULT, n);
	_getch();
}
void SwapSquare(SQUARE& A, SQUARE& B);

void SelectElementOfArray(SQUARE S[], int n, int index)
{
	PrintArrayOfSquare(S, n);
	S[index].Draw(2);
	Sleep(1000);
}

void MoveX(SQUARE S[], int n, int a, int b)
{
	int gap = (b - a) * (sizeOfSquare + 5);

	int tmp1 = S[a].x;
	int tmp2 = S[b].x;

	int cnt = 0;

	for (int i = 0; i <= gap; i = i + 5)
	{
		S[a].x = tmp1 + i;
		S[b].x = tmp2 - i;
		PrintArrayOfSquare(S, n);
		cls();
	}
	PrintArrayOfSquare(S, n);
}

void MoveY(SQUARE S[], int n, int a, int b, bool isUp)
{
	int m = sizeOfSquare;
	int tmp = S[a].y;
	
	for (int i = 0; i <= m; i = i + 5)
	{
		if (isUp)
		{
			S[a].y = tmp - i - 5;
			S[b].y = tmp - i - 5;
		}

		else
		{
			S[a].y = tmp + i + 5;
			S[b].y = tmp + i + 5;
		}
		PrintArrayOfSquare(S, n);
		cls();
	}
	PrintArrayOfSquare(S, n);
}

void HoanDoi(SQUARE S[], int n, int a, int b)
{
	PrintArrayOfSquare(S, n);
	S[a].Draw(2);
	S[b].Draw(2);
	int tmp = S[a].y;
	MoveY(S, n, a, b, true);
	MoveX(S, n, a, b);
	MoveY(S, n, a, b, false);
	SwapSquare(S[a], S[b]);
	Sleep(1000);
}

void SwapSquare(SQUARE& A, SQUARE& B)
{
	SQUARE TMP = A;
	A = B;
	B = TMP;
}

int* Incresments(int& t, int N) {
	int* H = new int[N];
	for (int j = 0; j < N; j++)
		H[j] = 0;
	H[0] = 1;
	while (3 * H[t] <= N) {
		t++;
		H[t] = 3 * H[t - 1] + 1;
	}
	return H;
}

void ShellSort(int MANG[], int n)
{
	int t = 0;
	int* H = new int[n];
	H = Incresments(t, n);

	SQUARE* arr = new SQUARE[n];
	ArrayToSquares(MANG, n, arr, 30, 100);

	for (int s = t - 1; s >= 0; s--)
	{
		int h = H[s];
		for (int j = h; j < n; j++)
		{
			int i = j - h;
			int K = arr[j].number;
			while (i >= 0)
			{
				if (K >= arr[i].number)
				{
					PrintArrayOfSquare(arr, n);
					arr[j].Draw(3);
					arr[i].Draw(4);
					Sleep(1000);
					break;
				}

				else
				{
					PrintArrayOfSquare(arr, n);
					arr[j].Draw(3);
					arr[i].Draw(2);
					Sleep(1000);
					HoanDoi(arr, n, i, i + h);
					i = i - h;
				}
			}
		}
	}
	PrintArrayOfSquare(arr, n);
}

void QuickSort(int *R, int n) {

	SQUARE* sR = new SQUARE[n + 1];
	ArrayToSquares(R, n, sR, 30, 100);

	PrintArrayOfSquare(sR, n);

	int M = 1;
	if (n <= M) {
		PrintArrayOfSquare(sR, n);
		return;
	}

	Stack S;
	S.Init();	

	
	int l = 0, r = n - 1, i, j, K;
	S.Push(l, r);

	SQUARE* left = new SQUARE[n];
	SQUARE* right = new SQUARE[n];
	
	_getch();
	while (S.isEmpty() == false) 
	{
		StackToSquare(S, left, right, 500, 30);
		i = l + 1, j = r, K = sR[l].number;		

		do {
			while (i <= j && sR[i].number < K) i++;
			while (j >= i - 1 && sR[j].number > K) j--;
			if (j > i) {
				sR[j].Draw(3);
				sR[i].Draw(2);
				Sleep(1000);
				HoanDoi(sR,n,i,j);
			}
		} while (j > i);

		sR[j].Draw(3);
		sR[l].Draw(2);
		Sleep(1000);
		HoanDoi(sR, n, l, j);

		if (r - j >= j - l && j - l > M)
		{						
			S.Push(j + 1, r);
			r = j - 1;
		}
		else
		{
			if (j - l > r - j && r - j > M)
			{
				S.Push(l, j - 1);
				l = j + 1;
			}
			else
			{
				if (r - j > M && M >= j - l)
				{
					l = j + 1;
				}
				else
					if (j - l > M && M >= r - j)
					{
						r = j - 1;
					}
					else
						if (S.isEmpty() == false)
						{
							l = S.Top->l;
							r = S.Top->r;
							S.Pop();
						}
			}
		}
	}
	S.Free();
}

void PrintStack(Stack S)
{
	int n = S.Length();
	SQUARE* squares = new SQUARE[n];

	if (S.isEmpty())
	{
		//DrawStack();
		return;
	}
	Node* t = S.Top;
	int i = 0;
	int tmpX = 300;
	int tmpY = 30;
	int gap = sizeOfSquare + 5;

	while (t != nullptr)
	{
		tmpY += gap;
		SQUARE L = SQUARE(tmpX, tmpY + gap, t->l);
		SQUARE R = SQUARE(L.x + gap, L.y, t->r);
		L.Draw(5);
		R.Draw(5);
		t = t->next;
	}

}

void StackToSquare(Stack S, SQUARE *left, SQUARE *right, int x, int y)
{
	Node* t = S.Top;
	int i = 0;

	while (t != nullptr)
	{
		left[i] = SQUARE(x, y, t->l);
		right[i] = SQUARE(x + sizeOfSquare + 5, y, t->r);
		y += sizeOfSquare + 5;
		t = t->next;
		i++;
	}
}



