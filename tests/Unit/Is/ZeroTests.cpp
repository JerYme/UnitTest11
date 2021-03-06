#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/Zero.hpp>

class IsZeroTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::Zero(0) is True", []() {
			AssertThat(ut11::Is::Zero(0), ut11::Is::True);
		});
		Then("Is::Zero(0.0f) is True", []() {
			AssertThat(ut11::Is::Zero(0.0f), ut11::Is::True);
		});
		Then("Is::Zero(0.5f) is False", []() {
			AssertThat(ut11::Is::Zero(0.5f), ut11::Is::False);
		});
		Then("Is::Zero(1) is False", []() {
			AssertThat(ut11::Is::Zero(1), ut11::Is::False);
		});

		Then("Is::Zero(-1) is False", []() {
			AssertThat(ut11::Is::Zero(-1), ut11::Is::False);
		});
		Then("Is::Zero is Operand", []() {
			AssertThat(ut11::detail::IsOperand< decltype(ut11::Is::Zero) >::value, ut11::Is::True);
		});
		Then("Is::Zero has an error message", []() {
			AssertThat(ut11::Is::Zero.GetErrorMessage(1), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsZeroTests)(ut11::Category("unit"));

class IsNotZeroTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::Not::Zero(0) is Not::True", []() {
			AssertThat(ut11::Is::Not::Zero(0), ut11::Is::Not::True);
		});

		Then("Is::Not::Zero(0.0f) is Not::True", []() {
			AssertThat(ut11::Is::Not::Zero(0.0f), ut11::Is::Not::True);
		});

		Then("Is::Not::Zero(0.5f) is True", []() {
			AssertThat(ut11::Is::Not::Zero(0.5f), ut11::Is::True);
		});

		Then("Is::Not::Zero(1) is Not::False", []() {
			AssertThat(ut11::Is::Not::Zero(1), ut11::Is::Not::False);
		});

		Then("Is::Not::Zero(-1) is Not::False", []() {
			AssertThat(ut11::Is::Not::Zero(-1), ut11::Is::Not::False);
		});

		Then("Is::Not::Zero is Operand", []() {
			AssertThat(ut11::detail::IsOperand< decltype(ut11::Is::Not::Zero) >::value, ut11::Is::True);
		});

		Then("Is::Not::Zero has an error message", []() {
			AssertThat(ut11::Is::Not::Zero.GetErrorMessage(1), ut11::Is::Not::EqualTo(""));
		});

	}
};
DeclareFixture(IsNotZeroTests)(ut11::Category("unit"));
