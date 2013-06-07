#include "stdafx.h"
#include "GomTvVod.h"

#include "PythonWrapper.h"

GomTvVod::GomTvVod(const std::string & name, const std::string & url)
    : name(name), url(url) 
{ }

void GomTvVod::getInfos()
{
    PythonWrapper::exec([&](const bp::object & globals)
    {
        bp::object setInfoFunc = globals[SET_VOD_INFO_FUNC_NAME];
        setInfoFunc(boost::ref(*this));
    });
}