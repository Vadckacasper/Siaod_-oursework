#pragma warning(disable : 4996)
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "locale.h"; 
using namespace std;



struct record
{
	char Depositor[30];
	unsigned short int Amount;
	char Date[10];
	char Lawyer[22];
};


struct elem {
	elem* next;
	union {
		record str;
		unsigned char digit[sizeof(record)];
	};

};

struct queue
{
	elem* head;
	elem* tail;

}p;

struct Vertex {
	record* data;
	Vertex* left, * right;
	int Balance;
};

void add_base(elem* p, record temp)
{


	p->str = temp;

}

void add_spis()
{
	ifstream base("testBase3.dat", ios::binary);
	record temp;
	base.read((char*)& temp, sizeof(record));
	p.head = new elem;
	p.head->str = temp;
	p.tail = p.head;

	for (int i = 0; i < 4000 - 1; i++)
	{
		base.read((char*)& temp, sizeof(record));
		p.tail->next = new elem();
		p.tail = p.tail->next;
		p.tail->str = temp;
	}
}

void Open_base()
{
	p.tail = p.head;
	int i = 0;
	int g = 0;
	while (p.tail != NULL)
	{
		cout << "1 / 0" << endl;
		int temp;
		cin >> temp;
		if (temp == 1)
		{
			int n = 0;
			while ((p.tail != nullptr) & (n < 500))
			{

				cout << i + 1 << ")";
				cout << p.tail->str.Depositor << "   "
					<< p.tail->str.Amount << "   "
					<< p.tail->str.Date << "   "
					<< p.tail->str.Lawyer << "   "
					<< endl;
				n++;
				i++;
				p.tail = p.tail->next;
			}
		}
		else
		{
			if (temp == 0)
				break;
			else
				while (p.tail != nullptr)
				{

					cout << i + 1 << ")";
					cout << p.tail->str.Depositor << "   "
						<< p.tail->str.Amount << "   "
						<< p.tail->str.Date << "   "
						<< p.tail->str.Lawyer << "   "
						<< endl;
					i++;
					p.tail = p.tail->next;
				}

		}
	}
}


void Digital_sort (elem **head, elem** tail)
{
	int byte[10] = {31,30,38,39,35,36,32,33};
int d, i, j, k, l = sizeof(record);
elem* w;
queue q[256];

for (j = 8 ; j >=0; j--) {
	for (i = 0; i < 256; i++)
		q[i].tail = (elem*)&q[i].head;

	w = *head;
	k = byte[j];
	while (w != NULL) {
		d = w->digit[k];
		q[d].tail->next = w;
		q[d].tail = w;
		w = w->next;
	}

	w = (elem*) & (*head);
	for (i = 0; i < 256; i++) {
		if (q[i].tail != (elem*)& q[i].head) {
			w->next = q[i].head;
			w = q[i].tail;
		}
	}
	w->next = NULL;
}
}

void Indexed_array(elem** head, elem** tail, record**& arr)
{
	int d;
	p.tail = p.head;
	for (size_t i = 0; i < 4000; i++)
	{
		arr[i] = &(p.tail->str);
		p.tail = p.tail->next;
	}


}
//:::::::::::::::::::::::::::::::::::Дерево::::::::::::::::::::::::::::::::::::::::::::::::::

