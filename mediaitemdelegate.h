#ifndef MEDIAITEMDELEGATE_H
#define MEDIAITEMDELEGATE_H
#include <QObject>
#include <QStyledItemDelegate>

class MediaItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MediaItemDelegate(QWidget *parent = nullptr) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

#endif // MEDIAITEMDELEGATE_H
