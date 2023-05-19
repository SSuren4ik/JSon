#pragma once
#include <iostream>
#include <stack>
#include "Iterator.h"
#include "Tokenizer.h"

using namespace std;

namespace JSON_LIB
{
	class JSon
	{
		ListValue* root;
		stack<IterVal*> st;
		Link* cur;
	public:

		JSon()
		{
			root = new ListValue("Main", root);
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
		string Write()
		{
			//string tmp = "";
			return root->WriteValue();
		}
		void next()
		{
			if (cur->val->getType() == 0)
				throw new exception("UZHE VNUTRI");
			if (st.top()->hasNext())
				cur = st.top()->GetNext();
			else
			{
				throw new exception("KONEC");
			}
		}
		void down()
		{
			if (cur->val->getType() == 0)
				throw exception("UZHE VNUTRI");
			st.push(cur->val->Iter());
			cur = st.top()->GetHead()->next;
		}
		void back()
		{
			if (cur->prev != st.top()->GetHead())
			{
				cur = st.top()->GetPrev();
			}
			else
			{
				if (st.size() != 1)
				{
					st.pop();
					cur = st.top()->GetCurrent();
				}
			}
		}
		void Add(string key, string val)
		{
			if (!st.top()->hasCur())
			{
				root->Last_add(new Link(new Value(key, val, root->GetLevel() + 1), nullptr, root->GetStart(), root->GetLevel() + 1));
				cur = st.top()->GetCurrent();
				//cout << cur->val->WriteValue() << endl;
				//cout << root->GetEnd()->val->WriteValue() << endl;
				//cout << root->WriteValue() << endl;
				return;
			}
			Link* curtmp = st.top()->GetCurrent();

			if (curtmp->val->getType() == 0)
			{
				string tmpKey = curtmp->val->GetKey();
				delete curtmp->val;
				curtmp->SetVal(new ListValue(tmpKey, nullptr, curtmp->level));
				((ListValue*)(curtmp->val))->Last_add(new Link(new Value(key, val, curtmp->level + 1), nullptr, ((ListValue*)curtmp->val)->GetEnd(), curtmp->level + 1));
				st.push(((ListValue*)(curtmp->val))->Iter());
				cur = st.top()->GetCurrent();
				//cout << cur->val->WriteValue();
				//cout << ((ListValue*)(curtmp->val))->GetEnd()->val->WriteValue();
				//cout << root->WriteValue();
			}
			else if (curtmp->val->getType() == 1)
			{
				((ListValue*)curtmp->val)->Last_add(new Link(new Value(key, val, curtmp->level + 1), nullptr, ((ListValue*)curtmp->val)->GetEnd(), curtmp->level + 1));
				st.push(((ListValue*)(curtmp->val))->Iter());
				cur = st.top()->GetCurrent();
			}
			//cout << cur->val->WriteValue();
			//cout << root->GetEnd()->val->WriteValue();
			//cout << root->WriteValue();
		}
		void Add_new(string key, string val)
		{
			if (!st.top()->hasCur())
			{
				root->Last_add(new Link(new Value(key, val, root->GetLevel() + 1), nullptr, root->GetStart(), root->GetLevel() + 1));
				cur = st.top()->GetCurrent();
				//cout << root->WriteValue() << endl;
				return;
			}
			st.top()->GetCurrent()->next = new Link(new Value(key, val, cur->level), nullptr, cur, cur->level);
			cur = st.top()->GetNext();
		}

		void parse(string filename)
		{
			//delete root;
			//root = new ListValue("Main", root);
			//cur = nullptr;
			//st.push(root->Iter());
			Tokenizer tokenizer(filename);
			Token token;
			if (tokenizer.hasMoreTokens())
			{
				token = tokenizer.getToken();
				if (token.type != TOKEN::CURLY_OPEN)
				{
					throw exception("Error of syntax");
				}
			}
			int ch = 1;
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
						ListValue* newList = new ListValue(key, root, root->GetLevel() + 1);
						cur = new Link(newList, nullptr, root->GetEnd(), root->GetLevel() + 1);
						cur->SetVal(newList);
						root->Last_add(cur);
						root = newList;
					}
					else if (token.type == TOKEN::STRING)
					{
						cur = new Link(nullptr, nullptr, root->GetEnd(), root->GetLevel() + 1);
						cur->SetVal(new Value(key, token.value, root->GetLevel() + 1));
						root->Last_add(cur);
					}
				}
				
				else if (token.type == TOKEN::CURLY_CLOSE)
				{
					ch--;
					if (ch == 0)
						root = root->GetParent();
				}	
			}
			st.push(root->Iter());
			cur = root->GetStart()->next;
			cout << root->WriteValue();
		}
		~JSon()
		{
			delete root;
		}
	};
}