int VR = 1, HR = 1;
void D_B_D(record*& x, Vertex*& p)
{

	if (p == nullptr)
	{
		p = new Vertex;

		p->data = x;
		p->left = p->right = nullptr;
		p->Balance = 0;
		VR = 1;
	}
	else if (strcmp(p->data->Depositor, x->Depositor) > 0)
	{
		//cout << p->data->Depositor << " > " << x->Depositor << endl;
		D_B_D(x, p->left);
		if (VR == 1)
		{
			if (p->Balance == 0)
			{
				Vertex* q;
				q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->Balance = 1;
				VR = 0;
				HR = 1;

			}
			else
			{
				p->Balance = 0;
				VR = 1;
				HR = 0;
			}
		}
		else
			HR = 0;
	}
	else if (strcmp(p->data->Depositor, x->Depositor) < 0) {
		//cout << p->data->Depositor << " < " << x->Depositor << endl;
		D_B_D(x, p->right);
		if (VR == 1)
		{
			p->Balance = 1;
			HR = 1;
			VR = 0;
		}
		else if (HR == 1)
			if (p->Balance == 1)
			{
				Vertex* q;
				q = p->right;
				p->Balance = 0;
				q->Balance = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else
				HR = 0;
	}
}

void print(Vertex* p)
{
	if (p)
	{
		print(p->left);
		cout << p->data->Depositor << "   "
			<< p->data->Amount << "   "
			<< p->data->Date << "   "
			<< p->data->Lawyer << endl;
		//cout << p->data <<"  ";
		print(p->right);
	}
}

int size_tree(Vertex* vertex)
{
	if (vertex == nullptr)
		return 0;
	else
	{
		return 1 + size_tree(vertex->left) + size_tree(vertex->right);
	}

}

double sum_height(Vertex* vertex, int l)
{
	if (vertex == nullptr)
		return 0;
	else
		return l + sum_height(vertex->left, l + 1) + sum_height(vertex->right, l + 1);
}

void del(Vertex* root)
{
	if (root)
	{
		del(root->left);
		del(root->right);
		delete root;
	}
}

void Search_tree(Vertex* root, string x)
{

	if (root)
	{
		string str(root->data->Depositor, sizeof(char) * x.length());
		//cout << str << endl;

		if (x < str)

		{//cout << "L" << endl;
			Search_tree(root->left, x);
		}
		if (x > str)
		{
			//cout << "R" << endl;
			Search_tree(root->right, x);
		}
		if (x == str)
		{

			cout << root->data->Depositor << "   "
				<< root->data->Amount << "   "
				<< root->data->Date << "   "
				<< root->data->Lawyer << endl;
			Search_tree(root->left, x);
			Search_tree(root->right, x);
		}
	}
}

int prompt_submenu_item()
{
	int varian;
	cout << endl << "Working with wood\n" << endl;
	/* << "1. To create a tree\n"*/
	cout << "1. Display the tree\n"
		<< "2. Search for an item in the tree\n"
		<< "3. Indicators of tree\n"
		<< "4. Exit\n" << endl;
	cout << ">>> ";
	cin >> varian;
	return varian;
}

int tree(Vertex* root)
{
	string temp;
	while (1)
	{
		int varian = prompt_submenu_item();
		switch (varian) {
			/*case 1:
				system("cls");
				for (int i = 0; i < 4000; i++)
					{
					/*cout << i << ") " << arr[i]->Depositor << "   "
						<< arr[i]->Amount << "    "
						<< arr[i]->Date << "    "
						<< arr[i]->Lawyer
						<< endl;
						D_B_D(arr[i], root);
					}
				break;*/
		case 1:
			system("cls");
			print(root);
			break;
		case 2:
			system("cls");
			cin >> temp;
			Search_tree(root, temp);
			break;

		case 3:
			system("cls");
			cout << endl << "Size tree " << size_tree(root) << endl;
			cout << endl << "Midd_height: " << sum_height(root, 1) / size_tree(root) << endl;
			break;
		case 4:
			system("cls");
			return 0;
			break;
		default:
			system("cls");
			cout << "You chose the wrong option" << endl;
			break;
		}
	}
}

void Search_Binary(record**& arr, int lef, int righ, Vertex* root)
{
	int key = 0;
	int midd = 0;
	cout << "Enter the item you want to find ";
	cin >> key;
	while(lef < righ)
	{
		midd = (lef + righ) / 2;
		if ((arr[midd]->Amount) < key)
			lef = midd + 1;
		else
			righ = midd;
	}
	if (key == 10000 || key == 20000 || key == 30000 || key == 40000)
		midd++;
	if (arr[midd]->Amount == key )
	{
		
		int i = 1;
		while (arr[midd]->Amount == key  )
		{
			
			cout << i << ") " << arr[midd]->Depositor << "   "
				<< arr[midd]->Amount << "    "
				<< arr[midd]->Date << "    "
				<< arr[midd]->Lawyer
				<< endl;

			i++;
			
			D_B_D(arr[midd], root);
			midd++;
			if (midd == 4000)
			{
				
				break;
			}
		}
		
	}
	else
	{
		cout << "Element's " << key << " not found!" << endl;
	}
	tree( root);
	del(root);
}
	
int prompt_menu_item()
{
	int variant;
	cout <<endl<< "Selected option\n" << endl;
	cout << "1. Sorted list\n"
		<< "2. Display list\n"
		<< "3. To create an indexed array\n"
		<< "4. Binary search\n"
		<< "5. Exit\n" << endl;
	cout << ">>> ";
	cin >> variant;
	return variant;
}



int main()
{

	record** arr = new record * [4000];
	Vertex* root = nullptr;
	p.head = NULL;
	p.tail = NULL;
	add_spis();

	while (1)
	{
		
		int variant = prompt_menu_item();
		system("cls");
		switch (variant) {
		case 1:
			Digital_sort(&p.head, &p.tail);
			break;
		case 2:
			Open_base();
			break;
		case 3:
			Indexed_array(&p.head, &p.tail, arr);
			break;
		case 4:
			Search_Binary(arr, 0, 4000,root);
			break;
		
		case 5:
			exit(EXIT_SUCCESS);
			break;
		default:
			cout << "You chose the wrong option" << endl;
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}