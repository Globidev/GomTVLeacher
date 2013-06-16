#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GomVodTreeView.h"

#include "ui_SettingsDialog.h"

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

    private :
        Logger();
};

class MainWindow : public QMainWindow
{
    public :
        MainWindow();

    protected :
        virtual void closeEvent(QCloseEvent *);

    private :
        std::unique_ptr<QMenu> optionMenu_;
        std::unique_ptr<QAction> optionAction_;
        std::unique_ptr<OptionDialog> optionDialog_;

        std::unique_ptr<QMenu> loggerMenu_;
        std::unique_ptr<QAction> loggerAction_;

        std::unique_ptr<QWidget> centralWidget_;
        std::unique_ptr<QVBoxLayout> centralLayout_;

        std::unique_ptr<QPushButton> loadMore_;
        std::unique_ptr<GomVodTreeView> treeView_;

        std::unique_ptr<QLineEdit> searchField_;

        int page_;
};

#endif // MAINWINDOW_H