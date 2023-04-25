//#pragma once
//#include <iostream>
//#include <fstream>
//#include <istream>
//#include <stack>
//#include <string>
//#include "Iterator.h"
//
// class  IValue
//{
//public:
//	virtual int getType() = 0;
//	virtual IterVal* Iter() = 0;//Итератор, которые проходится по объектам (2 метода у итератора: возврат следующего объекта и hasnext)
//	virtual string GetKey() = 0;
//	virtual string GetVal() = 0;//Если это объект, вернет его; если список, вернет весь список в JSON формате
//};
//
//
//class LIstValue : public IValue
//{
//	Link* start;
//	Link* end;
//	string key;
//public:
//	LIstValue(string k = "") {
//		start = new Link(nullptr, end);
//		end = start;
//		key = k;
//	}
//	LIstValue(const LIstValue& l)
//	{
//		start = new Link(nullptr, end);
//		end = start;
//		key = l.key;
//		Link* tmp = l.start->next;
//		while (tmp != nullptr)
//		{
//			Last_add(tmp->val);
//			tmp = tmp->next;
//		}
//	}
//	LIstValue& operator=(const LIstValue& l)
//	{
//		clear();
//		key = l.key;
//		Link* tmp = l.start->next;
//		while (tmp != nullptr)
//		{
//			Last_add(tmp->val);
//			tmp = tmp->next;
//		}
//		return *this;
//	}
//	void del_first()
//	{
//		if (isEmpty())
//			throw exception();
//		Link* p = start;
//		start = p->next;
//		delete p;
//		if (isEmpty())
//			end = nullptr;
//	}
//	void Del(Link* d)
//	{
//		if (isEmpty())
//			throw exception();
//		if (d == start)
//			del_first();
//		if (d == end)
//		{
//			Link* p = end;
//			end = end->prev;
//			delete p;
//		}
//		Link* p = d;
//		d = d->next;
//		delete p;
//	}
//	bool isEmpty()
//	{
//		return start == nullptr;
//	}
//	void clear()
//	{
//		while (!isEmpty())
//			del_first();
//	}
//	void Last_add(IValue* _val)
//	{
//		Link* tmp = new Link(_val, nullptr, end);
//		end->next = tmp;
//		end = tmp;
//	}
//	string GetKey()
//	{
//		return key;
//	}
//	Link* GetStart()
//	{
//		return start;
//	}
//	string GetVal()
//	{
//		IterVal* iter = start->val->Iter();
//		string tmp = "";
//		while (true)
//		{
//			tmp += '{\n';
//			tmp += '\t';
//
//
//
//
//
//		}
//	}
//	int getType()
//	{
//		return 1;
//	}
//	IterVal* Iter()
//	{
//		return new IterVal(start);
//	}
//};
//
//class Value : public IValue
//{
//	string key;
//	string val;
//public:
//	Value(string k = "", string v = "")
//	{
//		key = k;
//		val = v;
//	}
//	int getType()
//	{
//		return 0;
//	}
//	IterVal* Iter()
//	{
//		return nullptr;
//	}
//	string GetKey()
//	{
//		return key;
//	}
//	string GetVal()
//	{
//		return "\"" + key + "\": \"" + val + "\"";
//	}
//};
