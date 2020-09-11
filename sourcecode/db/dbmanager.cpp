#include "dbmanager.h"
#include <QUuid>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlDriver>
#include <QStringBuilder>
#include <QThreadStorage>
#include <QDir>

static QString TAG {"[DB]"};
static DBSetting DBSETTING;
static QString DBTYPE = "POSTGRESQL";
static QMap<QString, QString> SQLDRIVERNAME {{"POSTGRESQL", "QPSQL"}, {"SQLITE", "QSQLITE"}};
QStringList DBManager::mCreated = QStringList();
QStringList DBManager::mUpdate = QStringList();
QStringList DBManager::mSoftDelete = QStringList();
static QThreadStorage<QSqlDatabase> mDatabasePool;
#ifdef QT_DEBUG
bool DBManager::DEBUG = true;
#else
bool DBManager::DEBUG = false;
#endif

DBManager::DBManager()
    :
    parent(NULL)
{
    mDebug = DEBUG;
}

DBManager::~DBManager()
{
    if (parent == NULL)
    {
        for (int i = 0; i < childs.size(); i++)
        {
            delete childs[i];
        }
    }
}

DBManager* DBManager::createInstance(bool checkDBName, bool newConnection, QString* err)
{
    DBManager* db = new DBManager();

    if (db->init(DBSETTING.host, DBSETTING.port, DBSETTING.username, DBSETTING.password, DBSETTING.dbName, checkDBName, newConnection))
    {
        qDebug() << "init database successfully";
        return db;
    }

    qCritical() << TAG << "Error openning database connection :" << db->lastError().text();

    if (err != nullptr)
    {
        *err = db->lastError().text();
    }

    delete db;
    return nullptr;
}

bool DBManager::setDbSetting(const QString& host, int port, const QString& username, const QString& password, const QString& dbname)
{
    DBSETTING.set(host, port, username, password, dbname);
    return true;
    /*auto db = createInstance();
    bool ret = db != nullptr;
    if(db) delete db;
    return ret;*/
}

bool DBManager::checkConnection(QString& error)
{
    QString err;
    auto db = createInstance(true, false, &err);

    if (db == nullptr)
    {
        error = err;
        return false;
    }

    delete db;
    return true;
}

void DBManager::setDatabaseType(const QString& db)
{
    DBTYPE = db;
}

DBManager* DBManager::reset()
{
    mWhere = QString();
    mSelect = QString();
    mJoin = QString();
    mTable = QString();
    mLimit = QString();
    mStart = QString();
    mSort = QString();
    mGroup = QString();
    return this;
}

DBManager* DBManager::select(const QString& value)
{
    if (!mSelect.isEmpty())
    {
        mSelect.append(QStringLiteral(","));
    }

    mSelect.append(value);
    return this;
}

DBManager* DBManager::table(const QString& value)
{
    mTable = value;
    return this;
}

DBManager* DBManager::where(const QString& value, const QVariant& val)
{
    if (!mWhere.isEmpty())
    {
        mWhere.append(QStringLiteral(" AND "));
    }

    if (!val.isValid())
    {
        mWhere.append(value);
    }
    else
    {
        mWhere.append(value);

        if (val.type() == QVariant::String)
        {
            mWhere.append(QStringLiteral("'") + val.toString() + QStringLiteral("'"));
        }
        else
        {
            mWhere.append(QString::number(val.toInt()));
        }
    }

    return this;
}

DBManager* DBManager::like(const QString& value, const QString& val)
{
    if (!mWhere.isEmpty())
    {
        mWhere.append(QStringLiteral(" AND "));
    }

    mWhere.append(value);

    if (val.startsWith(QStringLiteral("%")) || val.endsWith(QStringLiteral("%")))
    {
        mWhere.append(QStringLiteral(" LIKE '"));
        mWhere.append(val);
        mWhere.append(QStringLiteral("'"));
    }
    else
    {
        mWhere.append(QStringLiteral(" LIKE '%"));
        mWhere.append(val);
        mWhere.append(QStringLiteral("%'"));
    }

    return this;
}

