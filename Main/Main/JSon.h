#pragma once
#include <iostream>
#include <stack>
#include "Iterator.h"
#include "Tokenizer.h"

using namespace std;

class JSon
{
	ListValue* root;
	stack<Iterator*> st;
	Link* cur;
public:

	JSon()
	{
		root = new ListValue("Main");
		cur = nullptr;
	}
	Link* GetCurrent()
	{
		return cur;
	}
	void Save(string filename) {
		fstream file;
		if (!file.is_open())
			file.open(filename, ios::out);
		file << root->WriteValue();
	}

	void next()
	{
		if (st.empty())
		{
			if (cur->next)
				cur = cur->next;
			else
				throw exception();
		}
		else
		{
			if (!st.top()->hasNext())
				throw - 1;
			cur = st.top()->GetNext();
		}
	}
	void down()
	{
		if (cur->val->getType() == 0)
			throw exception("UZHE VNUTRI");
		if (cur->val != nullptr)
		{
			st.push(cur->val->Iter());
			cur = st.top()->GetHead();
		}
	}
	void back()
	{
		if (st.empty())
		{
			if (cur->prev == nullptr)
				throw exception("It is head");
			cur = cur->prev;
			return;
		}
		else
		{
			if (cur->val->getType() == 0)
			{
				st.pop();
			}
			else
			{
				if (st.top()->hasPrev())
					cur = st.top()->GetPrev();
				else
				{
					st.pop();
					cur = st.top()->GetCurrent();
				}
			}
		}
	}
	void Add(string key, string val) 
	{
		if (st.empty())
		{
			root->Last_add(new Link(new Value(key, val), nullptr, root->GetStart(), root->GetLevel() + 1));
			return;
		}

		Link* current_el = st.top()->GetCurrent();
		
		if (current_el->val->getType()==0) 
		{
			string tmpKey = current_el->val->GetKey();
			string tmpVal = (current_el->val)->GetVal();
			delete current_el->val;
			current_el->SetVal(new ListValue(tmpKey, nullptr, current_el->level+1));
			((ListValue*)(current_el->val))->Last_add(new Link(new Value(key, val), nullptr, ((ListValue*)current_el->val)->GetEnd()));
		}
		else if (current_el->val->getType() == 1)
		{
			((ListValue*)current_el->val)->Last_add(new Link(new Value(key, val), nullptr, ((ListValue*)current_el->val)->GetEnd(), current_el->level));
		}
	}
	void parse(string filename)
	{
		Tokenizer tokenizer(filename);
		Token token;
		int ch = 0;
		if (tokenizer.hasMoreTokens()) 
		{
			token = tokenizer.getToken();
			if (token.type != TOKEN::CURLY_OPEN)
			{ 
				throw exception("Error of syntax");
			}
		}
		string key = "";

		while (tokenizer.hasMoreTokens())
		{
			Token token = tokenizer.getToken();
			if (token.type == TOKEN::STRING) {
				key = token.value;

				token = tokenizer.getToken();
				if (token.type != TOKEN::COLON)
				{
					throw exception("Error of syntax");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN)
				{
					ch++;
					ListValue* newList = new ListValue(key, root);
					cur = new Link(newList, nullptr, root->GetEnd());
					cur->SetVal(newList);
					root->Last_add(cur);
					root = newList;
				}
				else if (token.type == TOKEN::STRING)
				{
					ch++;
					cur = new Link(nullptr, nullptr, root->GetEnd(), root->GetLevel() + 1);
					cur->SetVal(new Value(key, token.value));
					root->Last_add(cur);
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE)
			{
				ch--;
				if (ch > 1)
					root = root->GetParent();
			}
			cout << root->WriteValue() << endl;
		}
		cur = root->GetStart()->next;
	}
};