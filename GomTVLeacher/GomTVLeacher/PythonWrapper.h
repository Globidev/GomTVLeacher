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

template <typename T>
std::list<T> sequenceToList(const bp::list & sequence)
{
    bp::stl_input_iterator<T> begin(sequence), end;
    return std::list<T>(begin, end);
}

#endif // PYTHONWRAPPER_H