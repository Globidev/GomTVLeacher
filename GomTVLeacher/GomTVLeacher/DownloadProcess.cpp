#include "stdafx.h"
#include "DownloadProcess.h"

DownloadProcess::DownloadProcess() : QProcess()
{
    QObject::connect(this, &QProcess::readyReadStandardOutput, [this]
    {
        QString output = readAllStandardOutput();
        qDebug() << output;
    });

    QObject::connect(this, &QProcess::readyReadStandardError, [this]
    {
        QString output = readAllStandardError();
        try { validationCallBack_(output.contains("Written")); }
        catch(const std::bad_function_call &) { }
    });
}

void DownloadProcess::setOnValidated(const ValidationCallBack & callBack)
{
    validationCallBack_ = callBack;
}

void DownloadProcess::start(const QString & url, const QString & fileName)
{
    QProcess::start("C:/Dev/Python33/Scripts/livestreamer.exe", 
                    QStringList() << url << "best" << "-o" << fileName);
}