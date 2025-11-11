#include <cstdint>
#include <print>
#include <string>

using std::println;

class binary_stack
{
    public:
    binary_stack(const std::string& binary)
        : binary_characters(binary), size(binary.size())
    {}

    int pop()
    {
        if (size == 0)
            return -1;

        char character = binary_characters[size-- - 1];

        if (character != '1' && character != '0')
        {
            return -1;
        }

        return character == '1' ? 1 : 0;
    }

    bool is_empty()
    {
        return size == 0;
    }

    private:
    size_t size;
    std::string binary_characters;
};

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        println("Usage: {} <binary_string>", argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; i++)
    {
        std::string binary_string = argv[i];

        if (binary_string.size() > 64)
        {
            println("[Error]: Number cannot exceed 64 bits");
            return -1;
        }

        binary_stack stack {binary_string};
        uint64_t decimal_value = 0;
        int shift = 0;

        while (!stack.is_empty())
        {
            int binary_digit = stack.pop();
            if (binary_digit == -1)
            {
                println("[Error]: Invalid character");
                return -1;
            }

            decimal_value |= static_cast<uint64_t>(binary_digit) << shift++;
        }

        println("The binary number {} is {} in base 10", binary_string,
                decimal_value);
    }
}
