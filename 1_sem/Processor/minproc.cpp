#include <fstream>
#include <sstream>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>
#include "proc.h"

int main ()
{
	std::vector <std::string> comm_copy;
	std::map <std::string, size_t> marks;
	int code[1024] = {0};
	size_t it = 0, cntr = 0, q_of_marks = 0;
	std::string str = "";

	std::ifstream comm ("commands.txt");
	if (!comm)
	{
		std::cout << "File isn't open!" << std::endl;
		return 0;
	}
	else std::cout << "File opened, OK (^_^)!" << std::endl;

	while (std::getline (comm, str))
	{
		std::istringstream iss (str);
        std::string word = "";
		iss >> word;
		if (word.back() == ':')
		{
			marks[word] = cntr - q_of_marks;
			q_of_marks++;
		}
		else
			comm_copy.push_back (str);
		if (!word.compare ("push") || !word.compare ("cmp") || !word.compare ("jne") || !word.compare ("je") || !word.compare ("call"))
			cntr += 2;
		else
			cntr ++;
	}
	/*
	std::ofstream o_comm ("commands_r.txt");
	for (size_t i = 0; i < comm_copy.size (); i++)
	{
		o_comm << comm_copy[i] << std::endl;
	}

	std::ifstream i_comm ("commands_r.txt");
	////while (std::getline (i_comm, str))*/
	for (auto el : comm_copy)
	{

		std::istringstream iss (el);
		std::string word = "";
		int number = 0;
		iss >> word;
		if (!word.compare ("push"))
		{
			code[it++] = 1;
			iss >> code[it++];
		}
		if (!word.compare ("out"))
		{
			code[it++] = 2;
			continue;
		}
		else if (!word.compare ("add"))
		{
			code[it++] = 3;
			continue;
		}
		else if (!word.compare ("sub"))
		{
			code[it++] = 4;
			continue;
		}
		else if (!word.compare ("mul"))
		{
			code[it++] = 5;
			continue;
		}
		else if (!word.compare ("div"))
		{
			code[it++] = 6;
			continue;
		}
		else if (!word.compare ("cmp"))
		{
			code[it++] = 7;
			iss >> code[it++];
		}
		else if (!word.compare ("input"))
		{
			code[it++] = 8;
			continue;
		}
		else if (!word.compare ("popr"))
		{
			std::string reg = "";
			iss >> reg;
			if (!reg.compare ("ax"))
				code[it++] = 10;
			else if (!reg.compare ("bx"))
				code[it++] = 12;
			continue;
		}
		else if (!word.compare ("pushr"))
		{
			std::string reg = "";
			iss >> reg;
			if (!reg.compare ("ax"))
				code[it++] = 11;
			else if (!reg.compare ("bx"))
				code[it++] = 13;
			continue;
		}
		else if (!word.compare ("inc"))
		{
			std::string reg = "";
			iss >> reg;
			if (!reg.compare ("ax"))
				code[it++] = 14;
			else if (!reg.compare ("bx"))
				code[it++] = 16;
			continue;
		}
		else if (!word.compare ("dec"))
		{
			std::string reg = "";
			iss >> reg;
			if (!reg.compare ("ax"))
				code[it++] = 15;
			else if (!reg.compare ("bx"))
				code[it++] = 17;
			continue;
		}
		else if (!word.compare ("jne"))
		{
			code[it++] = 30;
			std::string mark = "";
			iss >> mark;
			std::map <std::string, size_t>::iterator m_it = marks.find(mark);
			if (m_it != marks.end ())
				code[it++] = m_it -> second;
			continue;
		}
		else if (!word.compare ("je"))
		{
			code[it++] = 31;
			std::string mark = "";
			iss >> mark;
			std::map <std::string, size_t>::iterator m_it = marks.find(mark);
			if (m_it != marks.end ())
				code[it++] = m_it -> second;
			continue;
		}
		else if (!word.compare ("call"))
		{
			code[it++] = 32;
			std::string mark = "";
			iss >> mark;
			std::map <std::string, size_t>::iterator m_it = marks.find(mark);
			if (m_it != marks.end ())
				code[it++] = m_it -> second;
			continue;
		}
		else if (!word.compare ("ret"))
		{
			code[it++] = 33;
			continue;
		}
	}
	Proc p;
	/*for (int j = 0; j <= 18; j++)
		std::cout << j << "_" << code[j] << " ";
	std::cout << std::endl;
	*/
	p.start (code);
	return 0;
}
