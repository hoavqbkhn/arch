#ifndef QUERYHELPER_H
#define QUERYHELPER_H

#include "dbmanager.h"
#include <functional>
class QueryHelper
{
public:
    QueryHelper();
    static DBManager* filter(DBManager* db, const QVariantMap &data, const QMap<QString, QString> &fieldMap = QMap<QString, QString>());
    static DBManager* sort(DBManager* db, const QVariantMap &data);
    static DBManager* limitOffset(DBManager* db, const QVariantMap &data);
    static void installUserDefinedFilter(int type, std::function<void(DBManager *db, const QString &, int,const QVariantMap &)> func);

private:
    static QString getSign(int type);
};

#endif // QUERYHELPER_H
