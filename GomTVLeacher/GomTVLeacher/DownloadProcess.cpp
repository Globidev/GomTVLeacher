#include "stdafx.h"
#include "DownloadProcess.h"

#include "Settings.h"

#include "MainWindow.h"

DownloadProcess::DownloadProcess() : QProcess()
{
    QObject::connect(this, &QProcess::readyReadStandardOutput, [this]
    {
        QString output = readAllStandardOutput();
        Logger::log("stdout : " + output);
    });

    QObject::connect(this, &QProcess::readyReadStandardError, [this]
    {
        QString output = readAllStandardError();
        bool writeDebug = output.contains("Written");
        if(!writeDebug) Logger::log("stderr : " + output);
        try { validationCallBack_(writeDebug); validationCallBack_ = ValidationCallBack(); }
        catch(const std::bad_function_call &) { }
    });

    QObject::connect(this, static_cast<void(QProcess::*)(QProcess::ProcessError)>(&QProcess::error), [this]
    {
        try { validationCallBack_(false); }
        catch(const std::bad_function_call &) { }
        Logger::log("process error : " + errorString());
    });

    QObject::connect(this, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), [this](int code, QProcess::ExitStatus)
    {
        try { validationCallBack_(false); }
        catch(const std::bad_function_call &) { }
        Logger::log("process ended with code : " + QString::number(code));
    });
}

void DownloadProcess::setOnValidated(const ValidationCallBack & callBack)
{
    validationCallBack_ = callBack;
}

void DownloadProcess::start(const QString & url, const QString & fileName)
{
    auto livestreamerPath = Settings::value(SETTINGS_KEY_LIVESTREAMER_PATH,
                                            SETTINGS_DEFAULT_LIVESTREAMER_PATH)
                                            .toString();
    QProcess::start(livestreamerPath, QStringList() << 
                    url << "best" << "-o" << fileName);
}