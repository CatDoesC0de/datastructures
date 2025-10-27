#include <iostream>
#include <string>

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

#define INVALID_NUMERAL 0

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
        default: return INVALID_NUMERAL;
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
    //Empty string, nothing to parse
    if (Numeral.empty())
    {
        return INVALID_NUMERAL;
    }

    int SeenSymbols[7] = {0};

    //First pass for basic validation without parsing values
    for (char Symbol : Numeral)
    {
        int SymbolIndex = symbol_index(Symbol);

        //Check if this symbol is a valid symbol
        if (SymbolIndex == -1)
        {
            return INVALID_NUMERAL;
        }

        int& Count = SeenSymbols[SymbolIndex];
        // Return invalid if these symbols appear more than once
        if ((Symbol == 'V' || Symbol == 'L' || Symbol == 'D')
                && Count != 0)
        {
            return INVALID_NUMERAL;
        }

        //Symbols can't appear more than 3 times
        if (++Count > 3)
        {
            return INVALID_NUMERAL;
        }
    }

    int Result = INVALID_NUMERAL;

    //Keeps track of the last "value" parsed to check for descending order
    int LastParse = 0;
    
    //Second pass to parse values and enforce descending order for values
    for (size_t i = 0; i < Numeral.size(); i++)
    {
        int Value = map_symbol(Numeral[i]);
        if (i == Numeral.size() - 1) // Last symbol in string
        {
            if (LastParse != 0 && LastParse < Value)
            {
                Result = INVALID_NUMERAL;
                break;
            }

            Result += Value;
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
                Result = INVALID_NUMERAL;
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
                Result = INVALID_NUMERAL;
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
    if (Converted == INVALID_NUMERAL)
    {
        cout << Input << " is an invalid roman numeral\n";
    }
    else
    {
        cout << "Roman "  << Input << " to decimal: " <<  Converted << '\n';
    }

}
