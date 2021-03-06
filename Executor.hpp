/** License
*
* Copyright (c) 2015 Adam Śmigielski
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
* @author Adam Śmigielski
* @file Executor.hpp
**/

#ifndef UNIT_TESTS_EXECUTOR_HPP
#define UNIT_TESTS_EXECUTOR_HPP

#ifdef UNIT_TESTS_ENABLE

#include "ExecutorInterface.hpp"


namespace UnitTests
{
    class Executor : public ExecutorInterface
    {
    public:
        Executor();
        ~Executor();

        virtual Result Get_result() const;
		virtual const ResultsMap & Get_results_map() const;

        virtual void Run(Test * test);

    private:
		ExecutorInterface::ResultsMap m_results;
        Result m_result;
    };
}

#endif /* UNIT_TESTS_ENABLE */

#endif /* UNIT_TESTS_EXECUTOR_HPP */
