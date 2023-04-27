#pragma once
#include <iostream>
#include <stack>
#include "Iterator.h"
#include "Tokenizer.h"

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

	}
	void load(string filename)
	{
		fstream file;
		if(!file.is_open())
			file.open(filename, ios::out);
		IterVal* iter = root->Iter();
		while (iter->hasNext())
		{
			file << iter->next()->val->WriteValue();
		}
	}
	void load_current(string filename)
	{
		fstream file;
		if (!file.is_open())
			file.open(filename, ios::out);
			file << cur->val->GetVal();
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
			if(st.top()->hasPrev())
				cur = st.top()->prev();
			else
			{

			}
		}
	}
	IValue* parse(string filename)
	{
		Token* token;
		IValue* val;
		string key = "";
		stack<Token*> st;
		Tokenizer tokenizer(filename);
		while (tokenizer.hasMoreTokens())
		{
			token = tokenizer.getToken();
			switch (token->type)
			{
			case TOKEN::STRING:
			{
				break;
			}

			case TOKEN::CURLY_OPEN:
			{
				if (st.top()->type == TOKEN::COLON)
				{
					val = new LIstValue();
				}

				break;
			}
			break;
			}
		}

	}





		//token = tokenizer.getToken();
		//string str = "";
		//string tmp = "";
		//fstream file(filename);
		//file >> str;
		//int state = 0;
		//for (int i = 0; i < str.size(); i++)
		//{
		//	char c = str[i];
		//	switch (c)
		//	{
		//	case '{':
		//	{
		//		state = 1;
		//		break;
		//	}
		//	case ' ' || "\n":
		//	{
		//		break;
		//	}
		//	case '"':
		//	{
		//		i++;
		//		while (str[i] != '"')
		//		{
		//			tmp += str[i];
		//			i++;
		//		}
		//		cur->val->GetKey()
		//	}

};