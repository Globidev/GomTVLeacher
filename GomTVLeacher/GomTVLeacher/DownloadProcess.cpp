#include "stdafx.h"
#include "DownloadProcess.h"

#include "Settings.h"

#include "MainWindow.h"

DownloadProcess::DownloadProcess() : QProcess(),
    hasValidated_(false)
{
    QObject::connect(this, &QProcess::readyReadStandardOutput, [this]
    {
        QString output = readAllStandardOutput();
        Logger::log("stdout : " + output);
    });

    QObject::connect(this, &QProcess::readyReadStandardError, [this]
    {
        QString output = readAllStandardError();
        bool bytewrittenDebug = output.contains("Written");
        if(!bytewrittenDebug) Logger::log("stderr : " + output);
        validate(bytewrittenDebug);
    });

    QObject::connect(this, static_cast<ProcessErrorSignal>(&QProcess::error), [this]
    {
        validate(false);
        Logger::log("process error : " + errorString());
    });

    QObject::connect(this, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), [this](int code, QProcess::ExitStatus)
    {
        if(!hasValidated_) validate(false);
        Logger::log("process ended with code : " + QString::number(code));
    });
}

void DownloadProcess::setOnValidated(const ValidationCallBack & callBack)
{
    validationCallBack_ = callBack;
}

void DownloadProcess::validate(bool valid)
{
    if(valid) hasValidated_ = true;

    try
    { 
        validationCallBack_(valid); 
    }
    catch(const std::bad_function_call &) { }
}

void DownloadProcess::start(const QString & url, const QString & fileName)
{
    auto livestreamerPath = Settings::value(SETTINGS_KEY_LIVESTREAMER_PATH,
                                            SETTINGS_DEFAULT_LIVESTREAMER_PATH)
                                            .toString();
    QProcess::start(livestreamerPath, QStringList() << 
                    url << "best" << "-o" << fileName);
}