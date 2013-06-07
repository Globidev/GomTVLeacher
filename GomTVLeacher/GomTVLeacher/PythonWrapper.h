#ifndef PYTHONWRAPPER_H
#define PYTHONWRAPPER_H

class PythonWrapper : boost::noncopyable
{
    typedef std::function<void (const bp::object &)> PyFunctor;

    public :
        static PythonWrapper & instance();
        static void clean();

        static void exec(const PyFunctor &);
        static void exec(const QByteArray &);
        static void execFile(const QString &);

    private :
        PythonWrapper();
        bp::object globals_;
};

#endif // PYTHONWRAPPER_H