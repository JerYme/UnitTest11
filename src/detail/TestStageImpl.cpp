#include <UnitTest11/detail/TestStageImpl.hpp>
#include <UnitTest11/detail/TestFailedException.hpp>

ut11::detail::TestStageImpl::TestStageImpl()
	: m_given(),
	  m_when(),
	  m_then(),
	  m_finally(),
	  m_once()
{
}

ut11::detail::TestStageImpl::TestStageImpl(TestStep once)
	: m_given(),
	  m_when(),
	  m_then(),
	  m_finally(),
	  m_once(once)
{
}

ut11::detail::TestStageImpl::TestStageImpl(TestStep given, TestStep when, TestStep then, TestStep finally)
	: m_given(given),
	  m_when(when),
	  m_then(then),
	  m_finally(finally),
	  m_once()
{
}

ut11::detail::TestStageImpl::~TestStageImpl()
{
}


bool ut11::detail::TestStageImpl::Run(out::Output& output)
{
  if (!m_once.description.empty())
    {
      output.OnInfo(m_once.description);
    return true;
    }

	auto runInsideTryCatch = [&](std::function<void(void)> func) -> bool {

		try
		{
			func();
		}
		catch (const ut11::detail::TestFailedException& ex)
		{
			output.OnError(ex.GetLine(), ex.GetFile(), ex.GetMessage());
			return false;
		}
		catch(const std::exception& ex)
		{
			output.OnError(ex);
			return false;
		}
		catch(...)
		{
			output.OnUnknownError();
			return false;
		}
		return true;
	};

	auto theFinallyFunction = [&]() -> void {
		output.EndTest();

		Finally(output);
	};
	auto theGivenWhenThenFinallyFunctions = [&]() -> void
	{
		output.BeginTest();

		Given(output);
		When(output);
		Then(output);
		theFinallyFunction();
	};

	if (!runInsideTryCatch(theGivenWhenThenFinallyFunctions))
	{
		runInsideTryCatch(theFinallyFunction);

		return false;
	}
	return true;

}

void ut11::detail::TestStageImpl::Given(out::Output& output)
{
	if ( !m_given.logic )
		return;

	output.BeginGiven(m_given.description);
	m_given.logic();
	output.EndGiven(m_given.description);
}

void ut11::detail::TestStageImpl::When(out::Output& output)
{
	if ( !m_when.logic )
		return;

	output.BeginWhen(m_when.description);
	m_when.logic();
	output.EndWhen(m_when.description);
}

void ut11::detail::TestStageImpl::Then(out::Output& output)
{
	if ( !m_then.logic )
		return;

	output.BeginThen(m_then.description);
	m_then.logic();
	output.EndThen(m_then.description);
}

void ut11::detail::TestStageImpl::Finally(out::Output& output)
{
  if ( !m_finally.logic )
      return;

	output.BeginFinally(m_finally.description);
	m_finally.logic();
	output.EndFinally(m_finally.description);
}
