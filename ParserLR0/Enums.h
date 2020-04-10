#pragma once

enum Token : unsigned
{
    E, T, n, Plus, LP, RP, End
};

enum State : unsigned
{
    Start, s1, s2, s3, s4, s5, s6, s7, s8
};

enum ReduceType
{
    r0, // E0 -> E
    r1, // E -> E + T
    r2, // E -> T
    r3, // T -> n
    r4, // T -> (E)
};