DBManager* DBManager::likePost(const QString& value, const QString& val)
{
    if (!mWhere.isEmpty())
    {
        mWhere.append(QStringLiteral(" AND "));
    }

    mWhere.append(value);
    mWhere.append(QStringLiteral(" LIKE '"));
    mWhere.append(val);
    mWhere.append(QStringLiteral("%'"));
    return this;
}

DBManager* DBManager::likeNative(const QString& value, const QString& val)
{
    if (!mWhere.isEmpty())
    {
        mWhere.append(QStringLiteral(" AND "));
    }

    mWhere.append(value);
    mWhere.append(QStringLiteral(" LIKE '"));
    mWhere.append(val);
    mWhere.append(QStringLiteral("'"));
    return this;
}

DBManager* DBManager::whereOr(const QString& value)
{
    if (!mWhere.isEmpty())
    {
        mWhere.append(QStringLiteral(" OR "));
    }

    mWhere.append(value);
    return this;
}

DBManager* DBManager::join(const QString& value)
{
    if (!mJoin.isEmpty())
    {
        mJoin.append(QStringLiteral(" "));
    }

    mJoin.append(value);
    return this;
}

DBManager* DBManager::limit(int limit)
{
    mLimit = QString::number(limit);
    return this;
}

DBManager* DBManager::start(int start)
{
    mStart = QString::number(start);
    return this;
}

DBManager* DBManager::sort(const QString& sort)
{
    if (!mSort.isEmpty())
    {
        mSort.append(QStringLiteral(", "));
    }

    mSort.append(sort);
    return this;
}

DBManager* DBManager::group(const QString& group)
{
    mGroup = group;
    return this;
}

QString DBManager::getSelectQuery(const QString& select)
{
    QString sql = QString(QStringLiteral("SELECT "));

    /*if(mSoftDelete.contains(mTable))
        where(QStringLiteral("deleted = 0"));*/
    if (mSelect.isEmpty())
    {
        mSelect.append(QStringLiteral("*"));
    }

    if (!select.isEmpty())
    {
        sql.append(select);
    }
    else
    {
        sql.append(mSelect);
    }

    sql.append(QStringLiteral(" FROM ")).append(mTable).append(QStringLiteral(" "));

    if (!mJoin.isEmpty())
    {
        sql.append(mJoin);
    }

    if (!mWhere.isEmpty())
    {
        sql.append(QStringLiteral(" WHERE ")).append(mWhere);
    }

    if (!mGroup.isEmpty())
    {
        sql.append(QStringLiteral(" GROUP BY ")).append(mGroup);
    }

    if (!mSort.isEmpty())
    {
        sql.append(QStringLiteral(" ORDER BY ")).append(mSort);
    }

    if (!mLimit.isEmpty())
    {
        sql.append(QStringLiteral(" LIMIT ")).append(mLimit);
    }

    if (!mStart.isEmpty())
    {
        sql.append(QStringLiteral(" OFFSET ")).append(mStart);
    }

    if (mDebug)
    {
        qDebug() << TAG << sql;
    }

    return sql;
}

QSqlError DBManager::lastError()
{
    return mLastError;
}

QVariant DBManager::lastInsertedId()
{
    return mInsertedId;
}

QString DBManager::lastQuery()
{
    return mLastQuery;
}

DbResult DBManager::exec()
{
    QList<QVariant> result;
    QSqlQuery query(getDatabase());

    if (query.exec(getSelectQuery()))
    {
        QSqlRecord record = query.record();

        while (query.next())
        {
            QVariantMap map;

            for (int i = 0; i < record.count(); i++)
            {
                map.insert(record.fieldName(i), query.value(i));
                //                qDebug() << record.fieldName(i) << " -> " << query.value(i);
            }

            result.append(map);
        }
    }

    reset();
    postQuery(&query);
    return DbResult(result);
}

DbResult DBManager::execResult(const QString& sql)
{
    QList<QVariant> result;
    QSqlQuery query(getDatabase());

    if (query.exec(sql))
    {
        QSqlRecord record = query.record();

        while (query.next())
        {
            QVariantMap map;

            for (int i = 0; i < record.count(); i++)
            {
                map.insert(record.fieldName(i), query.value(i));
            }

            result.append(map);
        }
    }

    reset();
    postQuery(&query);
    return DbResult(result);
}

