#include <iostream>
#include "Iterator.h"
#include "JSon.h"
#include <string>
using namespace std;
using namespace JSON_LIB;

int main()
{
	JSon json;
	json.Add_new("name", "Suren1");
	json.Add("name", "Suren2");
	json.back();
	json.Add_new("name", "Suren3");
	json.Add_new("name", "Suren4");
	json.Add_new("name", "Suren5");
	json.Add_new("name", "Suren6");
	cout << json.Write();
	json.Save("text.txt");
	json.parse("text.txt");
	cout << json.Write();
	return 0; 
}
