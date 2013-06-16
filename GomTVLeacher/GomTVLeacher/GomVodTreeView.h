#ifndef GOMVODTREEVIEW_H
#define GOMVODTREEVIEW_H

#include "GomVodTreeDelegate.h"
#include "GomVodTreeItems.h"

class GomVodTreeView : public QTreeWidget
{
    public :
        explicit GomVodTreeView(QWidget * = NULL);

        void fetchVods(int page, const QString & = QString());
        void clear();

    private :
        inline void addVod(const GomTvVod &);
        void expandVod(QTreeWidgetItem *);

        std::unique_ptr<GomVodTreeDelegate> delegate_;
        std::vector<std::unique_ptr<GomVodTopTreeItem>> topLevelItems_;
};

Constant GET_VODS_FUNC_NAME = "getGomVods";

#endif // GOMVODETREEVIEW_H