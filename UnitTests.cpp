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
* @file UnitTests.hpp
**/

#ifdef UNIT_TESTS_ENABLE

#include "UnitTests.hpp"
#include "CreatorRegister.hpp"
#include "Executor.hpp"

#include <Platform\Platform.hpp>
#include <Utilities\basic\Assert.hpp>
#include <Utilities\basic\BreakToDebug.hpp>

#include <iostream>
#include <iomanip>

namespace UnitTests
{
    const static size_t s_index_length = 8;
    const static size_t s_result_length = 6;
    const static char * s_separator = " | ";

    Result Execute_tests(ExecutorInterface & executor, const char * filter)
    {
        /* Execute tests */
        auto reg = TestCreatorRegister::Get_singleton();
        reg->Execute(executor, filter);

        /* Log results */
        auto results = executor.Get_results_map();
        Platform::uint32 lp = 0;

        std::clog << "Results" << std::endl;

        std::clog << std::setw(s_index_length) << "Index" << s_separator;
        std::clog << std::setw(s_result_length) << "Result" << s_separator;
        std::clog << "Name" << std::endl;

        for (ExecutorInterface::ResultsMap::const_iterator it = results.begin(), end = results.end();
            end != it;
            ++it, ++lp)
        {
            std::clog << std::setw(s_index_length) << lp << s_separator;

            std::clog << std::setw(s_result_length);
            
            switch (it->second.m_result)
            {
            case Passed:       std::clog << "Pass" << s_separator; break;
            case Failed:       std::clog << "FAILED" << s_separator; break;
            case NotAvailable: std::clog << "Skip" << s_separator; break;
            case RESULT_MAX:
            default:
                std::clog << std::endl << std::endl << "Something went terribly wrong. See:" << __FILE__ << "@" << __LINE__ << std::endl << std::endl;
                ASSERT(0);
                break;
            }

            std::clog << it->first << std::endl;
        }

        for (auto it : results)
        {
            std::clog << std::endl << "/* *** Log for test: "
                << it.first << " *** */" << std::endl
                << it.second.m_log << std::endl
                << "/* *** End for test: "
                << it.first << " *** */" << std::endl;
        }

        /* Done */
        return executor.Get_result();
    }

    Result Execute_tests(const char * filter)
    {
        UnitTests::Executor exec;

        return Execute_tests(exec, filter);
    }
}

#endif /* UNIT_TESTS_ENABLE */