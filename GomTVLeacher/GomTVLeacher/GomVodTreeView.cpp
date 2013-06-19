#include "stdafx.h"
#include "GomVodTreeView.h"

#include "PythonWrapper.h"

GomVodTreeView::GomVodTreeView(QWidget * parent) : QTreeWidget(parent),
    delegate_(new GomVodTreeDelegate)
{
    QObject::connect(this, &QTreeWidget::itemExpanded,
                    [this](QTreeWidgetItem * item) { expandVod(item); });

    setHeaderLabel("Vods");
    setFont(QFont("Consolas"));
    setItemDelegate(delegate_.get());

    setMouseTracking(true);
}

void GomVodTreeView::fetchVods(int page, const QString & search)
{
    PythonWrapper::exec([=](const bp::object & globals)
    {
        bp::object getVods = globals[GET_VODS_FUNC_NAME];
        auto pyVods = bp::call<bp::list>(getVods.ptr(), std::to_string(page), search.toStdString());
        
        for(auto & vod : sequenceToList<GomTvVod>(pyVods)) addVod(vod);
    });
}

void GomVodTreeView::clear()
{
    topLevelItems_.clear();
    QTreeWidget::clear();
}

void GomVodTreeView::mouseMoveEvent(QMouseEvent * event)
{
    auto item = itemAt(event->pos());
    for(auto & topItem : topLevelItems_)
        for(auto subitem : topItem->children())
        {
            bool showSpoilers = subitem == item;
            if(showSpoilers)
                showSpoilers &= fontMetrics().boundingRect(
                    visualItemRect(item), Qt::AlignVCenter, subitem->text(0))
                        .contains(event->pos());
            subitem->setSpoilerShown(showSpoilers);
        }

    QTreeWidget::mouseMoveEvent(event);
}

void GomVodTreeView::addVod(const GomTvVod & vod)
{
    std::unique_ptr<GomVodTopTreeItem> item(new GomVodTopTreeItem(vod));
    addTopLevelItem(item.get());
    topLevelItems_.push_back(std::move(item));
}

void GomVodTreeView::expandVod(QTreeWidgetItem * item)
{
    openPersistentEditor(item);

    int index = indexOfTopLevelItem(item);
    topLevelItems_.at(index)->fetchChildren();

    for(int i(0); i < item->childCount(); ++ i)
        openPersistentEditor(item->child(i));
}