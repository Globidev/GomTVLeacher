#ifndef GOMVODTOPTREEITEMS_H
#define GOMVODTOPTREEITEMS_H

#include "GomTvVod.h"

class GomVodItemButton : public QPushButton
{
    public :
        GomVodItemButton(QWidget * = NULL);

};

enum GomVodTreeRoles
{
    ActionButtonRole = Qt::UserRole + 1
};

#define LambdaRole(code) [this]() -> QVariant { code }
enum VodState { Downloadable, Watchable };

template <class TreeItem>
struct GomVodTreeItem : public QTreeWidgetItem
{
    typedef std::map<int, std::function<QVariant ()>> Roles;

    GomVodTreeItem(QTreeWidget * parent = NULL) :
        QTreeWidgetItem(parent),
        actionButton(new QPushButton)
    {
        roles[ActionButtonRole]   = LambdaRole( 
            return QVariant::fromValue(actionButton.get()); );
        roles[Qt::BackgroundRole] = LambdaRole(
            return COLOR_FOR_STATE(state); );

        QObject::connect(actionButton.get(), &QPushButton::clicked,
                         [this] { self().onAction(); });
    }

    TreeItem & self()
    {
        return static_cast<TreeItem &>(*this);
    }

    QVariant data(int, int role) const
    {
        auto found = roles.find(role);
        return found != roles.end() ? found->second() : QVariant();
    }

    Roles roles;
    std::unique_ptr<QPushButton> actionButton;
    VodState state;
};

class GomVodTopTreeItem : public GomVodTreeItem<GomVodTopTreeItem>
{
    public :
        GomVodTopTreeItem(const GomTvVod &, QTreeWidget * = NULL);

        void fetchChildren();
        void onAction();

    private :
        GomTvVod vod_;
};

class GomVodSubTreeItem : public GomVodTreeItem<GomVodSubTreeItem>
{
    public :
        GomVodSubTreeItem(const GomTvVod::Set &, QTreeWidget * = NULL);

        void onAction();

    private :
        GomTvVod::Set set_;
};

Constant COLOR_FOR_STATE = [](VodState state) -> QColor
{
    return state == Downloadable ?
        Qt::blue : Qt::transparent;
};

#endif // GOMVODTOPTREEITEMS_H
