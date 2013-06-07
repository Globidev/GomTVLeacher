#include "stdafx.h"

#include "PythonWrapper.h"

#include "GomTvVod.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bp::list gomVods;

    PythonWrapper::exec([&](const bp::object & globals)
    {
        bp::object getVodsFunction = globals["getGomVods"];
        gomVods = bp::call<bp::list>(getVodsFunction.ptr());
        qDebug() << bp::len(gomVods);
        bp::stl_input_iterator<GomTvVod> begin(gomVods), end;
        std::list<GomTvVod> vods(begin, end);
        for(auto & vod : vods)
        {
            qDebug() << vod.name.c_str() << vod.url.c_str() << vod.date.c_str();
            for(auto & str : vod.sets)
                qDebug() << str.c_str();
        }

    });

    return app.exec();
}
