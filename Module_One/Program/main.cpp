#include <iostream>
#include <string>

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

using std::cout;

// Used to validate substraction pairs
static bool is_pair(int Value, int NextValue)
{
    switch (Value)
    {
        case I: return NextValue == V || NextValue == X;
        case X: return NextValue == L || NextValue == C;
        case C: return NextValue == D || NextValue == M;
        default: return false;
    }
}

// Could have used std::unordered_map here as well.
static int map_symbol(char Symbol)
{
    switch (Symbol)
    {
        case 'I': return I;
        case 'V': return V;
        case 'X': return X;
        case 'L': return L;
        case 'C': return C;
        case 'D': return D;
        case 'M': return M;
        default: return 0;
    }
}

static int symbol_index(char Symbol)
{
    switch (Symbol)
    {
        case 'I': return 0;
        case 'V': return 1;
        case 'X': return 2;
        case 'L': return 3;
        case 'C': return 4;
        case 'D': return 5;
        case 'M': return 6;
        default: return -1;
    }
}

static int roman_to_decimal(const std::string& Numeral)
{
    if (Numeral.empty())
    {
        return 0;
    }

    unsigned int SeenSymbols[7] = {0};
    for (char Symbol : Numeral)
    {
        int SymbolIndex = symbol_index(Symbol);
        if (SymbolIndex == -1)
        {
            return 0;
        }

        unsigned int& Count = SeenSymbols[SymbolIndex];
        if (Symbol == 'V' || Symbol == 'L' || Symbol == 'D')
        {
            if (Count != 0)
            {
                return 0;
            }
        }

        if (++Count > 3)
        {
            return 0;
        }
    }

    int Result = 0;
    int LastParse = 0;
    for (size_t i = 0; i < Numeral.size(); i++)
    {
        int Value = map_symbol(Numeral[i]);
        if (i == Numeral.size() - 1) // Last symbol in string
        {
            if (LastParse != 0 && LastParse < Value)
            {
                Result = 0;
                break;
            }
            else
            {
                Result += Value;
            }

            break;
        }

        int NextValue = map_symbol(Numeral[i + 1]);
        if (Value < NextValue) // Subtraction (2 symbol)
        {
            /* Make sure this is a valid subtraction pair
             *
             * If there was a last parse (LastParse != 0)
             * ensure that the parses are in descending order.
             *
             * Pairs of symbols must be < Last Parse e.g (IXIX, IIV) is invalid
             */
            if (!is_pair(Value, NextValue) ||
                (LastParse != 0 && LastParse <= NextValue - Value))
            {
                Result = 0;
                break;
            }

            Result += LastParse = NextValue - Value;
            i++; // Skip symbol;
        }
        else // Addition (1 symbol)
        {
            // Single symbols can be <= LastParse e.g (II, XX, CC) is valid
            if (LastParse != 0 && LastParse < Value)
            {
                Result = 0;
                break;
            }

            Result += LastParse = Value;
        }
    }

    return Result;
}

int main()
{
    std::string Input;
    cout << "Roman Numeral: ";
    std::cin >> Input;

    int Converted = roman_to_decimal(Input);
    if (Converted == 0)
    {
        cout << Input << " is an invalid roman numeral\n";
    }
    else
    {
        cout << "Roman "  << Input << " to decimal: " <<  Converted << '\n';
    }
}
