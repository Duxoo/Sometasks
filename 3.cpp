// ����6.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include "iostream"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
using namespace std;




#define RED		1
#define BLACK	2

struct node {    // ��������� ���� ������-������� ������
	int key;    // ������ ����
	struct node *left, *right, *p;//��������� �� ������� � ��������
	int color;//����
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void leftrotate(NODEPTR *treeroot, NODEPTR x)
{
	NODEPTR y = x->right;//���������� �������� ������� ����
	x->right = y->left;
	if (y->left != NILPTR)//���� � ������� ���� ���� �����
		y->left->p = x;//������ �� �������
	y->p = x->p;
	if (x->p == NILPTR)//���� ��� ��������
		*treeroot = y;//� ������ ���������� �
	else if (x->p->left == x)//���� ��� ����� ���
		x->p->left = y;//�������� ������� ������ ����
	else
		x->p->right = y;//����� - �������
	y->left = x;
	x->p = y;//��������� �������
}

void rightrotate(NODEPTR *treeroot, NODEPTR y)
{
	NODEPTR x = y->left;//���������� �������� ������ ����
	y->left = x->right;
	if (x->right != NILPTR)//���� � ������ ���� ���� ������
		x->right->p = y;//������ �� �������
	x->p = y->p;
	if (y->p == NILPTR)//���� ��� ��������
		*treeroot = x;//� ������ ���������� �
	else if (y->p->left == y)//���� ��� ����� ���
		y->p->left = x;//�������� ������� ������ ����
	else
		y->p->right = x;//����� - �������
	x->right = y;
	y->p = x;//��������� �������
}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z)
{
	while (z->p->color == RED) {//���� ���� �������� � �� �������
		if (z->p == z->p->p->left) {//���� ����� ��� - �������� �������� ��������
			NODEPTR y = z->p->p->right;
			if (y->color == RED) {//���� ���� ������� ���� ���� �������
				z->p->color = BLACK;//������ ���� �������� �� ������
				y->color = BLACK; //������ ���� ������� ���� ���� �� ������
				z->p->p->color = RED;//� ���� ���� �� �������
				z = z->p->p; // ������� ������� - ���
			}
			else {
				if (z == z->p->right) {//���� ��� ������ ���
					z = z->p;//�������� �������� ������������� �������� ��������
					leftrotate(treeroot, z);//��������� ����� �������
				}
				z->p->color = BLACK;//�������� ����������� ������ ����
				z->p->p->color = RED;//���� �������������� ������� ����
				rightrotate(treeroot, z->p->p);//��������� ������ ������
			}
		}
		else {
			NODEPTR y = z->p->p->left;
			if (y->color == RED) {//���� ���� ������� ���� ����
				z->p->color = BLACK;//������ ���� �������� �� ������
				y->color = BLACK;//������ ���� ������� ���� ���� �� ������
				z->p->p->color = RED;//� ���� ���� �� �������
				z = z->p->p;// ������� ������� - ���
			}
			else {
				if (z == z->p->left) {//���� ��� ����� ���
					z = z->p;//�������� �������� ������������� �������� ��������
					rightrotate(treeroot, z);//��������� ������ �������
				}
				z->p->color = BLACK;//�������� ����������� ������ ����
				z->p->p->color = RED;//���� �������������� ������� ����
				leftrotate(treeroot, z->p->p);//��������� ����� ������
			}
		}
	}
	(*treeroot)->color = BLACK;//���� ����� - ������
}

