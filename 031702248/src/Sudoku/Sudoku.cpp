#include "pch.h"
#include <iostream>
#include<fstream>
#include<string.h>
#include <typeinfo>
#include<math.h>
using namespace std;

int m, n;
int count_s;
int sudoku_s[9][9];
int N;
bool judge_ranks(int x, int y, int num)
{
	int i;
	for (i = 0;i < m;i++)
	{
		if (sudoku_s[i][y] == num && i != x)
		{
			return false;
		}
		if (sudoku_s[x][i] == num && i != y)
		{
			return false;
		}
	}
	return true;
}

bool judge_palace(int x, int y, int num)
{
	int i,j;
	int r, w;
	if ((m == 3) || (m == 5) || (m == 7))
	{
		return true;
	}
	else if (m == 4)
	{
		r = x / 2;
		w = y / 2;
		for (i = r * 2;i < r * 2 + 2;i++)
		{
			for (j = w * 2;j < w * 2 + 2;j++)
			{
				if ((sudoku_s[i][j] == num) & (i != x) && (j != y))
					return false;
			}
		}
	}
	else if (m == 6)
	{
		r = x / 2;
		w = y / 3;
		for (i = r * 2;i < r * 2 + 2;i++)
		{
			for (j = w * 3;j < w * 3 + 3;j++)
			{
				if ((sudoku_s[i][j] == num) & (i != x) && (j != y))
					return false;
			}
		}
	}
	else if (m == 8)
	{
		r = x / 4;
		w = y / 2;
		for (i = r * 4;i < r * 4 + 4;i++)
		{
			for (j = w * 2;j < w * 2 + 2;j++)
			{
				if ((sudoku_s[i][j] == num) & (i != x) && (j != y))
					return false;
			}
		}
	}
	else if (m == 9)
	{
		r = x / 3;
		w = y / 3;
		for (i = r * 3;i < r * 3+3;i++)
		{
			for (j = w * 3;j < w * 3 + 3;j++)
			{
				if ((sudoku_s[i][j] == num) & (i != x) && (j != y))
					return false;
			}
		}
	}
	else
		return false;

	return true;
}
bool parse_s(int loop)
{
	int i;
	int j;
	i = loop / m;//m是宫格阶级，i是行，j是列
	j = loop % m;
	if (loop == m * m)//循环次数loop循环m*m次结束函数
	{
		return true;
	}
	if (sudoku_s[i][j] == 0)//为0，进行循环
	{
		for (int number = 1;number <= m;number++)//number是1-m宫格阶级
		{
			sudoku_s[i][j] = number;
			if (judge_ranks(i, j, number) && judge_palace(i, j, number))//判断行，列，宫
			{
				if (parse_s(loop))//判断通过，递归
					return true;
			}
			sudoku_s[i][j] = 0;//不通过，重置为0，再循环
		}
	}
	else
		return parse_s(loop + 1);//不为0，进入下一层递归
	return false;//错解，返回上层
}

void output_s(int panmian)
{
	ofstream output;
	output.open("output.txt", ios::app);
	for (int i = 0;i < m;i++)
	{
		for (int j = 0; j < m;j++)
		{
			output << sudoku_s[i][j] << " ";
		}
		output << endl;
	}
	if (panmian != n)output << endl;
	output.close();
}

void input_s()
{
	ifstream myfile("input.txt");
	int i = 0;
	int j = 0;
	count_s = 0;
	N = 1;
	while (!myfile.eof())
	{
		myfile >> sudoku_s[i][j];
		count_s++;
		j++;
		if (j == m)
		{
			i++;
			j = 0;
		}
		if ((count_s == (m * m)) && (N <= n))
		{
			parse_s(0);
			output_s(N);
			count_s = 0;
			N++;
			i = 0;
			j = 0;
		}

	}
	myfile.close();
}

int main(int argc, char* argv[])
{
	if (argc < 9) 
	{
		cout<< "参数不足"<<endl;
		exit(1);
	}
			m = atoi(argv[2]);
			n = atoi(argv[4]);
			if (m > 9 || m < 3)
			{
				cout << "参数不符合";
				exit(2);
			}
	input_s();

	return 0;
}
