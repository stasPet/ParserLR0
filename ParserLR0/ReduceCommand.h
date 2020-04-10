#pragma once

#include <cstddef>
#include <stack>

#include "Command.h"
#include "Enums.h"

#include <iostream>

class ReduceCommand : public Command
{
private:
    ReduceType rt;              // reduction type
    const std::size_t rs = 3;   // reduction size

    std::stack<State> & ssr;    // stack state referance
    std::stack<Token> & str;    // stack token referance

    Token & tbr;                // token buffer referance

public:
    ReduceCommand(ReduceType t, 
                  std::stack<State> & ss,
                  std::stack<Token> & st,
                  Token & tb) : 
                                rt{t},
                                ssr{ss},
                                str{st},
                                tbr{tb} {}

    virtual void Execute() override
    {
        switch (rt)
        {
            case r0:
            {
                // E0 -> E
                std::cout << "Good!";
            }
                break;
            case r1:
            {
                // E -> E + T
                for (std::size_t i = 0; i < rs; ++i)
                {
                    ssr.pop();
                    str.pop();
                }

                tbr = E;
            }
                break;
            case r2:
            {
                // E -> T
                ssr.pop();
                str.pop();

                tbr = E;
            }
                break;
            case r3:
            {
                // T -> n
                ssr.pop();
                str.pop();

                tbr = T;
            }
                break;
            case r4:
            {
                // T -> (E)    
                for (std::size_t i = 0; i < rs; ++i)
                {
                    ssr.pop();
                    str.pop();
                }
            
                tbr = T;
            }
                break;
        }
    } 
};