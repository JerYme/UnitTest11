/*
 * ItemTests.cpp
 *
 *  Created on: 28 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class IsIterableContainingItemTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("a vector containing the passed int is true", []() {
			AssertThat(ut11::Is::Iterable::Containing::Item(5)(std::vector<int>({1,2,3,4,5})), ut11::Is::True);
		});

		Then("a vector not containing the passed int is false", []() {
			AssertThat(ut11::Is::Iterable::Containing::Item(6)(std::vector<int>({1,2,3,4,5})), ut11::Is::False);
		});

        Then("Is::Iterable::Containing::Item() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::Containing::Item(5)) >::value, ut11::Is::True);
        });

        Then("Is::Iterable::Containing::Item() has an error message", []() {
            AssertThat(ut11::Is::Iterable::Containing::Item(5).GetErrorMessage(std::vector<int>()), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsIterableContainingItemTests)();

class IsIterableNotContainingItemTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("a vector containing the passed int is not true", []() {
			AssertThat(ut11::Is::Iterable::Not::Containing::Item(5)(std::vector<int>({1,2,3,4,5})), ut11::Is::Not::True);
		});

		Then("a vector not containing the passed int is not false", []() {
			AssertThat(ut11::Is::Iterable::Not::Containing::Item(6)(std::vector<int>({1,2,3,4,5})), ut11::Is::Not::False);
		});

        Then("Is::Iterable::Containing::Item() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::Not::Containing::Item(5)) >::value, ut11::Is::True);
        });

        Then("Is::Iterable::Containing::Item() has an error message", []() {
            AssertThat(ut11::Is::Iterable::Not::Containing::Item(5).GetErrorMessage(std::vector<int>()), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsIterableNotContainingItemTests)();
