// лаба4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include <chrono>
using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; } //  пустая вершина без детей
};
unsigned char height(node* p) // получение высоты вершины
{
	if (!p) return 0;
	else return p->height; //получим высоту следующим способом : если вершины нет, ответ 0 иначе высота поддерева этой вершины
}

int bfactor(node* p) // разность высот между сыновьями
{
	return height(p->right) - height(p->left); // вручную посчитаем разницу
}

void fixheight(node* p) // обновим высоту, если сбалансированность нарушена
{
	unsigned char hl = height(p->left); // высота левого сына
	unsigned char hr = height(p->right); // высота правого сына
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr+1; // высота вершины - это высота сына с макс высотой плюс 1
}
node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;  // обменяем левого и правого сына
	p->left = q->right;
	q->right = p;
	fixheight(p); //починим дерево
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right; // обменяем правого и левого сына
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2) //если левый сын больше, чем на 1 больше правого сделаем правый поворот
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2) // Аналогично для правого
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k); // если дерево пустое создадим его
	if (k<p->key) //если ключ больше вершины, вставляем в левое поддерево
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k); // если ключ меньше вершины, вставляем в правое поддерево
	return balance(p); // отбалансируем вершину
}

void showtree(node *p) //выводим дерево
{
	if  (p != NULL) //если дерево не пустое
	{
		cout << p->key<< " "; //выводим данные
		showtree(p->left); //идем в левое поддерево
		showtree(p->right); //идем в правое поддерево
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
	std::cout << elapsed.count() << " секунд\n";
	system("pause");

    return 0;
}
