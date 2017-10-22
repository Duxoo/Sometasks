// ����3.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include<iostream>
#include <chrono>

using namespace std;

struct node
{
	int key; //������ ����
	node *parent; //��������� �� ��������
	char color; //����
	node *left; //��������� �� ������ ����
	node *right; //��������� �� �������� ����
};
class RBtree
{
	node *root; //������ ������
	node *q; //����
public:
	RBtree() //������ ������
	{
		q = NULL;
		root = NULL;
	}
	void insert(int); //������� ��������
	void insertfix(node *); //������ �������
	void colorfix(node *); //����������� ������� � ������ (��-�0 2)
	void col();
	void leftrotate(node *); //����� �������
	void rightrotate(node *); //������ �������
	void delfix(node *); //������ ��������
	void disp();
	void display(node *, int); //����� ������ �� �����
	void find();//�����
};
void RBtree::insert(int z)
{
	node *p, *q;
	node *t = new node; //������ ����� ���� � ��������� ������
	t->key = z; 
	t->left = NULL;
	t->right = NULL;
	t->color = 'r'; //����������� ���� - �������
	p = root;
	q = NULL;
	if (root == NULL) //���� ��� �����
	{
		root = t; //����� ���� - ������
		t->parent = NULL;
	}
	else //�����
	{
		while (p != NULL) //���� �� ������ �� �����
		{
			q = p;
			if (p->key<t->key) //���� ��������� �������� ������ ����, ��� ����
				p = p->right; //��������� � ������� ����
			else
				p = p->left; //����� � ������
		}
		t->parent = q; //���������� ��������
		if (q->key<t->key) //���� ��������� �������� ������ �������������
			q->right = t; //��������� ������� � ������ ���������
		else
			q->left = t; //����� � �����
	}
	insertfix(t); //��������� ������
}
void RBtree::insertfix(node *t)
{
	node *u;
	if (root == t) //���� ��� ������
	{
		t->color = 'b'; //�� ������
		return;
	}
	while (t->parent != NULL&&t->parent->color == 'r') //���� ���� �������� � ��� ������ 
	{
		node *g = t->parent->parent; //������� ����� ����, ����������� ��� �������� "�������"
		if (g->left == t->parent) //���� ����� ��� - �������� �������� ��������
		{
			if (g->right != NULL) //���� ���� ������ ���
			{
				u = g->right; //����� ���� ����� ������� ����
				if (u->color == 'r') //���� �� �������
				{
					t->parent->color = 'b'; //�������� ������
					u->color = 'b'; //������������� ��� � ������
					g->color = 'r'; //������������� "�������" � �������
					t = g; //������� ������� - "�������"
				}
			}
			else //�����
			{
				if (t->parent->right == t) //���� ��� ������ ���
				{
					t = t->parent;//�������� �������� ������������� �������� ��������
					leftrotate(t); //��������� ����� �������
				}
				t->parent->color = 'b'; //�������� ����������� ������ ����
				g->color = 'r'; //�������������� ������� ����
				rightrotate(g); //��������� ������ ������
			}
		}
		else //�����
		{
			if (g->left != NULL &&g->left->color=='r') //���� ���� ����� ��� � �� �������
			{
				u = g->left; //����������� ���� �������� ������ ����
				t->parent->color = 'b'; //�������� �������� �������� ������������� � ������
				u->color = 'b'; //������������� ���� � ������
				g->color = 'r'; //������������� � �������
				t = g; //�������� �������� �������� ����
			}
			else //�����
			{
				if (t->parent->left == t) //���� ��� ����� ���
				{
					t = t->parent; //����������� ��� �������� ��������
					rightrotate(t); //��������� ������ �������
				}
				t->parent->color = 'b'; //������ �������� � ������
				g->color = 'r'; //������ ���� � �������
				leftrotate(g); //��������� ����� �������
			}
		}
		root->color = 'b';//���� ����� - ������
	}
}

void RBtree::colorfix(node *p) 
{
	if (p != NULL) //���� ������ �� ������
	{
		if (p->right == NULL&&p->left == NULL) //���� ��� ����
		{
			if(p->color!='b') //���� ��� ���� �� ������
			p->color = 'b'; //������ � ������
		}
		colorfix(p->left); //��������� ��� ������ ���������
		colorfix(p->right); //� ��� �������
	}
}

