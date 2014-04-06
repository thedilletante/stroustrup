/*
Напишите функцию, которая получает в качестве аргументов
istream и vector<string>, а порождает map<string, vector<int>>, // likely meant map<string, int>
содержащий каждую строку и частоту ее вхождения. Прогоните
программу на текстовом файле с количеством строк, не менее
1000, разыскивая при это не менее 10 слов.
*/

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

typedef std::vector<std::string> strings;
typedef strings::const_iterator s_citer;

struct s_info
{
	const std::string * pstr;
	std::string::const_iterator current;
	std::string::const_iterator end;

	s_info(const std::string *p)
	: pstr(p), current(p->begin()), end(p->end())
	{}

	char curr() const { return *current; }
	void reset() { current = pstr->begin(); }
	bool isEnd() { return current == end; }
};

std::map<std::string, int> encount(std::istream *in, const strings &searched)
{
	std::map<std::string,int> result;
	std::vector<s_info> watched;
	// insert all string from searched with 0 frequency
	for (s_citer iter = searched.begin(), end = searched.end(); iter != end; ++iter)
	{
		result[*iter] = 0;
		if (iter->begin() != iter->end())
			watched.push_back(s_info(&(*iter)));
	}

	char ch;
	while (in->get(ch))
	{
		for (std::vector<s_info>::iterator iter = watched.begin(), end = watched.end(); iter != end; ++iter)
		{
			if (ch == iter->curr())
			{
				iter->current++;
				if (iter->isEnd())
				{
					result[*(iter->pstr)]++;
					iter->reset();
				}
			}
			else iter->reset();
		}
	}

	return result;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> vector;
	for (int i = 1; i < argc; ++i)
		vector.push_back(argv[i]);
	std::map<std::string, int> map = encount(&std::cin, vector);

	for (std::map<std::string, int>::const_iterator iter = map.begin(), end = map.end(); iter != end; ++iter)
		std::cout << iter->first << " = " << iter->second << std::endl;
	return 0;
}