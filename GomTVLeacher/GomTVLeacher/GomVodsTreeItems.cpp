#include "stdafx.h"
#include "GomVodTreeItems.h"

GomVodTopTreeItem::GomVodTopTreeItem(const GomTvVod & vod, QTreeWidget * parent) :
    GomVodTreeItem<GomVodTopTreeItem>(parent),
    vod_(vod)
{
    setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    actionButton->setText("Download Everything");

    roles[Qt::DisplayRole] = LambdaRole( return vod_.name.c_str(); );
}

void GomVodTopTreeItem::fetchChildren()
{
    if(!vod_.hasFetchedInfos)
    {
        vod_.getInfos();
        for(auto & set : vod_.sets)
            addChild(new GomVodSubTreeItem(set));
    }
}

void GomVodTopTreeItem::onAction()
{

}

GomVodSubTreeItem::GomVodSubTreeItem(const GomTvVod::Set & set, QTreeWidget * parent) :
    GomVodTreeItem<GomVodSubTreeItem>(parent), 
    set_(set)
{
    actionButton->setText("Download");

    roles[Qt::DisplayRole] = LambdaRole( return set_.first.c_str(); );
}

void GomVodSubTreeItem::onAction()
{

}
