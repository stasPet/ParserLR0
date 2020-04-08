#include <iostream>

#include <stack>
#include <vector>

/*
    E0 -> E
    E  -> E + T
    E  -> T
    T  -> n
    T  -> (E)
*/

enum Token {E, T, n, Plus, LP, RP, End};

void Shift(int statusNumber);
void Reduce(int productionNumber);

using FPtr = void(*)(int);

struct Action
{
    FPtr call{};
    int parametr{};
};

Action s1{Shift, 1};
Action s2{Shift, 2};
Action s3{Shift, 3};
Action s4{Shift, 4};
Action s5{Shift, 5};
Action s6{Shift, 6};
Action s7{Shift, 7};
Action s8{Shift, 8};

Action r0{Reduce, 0};
Action r1{Reduce, 1};
Action r2{Reduce, 2};
Action r3{Reduce, 3};
Action r4{Reduce, 4};

Action actionTable[][9]
{
   //   E     T     n     Plus  LP    RP    End
/*0*/ { {s1}, {s2}, {s3}, {},   {s4}, {},   {},   },
/*1*/ { {},   {},   {},   {s5}, {},   {},   {r0}, },
/*2*/ { {},   {},   {},   {r2}, {},   {r2}, {r2}, },
/*3*/ { {},   {},   {},   {r3}, {},   {r3}, {r3}, },
/*4*/ { {s6}, {s2}, {s3}, {},   {s4}, {},   {},   },
/*5*/ { {},   {s7}, {s3}, {},   {s4}, {},   {},   },
/*6*/ { {},   {},   {},   {s5}, {},   {s8}, {},   },
/*7*/ { {},   {},   {},   {r1}, {},   {r1}, {r1}, },
/*8*/ { {},   {},   {},   {r4}, {},   {r4}, {r4}, },
};

std::vector<Token> inTokens{LP, n, Plus, n, RP, Plus, n, End};
std::stack<std::pair<int, Token> > stack;

auto it = inTokens.begin();

int main()
{
    stack.push(std::make_pair(0, Token(-1) ) );

    while (true)
    {
        Action currentAction =
            actionTable[stack.top().first][*it];

        currentAction.call(currentAction.parametr);
    }

    return 0;
}

void Shift(int statusNumber)
{
    stack.push(std::make_pair(statusNumber, *it++) );
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
                stack.pop();

            it = inTokens.insert(it, E);
        }
            break;
        case 2:
        {
            // E -> T
            stack.pop();
            it = inTokens.insert(it, E);
        }
            break;
        case 3:
        {
            // T -> n
            stack.pop();
            it = inTokens.insert(it, T);
        }
            break;
        case 4:
        {
            // T -> (E)
            for (int i = 0; i < 3; ++i)
                stack.pop();

            it = inTokens.insert(it, T);
        }
            break;
    }
}