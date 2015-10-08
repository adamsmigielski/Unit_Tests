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
* @file Executor.cpp
**/

#ifdef UNIT_TESTS_ENABLE

#include "Creator.hpp"
#include "Executor.hpp"
#include "Test.hpp"

#include <iostream>
#include <sstream>

namespace UnitTests
{
    Executor::Executor()
        : m_result(NotAvailable)
    {

    }

    Executor::~Executor()
    {

    }

    Result Executor::Get_result() const
    {
        return m_result;
    }

	const ExecutorInterface::ResultsMap & Executor::Get_results_map() const
	{
		return m_results;
	}

    void Executor::Run(Test * test)
    {
        static Result result_lut[RESULT_MAX][RESULT_MAX] =
        {
            /* m_result = Passed */
            {
                Passed,
                Failed,
                Passed
            },
            /* m_result = Failed */
            {
                Failed,
                Failed,
                Failed
            },
            /* m_result = NotAvailable */
            {
                Passed,
                Failed,
                NotAvailable
            }
        };

        auto env = EnviromentBase::Get_singleton();
        auto name = test->Get_name();
        auto result = NotAvailable;

		DetailedResult & detailed = m_results[name];
        std::stringstream stream;

        auto buf = std::clog.rdbuf(stream.rdbuf());
        result = test->Run(*env);
        std::clog.rdbuf(buf);

        detailed.m_result = result;
        detailed.m_log = stream.str();

        m_result = result_lut[m_result][result];
    }
}

#endif /* UNIT_TESTS_ENABLE */
