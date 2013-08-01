#include "stdafx.h"
#include "VodCollectionManager.h"

#include "Settings.h"

VodCollectionManager::VodCollectionManager()
{
    qAddPostRoutine(clean);
}

void VodCollectionManager::clean()
{
    for(auto & process : instance().processes_)
    {
        process->terminate();
        process->kill();
    }
    instance().processes_.clear();
}

VodCollectionManager & VodCollectionManager::instance()
{
    static VodCollectionManager vodCollectionManager;
    return vodCollectionManager;
}

bool VodCollectionManager::hasSet(const GomTvVod & vod, const GomTvVod::Set & set)
{
    QDir testDir(rootDir());
    if(!testDir.cd(vod.category.c_str())) return false;
    return testDir.exists(VOD_NAME(vod.name, set.first));
}

bool VodCollectionManager::hasVod(const GomTvVod & vod)
{
    return std::all_of(vod.sets.begin(), vod.sets.end(), 
        std::bind(&VodCollectionManager::hasSet, vod, std::placeholders::_1));
}

void VodCollectionManager::download(const GomTvVod & vod, 
                                    const GomTvVod::Set & set,
                                    const DownloadProcess::ValidationCallBack & callBack)
{
    std::unique_ptr<DownloadProcess> process(new DownloadProcess);
    process->setOnValidated(callBack);
    process->start(set.second.c_str(), filePathForVod(vod, set));
    instance().processes_.push_back(std::move(process));
}

void VodCollectionManager::play(const GomTvVod & vod, const GomTvVod::Set & set)
{
    auto mediaPlayerPath = Settings::value(SETTINGS_KEY_MEDIA_PLAYER_PATH,
                                           SETTINGS_DEFAULT_MEDIA_PLAYER_PATH)
                                           .toString();
    QProcess::startDetached(mediaPlayerPath, QStringList() << "--one-instance" 
                                                           << "--playlist-enqueue" 
                                                           << QDir::toNativeSeparators(filePathForVod(vod, set)));
}

bool VodCollectionManager::processesStillRunning()
{
    return std::any_of(instance().processes_.begin(), instance().processes_.end(),
        [](const std::unique_ptr<DownloadProcess> & process) 
        { 
            return process->state() == QProcess::Running; 
        });
}

QString VodCollectionManager::filePathForVod(const GomTvVod & vod, 
                                             const GomTvVod::Set & set)
{
    QDir outputDir(rootDir());
    outputDir.mkdir(vod.category.c_str());
    outputDir.cd(vod.category.c_str());

    return outputDir.filePath(VOD_NAME(vod.name, set.first));
}

QDir VodCollectionManager::rootDir()
{
    return Settings::value(SETTINGS_KEY_VOD_OUTPUT_PATH,
                           SETTINGS_DEFAULT_VOD_OUTPUT_PATH)
                           .toString();
}

void VodCollectionManager::clearProcessesCallbacks()
{
    for(auto & process : instance().processes_)
        process->clearCallback();
}