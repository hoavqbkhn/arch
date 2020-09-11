#ifndef DBUTIL_H
#define DBUTIL_H

#include <QString>
#include <QDateTime>
class DbResult;
class DBUtil
{
public:
    DBUtil();
    static QString formatDateToVietnam(const QString &d, bool useTime = true);
    static QDate sqlDateToDate(const QString &value);
    static QDateTime sqlDateToDateTime(const QString &value);
    static QString DBResultToString(DbResult *result);
};


#endif // DBUTIL_H
