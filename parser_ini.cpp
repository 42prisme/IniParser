#include "parser_ini.hh"

ini::parser::parser(std::istream & p_input) :
 m_input(&p_input),
 m_file(),
 m_current_section(nullptr),
 m_current_line_number(0)
{}

std::istream *ini::parser::input(std::istream & p_input)
{
	std::istream *tmp = m_input;
	m_input = &p_input;
	return tmp;
}

std::istream *ini::parser::unset_input()
{
	std::istream *tmp = m_input;
	m_input = nullptr;
	return tmp;
}

ini::file_t && ini::parser::ini()
{
	return std::move(m_file);
}


/*
                           ____  ____ ______________
                          / __ \/ __ `/ ___/ ___/ _ \
                         / /_/ / /_/ / /  (__  )  __/
                        / .___/\__,_/_/  /____/\___/
                       /_/
*/

void formated_error_message(const char* error_msg, std::string const & p_line, std::size_t line_number, std::size_t char_number)
{
	std::cout << '[' << line_number << ':' << char_number << "] " << error_msg << std::endl;
	std::cout << p_line << std::endl;
	for (std::size_t i = 0 ; i < char_number; i++)
		std::cout << ' ';
	std::cout << '^' << std::endl;
}

static bool not_a_space(char c)
{
	return (c == ' ' || c == '\t') == false;
}

bool ini::parser::parse()
{
	if (m_input == nullptr)
		return (false);
	m_current_line_number = 0;
	while (m_input->good())
	{
		std::string line, buffer;
		std::getline(*m_input, line);
		m_current_line_number++;
		for(std::size_t i = 0; i < line.size(); ++i)
		{
			if(line[i] == '=')
			{
				on_value_token(buffer, line, i);
				break;
			}
			if(line[i] == '[')
			{
				on_section_token(buffer, line, i);
				break;
			}
			if(line[i] == ']')
			{
				formated_error_message("unexpected charactere ]", line, m_current_line_number, i);
				break;
			}

			if(not_a_space(line[i]))
				buffer += line[i];
		}
	}
	return (true);
}

void ini::parser::on_value_token(std::string const& buffer, std::string const& line, std::size_t i)
{
	ini::key_value_t key_val;
	key_val.first = buffer;
	i++;
	for (; i < line.size(); ++i)
	{
		if(key_val.second.size() == 0 && not_a_space(line[i]) == false)
			continue;
		key_val.second += line[i];
	}
	if(m_current_section == nullptr)
	{
		m_file.push_back(section_t());
		m_current_section = &(m_file.back());
	}

	m_current_section->second.push_back(key_val);
}

void ini::parser::on_section_token(std::string const& p_buffer, std::string const& line, std::size_t i)
{
	ini::section_t section;

	if(!p_buffer.empty())
	{
		formated_error_message("unexpected charactere", line, m_current_line_number, i);
		return;
	}

	i++;
	for(; i < line.size(); i++)
	{
		if(not_a_space(line[i]))
		{
			if (line[i] == ']')
			{
				m_file.push_back(section);
				m_current_section = &(m_file.back());
				return;
			}
			section.first.push_back(line[i]);
		}
	}
	formated_error_message("expected ]", line, m_current_line_number, i);
}
