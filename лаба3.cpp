// лаба3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<iostream>
#include <chrono>

using namespace std;

struct node
{
	int key; //данные узла
	node *parent; //указатель на родителя
	char color; //цвет
	node *left; //указатель на левого сына
	node *right; //указатель на красного сына
};
class RBtree
{
	node *root; //корень дерева
	node *q; //узел
public:
	RBtree() //пустое дерево
	{
		q = NULL;
		root = NULL;
	}
	void insert(int); //вставка элемента
	void insertfix(node *); //баланс вставки
	void colorfix(node *); //окрашивание листьев в черный (св-в0 2)
	void col();
	void leftrotate(node *); //левый поворот
	void rightrotate(node *); //правый поворот
	void delfix(node *); //баланс удаления
	void disp();
	void display(node *, int); //вывод дерева на экран
	void find();//поиск
};
void RBtree::insert(int z)
{
	node *p, *q;
	node *t = new node; //создем новый узел и заполняем данные
	t->key = z; 
	t->left = NULL;
	t->right = NULL;
	t->color = 'r'; //изначальный цвет - красный
	p = root;
	q = NULL;
	if (root == NULL) //если нет корня
	{
		root = t; //новый узел - корень
		t->parent = NULL;
	}
	else //иначе
	{
		while (p != NULL) //пока не дойдем до конца
		{
			q = p;
			if (p->key<t->key) //если введенное значение больше того, что было
				p = p->right; //переходим к правому сыну
			else
				p = p->left; //иначе к левому
		}
		t->parent = q; //заопминаем родителя
		if (q->key<t->key) //если введенное значение больше родительского
			q->right = t; //добавляем элемент в правое поддерево
		else
			q->left = t; //иначе в левое
	}
	insertfix(t); //выполняем баланс
}
void RBtree::insertfix(node *t)
{
	node *u;
	if (root == t) //если это корень
	{
		t->color = 'b'; //он черный
		return;
	}
	while (t->parent != NULL&&t->parent->color == 'r') //пока есть родители и они черные 
	{
		node *g = t->parent->parent; //создаем новый узел, присваиваем ему значение "дедушки"
		if (g->left == t->parent) //если левый сын - родитель текущего элемента
		{
			if (g->right != NULL) //если есть правый сын
			{
				u = g->right; //новый узел равен правому сыну
				if (u->color == 'r') //если он красный
				{
					t->parent->color = 'b'; //родитель черный
					u->color = 'b'; //перекрашиваем его в черный
					g->color = 'r'; //перекрашиваем "дедушку" в красный
					t = g; //текущий элемент - "дедушка"
				}
			}
			else //иначе
			{
				if (t->parent->right == t) //если это правый сын
				{
					t = t->parent;//текущему элементу присваивается значение родителя
					leftrotate(t); //выполняем левый поворот
				}
				t->parent->color = 'b'; //родителю присваиваем черный цвет
				g->color = 'r'; //присваиваиваем красный цвет
				rightrotate(g); //выполняем правый поворт
			}
		}
		else //иначе
		{
			if (g->left != NULL &&g->left->color=='r') //если есть левый сын и он красный
			{
				u = g->left; //присваиваем узлу значение левого сына
				t->parent->color = 'b'; //родителя текущего элемента перекрашиваем в черный
				u->color = 'b'; //перекрашиваем узел в чёрный
				g->color = 'r'; //перекрашиваем в красный
				t = g; //изменяем значение текущего узла
			}
			else //иначе
			{
				if (t->parent->left == t) //если это левый сын
				{
					t = t->parent; //присваиваем ему значение родителя
					rightrotate(t); //выполняем правый поворот
				}
				t->parent->color = 'b'; //красим родителя в черный
				g->color = 'r'; //красим узел в красный
				leftrotate(g); //выполняем левый поворот
			}
		}
		root->color = 'b';//цвет корня - черный
	}
}

