#include <print>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>

std::string normalize(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

std::unordered_map<std::string, std::string> 
load_state_map(std::ifstream& state_file)
{
	std::unordered_map<std::string, std::string> state_map;
	std::string abbreviation, city;	
	while (state_file >> abbreviation)
	{
		//Read the rest of the line for the city
		std::getline(state_file, city); 

		state_map[normalize(abbreviation)] = city;
	}

	return state_map;
}

int main()
{
	std::ifstream state_file ("states.txt");
	if (!state_file.is_open())
	{
		std::println("Unable to open 'states.txt'");
		return -1;
	}

	auto state_map = load_state_map(state_file);

	while (true)
	{
		std::print("Enter the state abbreviation to lookup (-1 to end): "); 

		std::string abbreviation_input;
		std::cin >> abbreviation_input;

		if (abbreviation_input == "-1")
		{
			break;
		}
		
		std::string normalized = normalize(abbreviation_input);
		if (state_map.find(normalized) != state_map.end())
		{
			std::string capital = state_map[normalized];
			std::println("Capital of {} is {}", abbreviation_input, capital);
		}
		else
		{
			std::println("Unable to find that state");
		}
	}

	state_file.close();
}
