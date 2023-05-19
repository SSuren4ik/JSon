#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <msclr\marshal_cppstd.h>
#include "D:\GitRepos\JSon\JSON2\JSon.h"
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
		String^ getStringCurrent()
		{
			String^ str = gcnew String(json->GetCurrent()->val->WriteValue().data());
			return str;
		}
		void Add_new(String^ k, String^ v)
		{
			string key = msclr::interop::marshal_as<std::string>(k);

			string val = msclr::interop::marshal_as<std::string>(v);

			json->Add_new(key, val);
		}
		void Down()
		{
			try
			{
				json->down();
			}
			catch (...)
			{
				;
			}
		}
		String^ getString() {
			String^ str = gcnew String(json->Write().data());
			return str;
		}
		void Back()
		{
			try
			{
				json->back();
			}
			catch (...)
			{

			}
		}
		void Next()
		{
			try
			{
				json->next();
			}
			catch (...)
			{
				;
			}
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