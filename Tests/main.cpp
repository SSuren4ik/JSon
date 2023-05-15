#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>
using namespace std;
using namespace JSON_LIB;

int main()
{
	JSon json;
	//json.Add_new("name", "Suren1");
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.Add_new("name", "Suren2");
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.Add("name", "Suren3");
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.back();
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.back();
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	json.parse("text.txt");
	json.Add("wefcwe", "qewf");
	json.Write();
	return 0; 
}
