#ifndef GOMTVVOD_H
#define GOMTVVOD_H

struct GomTvVod
{
    typedef std::pair<std::string, std::string> Set;
    typedef std::vector<Set> Sets;

    GomTvVod(const std::string &, const std::string &);

    void getInfos();
    void addSet(const std::string &);

    std::string category;
    std::string name;
    std::string url;
    std::string date;
    Sets sets;

    bool hasFetchedInfos;
};

Q_DECLARE_METATYPE(GomTvVod::Sets)

Constant SET_VOD_INFO_FUNC_NAME = "setVodInfos";

#endif // GOMTVVOD_H