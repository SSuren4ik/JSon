#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include "Value.h"
#include <string>

using namespace std;

int main()
{
	Value val("name", "Suren");
	cout << val.GetVal();
	return 0;
}