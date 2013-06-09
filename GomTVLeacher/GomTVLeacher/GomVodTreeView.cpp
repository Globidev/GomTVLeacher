#include "stdafx.h"
#include "GomVodTreeView.h"

#include "PythonWrapper.h"

GomVodTreeView::GomVodTreeView(QWidget * parent) : QTreeWidget(parent),
    delegate_(new GomVodTreeDelegate)
{
    QObject::connect(this, &QTreeWidget::itemExpanded,
                    [this](QTreeWidgetItem * item) { expandVod(item); });

    setHeaderLabel("Vods");
    setAlternatingRowColors(true);
    setItemDelegate(delegate_.get());

    fetchVods();
}

void GomVodTreeView::fetchVods()
{
    PythonWrapper::exec([this](const bp::object & globals)
    {
        bp::object getVods = globals[GET_VODS_FUNC_NAME];
        auto pyVods = bp::call<bp::list>(getVods.ptr());
        
        for(auto & vod : sequenceToList<GomTvVod>(pyVods)) addVod(vod);
    });
}

void GomVodTreeView::addVod(const GomTvVod & vod)
{
    std::unique_ptr<GomVodTopTreeItem> item(new GomVodTopTreeItem(vod));
    addTopLevelItem(item.get());
    topLevelItems_.push_back(std::move(item));
}

void GomVodTreeView::expandVod(QTreeWidgetItem * item)
{
    int index = indexOfTopLevelItem(item);
    topLevelItems_.at(index)->fetchChildren();

    openPersistentEditor(item);
    for(int i = 0; i < item->childCount(); ++ i)
        openPersistentEditor(item->child(i));
}