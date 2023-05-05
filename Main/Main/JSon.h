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
		st.push(root->Iter());
	}
	Link* GetCurrent()
	{
		return cur;
	}
	void Save(string filename) 
	{
		fstream file;
		if (!file.is_open())
			file.open(filename, ios::out);
		file << root->WriteValue();
	}
	void Write()
	{
		cout << root->WriteValue();
	}
	void next()
	{
		if (cur->next)
			cur = cur->next;
		else
			throw exception("NEKUDA");
		//if (st.empty())
		//{
		//	if (cur->next)
		//		cur = cur->next;
		//	else
		//		throw exception();
		//}
		//else
		//{
		//	if (!st.top()->hasNext())
		//		throw - 1;
		//	cur = st.top()->GetNext();
		//}
	}
	void down()
	{
		if (cur->val->getType() == 0)
			throw exception("UZHE VNUTRI");
		if (cur->val != nullptr)
		{
			st.push(root->Iter());
			root = (ListValue*)(cur->val);
			cur = root->GetStart()->next;
		}
	}
	void back()
	{
		if (cur->prev &&cur->prev!= root->GetStart())
		{
			cur = cur->prev;
		}
		else
		{
			if (st.empty())
				throw exception("UZHE NACHALO");
			cur = st.top()->GetCurrent();
			st.pop();
		}

		//if (st.empty())
		//{
		//	if (cur->prev == nullptr)
		//		throw exception("It is head");
		//	cur = cur->prev;
		//	return;
		//}
		//else
		//{
		//	if (cur->val->getType() == 0)
		//	{
		//		st.pop();
		//	}
		//	else
		//	{
		//		if (st.top()->hasPrev())
		//			cur = st.top()->GetPrev();
		//		else
		//		{
		//			st.pop();
		//			cur = st.top()->GetCurrent();
		//		}
		//	}
		//}
	}
	void Add(string key, string val) 
	{
		Link* curtmp;
		if (st.empty())
		{
			if (cur)
			{
				curtmp = cur;
			}
			else
			{
				root->Last_add(new Link(new Value(key, val, root->GetLevel()+1), nullptr, root->GetStart(), root->GetLevel() + 1));
				cur = root->GetEnd();
				return;
			}
		}
		else
		{
			curtmp = st.top()->GetCurrent();
		}

		if (curtmp->val->getType()==0) 
		{
			string tmpKey = curtmp->val->GetKey();
			string tmpVal = curtmp->val->GetVal();
			delete curtmp->val;
			curtmp->SetVal(new ListValue(tmpKey, nullptr, curtmp->level+1));
			((ListValue*)(curtmp->val))->Last_add(new Link(new Value(key, val, curtmp->level + 1), nullptr, ((ListValue*)curtmp->val)->GetEnd(), cur->level + 1));
			//cout << curtmp->val->WriteValue();
		}
		else if (curtmp->val->getType() == 1)
		{
			((ListValue*)curtmp->val)->Last_add(new Link(new Value(key, val), nullptr, ((ListValue*)curtmp->val)->GetEnd(), curtmp->level+1));
		}
	}

	void Add_new(string key, string val)
	{
		Link* curtmp;
		if (st.empty())
		{
			curtmp = root->GetEnd();
			curtmp->next = new Link(new Value(key, val), nullptr, root->GetEnd(), root->GetLevel()+1);
			root->Last_add(curtmp->next);
		}
		else
		{
			Iterator* iter = st.top();
			curtmp = iter->GetHead();
			while (iter->hasNext())
				curtmp = iter->GetNext();
			curtmp->next = new Link(new Value(key, val), nullptr, curtmp, curtmp->level);
			root->Last_add(curtmp->next);
		}
		cur = curtmp->next;
		//cout << root->WriteValue() << endl << endl;
	}

	void parse(string filename)
	{
		Tokenizer tokenizer(filename);
		Token token;
		int ch =0;
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
					ListValue* newList = new ListValue(key, root, root->GetLevel()+1);
					cur = new Link(newList, nullptr, root->GetEnd(), root->GetLevel() + 1);
					cur->SetVal(newList);
					root->Last_add(cur);
					root = newList;
				}
				else if (token.type == TOKEN::STRING)
				{
					ch++;
					cur = new Link(nullptr, nullptr, root->GetEnd(), root->GetLevel() + 1);
					cur->SetVal(new Value(key, token.value, root->GetLevel()+1));
					root->Last_add(cur);
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE)
			{
				ch--;
				if (ch ==0)
					root = root->GetParent();
			}
			//cout << root->WriteValue() << endl;
		}
		st.push(root->Iter());
		cur = root->GetStart()->next;
	}
};