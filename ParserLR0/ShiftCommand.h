#pragma once

#include <stack>
#include <queue>

#include "Command.h"
#include "Enums.h"

class ShiftCommand : public Command
{
private:
    State st;   

    std::queue<Token> & qtr;    // queue token referance

    std::stack<State> & ssr;    // stack state referance
    std::stack<Token> & str;    // stack token referance

    Token & tbr;                // token buffer referance
    bool nf;                    // next flag

public:
    ShiftCommand(State s, 
                 std::queue<Token> & fl,
                 std::stack<State> & ss,
                 std::stack<Token> & st,
                 Token & tb,
                 bool f = false) : 
                                   st{s},
                                   qtr{fl},
                                   ssr{ss},
                                   str{st},
                                   tbr{tb},
                                   nf{f} {}

    virtual void Execute() override
    {
        ssr.push(st);
        str.push(tbr);

        if (nf) qtr.pop();
        tbr = qtr.front();
    }
};