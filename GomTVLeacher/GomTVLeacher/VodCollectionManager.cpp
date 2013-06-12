#include "stdafx.h"
#include "VodCollectionManager.h"

VodCollectionManager::VodCollectionManager() :
    rootDir_(QDir::home())
{
    qAddPostRoutine(clean);
    qDebug() << rootDir_;
}

void VodCollectionManager::clean()
{

}

VodCollectionManager & VodCollectionManager::instance()
{
    static VodCollectionManager vodCollectionManager;
    return vodCollectionManager;
}

bool VodCollectionManager::hasSet(const GomTvVod & vod, const GomTvVod::Set & set)
{
    auto & self = instance();

    QDir testDir(self.rootDir_);
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
    QProcess::startDetached("C:/Program Files (x86)/VideoLAN/VLC/vlc.exe",
                            QStringList() << 
                            QDir::toNativeSeparators(filePathForVod(vod, set)));
}

QString VodCollectionManager::filePathForVod(const GomTvVod & vod, 
                                             const GomTvVod::Set & set)
{
    QDir outputDir(instance().rootDir_);
    outputDir.mkdir(vod.category.c_str());
    outputDir.cd(vod.category.c_str());

    return outputDir.filePath(VOD_NAME(vod.name, set.first));
}