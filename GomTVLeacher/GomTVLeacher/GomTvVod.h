#ifndef GOMTVVOD_H
#define GOMTVVOD_H

struct GomTvVod
{
    typedef std::vector<std::string> Sets;

    GomTvVod(const std::string &, const std::string &);

    std::string name;
    std::string url;
    std::string date;
    Sets sets;
};

#endif // GOMTVVOD_H