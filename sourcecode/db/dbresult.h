#ifndef DBRESULT_H
#define DBRESULT_H

#include <QList>
#include <QVariantMap>
class DbResult
{
public:
    DbResult();
    DbResult(const QList<QVariant> &data);
    inline bool isEmpty() { return mData.isEmpty(); }
    QVariantMap first();
    inline int size() { return mData.size(); }
    QVariantMap data(int pos);
    inline QVariantList &data() { return mData; }

private:
    QVariantList mData;
};


#endif // DBRESULT_H
