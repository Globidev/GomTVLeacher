#include "stdafx.h"
#include "GomVodTreeItems.h"

#include "VodCollectionManager.h"

#include "MainWindow.h"

GomVodTopTreeItem::GomVodTopTreeItem(const GomTvVod & vod, 
                                     QTreeWidget * parent) :
    GomVodTreeItem<GomVodTopTreeItem>(parent),
    vod_(vod)
{
    changeState(Downloadable);
    setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

    roles[Qt::DisplayRole] = LambdaRole(
        auto name = QString("%1 %2").arg(vod_.category.c_str(), 
                                         vod_.name.c_str());
        return QString("%1 %2").arg(name,
                                    QString(vod_.date.c_str()).rightJustified(85 - name.size())); );
}

void GomVodTopTreeItem::fetchChildren()
{
    if(!vod_.hasFetchedInfos)
    {
        vod_.getInfos();
        for(auto & set : vod_.sets) addSubset(set);
    }
}

GomTvVod GomVodTopTreeItem::vod() const
{
    return vod_;
}

void GomVodTopTreeItem::addSubset(const GomTvVod::Set & set)
{
    GomVodSubTreeItem * item = new GomVodSubTreeItem(set, this);
    addChild(item);
    children_.push_back(std::move(item));
}

void GomVodTopTreeItem::changeState(VodState state)
{
    state_ = state;
    switch(state_)
    {
        case Downloadable :
            actionButton->setIcon(QIcon(":/GomTVLeacher/DownloadArrow"));
            actionButton->setText("Download Everything");
            break;

        case StartedToDownload :
            actionButton->setText("Downloading ...");
            actionButton->setDisabled(true);
            for(auto & child : children_) 
                if(child->state_ == Downloadable)
                    child->onAction();
            break;

        case Watchable :
            // seems like closePersistentEditor deletes the editor... wtf
            treeWidget()->closePersistentEditor(this);
            actionButton.release();
            break;
    }

    emitDataChanged();
}

void GomVodTopTreeItem::onAction()
{
    if(state_ == Downloadable)
        changeState(StartedToDownload);
}

GomVodSubTreeItem::GomVodSubTreeItem(const GomTvVod::Set & set, 
                                     GomVodTopTreeItem * parent) :
    GomVodTreeItem<GomVodSubTreeItem>(), 
    set_(set), parent_(parent)
{

    changeState(VodCollectionManager::hasSet(parent->vod(), set_) ? Watchable : Downloadable);

    roles[Qt::DisplayRole] = LambdaRole( return set_.first.c_str(); );
}

void GomVodSubTreeItem::onAction()
{
    switch(state_)
    {
        case Downloadable :
            changeState(StartedToDownload);
            download();
            break;

        case Watchable :
            VodCollectionManager::play(parent_->vod(), set_);
            break;

        case Error :
            Logger::instance().show();
            changeState(Downloadable);
            break;
    }
}

void GomVodSubTreeItem::changeState(VodState state)
{
    state_ = state;
    switch(state_)
    {
        case Downloadable :
            actionButton->setIcon(QIcon(":/GomTVLeacher/DownloadArrow"));
            actionButton->setText("Download");
            actionButton->setEnabled(true);
            break;

        case StartedToDownload :
            actionButton->setText("Downloading ...");
            actionButton->setDisabled(true);
            break;

        case Watchable :
            actionButton->setIcon(QIcon(":/GomTVLeacher/PlayTriangle"));
            actionButton->setText("Watch");
            actionButton->setEnabled(true);
            if(VodCollectionManager::hasVod(parent_->vod()))
                parent_->changeState(Watchable);
            break;

        case Error :
            actionButton->setIcon(QIcon(":/GomTVLeacher/ErrorCross"));
            actionButton->setText("Error");
            actionButton->setEnabled(true);
            break;
    }

    emitDataChanged();
}

void GomVodSubTreeItem::download()
{
    VodCollectionManager::download(parent_->vod(), set_, [this](bool ok)
    {
        changeState(ok ? Watchable : Error);
    });
}
