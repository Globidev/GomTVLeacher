#ifndef SETTINGS_H
#define SETTINGS_H

class Settings : boost::noncopyable
{
    public :
        static Settings & instance();
        static void clean();

        static void setValue(const QString &, const QVariant &);
        static QVariant value(const QString &, const QVariant & = QVariant());

    private :
        Settings();
        QSettings settings_;
};

Constant SETTINGS_KEY_MEDIA_PLAYER_PATH = "MediaPlayer";
Constant SETTINGS_KEY_LIVESTREAMER_PATH = "Livestreamer";
Constant SETTINGS_KEY_VOD_OUTPUT_PATH = "VodOutputDir";

Constant SETTINGS_DEFAULT_MEDIA_PLAYER_PATH = "C:/Program Files (x86)/VideoLAN/VLC/vlc.exe";
Constant SETTINGS_DEFAULT_LIVESTREAMER_PATH = "livestreamer";
Constant SETTINGS_DEFAULT_VOD_OUTPUT_PATH = QDir::homePath();

#endif // SETTINGS_H