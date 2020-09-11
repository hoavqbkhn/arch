#ifndef MIGRATION_H
#define MIGRATION_H

#include <QDir>
#include <functional>

class DBManager;

class Migration
{
public:
    static bool migrateAll(const QStringList &filelist, const QString &dbtype, std::function<bool(const QString &)> afterCallback = nullptr);
    static void setAfterMigrate(std::function<bool(const QString &)> afterCallback);
    Migration(DBManager *db, const QStringList &filelist, const QString &dbtype);

private:
    DBManager *mDb;
    QStringList mFileNameList;
    QString mLastFile;
    QString mDbType;
    std::function<bool(const QString &)> mAfterMigrate = nullptr;

    bool migrate();
    void init();
    bool executeFile(const QString &filePath);
};

#endif // MIGRATION_H
