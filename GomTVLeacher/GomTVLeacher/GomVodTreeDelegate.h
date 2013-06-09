#ifndef GOMVODTREEDELEGATE_H
#define GOMVODTREEDELEGATE_H

#include "GomTvVod.h"

class GomVodTreeDelegate : public QStyledItemDelegate
{
    public :
        virtual void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const;
        virtual QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const;

        virtual QWidget * createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
        virtual void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
};

Constant ACTION_BUTTON_RECT = [](const QRect & rect, const QSize & size) -> QRect
{
    return QRect(rect.width() - size.width() - 20, 
                 rect.y() + rect.height() - 50,
                 size.width(), 40);
};

#endif // GOMVODTREEDELEGATE_H