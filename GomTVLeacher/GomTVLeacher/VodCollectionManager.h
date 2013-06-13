#ifndef VODCOLLECTIONMANAGER_H
#define VODCOLLECTIONMANAGER_H

#include "GomTvVod.h"
#include "DownloadProcess.h"

class VodCollectionManager : boost::noncopyable
{
    public :
        static VodCollectionManager & instance();
        static void clean();

        static bool hasSet(const GomTvVod &, const GomTvVod::Set &);
        static bool hasVod(const GomTvVod &);

        static void download(const GomTvVod &, const GomTvVod::Set &,
                             const DownloadProcess::ValidationCallBack &);

        static void play(const GomTvVod &, const GomTvVod::Set &);

        static bool processesStillRunning();

        static QDir rootDir();

    private :
        VodCollectionManager();

        static inline QString filePathForVod(const GomTvVod &, 
                                             const GomTvVod::Set &);

        std::vector<std::unique_ptr<DownloadProcess>> processes_;
};

Constant VOD_NAME = [](const std::string & name, const std::string & sub) -> QString
{
    return QString("[%1] %2.avi").arg(name.c_str(), sub.c_str());
};

#endif // VODCOLLECTIONMANAGER_H