#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <msclr\marshal_cppstd.h>
#include "JSon.h"
using namespace System;
using namespace std;
using namespace msclr::interop;

namespace My_dll
{ 
	public ref class Json
	{
		JSON_LIB::JSon* json;

	public:
		Json()
		{
			json = new JSON_LIB::JSon();
		}
		void addVal(String^ k, String^ v)
		{
			string key = msclr::interop::marshal_as<std::string>(k);

			string val = msclr::interop::marshal_as<std::string>(v);

			json->Add(key, val);
		}
		void Add_new(String^ k, String^ v)
		{
			string key = msclr::interop::marshal_as<std::string>(k);

			string val = msclr::interop::marshal_as<std::string>(v);

			json->Add_new(key, val);
		}
		void Down()
		{
			json->down();
		}
		String^ getString() {
			String^ str = gcnew String(json->Write().data());
			return str;
		}
		void Back()
		{
			json->back();
		}
		void Next()
		{
			json->next();
		}
		void Save(String^ addr)
		{
			string data = marshal_as<string>(addr);
			json->Save(data);
		}
		void load(String^ addr) {
			delete json;			
			string data = marshal_as<string>(addr);
			json = new JSON_LIB::JSon();
			json->parse(data);
		}
	};
}