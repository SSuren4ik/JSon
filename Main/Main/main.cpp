#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>

using namespace std;

int main()
{
	JSon json;
	json.parse("text2.txt");
	//json.Add_new("name", "Suren1");
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.Add_new("name", "Suren2");
	//cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.Add_new("name", "Suren3");
	//json.Write();
	//json.Add("height", "180");
	//json.Write();
	//json.Add("weight", "70");
	//json.Write();
	//json.Add("kaif", "Imeu");
	//json.Write();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.next();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.next();	
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.down();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.next();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.next();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.back();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.back();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	json.back();
	cout << json.GetCurrent()->val->WriteValue() << endl;
	//json.Save("text2.txt");
		return 0; 
}
