#pragma once
#include <iostream>
#include <string>

using namespace std;

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

string GetWhiteSpace(int level)
{
	string tmp = "";
	for (int i = 0; i < level; i++)
	{
		tmp += "   ";
	}
	return tmp;
}

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

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual bool hasPrev() = 0;
	virtual Link* GetNext() = 0;
	virtual Link* GetHead() = 0;
	virtual Link* GetCurrent() = 0;
	virtual Link* GetPrev() = 0;
};

class IterVal : public Iterator
{
	Link* cur;
	Link* h;
public:
	IterVal(Link* _h)
	{
		h = _h;
		if (h->next)
			cur = h->next;
		else
			throw - 1;
	}
	bool IsEmpty()
	{
		return cur==nullptr;
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
	void Delete(Link* d)//Почему удаляем Link, а добавляем Value???
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
		string form = "{\n  \"" + key + "\": \n";
		for (Link* t = start->next; t != nullptr; t = t->next) {
			form = form + GetWhiteSpace(t->level) + "\{\n " + GetWhiteSpace(t->level) + "\"" + t->val->GetKey()
				+ "\": \"" + t->val->GetVal() + "\"\n" + GetWhiteSpace(t->level) + "}";
			if (t != end)
				form+= ",";
			form+= "\n";
		}
		form += "}\n";
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
		return GetWhiteSpace(level) + "\{\n " + GetWhiteSpace(level) + "\"" + key + "\": \"" + val + "\"\n" + GetWhiteSpace(level) + "}";
	}
	string GetVal()
	{
		return val;
	}
};
