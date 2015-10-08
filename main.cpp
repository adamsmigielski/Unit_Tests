/** License
*
* Copyright (c) 2015 Adam Œmigielski
*
*
*  Permission is hereby granted, free of charge, to any person obtaining a
*      copy of this software and associated documentation files (the
*      "Software"), to deal in the Software without restriction, including
*      without limitation the rights to use, copy, modify, merge, publish,
*      distribute, sublicense, and/or sell copies of the Software, and to
*      permit persons to whom the Software is furnished to do so, subject to
*      the following conditions: The above copyright notice and this permission
*      notice shall be included in all copies or substantial portions of the
*      Software.
*
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
*      OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*      MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*      IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
*      CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*      TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*      SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
**/

/**
* @author Adam Œmigielski
* @file main.cpp
**/

#include <Unit_Tests\UnitTests.hpp>
#include <Unit_Tests\ExecutorInterface.hpp>

#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>


int main(int argc, char * argv[])
{
    std::string file_name = "test_log.txt";
    std::string test_name = "*";

    for (int i = 1; i < argc; ++i)
    {
        std::string buf;
        buf.resize(strlen(argv[i]));

        if (1 == sscanf(argv[i], "log=%s", buf.data()))
        {
            file_name = buf;
        }
        else if (1 == sscanf(argv[i], "test=%s", buf.data()))
        {
            test_name = buf;
        }
    }

    std::fstream file;
    file.open(file_name.c_str(), std::fstream::out);
    if (false == file.is_open())
    {
        return -1;
    }

    auto buf = std::clog.rdbuf(file.rdbuf());

    auto result = UnitTests::Execute_tests(test_name.c_str());

    std::clog.rdbuf(buf);

    switch (result)
    {
    case UnitTests::Passed: return 0; break;
    case UnitTests::NotAvailable: return 0; break;
    case UnitTests::Failed: return -1024; break;
    default:
        return -1;
        break;
    }
}
