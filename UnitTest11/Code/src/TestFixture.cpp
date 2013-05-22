#include <UnitTest11/TestFixture.hpp>

ut11::TestFixture::~TestFixture()
{
}

ut11::TestFixtureImpl::TestFixtureImpl()
    : m_name(),
      m_StageBuilder(new ut11::Utility::TestStageBuilderImpl)
{
}

ut11::TestFixtureImpl::TestFixtureImpl(std::string name)
    : m_name(name),
      m_StageBuilder(new ut11::Utility::TestStageBuilderImpl)
{
}

ut11::TestFixtureImpl::TestFixtureImpl(std::string name, std::unique_ptr<ut11::Utility::TestStageBuilder> builder)
    : m_name(name),
      m_StageBuilder(std::move(builder))
{
}

ut11::TestFixtureImpl::~TestFixtureImpl()
{
}

void ut11::TestFixtureImpl::Given(std::string description, std::function<void(void)> logic)
{
    m_StageBuilder->PushGiven(Utility::TestStep(description, logic));
}

void ut11::TestFixtureImpl::When(std::string description, std::function<void(void)> logic)
{
    m_StageBuilder->PushWhen(Utility::TestStep(description, logic));
}

void ut11::TestFixtureImpl::Then(std::string description, std::function<void(void)> logic)
{
    m_StageBuilder->PushThen(Utility::TestStep(description, logic));
}

void ut11::TestFixtureImpl::Finally(std::string description, std::function<void(void)> logic)
{
    m_StageBuilder->PushFinally(Utility::TestStep(description, logic));
}

ut11::TestFixtureResults ut11::TestFixtureImpl::Run(Output& output)
{
    output.BeginFixture(m_name);
    Run();

    ut11::TestFixtureResults counter;
    auto Stages = m_StageBuilder->Stage();
    for(auto Stage : Stages)
    {
        ++counter.ran;

        if ( Stage->Run(output) )
            ++counter.succeeded;
    }
    output.EndFixture(m_name);
    return counter;
}

void ut11::TestFixtureImpl::Run()
{
}
