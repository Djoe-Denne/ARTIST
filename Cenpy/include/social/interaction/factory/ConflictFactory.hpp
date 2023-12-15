#pragma once

#include <string>
#include <social/interaction/Conflict.hpp>

class ConflictFactory
{
public:
    static Conflict createConflict(const std::string &name);
};
