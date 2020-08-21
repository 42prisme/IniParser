#ifndef PARSER_INI_HH
#define PARSER_INI_HH

#include <list>
#include <string>
#include <iostream>


namespace ini
{

using key_value_t = std::pair<std::string, std::string>;
using section_t = std::pair<std::string, std::list<key_value_t>>;
using file_t = std::list<section_t>;


class parser
{
public:
	parser()  = default;
	~parser() = default;

	explicit parser(std::istream &);

	std::istream *input(std::istream &);
	std::istream *unset_input();

	bool parse();

	file_t && ini();

private:
	parser(parser const &)             = delete;
	parser(parser &&)                  = delete;
	parser & operator=(parser const &) = delete;
	parser & operator=(parser &&)      = delete;

	void on_value_token(std::string const&, std::string const&, std::size_t);

	void on_section_token(std::string const&, std::string const&, std::size_t);


	std::istream * m_input;

	file_t m_file;
	section_t * m_current_section;

	std::size_t m_current_line_number;
};
	
}





#endif