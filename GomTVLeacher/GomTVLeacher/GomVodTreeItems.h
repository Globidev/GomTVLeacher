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
enum VodState { Downloadable, StartedToDownload, Watchable, Error };

template <class TreeItem>
struct GomVodTreeItem : public QTreeWidgetItem
{
    typedef std::map<int, std::function<QVariant ()>> Roles;

    GomVodTreeItem(QTreeWidget * parent = NULL) :
        QTreeWidgetItem(parent),
        actionButton(new QCommandLinkButton)
    {
        roles[ActionButtonRole]   = LambdaRole( 
            return QVariant::fromValue(actionButton.get()); );
        roles[Qt::BackgroundRole] = LambdaRole(
            return COLOR_FOR_STATE(state_); );

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
    std::unique_ptr<QCommandLinkButton> actionButton;
    VodState state_;
};

class GomVodTopTreeItem;

class GomVodSubTreeItem : public GomVodTreeItem<GomVodSubTreeItem>
{
    public :
        GomVodSubTreeItem(const GomTvVod::Set &, GomVodTopTreeItem *);
        void onAction();

    private :
        inline void changeState(VodState);
        inline void download();

        GomTvVod::Set set_;
        GomVodTopTreeItem * parent_;
};

class GomVodTopTreeItem : public GomVodTreeItem<GomVodTopTreeItem>
{
    public :
        GomVodTopTreeItem(const GomTvVod &, QTreeWidget * = NULL);

        void fetchChildren();
        void changeState(VodState);
        void onAction();

        GomTvVod vod() const;

    private :
        inline void addSubset(const GomTvVod::Set &);

        GomTvVod vod_;
        std::vector<GomVodSubTreeItem *> children_;
};

Constant COLOR_FOR_STATE = [](VodState state) -> QColor
{
    switch(state)
    {
        case Downloadable      : return Qt::transparent;
        case StartedToDownload : return QColor(255, 255, 128, 100);
        case Watchable         : return QColor(0, 255, 0, 100);
        case Error             : return QColor(255, 0, 0, 100);
    }

    return QColor();
};

#endif // GOMVODTOPTREEITEMS_H
