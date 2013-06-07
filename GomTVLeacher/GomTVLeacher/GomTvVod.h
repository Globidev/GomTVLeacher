#ifndef GOMTVVOD_H
#define GOMTVVOD_H

Constant SET_VOD_INFO_FUNC_NAME = "setVodInfos";

struct GomTvVod
{
    typedef std::vector<std::string> Sets;

    GomTvVod(const std::string &, const std::string &);

    void getInfos();

    std::string name;
    std::string url;
    std::string date;
    Sets sets;
};

#endif // GOMTVVOD_H