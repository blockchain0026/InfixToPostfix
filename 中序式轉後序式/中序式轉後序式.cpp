// 中序式轉後序式.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
using namespace std;

#define operator(ch) ((ch) == '(')|((ch) == ')')|((ch) == '+')|((ch)=='-')|((ch)=='*')|((ch)=='/')?1:0
#define operands(ch) ((ch) >= 'a') && ((ch) <= 'z')?1:0
#define MAX_N 1000

typedef struct STACK
{
	char item[MAX_N];
	int top = -1;
}stack_o;

void push(stack_o *a, char op)
{
	if (a->top < (MAX_N - 1))
	{
		a->top++;
		a->item[a->top] = op;
	}
}

void pop(stack_o *a, char *op)
{
	if (a->top >= 0)
	{
		*op = a->item[a->top];
		a->top--;
	}
}

void in_to_post(char ori[MAX_N], char fix[MAX_N])
{
	stack_o *a = new stack_o;
	char op[5] = { '(','+','-','*','/' };
	int com[5] = { 0,1,1,2,2 };
	char token;
	int i = 0, j = 0, n = 0;

	while (ori[i] != '\0')
	{
		if (operands(ori[i]))      //是否為運算元
		{
			fix[n] = ori[i];
			n++;
			goto here;
		}
		else if (operator(ori[i])) //是否為運算子
		{
			if (ori[i] == '(')     //若為左括弧則無條件PUSH
			{
				push(a, ori[i]);
				goto here;
			}
			else if (ori[i] == ')')     //若為右括弧則
			{
				while (a->item[a->top] != '(') //不斷POP至後序式，直到遇見左括號
				{
					pop(a, &fix[n]);
					n++;
				}
				if (a->item[a->top] == '(') //若遇見左括號，則消除左括號
					a->top--;
				goto here;
			}

			if ((a->top) < 0)
			{
				push(a, ori[i]);

				goto here;
			}

			if ((a->top) >= 0)
			{
			against:
				int k = 0, m = 0;
				for (j = 0; op[j] != a->item[a->top]; j++) //找出堆疊頂端符號之優先序
					k++;
				for (j = 0;ori[i] != op[j];j++) //找出原式符號之優先序
					m++;

				if (com[k] > com[m] | com[k] == com[m]) //若原式符號較不優先
				{
					pop(a, &fix[n]); //輸出堆疊頂端符號至後序式
					n++;
					if (a->top < 0)
						push(a, ori[i]);
					else
						goto against;  //再次比較優先序
				}
				if (com[k] < com[m]) //若原式符號優先
					push(a, ori[i]);
			}
		}
	here:
		i++;
	}
	while (a->top != -1)
	{
		pop(a, &fix[n]);
		n++;
	}
	fix[n] = '\0';
}


int main()
{
	cout << "【 ProgramF 】" << endl << endl << "中序式轉後序式：" << endl;
	while (true)
	{
		char fix[100];
		char *orn = new char[1000];
		char test;
		cin >> orn;
		in_to_post(orn, fix);



		cout << fix << endl << endl;
	}
	system("pause");

	return 0;
}



