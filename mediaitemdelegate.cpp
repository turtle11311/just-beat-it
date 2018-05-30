#include "mediaitemdelegate.h"
#include "mediainfo.h"
#include <QPainter>

void MediaItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
    if (index.data().canConvert<MediaInfo>()) {
            MediaInfo mediainfo = qvariant_cast<MediaInfo>(index.data());

            if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.highlight());
            mediainfo.paint(painter, option.rect, option.palette);
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }
}

QSize MediaItemDelegate::sizeHint(const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
    Q_UNUSED(option);

    MediaInfo mediainfo = qvariant_cast<MediaInfo>(index.data());
    return mediainfo.sizeHint();
}
