#include <iostream>

#include <stack>
#include <forward_list>

/*  no.| production
    1. | E0 -> E
    2. | E  -> E + T
    3. | E  -> T
    4. | T  -> n
    5. | T  -> (E)
*/

enum Token {E, T, n, Plus, LP, RP, End};

void Shift(int stateNumber);
void Goto(int stateNumber);
void Reduce(int productionNumber);

using FPtr = void(*)(int);

struct Action
{
    FPtr call{};
    int parametr{};
};

Action g1{Goto, 1};
Action g2{Goto, 2};
Action g6{Goto, 6};
Action g7{Goto, 7};

Action s3{Shift, 3};
Action s4{Shift, 4};
Action s5{Shift, 5};
Action s8{Shift, 8};

Action r0{Reduce, 0};
Action r1{Reduce, 1};
Action r2{Reduce, 2};
Action r3{Reduce, 3};
Action r4{Reduce, 4};

Action actionTable[][9]
{
   //   E     T     n     Plus  LP    RP    End
/*0*/ { {g1}, {g2}, {s3}, {},   {s4}, {},   {},   },
/*1*/ { {},   {},   {},   {s5}, {},   {},   {r0}, },
/*2*/ { {},   {},   {},   {r2}, {},   {r2}, {r2}, },
/*3*/ { {},   {},   {},   {r3}, {},   {r3}, {r3}, },
/*4*/ { {g6}, {g2}, {s3}, {},   {s4}, {},   {},   },
/*5*/ { {},   {g7}, {s3}, {},   {s4}, {},   {},   },
/*6*/ { {},   {},   {},   {s5}, {},   {s8}, {},   },
/*7*/ { {},   {},   {},   {r1}, {},   {r1}, {r1}, },
/*8*/ { {},   {},   {},   {r4}, {},   {r4}, {r4}, },
};

// std::forward_list<Token> inTokens{LP, n, Plus, n, RP, Plus, n, Plus, LP, n, Plus, n, RP, End};
std::forward_list<Token> inTokens{n, End};

std::stack<int> stateStack;
std::stack<Token> tokenStack;

auto it = inTokens.begin();
auto tokenBuffer = *it;

int main()
{
    stateStack.push(0);
  
    while (true)
    {
        Action currentAction =
            actionTable[stateStack.top() ][tokenBuffer];

        currentAction.call(currentAction.parametr);
    }

    return 0;
}

void Shift(int stateNumber)
{
    stateStack.push(stateNumber);

    tokenStack.push(tokenBuffer);
    tokenBuffer = *++it;
}
void Goto(int stateNumber)
{
    stateStack.push(stateNumber);

    tokenStack.push(tokenBuffer);
    tokenBuffer = *it;
}
void Reduce(int productionNumber)
{
    switch (productionNumber)
    {
        case 0:
        {
            // E0 -> E
            std::cout << "Good!";
        }
            break;
        case 1:
        {
            // E -> E + T
            for (int i = 0; i < 3; ++i)
            {
                stateStack.pop();
                tokenStack.pop();
            }

            tokenBuffer = E;
        }
            break;
        case 2:
        {
            // E -> T
            stateStack.pop();
            tokenStack.pop();

            tokenBuffer = E;
        }
            break;
        case 3:
        {
            // T -> n
            stateStack.pop();
            tokenStack.pop();

            tokenBuffer = T;
        }
            break;
        case 4:
        {
            // T -> (E)
            for (int i = 0; i < 3; ++i)
            {
                stateStack.pop();
                tokenStack.pop();
            }
            
            tokenBuffer = T;
        }
            break;
    }
}