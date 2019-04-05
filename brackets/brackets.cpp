

// Lets assume that there is a string containing, amongst other symbols, brackets of N different types,
// like (] {} () <> «», etc. You need to implement algorithm that validates that an input stream 
// contains properly paired and nested brackets of several types, in other words checks
// whether the given string is a valid bracket sequence or not. For instance these strings
// "()[]{({})}" "[([]{})]" are valid, but these ones "[(])[]", "[[[{})))", "[)" are not.


#include <iostream>
#include <string>
#include <vector>
#include <functional>



enum BracketType{
    None, Curly, Square, Round
};


// stack-based impl
bool validate1(const std::string& s)
{
    std::vector<BracketType> q;

    for (auto c : s)
    {
        switch(c)
        {
            case '[': q.push_back(Square); break;
            case '{': q.push_back(Curly); break;
            case '(': q.push_back(Round); break;
            case ']': if(q.empty()) return false; if (q.back() != Square) return false; q.pop_back(); break;
            case '}': if(q.empty()) return false; if (q.back() != Curly) return false; q.pop_back(); break;
            case ')': if(q.empty()) return false; if (q.back() != Round) return false; q.pop_back(); break;
            default: break;
        }
    }

    return q.empty();
}


std::tuple<BracketType, bool> classify_bracket(const char c)
{
    switch(c)
    {
    case '[': return std::make_tuple(Square, false);
    case ']': return std::make_tuple(Square, true);
    case '{': return std::make_tuple(Curly, false);
    case '}': return std::make_tuple(Curly, true);
    case '(': return std::make_tuple(Round,false);
    case ')': return std::make_tuple(Round,true);
    default: return std::make_tuple(None,false);
    }
}

bool validate2_inner(const char* s, const char** outp, int level)
{
    const auto b = classify_bracket( s[0] );
    const BracketType b_type = std::get<0>(b);
    if (b_type == None)
    {
        *outp = s + 1;
        return true;
    }

    const char *p = s + 1;
    while (*p != 0)
    {
        // for (int i = 0; i < level; ++i)
        // {
        //     std::cout << " ";
        // }
        // std::cout << *p << std::endl;
        const auto b_inner = classify_bracket(*p);
        const BracketType b_inner_type = std::get<0>(b_inner);
        const bool b_inner_is_closing = std::get<1>(b_inner);
        if (b_inner_type != None)
        {
            if (!b_inner_is_closing)
            {
                if (!validate2_inner(p, &p, level+1))
                {
                    return false;
                }
            }
            else
            {
                *outp = p + 1;
                return b_type == b_inner_type;
            }
        }
        else
        {
            ++p;
        }
    }

    return true;
}



// recursion-based impl
bool validate2(const std::string& s)
{
    for (const char *p = &s[0]; *p != 0; )
    {
        // std::cout << *p<<std::endl;
        if (!validate2_inner(p, &p, 1))
        {
            return false;
        }
    }

    return true;
}


template<typename F>
bool test1(F validator, const std::string& s, bool outcome)
{
    return (validator(s) == outcome);
}

void test(const std::string& s, bool outcome)
{
    auto str_outcome = [](bool f){ return f ? "OK" : "FAILED"; };
    std::cout<<"test case: " << s << std::endl;
    std::cout
        << "  v1 -- "
        << str_outcome(test1(&validate1, s, outcome))
        << std::endl
        << "  v2 -- "
        << str_outcome(test1(&validate2, s, outcome))
        << std::endl;
}


int main()
{
   test("()[]{([])}", true);
   test("[([]{})]", true);
   test("[((){})]", true);
   test("[(])[]", false);
   test("[[[{})))", false);
   test("[)", false);

   return 0;
}
