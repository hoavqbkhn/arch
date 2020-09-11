#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "dbresult.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVariantMap>
#include <QStringList>

struct DBSetting
{
    DBSetting() {}
    DBSetting(const QString& host, int port, const QString& username, const QString& password, const QString& dbname):
        port(port), host(host), username(username), password(password), dbName(dbname) {}
    void set(const QString& host, int port, const QString& username, const QString& password, const QString& dbname)
    {
        this->port = port;
        this->host = host;
        this->username = username;
        this->password = password;
        this->dbName = dbname;
    }
    int port;
    QString host;
    QString username;
    QString password;
    QString dbName;
};
class DBManager
{
    private:
        DBManager();
    public:
        ~DBManager();
        static DBManager* createInstance(bool checkDBName = false, bool newConnection = false, QString* err = nullptr);
        static bool setDbSetting(const QString& host, int port, const QString& username, const QString& password, const QString& dbname);
        static bool checkConnection(QString& error);
        static void setDatabaseType(const QString& DBManager);
        DBManager* reset();
        DBManager* select(const QString& value);
        DBManager* table(const QString& value);
        DBManager* where(const QString& value, const QVariant& val = QVariant());
        DBManager* like(const QString& value, const QString& val);
        DBManager* likePost(const QString& value, const QString& val);
        DBManager* likeNative(const QString& value, const QString& val);
        DBManager* whereOr(const QString& value);
        DBManager* join(const QString& value);
        DBManager* limit(int limit);
        DBManager* start(int start);
        DBManager* sort(const QString& sort);
        DBManager* group(const QString& group);
        QString getSelectQuery(const QString& select = QString());
        QSqlError lastError();
        QVariant lastInsertedId();
        QString lastQuery();
        DbResult exec();
        DbResult execResult(const QString& sql);
        DbResult get(const QString& tableName);
        bool exec(const QString& sqlcommand);
        bool insert(const QString& table, const QVariantMap& data);
        bool update(const QString& table, const QVariantMap& data);
        bool del(const QString& table);
        int count();
        DBManager* clone();
        bool beginTransaction();
        bool commit();
        bool roolback();
        inline bool isSupportTransaction()
        {
            return mSupportTransaction;
        }
        inline DBManager* clearSelect()
        {
            mSelect.clear();
            return this;
        }
        bool isSQLite();
        bool truncateTable(const QString& table);
        static QSqlDatabase getDatabase();

    private:
        static QStringList mCreated;
        static QStringList mUpdate;
        static QStringList mSoftDelete;
        static bool DEBUG;
        bool mSupportTransaction = false;
        QString mWhere;
        QString mSelect;
        QString mJoin;
        QString mTable;
        QString mLimit;
        QString mStart;
        QString mSort;
        QString mGroup;
        QList<DBManager*> childs;
        DBManager* parent;
        QString mLastQuery;
        QVariant mInsertedId;
        QSqlError mLastError;

        bool init(const QString& host, int port, const QString& username, const QString& password, const QString& dbname, bool checkDBName = false, bool newConnection = false);
        void postQuery(QSqlQuery* query);
        QString dataToString(const QVariantMap& map);

    protected:
        bool mDebug;
};

#endif // DBMANAGER_H
