#include "stdafx.h"
#include "GomVodTreeDelegate.h"

#include "GomVodTreeItems.h"

void GomVodTreeDelegate::paint(QPainter * painter, 
                               const QStyleOptionViewItem & option, 
                               const QModelIndex & index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    if(index.data(NoSpoilRole).toBool())
    {
        QRect r = painter->fontMetrics().boundingRect(option.rect, Qt::AlignVCenter, index.data().toString());
        r.setWidth(500);
        painter->fillRect(r, Qt::yellow);
    }
}

QSize GomVodTreeDelegate::sizeHint(const QStyleOptionViewItem & option, 
                                   const QModelIndex & index) const
{
    return QSize(option.rect.width(), 60);
}


QWidget * GomVodTreeDelegate::createEditor(QWidget * parent, 
                                           const QStyleOptionViewItem & option, 
                                           const QModelIndex & index) const
{
    auto editor = index.data(ActionButtonRole).value<QPushButton *>();
    if(editor)
        editor->setParent(parent);
    return editor;
}

void GomVodTreeDelegate::updateEditorGeometry(QWidget * editor, 
                                              const QStyleOptionViewItem & option,
                                              const QModelIndex & index) const
{
    editor->setGeometry(ACTION_BUTTON_RECT(option.rect, editor->sizeHint()));
}