#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>
using namespace std;
using namespace JSON_LIB;

int main()
{
	JSon json;
	json.Add("name", "Suren3");
	cout << json.GetCurrent()->val->WriteValue() << endl;
 	json.Add("name", "Suren4");
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.Add_new("name", "Suren5");
	cout << endl;
	cout << json.Write();
	json.Save("text.txt");
	json.parse("text.txt");
	json.Write();
	return 0; 
}
