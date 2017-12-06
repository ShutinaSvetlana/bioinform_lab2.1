// BioinfLab2.1.cpp: определ€ет точку входа дл€ консольного приложени€.
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
{ //‘ункци€ вычисл€ет произведение элементов вектора.
	int R_res = 1;
	for (int i = 0; i < n; i++)
		R_res *= V[i];
	return R_res;
}

void Enumeration_Of_Values(int *s, int I, int* count_elem, int n)
{	
	//	‘ункци€ генерирует определенный вектор k-значной логики, где каждый элемент может
	//	принимать разное максимальное значение, в полном переборе вариантов.
	//	√енерируетс€ I вектор в этом полном переборе.
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
	int N = t;//сколько параметров будет у алгоритма
	int* bestS = new int[N];
	int *R = new int[N];//вектор числа повторений у циклов
	for (int i = 0; i < N; i++)
		R[i] = strlen(str[0].c_str()) - l + 1;
	int bestScore = 0;
	int M = Count(R, N);//сколько итераций вообще будет

	int *s = new int[N];//вектор текущих значений индексов имитируемых вложенных циклов

	//основной цикл
	for (int i = 0; i < M; i++)
	{
		Enumeration_Of_Values(s, i, R, N);//теперь в s лежат нужные индексы
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

	ifstream input("input.txt"); // открыли файл дл€ чтени€	
	string l1; //размер шаблона
	input >> l1; //считали кол-во	

	int l; //размер шаблона
	l = atoi(l1.c_str()); //перевод в int	

	string t1; //кол-во строк
	input >> t1; //считали кол-во	

	int t; //кол-во строк	
	t = atoi(t1.c_str()); //перевод в int	

	string* str = new string[t]; //строка
	getline(input, str[0]); //считали первую строку из файла до конца
	for (int i = 0; i < t; i++)
		getline(input, str[i]); //считали строки из файла

	string* result = new string[t]; //результат
	result = SearchMotif(str, t, l); //поиск 

	input.close(); // закрываем файл

	ofstream output; //создаем файл дл€ записи
	output.open("output.txt"); //открыли файл дл€ записи	
	for (int i = 0; i < t; i++)
		output << result[i] << endl;
	output.close(); // закрываем файл

	delete[] str;
	delete[] result;

	return 0;
}

