#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>

using namespace std;

int main()
{
	fstream file("text.txt");
	LIstValue list("students");
	Value val1("name", "Suren1");
	Value val2("name", "Suren2");
	Value val3("name", "Suren3");
	list.Last_add(&val2);
	list.Last_add(&val3);
	file << list.GetVal();
	return 0;
}