DbResult DBManager::get(const QString& tableName)
{
    return table(tableName)->exec();
}

bool DBManager::exec(const QString& sqlcommand)
{
    QSqlQuery query(getDatabase());
    bool ok = query.exec(sqlcommand);
    reset();
    postQuery(&query);

    if (mDebug)
    {
        qDebug() << TAG << sqlcommand;
    }

    if (!ok)
    {
        qCritical() << TAG << lastQuery();
        qCritical() << TAG << mLastError.text();
    }

    return ok;
}

bool DBManager::insert(const QString& table, const QVariantMap& data)
{
    QSqlQuery query(getDatabase());
    QString sql = QString(QStringLiteral("INSERT INTO "));
    QString values = QString(QStringLiteral("VALUES ("));
    sql.append(table).append(QStringLiteral(" ("));
    const QList<QString>& keys = data.keys();

    for (int i = 0; i < keys.size(); i++)
    {
        sql.append(keys.at(i));
        values.append(QStringLiteral("?"));

        if (i != keys.size() - 1)
        {
            sql.append(QStringLiteral(","));
            values.append(QStringLiteral(","));
        }
    }

    sql.append(QStringLiteral(") ")).append(values).append(QStringLiteral(")"));
    query.prepare(sql);

    for (int i = 0; i < keys.size(); i++)
    {
        query.bindValue(i, data[keys.at(i)]);
    }

    reset();
    bool res = query.exec();

    if (mDebug)
    {
        qDebug() << TAG << query.lastQuery() << dataToString(data);
    }

    postQuery(&query);

    if (!res)
    {
        qCritical() << TAG << query.lastQuery() << dataToString(data);
        qCritical() << TAG << mLastError.text();
    }

    return res;
}

bool DBManager::update(const QString& table, const QVariantMap& data)
{
    QSqlQuery query(getDatabase());
    QString sql = QString(QStringLiteral("UPDATE "));
    sql.append(table).append(QStringLiteral(" SET "));

    if (mUpdate.contains(table))
    {
        sql.append(QStringLiteral("updated_at = NOW() "));
    }

    const QList<QString>& keys = data.keys();

    for (int i = 0; i < keys.size(); i++)
    {
        sql.append(keys.at(i));

        if (data.value(keys.at(i)).type() != QVariant::Invalid)
        {
            sql.append(QStringLiteral(" = ?"));
        }

        if (i != keys.size() - 1)
        {
            sql.append(QStringLiteral(","));
        }
    }

    sql.append(QStringLiteral(" WHERE ")).append(mWhere);
    query.prepare(sql);

    for (int i = 0; i < keys.size(); i++)
    {
        query.bindValue(i, data[keys.at(i)]);
    }

    reset();
    bool res = query.exec();

    if (mDebug)
    {
        qDebug() << TAG << query.lastQuery() << dataToString(data);
    }

    postQuery(&query);

    if (!res)
    {
        qCritical() << TAG << query.lastQuery() << dataToString(data);
        qCritical() << TAG << mLastError.text();
    }

    return res;
}

bool DBManager::del(const QString& table)
{
    if (mSoftDelete.contains(table))
    {
        QVariantMap map;
        map.insert(QStringLiteral("deleted"), 1);
        return update(table, map);
    }
    else
    {
        QSqlQuery query(getDatabase());
        QString sql = QString(QStringLiteral("DELETE FROM "));
        sql.append(table).append(QStringLiteral(" WHERE ")).append(mWhere);
        reset();
        bool res = query.exec(sql);

        if (mDebug)
        {
            qDebug() << TAG << query.lastQuery();
        }

        postQuery(&query);

        if (!res)
        {
            qCritical() << TAG << query.lastQuery();
            qCritical() << TAG << mLastError.text();
        }

        return res;
    }
}

