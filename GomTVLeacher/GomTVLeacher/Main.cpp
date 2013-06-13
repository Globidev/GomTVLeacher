#include "stdafx.h"

#include "PythonWrapper.h"

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow v;
    v.show();

    return app.exec();
}
