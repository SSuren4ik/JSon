#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>
using namespace std;
using namespace JSON_LIB;

int main()
{
	JSon json;
	//json.Add("name", "Suren3");
	////cout << json.GetCurrent()->val->() << endl;
 //	json.Add("name", "Suren4");
	////cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.Add("name", "Suren5");
	//json.Add("name", "Suren1");
	//json.Add_new("name", "Suren1");
	//json.Add_new("name", "Suren1");
	//json.Add("name", "Suren2");
	//json.Add_new("name", "Suren3");
	//json.Add("name", "Suren2");
	//json.Add_new("name", "Suren3");
	//cout << endl << endl;
	//cout << json.Write();
	//json.Save("text.txt");
	json.parse("text.txt");
	json.Add("ergbesr", "edagvw");
	cout << json.Write();
	return 0; 
}
