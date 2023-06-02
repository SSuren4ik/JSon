#pragma once
#include <iostream>
#include <string>

using namespace std;

string GetWhiteSpace(int level);
int Check(int a);

namespace JSON_LIB
{
	class IterVal;

	class  IValue
	{
	public:
		virtual int getType() = 0;
		virtual int GetLevel() = 0;
		virtual string WriteValue() = 0;
		virtual IterVal* Iter() = 0;
		virtual string GetKey() = 0;
		virtual string GetVal() = 0;
	};

	struct Link
	{
		Link* next;
		Link* prev;
		IValue* val;
		int level;
	public:
		Link(IValue* _val = nullptr, Link* _n = nullptr, Link* _pr = nullptr, int lv = 0)
		{
			val = _val;
			next = _n;
			prev = _pr;
			level = lv;
		}
		void SetVal(IValue* v)
		{
			val = v;
		}
		~Link()
		{
			delete val;
		}
	};


	class IterVal
	{
		Link* cur;
		Link* h;
	public:
		IterVal(Link* _h)
		{
			h = _h;
			cur = h->next;
		}
		bool IsEmpty()
		{
			return cur == nullptr;
		}
		bool hasNext()
		{
			return cur->next;
		}
		bool hasPrev()
		{
			return cur->prev;
		}
		bool hasCur()
		{
			return cur;
		}
		Link* GetNext()
		{
			Update();
			if (!hasNext())
			{
				throw exception();
			}
			cur = cur->next;
			return cur;
		}
		Link* GetPrev()
		{
			if (cur == h)
			{
				throw exception();
			}
			cur = cur->prev;
			return cur;
		}
		Link* GetCurrent()
		{
			Update();
			if (cur == nullptr)
			{
				throw exception();
			}
			return cur;
		}
		Link* GetHead()
		{
			if (h == nullptr)
			{
				throw exception();
			}
			return h;
		}
		void Update()
		{
			if (IsEmpty())
			{
				cur = h->next;
			}
		}
	};

	class Value : public IValue
	{
		string key;
		string val;
		int level;
	public:
		Value(string k = "", string v = "", int lv = 0)
		{
			key = k;
			val = v;
			level = lv;
		}
		int getType()
		{
			return 0;
		}
		IterVal* Iter()
		{
			return nullptr;
		}
		string GetKey()
		{
			return key;
		}
		int GetLevel()
		{
			return level;
		}
		string WriteValue()
		{
			return "\"" + key + "\": \"" + val + "\"";
		}
		string GetVal()
		{
			return val;
		}
	};


	class ListValue : public IValue
	{
		Link* start;
		Link* end;
		string key;
		ListValue* parent;
		int level;
	public:
		ListValue(string k = "", ListValue* _parent = nullptr, int lv = 0) {
			start = new Link(nullptr, end);
			parent = _parent;
			end = start;
			key = k;
			level = lv;
		}
		ListValue(const ListValue& l)
		{
			start = new Link(nullptr, end);
			end = start;
			key = l.key;
			level = l.level;
			Link* tmp = l.start->next;
			while (tmp != nullptr)
			{
				Last_add(new Link(tmp->val, nullptr, end));
				tmp = tmp->next;
			}
		}
		ListValue& operator=(const ListValue& l)
		{
			clear();
			key = l.key;
			level = l.level;
			Link* tmp = l.start->next;
			while (tmp != nullptr)
			{
				Last_add(new Link(tmp->val, nullptr, end));
				tmp = tmp->next;
			}
			return *this;
		}
		void del_first()
		{
			if (isEmpty())
				throw exception();
			Link* p = start;
			start = p->next;
			delete p;
			if (isEmpty())
				end = nullptr;
		}
		void Delete(Link* d)
		{
			if (isEmpty())
				throw exception();
			if (d == start)
				del_first();
			if (d == end)
			{
				Link* p = end;
				end = end->prev;
				delete p;
			}
			Link* p = d;
			d = d->next;
			delete p;
		}
		bool isEmpty()
		{
			return start == end;
		}
		void clear()
		{
			while (!isEmpty())
				del_first();
		}
		void Last_add(Link* val)
		{
			end->next = val;
			end = end->next;
		}

		string GetKey()
		{
			return key;
		}
		Link* GetEnd()
		{
			return end;
		}
		Link* GetStart()
		{
			return start;
		}
		int GetLevel()
		{
			return level;
		}

		string GetVal()
		{
			string form ="\""+ key + "\"" + "\:\n";
			int ch = 0;
			for (Link* t = start->next; t != nullptr; t = t->next)
			{
				if ( ch == 0)
					form += GetWhiteSpace(t->val->GetLevel() + 2) + "{\n";
				if (t->val->getType() == 1)
				{
					form += GetWhiteSpace(t->val->GetLevel() + 2);
					form += t->val->WriteValue();
				}
				else
				{
					form = form + GetWhiteSpace(t->val->GetLevel() + 2) + t->val->WriteValue();
				}
				if (t->next != nullptr)
				{
					form += ",";
					form += "\n";
				}
				else
				{
					form += "\n";
					form += GetWhiteSpace(t->val->GetLevel() + 2) + "}";
				}
				ch++;
				//cout << form << endl;
			}
			//cout << form << endl;
			return form;
		}
		int getType()
		{
			return 1;
		}
		string WriteValue()
		{
			return GetVal();
		}
		ListValue* GetParent()
		{
			return parent;
		}
		IterVal* Iter()
		{
			return new IterVal(start);
		}
		~ListValue()
		{
			clear();
		}
	};
}