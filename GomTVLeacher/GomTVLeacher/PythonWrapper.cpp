#include "stdafx.h"
#include "PythonWrapper.h"

#include "GomTVModule.h"

PythonWrapper & PythonWrapper::instance()
{
    static PythonWrapper pythonWrapper;
    return pythonWrapper;
}

PythonWrapper::PythonWrapper()
{
    Py_Initialize();
    initGomTvModule();

    globals_ = bp::import("__main__").attr("__dict__");
    execFile(":/GomTVLeacher/GOMParser");

    qAddPostRoutine(clean);
}

void PythonWrapper::clean()
{
    Py_Finalize();
}

void PythonWrapper::exec(const QByteArray & code)
{
    exec([&](const bp::object & globals)
    {
        bp::exec(code.constData(), globals);
    });
}

void PythonWrapper::execFile(const QString & fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
        exec(file.readAll());
}

void PythonWrapper::exec(const PyFunctor & functor)
{
    try
    {
        functor(instance().globals_);
    }
    catch(const bp::error_already_set &)
    {
        PyErr_Print();
    }
}