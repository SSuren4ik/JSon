#pragma once
#include <iostream>
#include <string>

using namespace std;

class IterVal;

class  IValue
{
public:
	virtual int getType() = 0;
	virtual IterVal* Iter() = 0;//Итератор, которые проходится по объектам (2 метода у итератора: возврат следующего объекта и hasnext)
	virtual string GetKey() = 0;
	virtual string GetVal() = 0;//Если это объект, вернет его; если список, вернет весь список в JSON формате
};

struct Link
{
	Link* next;
	Link* prev;
	IValue* val;
public:
	Link(IValue* _val = nullptr, Link* _n = nullptr, Link* _pr = nullptr)
	{
		val = _val;
		next = _n;
		prev = _pr;
	}
};

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual bool hasPrev() = 0;
	virtual Link* next() = 0;
	virtual Link* prev() = 0;
};

class IterVal : public Iterator
{
	Link* cur;
	Link* h;
public:
	IterVal(Link* _h = nullptr)
	{
		h = _h;
	}
	bool hasNext()
	{
		return cur->next;
	}
	bool hasPrev()
	{
		return cur->prev;
	}
	Link* next()
	{
		if (!hasNext())
		{
			throw exception();
		}
		cur = cur->next;
		return cur;
	}
	Link* prev()
	{
		if (cur == h)
		{
			throw exception();
		}
		cur = cur->prev;
		return cur;
	}
	bool Find(string k)
	{
		IValue* tmp = h->val;
		if (tmp->getType() == 0)
		{
			if (tmp->GetKey() == k)
				return true;
			return false;
		}
		IterVal* iter = tmp->Iter();
		while (true)
		{
			if (tmp->GetKey() == k)
				return true;
			if (iter->hasNext())
				tmp = iter->next()->val;
			else
				return false;
		}
	}
};

class LIstValue : public IValue
{
	Link* start;
	Link* end;
	string key;
public:
	LIstValue(string k = "") {
		start = new Link(nullptr, end);
		end = start;
		key = k;
	}
	LIstValue(const LIstValue& l)
	{
		start = new Link(nullptr, end);
		end = start;
		key = l.key;
		Link* tmp = l.start->next;
		while (tmp != nullptr)
		{
			Last_add(tmp->val);
			tmp = tmp->next;
		}
	}
	LIstValue& operator=(const LIstValue& l)
	{
		clear();
		key = l.key;
		Link* tmp = l.start->next;
		while (tmp != nullptr)
		{
			Last_add(tmp->val);
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
	void Del(Link* d)
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
		return start == nullptr;
	}
	void clear()
	{
		while (!isEmpty())
			del_first();
	}
	void Last_add(IValue* _val)
	{
		Link* tmp = new Link(_val, nullptr, end);
		end->next = tmp;
		end = tmp;
	}
	string GetKey()
	{
		return key;
	}
	Link* GetStart()
	{
		return start;
	}
	string GetVal()
	{
		string form = "{\n  \"" + key + "\": ";
		IterVal* iter = start->val->Iter();
		while (true)
		{
			form += iter->
		}

	}
	int getType()
	{
		return 1;
	}
	IterVal* Iter()
	{
		return new IterVal(start);
	}
};

class Value : public IValue
{
	string key;
	string val;
public:
	Value(string k = "", string v = "")
	{
		key = k;
		val = v;
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
	string GetVal()
	{
		return "{\n  \"" + key + "\": \"" + val + "\"\n}";
	}
};
