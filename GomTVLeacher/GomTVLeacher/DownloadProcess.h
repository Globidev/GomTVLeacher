#ifndef DOWNLOADPROCESS_H
#define DOWNLOADPROCESS_H

class DownloadProcess : public QProcess, boost::noncopyable
{
    public :
        typedef std::function <void (bool)> ValidationCallBack;

        DownloadProcess();

        void setOnValidated(const ValidationCallBack &);
        void start(const QString &, const QString &);          

    private :
        ValidationCallBack validationCallBack_;
};

#endif // DOWNLOADPROCESS_H