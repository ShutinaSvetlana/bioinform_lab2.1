// BioinfLab2.1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include"algorithm"
using namespace std;

int Count(int* V, int n)
{ //������� ��������� ������������ ��������� �������.
	int R_res = 1;
	for (int i = 0; i < n; i++)
		R_res *= V[i];
	return R_res;
}

void Enumeration_Of_Values(int *s, int I, int* count_elem, int n)
{	
	//	������� ���������� ������������ ������ k-������� ������, ��� ������ ������� �����
	//	��������� ������ ������������ ��������, � ������ �������� ���������.
	//	������������ I ������ � ���� ������ ��������.
	int* count_in_block = new int[n];
	int  count = Count(count_elem, n);
	count_in_block[0] = count / count_elem[0];

	for (int i = 1; i < n; i++)
		count_in_block[i] = count_in_block[i - 1] / count_elem[i];

	for (int i = 0; i < n; i++)
		s[i] = (I / count_in_block[i]) % count_elem[i];

	delete[] count_in_block;
}

string* BestMotif(int* s, string* str, int t, int l)
{
	string* result = new string[t];
	for (int i = 0; i < t; i++)
		result[i] = str[i].substr(s[i], l);
	return result;	
}

int Score(int* s, string* str, int t, int l)
{
	int score = 0;	
	int* count = new int[4];

	int* countAll = new int[l];
	for (int i = 0; i < l; i++)
	{
		for (int i = 0; i < 4; i++)
			count[i] = 0;
		for (int j = 0; j < t; j++)
		{
			if (str[j].c_str()[s[j] + i] == 'A')
				count[0]++;
			else
			{
				if (str[j].c_str()[s[j] + i] == 'C')
					count[1]++;
				else
				{
					if (str[j].c_str()[s[j] + i] == 'G')
						count[2]++;
					else
						count[3]++;
				}
			}

		}
		countAll[i] = max(max(max(count[0], count[1]), count[2]), count[3]);
		score += countAll[i];
	}

	delete[] count;
	delete[] countAll;

	return score;
}


string* SearchMotif(string* str, int t, int l)
{
	int N = t;//������� ���������� ����� � ���������
	int* bestS = new int[N];
	int *R = new int[N];//������ ����� ���������� � ������
	for (int i = 0; i < N; i++)
		R[i] = strlen(str[0].c_str()) - l + 1;
	int bestScore = 0;
	int M = Count(R, N);//������� �������� ������ �����

	int *s = new int[N];//������ ������� �������� �������� ����������� ��������� ������

	//�������� ����
	for (int i = 0; i < M; i++)
	{
		Enumeration_Of_Values(s, i, R, N);//������ � s ����� ������ �������
		if (Score(s, str, t, l) >= bestScore)
		{
			bestScore = Score(s, str, t, l);
			for (int j = 0; j < t; j++)
				bestS[j] = s[j];
		}

	}

	string* result = new string[t];
	result = BestMotif(bestS, str, t, l);

	delete[] R;
	delete[] s;
	delete[] bestS;	

	return result;
}

int main()
{
	setlocale(LC_ALL, ".1251");

	ifstream input("input.txt"); // ������� ���� ��� ������	
	string l1; //������ �������
	input >> l1; //������� ���-��	

	int l; //������ �������
	l = atoi(l1.c_str()); //������� � int	

	string t1; //���-�� �����
	input >> t1; //������� ���-��	

	int t; //���-�� �����	
	t = atoi(t1.c_str()); //������� � int	

	string* str = new string[t]; //������
	getline(input, str[0]); //������� ������ ������ �� ����� �� �����
	for (int i = 0; i < t; i++)
		getline(input, str[i]); //������� ������ �� �����

	string* result = new string[t]; //���������
	result = SearchMotif(str, t, l); //����� 

	input.close(); // ��������� ����

	ofstream output; //������� ���� ��� ������
	output.open("output.txt"); //������� ���� ��� ������	
	for (int i = 0; i < t; i++)
		output << result[i] << endl;
	output.close(); // ��������� ����

	delete[] str;
	delete[] result;

	return 0;
}

