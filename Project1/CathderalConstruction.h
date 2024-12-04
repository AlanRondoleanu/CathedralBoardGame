#ifndef CATHEDRALCONSTRUCTION_HPP
#define CATHEDRALCONSTRUCTION_HPP

#include <iostream>
#include <vector>

class CathderalConstruction
{
public:
	CathderalConstruction();
	
	std::vector<std::string> rotate(std::vector<std::string> t_instructions);

	std::vector<std::vector<std::string>> instructions;
private:

};

#endif
