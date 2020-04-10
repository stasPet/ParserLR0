#pragma once

struct Command
{
    virtual ~Command() {}
    virtual void Execute() = 0;
};