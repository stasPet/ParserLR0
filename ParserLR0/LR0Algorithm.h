#include <cstddef>

#include <queue>
#include <stack>

#include "Command.h"
#include "Node.h"

#include <iostream>

/*  no.| production
    1. | E0 -> E
    2. | E  -> E + T
    3. | E  -> T
    4. | T  -> n
    5. | T  -> (E)
*/

class LR0Algorithm
{
private:
    class ShiftCommand : public Command
    {
    private:
        State st;   
        LR0Algorithm & lra;     // holder
        bool nf;                // next flag

    public:
        ShiftCommand(State s, LR0Algorithm & r, bool f = false) :
            st{s}, lra{r}, nf{f} {}

        virtual void Execute() override;
    };

    class ReduceCommand : public Command
    {
    private:
        ReduceType rt;              // reduction type
        const std::size_t rs = 3;   // reduction size
        LR0Algorithm & lra;         // holder

    public:
        ReduceCommand(ReduceType t, LR0Algorithm & r) :
            rt{t}, lra{r} {}

        virtual void Execute() override;
    };

public:
    LR0Algorithm()
    {
        ss.push(State::Start);
        tb = qt.front();
  
        Command * currentCommand = commandTable[ss.top() ][tb];

        while (currentCommand != &rr0)
        {
            currentCommand->Execute();
            currentCommand = commandTable[ss.top() ][tb];
        }
    }

private:
    std::queue<Token> qt
    {
        {LP, n, Plus, n, RP, Plus, n, Plus, LP, n, Plus, n, RP, End}
    };

    std::stack<State> ss;
    std::stack<Token> st;
    std::stack<Node *> sn;

    Token tb;

    ShiftCommand ss1{State::s1, *this};
    ShiftCommand ss2{State::s2, *this};
    ShiftCommand ss6{State::s6, *this};
    ShiftCommand ss7{State::s7, *this};

    ShiftCommand ss3{State::s3, *this, true};
    ShiftCommand ss4{State::s4, *this, true};
    ShiftCommand ss5{State::s5, *this, true};
    ShiftCommand ss8{State::s8, *this, true};

    ReduceCommand rr0{ReduceType::r0, *this};   // E0 -> E
    ReduceCommand rr1{ReduceType::r1, *this};   // E  -> E + T
    ReduceCommand rr2{ReduceType::r2, *this};   // E  -> T
    ReduceCommand rr3{ReduceType::r3, *this};   // T  -> n
    ReduceCommand rr4{ReduceType::r4, *this};   // T  -> (E)

    Command * commandTable[9][7]
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