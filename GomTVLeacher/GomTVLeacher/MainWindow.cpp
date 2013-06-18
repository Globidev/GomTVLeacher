#include "stdafx.h"
#include "MainWindow.h"

#include "VodCollectionManager.h"
#include "Settings.h"

OptionDialog::OptionDialog(QWidget * parent) : QDialog(parent)
{
    ui.setupUi(this);

    ui.vodEdit->setText(Settings::value(SETTINGS_KEY_VOD_OUTPUT_PATH).toString());
    ui.livestreamerEdit->setText(Settings::value(SETTINGS_KEY_LIVESTREAMER_PATH).toString());
    ui.mediaPlayerEdit->setText(Settings::value(SETTINGS_KEY_MEDIA_PLAYER_PATH).toString());

    QObject::connect(ui.vodBrowse, &QPushButton::clicked, [this]
    {
        auto path = QFileDialog::getExistingDirectory(this, "VOD directory", 
                                                      ui.vodEdit->text());
        if(!path.isEmpty()) ui.vodEdit->setText(path);
    });

    QObject::connect(ui.livestreamerBrowse, &QPushButton::clicked, [this]
    {
        auto path = QFileDialog::getOpenFileName(this, "livestreamer cli", 
                                                 ui.livestreamerEdit->text(),
                                                 "livestreamer(livestreamer.exe)");
        if(!path.isEmpty()) ui.livestreamerEdit->setText(path);
    });

    QObject::connect(ui.mediaPlayerBrowse, &QPushButton::clicked, [this]
    {
        auto path = QFileDialog::getOpenFileName(this, "VOD directory",
                                                 ui.mediaPlayerEdit->text(),
                                                 "executable(*.exe)");
        if(!path.isEmpty()) ui.mediaPlayerEdit->setText(path);
    });

    QObject::connect(this, &QDialog::accepted, [this]
    {
        Settings::setValue(SETTINGS_KEY_VOD_OUTPUT_PATH, ui.vodEdit->text());
        Settings::setValue(SETTINGS_KEY_LIVESTREAMER_PATH, ui.livestreamerEdit->text());
        Settings::setValue(SETTINGS_KEY_MEDIA_PLAYER_PATH, ui.mediaPlayerEdit->text());
    });
}

Logger & Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::log(const QString & text)
{
    instance().append(text);
}

MainWindow::MainWindow() : QMainWindow(),
    page_(1)
{
    ui.setupUi(this);
    ui.verticalLayout->insertWidget(1, &treeView_);

    QObject::connect(ui.actionOptions, &QAction::triggered,
                     &optionDialog_, &QDialog::exec);

    QObject::connect(ui.actionLogs, &QAction::triggered,
                     &Logger::instance(), &QWidget::show);

    QObject::connect(ui.loadMore, &QPushButton::clicked, [this]
    {
        treeView_.fetchVods(page_ ++, ui.searchField->text());
    });

    setMinimumSize(900, 600);
    treeView_.fetchVods(page_ ++);

    QObject::connect(ui.searchField, &QLineEdit::returnPressed, [this]
    {
        page_ = 1;
        treeView_.clear();
        treeView_.fetchVods(page_ ++, ui.searchField->text());
    });
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    bool doQuit = true;
    if(VodCollectionManager::processesStillRunning())
        doQuit = QMessageBox::question(NULL, "Warning", 
                                       "Download processes are still running\nDo you still want to close the application ?")
                                       == QMessageBox::Yes;
    event->setAccepted(doQuit);
}