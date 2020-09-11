#include "dbutil.h"
#include "dbresult.h"
#include <QDateTime>
#include <QStringBuilder>

static QStringList format{"yyyy-MM-dd", "yyyy-MM-ddThh:mm:ss", "yyyy-MM-dd hh:mm:ss", "yyyy-MM-ddThh:mm:ss.zzz"};
DBUtil::DBUtil()
{

}

QString DBUtil::formatDateToVietnam(const QString &d, bool useTime)
{
    if(d.isEmpty())
        return d;
    auto date = QDateTime::fromString(d, QLatin1String("yyyy-MM-ddThh:mm:ss"));
    if(useTime)
        return date.toString(QLatin1String("dd-MM-yyyy hh:mm:ss"));
    return date.toString(QLatin1String("dd-MM-yyyy"));
}

QDate DBUtil::sqlDateToDate(const QString &value)
{
    for(const QString &s : format) {
        auto date = QDate::fromString(value, s);
        if(date.isValid())
            return date;
    }
    return QDate();
}

QDateTime DBUtil::sqlDateToDateTime(const QString &value)
{
    for(const QString &s : format) {
        auto date = QDateTime::fromString(value, s);
        if(date.isValid())
            return date;
    }
    return QDateTime();
}

QString DBUtil::DBResultToString(DbResult *result)
{
    QString str;
    for(int i = 0; i < result->size(); i++) {
        //str = str %
    }
    return str;
}
