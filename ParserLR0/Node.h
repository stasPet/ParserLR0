#pragma once
#include "Enums.h"

struct Node
{
    Node * ln;
    Node * rn;

    Token tv;

    Node(Token t, Node * l = nullptr, Node * r = nullptr) :
        tv{t}, ln{l}, rn{r} {}
};