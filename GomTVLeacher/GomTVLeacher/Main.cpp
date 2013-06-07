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
    });

    auto gomVodsList = sequenceToList<GomTvVod>(gomVods);
    for(auto & vod : gomVodsList)
    {
        qDebug() << vod.name.c_str() << vod.url.c_str()
                 << "getting sets infos...";
        vod.getInfos();
        qDebug() << vod.sets.size();
    }

    return app.exec();
}
