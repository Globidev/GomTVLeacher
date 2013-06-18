#ifndef DOWNLOADPROCESS_H
#define DOWNLOADPROCESS_H

class DownloadProcess : public QProcess, boost::noncopyable
{
    public :
        typedef std::function <void (bool)> ValidationCallBack;
        typedef void(QProcess::*ProcessErrorSignal)(QProcess::ProcessError);

        DownloadProcess();

        void setOnValidated(const ValidationCallBack &);
        void start(const QString &, const QString &);     

        void validate(bool);

    private :
        ValidationCallBack validationCallBack_;
        bool hasValidated_;
};

#endif // DOWNLOADPROCESS_H