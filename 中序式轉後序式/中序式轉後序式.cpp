// ���Ǧ����Ǧ�.cpp : �w�q�D���x���ε{�����i�J�I�C
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
		if (operands(ori[i]))      //�O�_���B�⤸
		{
			fix[n] = ori[i];
			n++;
			goto here;
		}
		else if (operator(ori[i])) //�O�_���B��l
		{
			if (ori[i] == '(')     //�Y�����A���h�L����PUSH
			{
				push(a, ori[i]);
				goto here;
			}
			else if (ori[i] == ')')     //�Y���k�A���h
			{
				while (a->item[a->top] != '(') //���_POP�ܫ�Ǧ��A����J�����A��
				{
					pop(a, &fix[n]);
					n++;
				}
				if (a->item[a->top] == '(') //�Y�J�����A���A�h�������A��
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
				for (j = 0; op[j] != a->item[a->top]; j++) //��X���|���ݲŸ����u����
					k++;
				for (j = 0;ori[i] != op[j];j++) //��X�즡�Ÿ����u����
					m++;

				if (com[k] > com[m] | com[k] == com[m]) //�Y�즡�Ÿ������u��
				{
					pop(a, &fix[n]); //��X���|���ݲŸ��ܫ�Ǧ�
					n++;
					if (a->top < 0)
						push(a, ori[i]);
					else
						goto against;  //�A������u����
				}
				if (com[k] < com[m]) //�Y�즡�Ÿ��u��
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
	cout << "�i ProgramF �j" << endl << endl << "���Ǧ����Ǧ��G" << endl;
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



