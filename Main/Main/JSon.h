#pragma once
#include <iostream>
#include <stack>
#include "Iterator.h"
//#include "Value.h"

using namespace std;

class JSon
{
	LIstValue* root;
	stack<Iterator*> st;
	Link* cur;
public:

	JSon()
	{
		root = new LIstValue("Main");
		st.push(root->Iter());
		cur = root->GetStart();
	}
	void save(string filename)
	{
		//Value* v = new Value();
		//ifstream in(filename);
		//string text;
		//string value = "";
		//string tmp = "";
		//string _key = "";
		//in >> text;
		//int i = 0;
		//int count_obj = 0;
		//int cov = 0;
		//int figskob = 0;
		//int ch = 0;
		//while (i <= text.size())
		//{
		//	char c = text[i];
		//	switch (ch)
		//	{
		//		case 0:
		//		{
		//			if()
		//			ch = 1;
		//			break;
		//		}


		//		//case '}':
		//		//{
		//		//	ch = 0;
		//		//	break;
		//		//}
		//		//case ':':
		//		//{
		//		//	if(text[i-1]=='"' && ch == 1)
		//		//	 _key= tmp;
		//		//}
		//		//case '"':
		//		//{
		//		//	if (text[i - 1] == '"' && ch == 1)
		//		//		_key = tmp;
		//		//}
		//	}
		//}
	}
	void load(string filename)
	{

	}
	void next()
	{
		if (!st.top()->hasNext())
			throw - 1;
		cur = st.top()->next();
	}
	void down()
	{
		if (cur->val->getType() == 0)
			return;
		st.push(cur->val->Iter());
	}
	void back()
	{
		if (cur->val->getType() == 0)
		{
			st.pop();

		}
		else
		{
			cur = st.top()->prev();
		}
	}

};