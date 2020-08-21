#include "parser_ini.hh"
#include <fstream>
#include <iostream>

int main(int, char **, char **)
{
	ini::parser parser;
	std::ifstream file;

	file.open("test.ini");

	parser.input(file);
	if (parser.parse() == false)
		return (1);
	ini::file_t ini = parser.ini();
	
	for (ini::file_t::const_iterator it_section = ini.cbegin() ; it_section != ini.cend(); ++it_section)
	{
		std::cout << it_section->first << std::endl;
		for (std::list<ini::key_value_t>::const_iterator it_key_value = it_section->second.cbegin() ; it_key_value != it_section->second.cend(); ++it_key_value)
		{
			std::cout << it_key_value->first << " : " << it_key_value->second << std::endl;
		}	
	}

	return (0);
}