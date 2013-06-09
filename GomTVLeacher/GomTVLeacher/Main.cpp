#include "stdafx.h"

#include "PythonWrapper.h"

#include "GomVodTreeView.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GomVodTreeView v;
    v.show();

    return app.exec();
}
