#include <print>
#include <set>
#include <string>
#include <fstream>

std::string normalize(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::println("Usage: {} <file>", argv[0]);
		return -1;
	}

	std::ifstream input_file(argv[1]);

	if (!input_file.is_open())
	{
		std::println("Unable to open file");
		return -1;
	}

	std::set<std::string> word_set;
	std::string token;

	while (input_file >> token)
	{
		std::string normalized = normalize(token);
		if (!normalized.empty())
		{
			word_set.insert(normalized);
		}
	}

	input_file.close();

	for (const auto& word : word_set)
	{
		std::println("{}", word);
	}
}
