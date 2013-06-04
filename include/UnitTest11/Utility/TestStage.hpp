#ifndef UNITTEST11_UTILITY_TESTSTAGE_HPP
#define UNITTEST11_UTILITY_TESTSTAGE_HPP

#include "../Output.hpp"

namespace ut11
{
    namespace Utility
    {
        class TestStage
        {
        public:
            virtual ~TestStage();

            virtual bool Run(Output& output) = 0;
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTAGE_HPP