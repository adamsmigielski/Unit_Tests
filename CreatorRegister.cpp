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
* @file Creator.cpp
**/

#ifdef UNIT_TESTS_ENABLE

#include <Platform\Platform.hpp>
#include <Utilities\containers\PointerContainer.hpp>

#include "Creator.hpp"
#include "CreatorRegister.hpp"
#include "ExecutorInterface.hpp"
#include "Test.hpp"

#include <memory>

namespace UnitTests
{
    TestCreatorRegister::TestCreatorRegister()
    {

    }

    TestCreatorRegister::~TestCreatorRegister()
    {

    }

    void TestCreatorRegister::Execute(ExecutorInterface & executor, const char * filter)
    {
        if (0 == strcmp(filter, "*"))
        {
            for (auto it = m_list.begin(), end = m_list.end();
                it != end;
                ++it)
            {
                std::unique_ptr<Test> test((*it)->Create());

                if (nullptr == test)
                {
                    continue;
                }

                executor.Run(test.get());
            }
        }
        else
        {
            for (auto it = m_list.begin(), end = m_list.end();
                it != end;
                ++it)
            {
                std::unique_ptr<Test> test((*it)->Create());

                if (nullptr == test)
                {
                    continue;
                }

                if ( 0 != strcmp( filter, test->Get_name() ) )
                {
                    continue;
                }

                executor.Run(test.get());
            }
        }
    }


    void TestCreatorRegister::Register(TestCreatorBase * creator)
    {
        m_list.push_front(creator);
    }
}

#endif /* UNIT_TESTS_ENABLE */
