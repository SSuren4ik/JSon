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
	virtual IterVal* Iter() = 0;//Итератор, которые проходится по объектам (2 метода у итератора: возврат следующего объекта и hasnext)
	virtual string GetKey() = 0;
	virtual string GetVal() = 0;//Если это объект, вернет его; если список, вернет весь список в JSON формате
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
	int level;
public:
	LIstValue(string k = "", int lv = 0) {
		start = new Link(nullptr, end);
		end = start;
		key = k;
		level = lv;
	}
	LIstValue(const LIstValue& l)
	{
		start = new Link(nullptr, end);
		end = start;
		key = l.key;
		level = l.level;
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
		level = l.level;
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
		return start == nullptr;
	}
	void clear()
	{
		while (!isEmpty())
			del_first();
	}
	void Last_add(IValue* _val)
	{
		Link* tmp = new Link(_val, nullptr, end, level+1);
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
	int GetLevel()
	{
		return level;
	}
	string GetVal()
	{
		string form = "{\n  \"" + key + "\": \n";
		for (Link* t = start->next; t != nullptr; t = t->next) {
			form = form + GetWhiteSpace(t->level) + "\{\n " + GetWhiteSpace(t->level) + t->val->GetKey()
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
	IterVal* Iter()
	{
		return new IterVal(start);
	}
	~LIstValue()
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
		return GetWhiteSpace(level) + "\{\n " + GetWhiteSpace(level) + key + "\": \"" + val + "\"\n" + GetWhiteSpace(level) + "}";
	}
	string GetVal()
	{
		return val;
	}
};
