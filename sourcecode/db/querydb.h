#ifndef QUERYDB_H
#define QUERYDB_H

#include <QString>
#include <QMap>
#include <QVariant>


struct FilterData {
    FilterData(int type, const QVariant &data)
    {
        this->type = type;
        this->data = data;
    }

    int type;
    QVariant data;
};

class DMessage;

class QueryDB
{
public:
    QueryDB();
    void setFilter(const QString &key, int type, const QVariant &data);
    void addData(const QString &key, const QVariant &d);
    void clearFilter();
    void clearAll();
    void clearData();
    void clearSort();
    void removeFilter(const QString &key);
    void setSort(const QString &sort);
    void setLimit(int val);
    void setStart(int val);
    inline int getLimit() { return mLimit; }
    void bind(DMessage *msg);

private:
    QMap<QString, FilterData> mFilter;
    QMap<QString, QVariant> mData;
    QString mSort;
    int mLimit;
    int mStart;
};

#endif // QUERYDB_H
