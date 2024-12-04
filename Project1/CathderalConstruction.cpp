#include "CathderalConstruction.h"

CathderalConstruction::CathderalConstruction()
{
	// Building 1
	instructions.push_back({ "up", "middle", "left", "middle", "right", "middle", "down", "down" });
	// Building 2
	instructions.push_back({ "up", "middle", "left", "middle", "right", "middle", "down" });
	// Building 3
	instructions.push_back({ "up", "middle", "left", "middle", "right" });
	// Building 4
	instructions.push_back({ "left", "up", "middle", "right", "up" });
	// Building 5
	instructions.push_back({ "left", "up", "right"});
	// Building 6
	instructions.push_back({ "up", "right" });
	// Building 7
	instructions.push_back({ "up", "up" });
	// Building 8
	instructions.push_back({ "up"});
	// Building 9
	instructions.push_back({ "middle" });
	// Building 10
	instructions.push_back({ "left", "middle", "up", "right"});
	// Building 11
	instructions.push_back({ "left", "up", "middle", "down", "right" });

}

std::vector<std::string> CathderalConstruction::rotate(std::vector<std::string> t_instructions)
{
	std::vector<std::string> temp = t_instructions;

	for (auto& instruction : temp)
	{
		if (instruction == "up")
		{
			instruction = "right";
		}
		else if (instruction == "right")
		{
			instruction = "down";
		}
		else if (instruction == "down")
		{
			instruction = "left";
		}
		else if (instruction == "left")
		{
			instruction = "up";
		}
	}

	return temp;
}
