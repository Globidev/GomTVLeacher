#include "stdafx.h"
#include "GomTVModule.h"

#include "GomTvVod.h"

BOOST_PYTHON_MODULE(GomTv)
{
    using namespace bp;

    class_<GomTvVod>("GomTvVod", init<const std::string &, const std::string &>())
        .def_readwrite("name", &GomTvVod::name)
        .def_readwrite("url", &GomTvVod::url)
        .def_readwrite("date", &GomTvVod::date)
        .def_readwrite("category", &GomTvVod::category)
        .def("addSet", &GomTvVod::addSet)
        ;
};

void initGomTvModule()
{
    initGomTv();
}