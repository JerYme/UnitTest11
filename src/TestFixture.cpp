#include <UnitTest11/TestFixture.hpp>

ut11::detail::TestFixtureAbstract::~TestFixtureAbstract()
{
}

ut11::TestFixture::TestFixture()
	: m_name(),
	  m_StageBuilder(new ut11::detail::TestStageBuilderImpl),
	  m_categories()
{
}

ut11::TestFixture::TestFixture(std::string name)
	: m_name(name),
	  m_StageBuilder(new ut11::detail::TestStageBuilderImpl),
	  m_categories()
{
}

ut11::TestFixture::TestFixture(std::string name, std::unique_ptr<ut11::detail::TestStageBuilder> builder)
	: m_name(name),
	  m_StageBuilder(std::move(builder)),
	  m_categories()
{
}

ut11::TestFixture::~TestFixture()
{
}

void ut11::TestFixture::AddCategory(ut11::Category category)
{
	m_categories.insert(category);
}

std::set<ut11::Category> ut11::TestFixture::GetCategories() const
{
	return m_categories;
}

void ut11::TestFixture::Given(std::string description, std::function<void(void)> logic)
{
	m_StageBuilder->PushGiven(detail::TestStep(description, logic));
}

void ut11::TestFixture::When(std::string description, std::function<void(void)> logic)
{
	m_StageBuilder->PushWhen(detail::TestStep(description, logic));
}

void ut11::TestFixture::Then(std::string description, std::function<void(void)> logic)
{
	m_StageBuilder->PushThen(detail::TestStep(description, logic));
}

void ut11::TestFixture::Finally(std::string description, std::function<void(void)> logic)
{
	m_StageBuilder->PushFinally(detail::TestStep(description, logic));
}

void ut11::TestFixture::Info(std::string message)
{
  if (m_isRunning)
    {
      m_output->OnInfo(message);
      return;
    }

m_StageBuilder->PushInfo(detail::TestStep(message));

}

ut11::detail::TestFixtureResults ut11::TestFixture::Run(out::Output& output)
{
	output.BeginFixture(m_name);
	Run();

	m_output = &output;

	ut11::detail::TestFixtureResults counter;
	for (auto stage : m_StageBuilder->Build())
	{
	    m_isRunning = true;
		++counter.ran;

		if ( stage->Run(output) )
			++counter.succeeded;
	}
	output.EndFixture(m_name);
	return counter;
}

void ut11::TestFixture::Run()
{
}