int DBManager::count()
{
    QSqlQuery query(getDatabase());
    DBManager* db = clone();
    QString sql = db->getSelectQuery(QStringLiteral("count(*)"));
    query.exec(sql);
    postQuery(&query);

    if (query.next())
    {
        return query.value(0).toInt();
    }

    return 0;
}

DBManager* DBManager::clone()
{
    DBManager* db = new DBManager();
    *db = *this;
    db->parent = this;
    this->childs.push_back(db);
    return db;
}

bool DBManager::beginTransaction()
{
    return getDatabase().transaction();
}

bool DBManager::commit()
{
    return getDatabase().commit();
}

bool DBManager::roolback()
{
    return getDatabase().rollback();
}

bool DBManager::isSQLite()
{
    return DBTYPE.compare("SQLITE") == 0;
}

bool DBManager::truncateTable(const QString& table)
{
    if (isSQLite())
    {
        this->exec(QString("DELETE FROM %1").arg(table));
    }
    else
    {
        this->exec(QString("TRUNCATE TABLE %1").arg(table));
    }

    return true;
}

QSqlDatabase DBManager::getDatabase()
{
    if (mDatabasePool.hasLocalData())
    {
        return mDatabasePool.localData();
    }
    else
    {
        auto database = QSqlDatabase::addDatabase(SQLDRIVERNAME[DBTYPE], QUuid::createUuid().toString());
        mDatabasePool.setLocalData(database);
        return database;
    }
}

bool DBManager::init(const QString& host, int port, const QString& username, const QString& password, const QString& dbname, bool checkDBName, bool newConnection)
{
    auto database = getDatabase();

    if (database.isOpen())
    {
        if (newConnection)
        {
            database.close();
        }
        else
        {
            mSupportTransaction = database.driver()->hasFeature(QSqlDriver::Transactions);
            return true;
        }
    }

    bool ret = false;

    if (DBTYPE == "POSTGRESQL")
    {
        database.setPort(port);
        database.setHostName(host);
        database.setUserName(username);
        database.setPassword(password);
        database.setConnectOptions("connect_timeout=1");

        if (checkDBName)
        {
            database.open();
            database.exec(QString("CREATE DATABASE IF NOT EXISTS %1").arg(dbname));
            database.close();
        }

        database.setDatabaseName(dbname);
        ret = database.open();
    }
    else if (DBTYPE == "SQLITE")
    {
        QString dirpath = "global/sqlite_db_path";
        QString dbname = "global/sqlite_db_name";
        QDir dir = QDir::home();

        if (dbname.isEmpty())
        {
            dbname = "vcg.db";
        }

        if (!dbname.endsWith(".db"))
        {
            dbname += ".db";
        }

        if (dirpath.isEmpty())
        {
            dir.mkdir(".vcg");
            dir.cd(".vcg");
        }
        else
        {
            dir.setPath(dirpath);
        }

        bool reset = false;

        if (reset)
        {
            QFile::remove(dir.absoluteFilePath(dbname));
        }

        database.setConnectOptions("QSQLITE_BUSY_TIMEOUT=1");
        database.setDatabaseName(dir.absoluteFilePath(dbname));
        qDebug() << TAG << "SQLite database path :" << dir.absoluteFilePath(dbname);
        ret = database.open();
    }

    mSupportTransaction = database.driver()->hasFeature(QSqlDriver::Transactions);
    qDebug() << TAG << "Database support transaction :" << mSupportTransaction;

    if (!ret)
    {
        mLastError = database.lastError();
    }

    reset();
    return ret;
}

void DBManager::postQuery(QSqlQuery* query)
{
    mLastError = query->lastError();
    mLastQuery = query->lastQuery();
    mInsertedId = query->lastInsertId();
}

QString DBManager::dataToString(const QVariantMap& map)
{
    QString str;
    str.append(QStringLiteral("{"));
    QMapIterator<QString, QVariant> i(map);

    while (i.hasNext())
    {
        i.next();
        str.append(i.key()).append(QStringLiteral(": ")).append(i.value().toString()).append(QStringLiteral(","));
    }

    str.append(QStringLiteral("}"));
    return str;
}
