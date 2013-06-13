#include "stdafx.h"
#include "Settings.h"

Settings & Settings::instance()
{
    static Settings settings;
    return settings;
}

void Settings::clean()
{
    //instance().settings_.sync();
}

Settings::Settings() :
    settings_(QSettings::IniFormat, 
              QSettings::UserScope, 
              ".GlobiData/GomTVLeacher", "GomTVLeacher")
{
    qAddPostRoutine(clean);
}

void Settings::setValue(const QString & key, const QVariant & value)
{
    instance().settings_.setValue(key, value);
}

QVariant Settings::value(const QString & key, const QVariant & defaultValue)
{
    return instance().settings_.value(key, defaultValue);
}