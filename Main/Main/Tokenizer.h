#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum class TOKEN {
	CURLY_OPEN,
	CURLY_CLOSE,
	COLON,
	STRING,
	COMMA
};

struct Token
{
	string value;
	TOKEN type;
	string getStringType() {
		switch (type)
		{
		case TOKEN::CURLY_OPEN:
			return "CURLY_OPEN";
		case TOKEN::CURLY_CLOSE:
			return "CURLY_CLOSE";
		case TOKEN::COLON:
			return "COLON";
		case TOKEN::STRING:
			return "STRING";
		case TOKEN::COMMA:
			return "COMMA";
		default:
			return "ERROR";
		} 
	}
};

class Tokenizer {
	fstream file;
public:
	Tokenizer(string filename)
	{
		if(!file.is_open())
		file.open(filename, ios::in);
		if (file.bad())
			throw exception("Fail error");
	}
	char getWithoutWhiteSpace()
	{
		char c = ' ';
		while ((c == ' ' || c == '\n'))
		{
			file.get(c);

			if ((c == ' ' || c == '\n') && file.bad())
			{
				return ' ';
			}
			else if (!file.good())
			{
				return c;
			}
		}
		return c;
	}
	Token getToken()
	{
		char c;
		if (file.eof()) {
			throw exception("Exhaused tokens");
		}
		if (!file.is_open())
			throw exception("Error");
		c = getWithoutWhiteSpace();

		Token token;
		switch (c)
		{
		case '"':
		{
			token.type = TOKEN::STRING;
			token.value = "";
			file.get(c);
			while (c != '"')
			{
				token.value += c;
				file.get(c);
			}
			break;
		}
		case'{':
		{
			token.type = TOKEN::CURLY_OPEN;
			break;
		}
		case'}':
		{ 
			token.type = TOKEN::CURLY_CLOSE;
			break;
		}
		case':':
		{
			token.type = TOKEN::COLON;
			break;
		}
		case',':
		{
			token.type = TOKEN::COMMA;
			break;
		}
		}
		return token;
	}
	bool hasMoreTokens()
	{
		if (file.eof())
			return false;
		return true;
	}
};