void RBtree::col()
{
	colorfix(root); //�������� ������� �� �����
}
void RBtree ::find()
{
	int x=0;
	cout<<" ������� ������� ���� : ";
	cin>>x;
 if(root==NULL)
     {
           cout<<"\������ ������\n" ;
           return  ;
     }
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->key==x)
                found=1;
            if(found==0)
            {
                 if(p->key<x)
                      p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          cout<<"\n������� �� ������.";
     else
     {
                cout<<"\n\t ��������� ����: ";
                cout<<"\n ����: "<<p->key;
                cout<<"\n ����: ";
    if(p->color=='b')
     cout<<"������";
    else
     cout<<"�������";
                if(p->parent!=NULL)
                       cout<<"\n ��������: "<<p->parent->key;
                else
                       cout<<"\n ��� ��������.  ";
                if(p->right!=NULL)
                       cout<<"\n ������ ���: "<<p->right->key;
                else
                       cout<<"\n ������� ���� ���.  ";
                if(p->left!=NULL)
                       cout<<"\n ����� ���: "<<p->left->key;
                else
                       cout<<"\n ������ ���� ���.  ";
                cout<<endl;
     }
}

void RBtree::leftrotate(node *p)
{
	if (p->right == NULL)
		return;
	else
	{
		node *y = p->right; //���������� �������� ������� ����
		if (y->left != NULL) //���� � ������� ���� ���� �����
		{
			p->right = y->left; //������ �� �������
			y->left->parent = p;
		}
		else //�����
			p->right = NULL; //������ ��� ����� 0
		if (p->parent != NULL) //���� ���� ��������
			y->parent = p->parent; 
		if (p->parent == NULL) //���� ��� ���
			root = y; //� ������ ���������� �
		else
		{
			if (p == p->parent->left) //���� ��� ����� ���
				p->parent->left = y; //�������� ������� ������ ����
			else
				p->parent->right = y; //����� - �������
		}
		y->left = p; 
		p->parent = y; //��������� �������
	}
}
void RBtree::rightrotate(node *p)
{
	if (p->left == NULL)
		return;
	else
	{
		node *y = p->left; //���������� �������� ������ ����
		if (y->right != NULL) //���� ���� ������
		{
			p->left = y->right; //������ �������
			y->right->parent = p;
		}
		else
			p->left = NULL; //����� ������ ���� ���
		if (p->parent != NULL) //���� ���� ��������
			y->parent = p->parent; //���������� ���
		if (p->parent == NULL) //���� ��� ������
			root = y; //����������� ��������
		else
		{
			if (p == p->parent->left) //���� ��� ����� ���
				p->parent->left = y; //�������� ��� ��������
			else
				p->parent->right = y; //����� �������� �������� ������� ����
		}
		y->right = p; //����������� ������� ���� ����� ��������
		p->parent = y; //����������� �������� ������������� ����
	}
}
void RBtree::disp()
{
	display(root, 0);
}
void RBtree::display(node *p, int lvl)
{
	if (root == NULL) //���� ��� ���������
	{
		cout << "\n������ ������.";
		return;
	}
	if (p != NULL)
	{
		display(p->right, lvl + 1); //������� ������ ���������
		for (int i = 0;i < lvl; i++)
			cout << "      "; //������� ������ ����� ��������
		cout << p->key <<p->color << endl; //������� �������� � ���� ����
		display(p->left, lvl + 1); //��������� � ������� ����������
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	RBtree obj;
	//��������� ������
	obj.insert(14);
	obj.insert(8);
	obj.insert(17);
	obj.insert(2);
	obj.insert(9);
	obj.insert(15);
	obj.insert(25);
	obj.insert(22);
	obj.insert(27);
	obj.insert(6);
	obj.insert(11);
	obj.insert(0);
	obj.insert(26);
	obj.insert(24);
	obj.insert(21);
	obj.insert(12);
	obj.insert(5);
	obj.insert(16);
	obj.col(); //��������� ������ � ������
	obj.disp(); //������� �� �����
		auto start = std::chrono::system_clock::now();
	obj.find();
	auto end = std::chrono::system_clock::now();
	auto elapsed = (end - start)/100000;
	std::cout << elapsed.count() <<"������ '\n'";

	start = std::chrono::system_clock::now();

	system("pause");
    return 0;
}