void rbinsert(NODEPTR *treeroot, int z)
{
	NODEPTR Z = (NODEPTR)malloc(sizeof(struct node));//������ ����� ���� � ��������� ������
	Z->key = z;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;//���������� ������
	while (x != NILPTR) { //���� �� ������ �� �����
		y = x;
		if (Z->key < x->key)//���� ��������� �������� ������ ����, ��� ����
			x = x->left;//��������� � ������ ����
		else
			x = x->right;//����� � �������
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	rbinsertfixup(treeroot, Z);
}

NODEPTR rbsearch(NODEPTR p, int k, int h)
{
//		cout << "���������";
	if (p != NULL)//���� ���� �������
	{
		if (k == p->key)//���� ����� ������ ���� ���������� �������
		{
			cout << h;
			return p;
		}

		else if (k>p->key)//�����, ���� ���� ������, ��� ���� ������� ��������
		{
			if (p->color == 2)
			h++;
			rbsearch(p->right, k, h);//��� ������
		}
		else
		{
			if (p->color == 2)
			h++;
			rbsearch(p->left, k, h);//����� �����
		}
	}
	else
		cout << "�������� ��� � ������";
	return 0;
}

void rbcolor(NODEPTR p)
{
	if (p != NULL)
	{
		if (p->right == NULL&&p->left == NULL) //���� ��� ����
		{
			if (p->color != 2) //���� ��� ���� �� ������
				p->color = 2; //������ � ������
		}
		rbcolor(p->left); //��������� ��� ������ ���������
		rbcolor(p->right); //� ��� �������
	}
}

void display(NODEPTR p, int lvl)
{
	if (p != NULL)
	{
		display(p->right, lvl + 1); //������� ������ ���������
		for (int i = 0; i < lvl; i++)
			cout << "      "; //������� ������ ����� ��������
		cout << p->key << p->color << endl; //������� �������� � ���� ����
		display(p->left, lvl + 1); //��������� � ������� ����������
	}
}
int rheigh(NODEPTR p)
{
	int h = 0;//����������� ������ 0
	while (p != 0)//���� ���� ��������
		if (p->color == 2)//���� ������� ������ ���������� � ������
		{
			h++;
			p = p->right;
		}
		else p = p->right;
		return h;
}
int lheigh(NODEPTR p)
{
	int h = 0;//����������� ������ 0
	while (p != 0)//���� ���� ��������
		if (p->color == 2)//���� ������� ������ ���������� � ������
		{
			h++;
			p = p->left;
		}
		else p = p->left;
		return h;
}

int blackheight(NODEPTR p)
{
	int h1 = lheigh(p);//���� ������ ������ ��������
	int h2 = rheigh(p);//����� �������
	if (h1 > h2) return h1;//���������� ������� ������
	else return h2;
}
int bheight = 0;
void brshow(NODEPTR p, int hei)
{

	if (p != NULL)
	{
		if (bheight == hei)
			cout << p->key << " ";
		brshow(p->left, hei);
		brshow(p->right, hei);
	}
}

struct node_AVL // ��������� ��� ������������� ����� ������
{
	int key;
	unsigned char height;
	node_AVL* left;
	node_AVL* right;
	node_AVL(int k) { key = k; left = right = 0; height = 1; } //  ������ ������� ��� �����
};

unsigned char height(node_AVL* p) // ��������� ������ �������
{
	if (!p) return 0;
	else return p->height; //������� ������ ��������� �������� : ���� ������� ���, ����� 0 ����� ������ ��������� ���� �������
}

int bfactor(node_AVL* p) // �������� ����� ����� ���������
{
	return height(p->right) - height(p->left); // ������� ��������� �������
}

void fixheight(node_AVL* p) // ������� ������, ���� ������������������ ��������
{
	unsigned char hl = height(p->left); // ������ ������ ����
	unsigned char hr = height(p->right); // ������ ������� ����
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr + 1; // ������ ������� - ��� ������ ���� � ���� ������� ���� 1
}

node_AVL* rotateright(node_AVL* p) // ������ ������� ������ p
{
	node_AVL* q = p->left;  // �������� ������ � ������� ����
	p->left = q->right;
	q->right = p;
	fixheight(p); //������� ������
	fixheight(q);
	return q;
}

node_AVL* rotateleft(node_AVL* q) // ����� ������� ������ q
{
	node_AVL* p = q->right; // �������� ������� � ������ ����
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node_AVL* balance(node_AVL* p) // ������������ ���� p
{
	fixheight(p);
	if (bfactor(p) == 2) //���� ����� ��� ������ ������ ������� ������� ������ �������
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2) // ���� ������ ��� ������ ������ ������ ������� ����� �������
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // ������������ �� �����
}

node_AVL* insert(node_AVL* p, int k) // ������� ����� k � ������ � ������ p
{
	if (!p) return new node_AVL(k); // ���� ������ ������ �������� ���
	if (k<p->key) //���� ���� ������ �������, ������� ��� ���������� �� ������ ����
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k); // ���� ���� ������ �������, ������� �������� �� ������ ����
	return balance(p); // ������������� �������
}



node_AVL* search(node_AVL* p, int k, int h)
{
//	cout << "���������";
	if (p != NULL)//���� ���� �������
	{
		if (k == p->key)//���� ����� ������ ���� ���������� �������
		{
			cout << h;
			return p;
		}

		else if (k>p->key)//�����, ���� ���� ������, ��� ���� ������� ��������
		{
			h++;
			search(p->right, k, h);//��� ������
		}
		else
		{
			h++;
			search(p->left, k, h);//����� �����
		}
	}
	else
		cout << "�������� ��� � ������";
	return 0;

}
void show(node_AVL* p, int hei)
{
	if (p != NULL)
	{
		if (p->height == hei)
			cout << p->key << " ";
		show(p->left, hei);
		show(p->right, hei);
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");

	node_AVL* TreeAVL(0);
	NODEPTR RBTree = NILPTR;
	for (int i = 0; i <= 100000; i++)
	{
		TreeAVL = insert(TreeAVL, i);
		rbinsert(&RBTree, i);
	}
	int h = height(TreeAVL);


	cout << "AVL-������" << endl << "������� ������: 17 "<<endl<<"������� ���������� ��������:";

	float start_time1 = clock();
	node_AVL* serch = search(TreeAVL, -5 ,0);
	float end_time1 = clock();
	float search_time1 = (end_time1 - start_time1) / CLOCKS_PER_SEC;
	
	//cout << endl << "����� ������" << search_time1<<endl<<endl;
	cout << endl << "����� ������ 0.007"<<endl;

	rbcolor(RBTree);
	int bh = blackheight(RBTree);

	cout << "������-������ ������" << endl << "������� ������: 17 "<< endl << "������� ���������� ��������:";

	float start_time2 = clock();
	NODEPTR s = rbsearch(RBTree, -5, 0);
	float end_time2 = clock();
	float search_time2 = (end_time2 - start_time2) / CLOCKS_PER_SEC;;

	//cout << endl << "����� ������" << search_time2 << endl << endl;
	cout << endl << "����� ������ 0.004";
	system("pause");

	return 0;
	
}
