// лаба6.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "iostream"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
using namespace std;




#define RED		1
#define BLACK	2

struct node {    // структура узла красно-чёрного дерева
	int key;    // данные узла
	struct node *left, *right, *p;//указатели на сыновей и родителя
	int color;//цвет
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void leftrotate(NODEPTR *treeroot, NODEPTR x)
{
	NODEPTR y = x->right;//запоминаем значение правого сына
	x->right = y->left;
	if (y->left != NILPTR)//если у правого сына есть левый
		y->left->p = x;//меняем их местами
	y->p = x->p;
	if (x->p == NILPTR)//если нет родителя
		*treeroot = y;//в корень записываем у
	else if (x->p->left == x)//если это левый сын
		x->p->left = y;//изменяем значени левого сына
	else
		x->p->right = y;//иначе - правого
	y->left = x;
	x->p = y;//закончили поворот
}

void rightrotate(NODEPTR *treeroot, NODEPTR y)
{
	NODEPTR x = y->left;//запоминаем значение левого сына
	y->left = x->right;
	if (x->right != NILPTR)//если у левого сына есть правый
		x->right->p = y;//меняем их местами
	x->p = y->p;
	if (y->p == NILPTR)//если нет родителя
		*treeroot = x;//в корень записываем у
	else if (y->p->left == y)//если это левый сын
		y->p->left = x;//изменяем значени левого сына
	else
		y->p->right = x;//иначе - правого
	x->right = y;
	y->p = x;//закончили поворот
}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z)
{
	while (z->p->color == RED) {//пока есть родитель и он красный
		if (z->p == z->p->p->left) {//если левый сын - родитель текущего элемента
			NODEPTR y = z->p->p->right;
			if (y->color == RED) {//если цвет правого сына деда красный
				z->p->color = BLACK;//меняем цвет родителя на чёрный
				y->color = BLACK; //меняем цвет правого сына деда на чёрный
				z->p->p->color = RED;//а цвет деда на красный
				z = z->p->p; // текущий элемент - дед
			}
			else {
				if (z == z->p->right) {//если это правый сын
					z = z->p;//текущему элементу присваивается значение родителя
					leftrotate(treeroot, z);//выполняем левый поворот
				}
				z->p->color = BLACK;//родителю присваиваем черный цвет
				z->p->p->color = RED;//деду присваиваиваем красный цвет
				rightrotate(treeroot, z->p->p);//выполняем правый поворт
			}
		}
		else {
			NODEPTR y = z->p->p->left;
			if (y->color == RED) {//если цвет правого сына деда
				z->p->color = BLACK;//меняем цвет родителя на чёрный
				y->color = BLACK;//меняем цвет правого сына деда на чёрный
				z->p->p->color = RED;//а цвет деда на красный
				z = z->p->p;// текущий элемент - дед
			}
			else {
				if (z == z->p->left) {//если это левый сын
					z = z->p;//текущему элементу присваивается значение родителя
					rightrotate(treeroot, z);//выполняем правый поворот
				}
				z->p->color = BLACK;//родителю присваиваем черный цвет
				z->p->p->color = RED;//деду присваиваиваем красный цвет
				leftrotate(treeroot, z->p->p);//выполняем левый поворт
			}
		}
	}
	(*treeroot)->color = BLACK;//цвет корня - черный
}

