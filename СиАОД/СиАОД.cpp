#pragma warning(disable : 4996)
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
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

/*struct Base
{
	record element;
	Base* next;
};*/

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

	int i = 0;
	int g = 0;
	while (p.head != NULL)
	{
		cout << "1 / 0" << endl;
		int temp;
		cin >> temp;
		if (temp == 1)
		{
			int n = 0;
			while ((p.head != p.tail) & (n < 20))
			{

				cout << i + 1 << ")";
				cout << p.head->str.Depositor << "   "
					<< p.head->str.Amount << "   "
					<< p.head->str.Date << "   "
					<< p.head->str.Lawyer << "   "
					<< endl;
				n++;
				i++;
				p.head = p.head->next;
			}
		}
		else
		{
			if (temp == 0)
				break;
			else
				while (p.head != NULL)
				{

					cout << i + 1 << ")";
					cout << p.head->str.Depositor << "   "
						<< p.head->str.Amount << "   "
						<< p.head->str.Date << "   "
						<< p.head->str.Lawyer << "   "
						<< endl;
					i++;
					p.head = p.head->next;
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
	  //k = sizeof(record)  - j;
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

void Search()
{

}

int main()
{

	
	p.head = NULL;
	p.tail = NULL;
	add_spis();
	Digital_sort(&p.head, &p.tail);
	Open_base();
	return 0;
}