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

Logger::Logger() : QTextBrowser()
{

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
    treeView_(      new GomVodTreeView(this)),
    optionMenu_(    new QMenu("Options", this)),
    optionAction_(  new QAction("options", optionMenu_.get())), 
    optionDialog_(  new OptionDialog(this)),
    loggerMenu_(    new QMenu("Logs", this)),
    loggerAction_(  new QAction("logs", loggerMenu_.get())),
    loadMore_(      new QPushButton("Load more")),
    centralWidget_( new QWidget),
    centralLayout_( new QVBoxLayout(centralWidget_.get())),
    page_(1)
{
    setCentralWidget(centralWidget_.get());
    centralLayout_->addWidget(treeView_.get());
    centralLayout_->addWidget(loadMore_.get());

    menuBar()->addMenu(optionMenu_.get());
    optionMenu_->addAction(optionAction_.get());

    QObject::connect(optionAction_.get(), &QAction::triggered,
                     optionDialog_.get(), &QDialog::exec);

    menuBar()->addMenu(loggerMenu_.get());
    loggerMenu_->addAction(loggerAction_.get());

    QObject::connect(loggerAction_.get(), &QAction::triggered,
                     &Logger::instance(), &QWidget::show);

    QObject::connect(loadMore_.get(), &QPushButton::clicked, [this]
    {
        treeView_->fetchVods(page_ ++);
    });

    setMinimumSize(800, 600);
    treeView_->fetchVods(page_ ++);
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