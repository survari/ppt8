#ifndef C_DEC16_R_HPP
#define C_DEC16_R_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Dec16_R : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 86;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // dec16_r <r>
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit()-1);
        return 0;
    }
};

#endif