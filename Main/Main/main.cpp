#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>

using namespace std;

int main()
{
	JSon json;
	//json.Add("name", "Suren1");
	//json.Add("name", "Suren2");
	//json.Add("name", "Suren3");
	//json.Save("text.txt");
	json.parse("text.txt");
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.next();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.next();	
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.back();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.back();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.Save("text2.txt");
	return 0; 
}
