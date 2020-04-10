#include "LR0Algorithm.h"

void LR0Algorithm::ShiftCommand::Execute()
{
    lra.ss.push(st);
    lra.st.push(lra.tb);

    if (nf) lra.qt.pop();
    lra.tb = lra.qt.front();
}

void LR0Algorithm::ReduceCommand::Execute()
{
    switch (rt)
    {
        case r0:
        {
            /*
                E0 -> E
                Unreachable code!
            */
        }
            break;
        case r1:
        {
            // E -> E + T

            Node * t = new Node{Plus};

            t->rn = lra.sn.top();
            lra.sn.pop();

            t->ln = lra.sn.top();
            lra.sn.pop();

            lra.sn.push(t);

            for (std::size_t i = 0; i < rs; ++i)
            {
                lra.ss.pop();
                lra.st.pop();
            }

            lra.tb = E;
        }
            break;
        case r2:
        {
            // E -> T
            lra.ss.pop();
            lra.st.pop();

            lra.tb = E;
        }
            break;
        case r3:
        {
            // T -> n
            lra.sn.push(new Node{n} );

            lra.ss.pop();
            lra.st.pop();

            lra.tb = T;
        }
            break;
        case r4:
        {
            // T -> (E)    
            for (std::size_t i = 0; i < rs; ++i)
            {
                lra.ss.pop();
                lra.st.pop();
            }
            
            lra.tb = T;
        }
            break;
    }
} 