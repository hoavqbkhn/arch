#include "dbresult.h"

#include <QDebug>

DbResult::DbResult()
{
}

DbResult::DbResult(const QList<QVariant> &data):
    mData(data)
{
}

QVariantMap DbResult::first()
{
    return data(0);
}

QVariantMap DbResult::data(int pos)
{
    if(isEmpty() || pos < 0 || pos > size() - 1)
        return QVariantMap();
    return mData[pos].toMap();
}
