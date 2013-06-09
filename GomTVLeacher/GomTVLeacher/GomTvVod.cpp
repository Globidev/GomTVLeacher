#include "stdafx.h"
#include "GomTvVod.h"

#include "PythonWrapper.h"

GomTvVod::GomTvVod(const std::string & name, const std::string & url)
    : name(name), url(url) , hasFetchedInfos(false)
{ }

void GomTvVod::getInfos()
{
    PythonWrapper::exec([&](const bp::object & globals)
    {
        bp::object setInfoFunc = globals[SET_VOD_INFO_FUNC_NAME];
        setInfoFunc(boost::ref(*this));
    });
    hasFetchedInfos = true;
}

void GomTvVod::addSet(const std::string & setName)
{
    Set set = std::make_pair(setName, url + "/?set=" + std::to_string(sets.size() + 1));
    sets.push_back(set);
}