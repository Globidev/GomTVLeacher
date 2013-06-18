#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GomVodTreeView.h"

#include "ui_SettingsDialog.h"
#include "ui_MainWindow.h"

class OptionDialog : public QDialog
{
    public :
        OptionDialog(QWidget * = NULL);

    private :
        Ui::UiOptionDialog ui;
};

class Logger : public QTextBrowser, boost::noncopyable
{
    public :
        static Logger & instance();
        static void log(const QString &);
};

class MainWindow : public QMainWindow
{
    public :
        MainWindow();

    protected :
        virtual void closeEvent(QCloseEvent *);

    private :
        Ui::UiMainWindow ui;
        OptionDialog optionDialog_;

        GomVodTreeView treeView_;

        int page_;
};

#endif // MAINWINDOW_H