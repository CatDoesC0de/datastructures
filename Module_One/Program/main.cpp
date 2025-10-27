#include <iostream>
#include <string>
#include <unordered_map>

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

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

//Could have used std::unordered_map here as well.
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

static int roman_to_decimal(std::string& Numeral)
{
    if (Numeral.size() == 0)
    {
        return 0;
    }
    
    std::unordered_map<char, int> SeenSymbols;
    for (char Symbol : Numeral)
    {
        if (map_symbol(Symbol) == 0)
        {
            return 0;
        }

        if (Symbol == 'V' || Symbol == 'L' || Symbol == 'D') 
        {
           if (SeenSymbols[Symbol] != 0)
           {
               return 0;
           }
        }

        int Count = SeenSymbols[Symbol]++;
        if (Count > 3)
        {
           return 0;
        }
    }

    int Result = 0;
    int LastParse = 0;
    for (int i = 0; i < Numeral.size(); i++)
    {
        int Value = map_symbol(Numeral[i]);
        if (i == Numeral.size() - 1) //Last symbol in string
        {
            if (LastParse != 0)
            {
                if (LastParse > Value)
                {
                    Result += Value;
                }
                else //Invalid input
                {
                    Result =  0;
                }
            }
            else //Only symbol in input
            {
                Result = Value;
            }

            break;
        }

        int NextValue = map_symbol(Numeral[i + 1]);
        if (Value < NextValue) //Subtraction (2 symbol)
        {
            /* Make sure this is a valid subtraction pair
             *
             * If there was a last parse (LastParse != 0)
             * ensure that the parses are in descending order.
             *
             * Pairs of symbols must be < Last Parse e.g (IXIX, IIV) is invalid
             */
            if (!is_pair(Value, NextValue)
                    && LastParse != 0
                    && LastParse <= NextValue - Value)
            {
                Result = 0;
                break;
            }

            Result += LastParse = NextValue - Value;
            i++; //Skip symbol;
        }
        else //Addition (1 symbol)
        {
            //Single symbols can be <= LastParse e.g (II, XX, CC) is valid
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
    printf("Roman Numeral: ");
    std::cin >> Input;

    int Converted = roman_to_decimal(Input);

    if (Converted == 0)
    {
        printf("'%s' is an invalid Roman Numeral.\n", Input.c_str());
    }
    else
    {
        printf("Roman '%s' to decimal: %i\n", Input.c_str(), Converted);
    }
}
