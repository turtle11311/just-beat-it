#include "youtubemedialistmodel.h"

YoutubeMediaListModel::YoutubeMediaListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant YoutubeMediaListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
            return QStringLiteral("Column %1").arg(section);
        else
            return QStringLiteral("Row %1").arg(section);
    return QVariant();
}

int YoutubeMediaListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return mlst.size();
}

QVariant YoutubeMediaListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= mlst.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return QVariant::fromValue<MediaInfo>(mlst.at(index.row()));
    else
        return QVariant();
}

void YoutubeMediaListModel::setMediaList(const QList<MediaInfo> &list)
{
    mlst = list;
}