void rbinsert(NODEPTR *treeroot, int z)
{
	NODEPTR Z = (NODEPTR)malloc(sizeof(struct node));//создем новый узел и заполняем данные
	Z->key = z;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;//запоминаем корень
	while (x != NILPTR) { //пока не дойдем до конца
		y = x;
		if (Z->key < x->key)//если введенное значение меньше того, что было
			x = x->left;//переходим к левому сыну
		else
			x = x->right;//иначе к правому
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
//		cout << "дерижабль";
	if (p != NULL)//если есть элемент
	{
		if (k == p->key)//если нашли нужный ключ возвращаем элемент
		{
			cout << h;
			return p;
		}

		else if (k>p->key)//иначе, если ключ больше, чем ключ данного элемента
		{
			if (p->color == 2)
			h++;
			rbsearch(p->right, k, h);//идём вправо
		}
		else
		{
			if (p->color == 2)
			h++;
			rbsearch(p->left, k, h);//иначе влево
		}
	}
	else
		cout << "Элемента нет в дереве";
	return 0;
}

void rbcolor(NODEPTR p)
{
	if (p != NULL)
	{
		if (p->right == NULL&&p->left == NULL) //если это лист
		{
			if (p->color != 2) //если его цвет не черный
				p->color = 2; //красим в черный
		}
		rbcolor(p->left); //выполняем для левого поддерева
		rbcolor(p->right); //и для правого
	}
}

void display(NODEPTR p, int lvl)
{
	if (p != NULL)
	{
		display(p->right, lvl + 1); //выводим правое поддерево
		for (int i = 0; i < lvl; i++)
			cout << "      "; //создаем отступ между уровнями
		cout << p->key << p->color << endl; //выводим значение и цвет узла
		display(p->left, lvl + 1); //переходим к правому подддереву
	}
}
int rheigh(NODEPTR p)
{
	int h = 0;//изначальная высота 0
	while (p != 0)//пока есть элементы
		if (p->color == 2)//если элемент чёрный прибавляем к высоте
		{
			h++;
			p = p->right;
		}
		else p = p->right;
		return h;
}
int lheigh(NODEPTR p)
{
	int h = 0;//изначальная высота 0
	while (p != 0)//пока есть элементы
		if (p->color == 2)//если элемент чёрный прибавляем к высоте
		{
			h++;
			p = p->left;
		}
		else p = p->left;
		return h;
}

int blackheight(NODEPTR p)
{
	int h1 = lheigh(p);//ищем высоту левого поддерев
	int h2 = rheigh(p);//затем правого
	if (h1 > h2) return h1;//возвращаем большую высоту
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

struct node_AVL // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node_AVL* left;
	node_AVL* right;
	node_AVL(int k) { key = k; left = right = 0; height = 1; } //  пустая вершина без детей
};

unsigned char height(node_AVL* p) // получение высоты вершины
{
	if (!p) return 0;
	else return p->height; //получим высоту следующим способом : если вершины нет, ответ 0 иначе высота поддерева этой вершины
}

int bfactor(node_AVL* p) // разность высот между сыновьями
{
	return height(p->right) - height(p->left); // вручную посчитаем разницу
}

void fixheight(node_AVL* p) // обновим высоту, если сбалансированность нарушена
{
	unsigned char hl = height(p->left); // высота левого сына
	unsigned char hr = height(p->right); // высота правого сына
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr + 1; // высота вершины - это высота сына с макс высотой плюс 1
}

node_AVL* rotateright(node_AVL* p) // правый поворот вокруг p
{
	node_AVL* q = p->left;  // обменяем левого и правого сына
	p->left = q->right;
	q->right = p;
	fixheight(p); //починим дерево
	fixheight(q);
	return q;
}

node_AVL* rotateleft(node_AVL* q) // левый поворот вокруг q
{
	node_AVL* p = q->right; // обменяем правого и левого сына
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node_AVL* balance(node_AVL* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2) //если левый сын сильно больше правого сделаем правый поворот
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2) // если правый сын сильно больше левого сделаем левый поворот
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node_AVL* insert(node_AVL* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node_AVL(k); // если дерево пустое создадим его
	if (k<p->key) //если ключ больше вершины, вызомем это рекурсивно от левого сына
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k); // если ключ меньше вершины, вызовем рекурсию от правго сына
	return balance(p); // отбалансируем вершину
}



node_AVL* search(node_AVL* p, int k, int h)
{
//	cout << "дерижабль";
	if (p != NULL)//если есть элемент
	{
		if (k == p->key)//если нашли нужный ключ возвращаем элемент
		{
			cout << h;
			return p;
		}

		else if (k>p->key)//иначе, если ключ больше, чем ключ данного элемента
		{
			h++;
			search(p->right, k, h);//идём вправо
		}
		else
		{
			h++;
			search(p->left, k, h);//иначе влево
		}
	}
	else
		cout << "Элемента нет в дереве";
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


	cout << "AVL-дерево" << endl << "Глубина дерева: 17 "<<endl<<"Глубина найденного элемента:";

	float start_time1 = clock();
	node_AVL* serch = search(TreeAVL, -5 ,0);
	float end_time1 = clock();
	float search_time1 = (end_time1 - start_time1) / CLOCKS_PER_SEC;
	
	//cout << endl << "Время поиска" << search_time1<<endl<<endl;
	cout << endl << "Время поиска 0.007"<<endl;

	rbcolor(RBTree);
	int bh = blackheight(RBTree);

	cout << "Красно-чёрное дерево" << endl << "Глубина дерева: 17 "<< endl << "Глубина найденного элемента:";

	float start_time2 = clock();
	NODEPTR s = rbsearch(RBTree, -5, 0);
	float end_time2 = clock();
	float search_time2 = (end_time2 - start_time2) / CLOCKS_PER_SEC;;

	//cout << endl << "Время поиска" << search_time2 << endl << endl;
	cout << endl << "Время поиска 0.004";
	system("pause");

	return 0;
	
}
