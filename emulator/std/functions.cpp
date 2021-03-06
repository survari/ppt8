#include <cstdint>
#include <string>
#include <ctime>
#include <iostream>
#include <random>

#include "functions.hpp"
#include "../runtime/runtime.hpp"
#include "std.hpp"

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> rnd(0, 65536);

int ppt8_std::functions::interrupt(uint8_t code, Runtime *runtime)
{
    std::string s;
    char c = ' ';

    std::time_t t = std::time(0);   // get time now
    std::tm* date = std::localtime(&t);

    switch (code)
    {
        case 1: // print character in DL to screen
            print_char(runtime->getDX()->getLower8bit());
            break;

        case 2: // print 0-terminated string from memory address in AX
            for (int i = 0; runtime->getMemory()->getValueFromAddress(runtime->getAX()->getComplete16bit()+i) != 0; i++)
                print_char(runtime->getMemory()->getValueFromAddress(runtime->getAX()->getComplete16bit()+i));

            break;

        case 3: // read char without echo
            c = ppt8_std::get_char();
            runtime->getDX()->setValueLower8bit(c);
            break;

        case 4: // exit programm with exit code in DX
            c = ppt8_std::get_char();
            runtime->getDX()->setValueLower8bit(c);
            std::cout << c;
            break;

        case 5: // get date
            /*
             * year = date.tm_year (+ 1900)  - maybe no +1900 because of the large number (16bits)
             * month = date.tm_month + 1
             * day_of_month = date.tm_mday
             * day_of_year = date.tm_yday
             *
             * */

            runtime->getEX()->setValueLower8bit(date->tm_year);
            runtime->getFX()->setValueLower8bit(date->tm_mon+1);
            runtime->getGX()->setValueLower8bit(date->tm_mday);

            break;

        case 6: // read char with echo
            c = ppt8_std::get_char();
            std::cout << c;
            runtime->getDX()->setValueLower8bit(c);
            break;

        case 7:
            exit(runtime->getDX()->getComplete16bit());

        case 8:
            runtime->getDX()->setValueComplete16bit(rnd(rng));
            break;

        case 9: // read line into address stored in a, size in dx
            {
                std::string line;
                std::getline(std::cin, line);

                for (int i = 0; i < line.size(); i++)
                    runtime->getMemory()->setValue(runtime->getAX()->getComplete16bit()+i, line[i]);
            }
            break;

        default:
            return 2;
    }

    return 0;
}

int ppt8_std::functions::compare(int a, int b)
{
    if (a == b)
        return 0;
    if (a < b)
        return 1;
    if (a > b)
        return 2;
    return 3;
}

int ppt8_std::functions::print_char(uint8_t c)
{
    switch (c)
    {
        case 0xC4:
            std::cout << "Ä";
            break;

        case 0xD6:
            std::cout << "Ö";
            break;

        case 0xDC:
            std::cout << "Ü";
            break;

        case 0xE4:
            std::cout << "ä";
            break;

        case 0xF6:
            std::cout << "ö";
            break;

        case 0xFC:
            std::cout << "ü";
            break;

        case 0xDF:
            std::cout << "ß";
            break;

        default:
            std::cout << (char) c;
            break;
    }

    return 0;
}
