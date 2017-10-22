// ����4.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"
#include <chrono>
using namespace std;

struct node // ��������� ��� ������������� ����� ������
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; } //  ������ ������� ��� �����
};
unsigned char height(node* p) // ��������� ������ �������
{
	if (!p) return 0;
	else return p->height; //������� ������ ��������� �������� : ���� ������� ���, ����� 0 ����� ������ ��������� ���� �������
}

int bfactor(node* p) // �������� ����� ����� ���������
{
	return height(p->right) - height(p->left); // ������� ��������� �������
}

void fixheight(node* p) // ������� ������, ���� ������������������ ��������
{
	unsigned char hl = height(p->left); // ������ ������ ����
	unsigned char hr = height(p->right); // ������ ������� ����
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr+1; // ������ ������� - ��� ������ ���� � ���� ������� ���� 1
}
node* rotateright(node* p) // ������ ������� ������ p
{
	node* q = p->left;  // �������� ������ � ������� ����
	p->left = q->right;
	q->right = p;
	fixheight(p); //������� ������
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ q
{
	node* p = q->right; // �������� ������� � ������ ����
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // ������������ ���� p
{
	fixheight(p);
	if (bfactor(p) == 2) //���� ����� ��� ������, ��� �� 1 ������ ������� ������� ������ �������
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2) // ���������� ��� �������
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // ������������ �� �����
}

node* insert(node* p, int k) // ������� ����� k � ������ � ������ p
{
	if (!p) return new node(k); // ���� ������ ������ �������� ���
	if (k<p->key) //���� ���� ������ �������, ��������� � ����� ���������
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k); // ���� ���� ������ �������, ��������� � ������ ���������
	return balance(p); // ������������� �������
}

void showtree(node *p) //������� ������
{
	if  (p != NULL) //���� ������ �� ������
	{
		cout << p->key<< " "; //������� ������
		showtree(p->left); //���� � ����� ���������
		showtree(p->right); //���� � ������ ���������
	}
}

void printree(node* p, int lvl)
{
	if (p != NULL)
	{
		printree(p->right, lvl + 1);
		for (int i = 0;i < lvl; i++)
			cout << "   ";
		cout << p->key << endl;
		printree(p->left, lvl + 1);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	node *Tree(0);
	auto start = std::chrono::system_clock::now();
	Tree = insert(Tree, 20);
   printree(Tree, 0);
     cout<<endl;
	Tree = insert(Tree, 15);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 9);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 18);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 37);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 35);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 27);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 36);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 40);
	   printree(Tree, 0);
	     cout<<endl;
	Tree = insert(Tree, 51);
	   printree(Tree, 0);
	   cout<<endl;
	   	showtree(Tree);
		cout<<endl;
auto end = std::chrono::system_clock::now();
	auto elapsed = (end - start)/10000;
	std::cout << elapsed.count() << " ������\n";
	system("pause");

    return 0;
}