void RBtree::colorfix(node *p) 
{
	if (p != NULL) //если дерево не пустое
	{
		if (p->right == NULL&&p->left == NULL) //если это лист
		{
			if(p->color!='b') //если его цвет не черный
			p->color = 'b'; //красим в черный
		}
		colorfix(p->left); //выполняем для левого поддерева
		colorfix(p->right); //и для правого
	}
}

void RBtree::col()
{
	colorfix(root); //вызываем функцию от корня
}
void RBtree ::find()
{
	int x=0;
	cout<<" Введите искомый ключ : ";
	cin>>x;
 if(root==NULL)
     {
           cout<<"\Дерево пустое\n" ;
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
          cout<<"\nЭлемент не найден.";
     else
     {
                cout<<"\n\t Найденный узел: ";
                cout<<"\n Ключ: "<<p->key;
                cout<<"\n Цвет: ";
    if(p->color=='b')
     cout<<"Черный";
    else
     cout<<"Красный";
                if(p->parent!=NULL)
                       cout<<"\n Родитель: "<<p->parent->key;
                else
                       cout<<"\n Нет родителя.  ";
                if(p->right!=NULL)
                       cout<<"\n Правый сын: "<<p->right->key;
                else
                       cout<<"\n Правого сына нет.  ";
                if(p->left!=NULL)
                       cout<<"\n Левый сын: "<<p->left->key;
                else
                       cout<<"\n Левого сына нет.  ";
                cout<<endl;
     }
}

void RBtree::leftrotate(node *p)
{
	if (p->right == NULL)
		return;
	else
	{
		node *y = p->right; //запоминаем значение правого сына
		if (y->left != NULL) //если у правого сына есть левый
		{
			p->right = y->left; //меняем их местами
			y->left->parent = p;
		}
		else //иначе
			p->right = NULL; //правый сын равен 0
		if (p->parent != NULL) //если есть родитель
			y->parent = p->parent; 
		if (p->parent == NULL) //если его нет
			root = y; //в корень записываем у
		else
		{
			if (p == p->parent->left) //если это левый сын
				p->parent->left = y; //изменяем значени левого сына
			else
				p->parent->right = y; //иначе - правого
		}
		y->left = p; 
		p->parent = y; //закончили поворот
	}
}
void RBtree::rightrotate(node *p)
{
	if (p->left == NULL)
		return;
	else
	{
		node *y = p->left; //запоминаем значение левого сына
		if (y->right != NULL) //если есть правый
		{
			p->left = y->right; //меняем местами
			y->right->parent = p;
		}
		else
			p->left = NULL; //иначе левого сына нет
		if (p->parent != NULL) //если есть родитель
			y->parent = p->parent; //запоминаем его
		if (p->parent == NULL) //если это корень
			root = y; //присваиваем значение
		else
		{
			if (p == p->parent->left) //если это левый сын
				p->parent->left = y; //изменяем его значение
			else
				p->parent->right = y; //иначе изменяем значение правого сына
		}
		y->right = p; //присваиваем правому сыну новое значение
		p->parent = y; //присваиваем значение родительскому узлу
	}
}
void RBtree::disp()
{
	display(root, 0);
}
void RBtree::display(node *p, int lvl)
{
	if (root == NULL) //если нет элементов
	{
		cout << "\nДерево пустое.";
		return;
	}
	if (p != NULL)
	{
		display(p->right, lvl + 1); //выводим правое поддерево
		for (int i = 0;i < lvl; i++)
			cout << "      "; //создаем отступ между уровнями
		cout << p->key <<p->color << endl; //выводим значение и цвет узла
		display(p->left, lvl + 1); //переходим к правому подддереву
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	RBtree obj;
	//заполняем дерево
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
	obj.col(); //окршиваем листья в черный
	obj.disp(); //выводим на экран
		auto start = std::chrono::system_clock::now();
	obj.find();
	auto end = std::chrono::system_clock::now();
	auto elapsed = (end - start)/100000;
	std::cout << elapsed.count() <<"секунд '\n'";

	start = std::chrono::system_clock::now();

	system("pause");
    return 0;
}
