#include "querydb.h"
#include "dmessage.h"

QueryDB::QueryDB():
    mLimit(0),
    mStart(0)
{
}

void QueryDB::setFilter(const QString &key, int type, const QVariant &data)
{
    FilterData filter(type, data);
    mFilter.insert(key, filter);
}

void QueryDB::addData(const QString &key, const QVariant &d)
{
    mData.insert(key, d);
}

void QueryDB::clearFilter()
{
    mFilter.clear();
}

void QueryDB::clearAll()
{
    mFilter.clear();
    mData.clear();
    mSort = QString();
    mStart = 0;
    mLimit = 0;
}

void QueryDB::clearData()
{
    mData.clear();
}

void QueryDB::clearSort()
{
    mSort = QString();
}

void QueryDB::removeFilter(const QString &key)
{
    if(mFilter.contains(key))
        mFilter.remove(key);
}

void QueryDB::setSort(const QString &sort)
{
    mSort = sort;
}

void QueryDB::setLimit(int val)
{
    mLimit = val;
}

void QueryDB::setStart(int val)
{
    mStart = val;
}

void QueryDB::bind(DMessage *msg)
{
    msg->resetQuery();
    msg->setSort(mSort);
    if(mLimit > 0)
        msg->setLimit(mLimit);
    if(mStart > 0)
        msg->setStart(mStart);
    QMapIterator<QString, FilterData> i(mFilter);
    while (i.hasNext()) {
        i.next();
        const FilterData &d = i.value();
        msg->addFilter(i.key(), d.type, d.data);
    }
    QMapIterator<QString, QVariant> d(mData);
    while (d.hasNext()) {
        d.next();
        msg->addData(d.key(), d.value());
    }
}
