#include "ShiftCommand.h"
#include "ReduceCommand.h"

class LR0Algorithm
{
public:
    LR0Algorithm()
    {
        ss.push(State::Start);
        tb = fl.front();
  
        while (true)
        {
            Command * currentCommand = actionTable[ss.top() ][tb];
            currentCommand->Execute();
        }
    }

private:
    std::queue<Token> fl
    {
        {LP, n, Plus, n, RP, Plus, n, Plus, LP, n, Plus, n, RP, End}
    };

    std::stack<State> ss;
    std::stack<Token> st;

    Token tb;

    ShiftCommand ss1{State::s1, fl, ss, st, tb};
    ShiftCommand ss2{State::s2, fl, ss, st, tb};
    ShiftCommand ss6{State::s6, fl, ss, st, tb};
    ShiftCommand ss7{State::s7, fl, ss, st, tb};

    ShiftCommand ss3{State::s3, fl, ss, st, tb, true};
    ShiftCommand ss4{State::s4, fl, ss, st, tb, true};
    ShiftCommand ss5{State::s5, fl, ss, st, tb, true};
    ShiftCommand ss8{State::s8, fl, ss, st, tb, true};

    ReduceCommand rr0{ReduceType::r0, ss, st, tb};
    ReduceCommand rr1{ReduceType::r1, ss, st, tb};
    ReduceCommand rr2{ReduceType::r2, ss, st, tb};
    ReduceCommand rr3{ReduceType::r3, ss, st, tb};
    ReduceCommand rr4{ReduceType::r4, ss, st, tb};

    Command * actionTable[9][7]
    {
        //   E       T       n       Plus    LP      RP      End
 /*Start*/ { {&ss1}, {&ss2}, {&ss3}, {},     {&ss4}, {},     {},     },
    /*s1*/ { {},     {},     {},     {&ss5}, {},     {},     {&rr0}, },
    /*s2*/ { {},     {},     {},     {&rr2}, {},     {&rr2}, {&rr2}, },
    /*s3*/ { {},     {},     {},     {&rr3}, {},     {&rr3}, {&rr3}, },
    /*s4*/ { {&ss6}, {&ss2}, {&ss3}, {},     {&ss4}, {},     {},     },
    /*s5*/ { {},     {&ss7}, {&ss3}, {},     {&ss4}, {},     {},     },
    /*s6*/ { {},     {},     {},     {&ss5}, {},     {&ss8}, {},     },
    /*s7*/ { {},     {},     {},     {&rr1}, {},     {&rr1}, {&rr1}, },
    /*s8*/ { {},     {},     {},     {&rr4}, {},     {&rr4}, {&rr4}, },
    };
};