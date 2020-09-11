#include "migration.h"
#include "dbmanager.h"
#include <QDebug>



static QString TAG{"MIGRATION"};
static std::function<bool(const QString &)> sAfterMigrate = nullptr;

bool Migration::migrateAll(const QStringList &filelist, const QString &dbtype, std::function<bool(const QString &)> afterCallback)
{
    auto db = DBManager::createInstance(false, true);
    Migration mg(db, filelist, dbtype);
    mg.mAfterMigrate = afterCallback;
    return mg.migrate();
}

void Migration::setAfterMigrate(std::function<bool (const QString &)> afterCallback)
{
    sAfterMigrate = afterCallback;
}

Migration::Migration(DBManager *db, const QStringList &filelist, const QString &dbtype):
    mDb(db),
    mFileNameList(filelist),
    mDbType(dbtype)
{
    init();
}

bool Migration::migrate()
{
    bool started = false;
    bool errorOccure = false;
    const QString oldLastFile = mLastFile;
    for(const QString &file : mFileNameList) {
        if(!file.compare(".") || !file.compare("..")) continue;
        if(!started) {
            if(mLastFile.isEmpty()) {
                started = true;
            } else if(mLastFile.compare(file) == 0) {
                started = true;
                continue;
            }
        }
        if(started) {
            if(executeFile(file)) {
                mLastFile = file;
                if(sAfterMigrate != nullptr) {
                    if(!sAfterMigrate(mLastFile)) {
                        errorOccure = true;
                        break;
                    }
                }
                if(mAfterMigrate != nullptr) {
                    if(!mAfterMigrate(mLastFile)) {
                        errorOccure = true;
                        break;
                    }
                }
            } else {
                errorOccure = true;
                break;
            }
        }
    }
    if(mLastFile.compare(oldLastFile)) {
        QVariantMap data;
        data.insert("name", mLastFile);
        mDb->where("name = ", oldLastFile)->update("migrations", data);
    }
    return !errorOccure;
}

void Migration::init()
{
    if(!mDb->exec("SELECT 1 FROM migrations LIMIT 1")) {
        mDb->exec("CREATE TABLE migrations (name VARCHAR(255) NOT NULL DEFAULT '');");
        QVariantMap data;
        data.insert("name", "");
        mDb->insert("migrations", data);
    } else {
        DbResult res = mDb->table("migrations")->limit(1)->exec();
        if(!res.isEmpty())
            mLastFile = res.first().value("name").toString();
    }
}

bool Migration::executeFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)) {
        qCritical() << TAG << "Can not open file" << file.fileName();
        return false;
    }
    const QString sqlCommand(file.readAll());
    if(mDbType == "SQLITE") {
        const QStringList sqllist = sqlCommand.split("-- separator");
        for(const QString &cmd : sqllist) {
            bool ret = mDb->exec(cmd);
            if(!ret) {
                qCritical() << TAG << "Migration file" << filename << "error :" << mDb->lastError().text();
                return false;
            }
        }
        return true;
    } else {
        bool ret = mDb->exec(sqlCommand);
        if(!ret)
            qCritical() << TAG << "Migration file" << filename << "error :" << mDb->lastError().text();
        return ret;
    }
}
