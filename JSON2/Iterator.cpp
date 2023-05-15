#include "Iterator.h"

int Check(int a)
{
	if (a <= 0)
		return 0;
	return a;

}

string GetWhiteSpace(int level)
{
	string tmp = "";
	for (int i = 0; i < level; i++)
	{
		tmp += "   ";
	}
	return tmp;
}