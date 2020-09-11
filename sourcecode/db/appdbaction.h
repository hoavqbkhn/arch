#ifndef APPDBACTION_H
#define APPDBACTION_H

#include "dmessage.h"
#include "dbmanager.h"
#include <QMap>
#include <functional>

class AppDBAction
{
public:
    enum Flag {
        BEFORE_INSERT       = 0x1,
        AFTER_INSERT        = 0x2,
        BEFORE_UPDATE       = 0x4,
        AFTER_UPDATE        = 0x8,
        BEFORE_DELETE       = 0x10,
        AFTER_DELETE        = 0x20,
        SOFT_DELETE         = 0x40,
        BEFORE_RESTORE      = 0x80,
        AFTER_RESTORE       = 0x100,
        HAS_UPDATE_FIELD    = (1 << 16),
        USE_TRANSACTION     = (1 << 17),
    };

    AppDBAction(const QString &tableName, const QString idfield);
    virtual ~AppDBAction();
    DMessage exec(DMessage *msg);

protected:
    int mFlag = 0;
    DBManager *mDb;
    QString mTableName;
    QString mIdField;
    QMap<int, std::function<DMessage(DMessage*)> > mFunctionMap;

    virtual DMessage insert(DMessage *msg);
    virtual DMessage update(DMessage *msg);
    virtual DMessage del(DMessage *msg);
    virtual DMessage restoreDelete(DMessage *msg);
    virtual DMessage get(DMessage *msg);
    virtual DMessage query(DMessage *msg);

    void setStart(DMessage *msg, DMessage *src);
    virtual QMap<QString, QString> fieldMap() const;
    virtual void selectAndJoin() {}
    virtual bool beforeInsert(const QVariantMap &/*data*/, DMessage */*retMsg*/) { return true; }
    virtual void afterInsert(const QVariantMap &/*data*/) {}
    virtual bool beforeUpdate(const QVariantMap &/*oldData*/, DMessage */*msg*/, DMessage */*retMsg*/) { return true; }
    virtual void afterUpdate(const QVariantMap &/*oldData*/, const QVariantMap &/*newData*/) {}
    virtual bool beforeDelete(const QVariantMap &/*oldData*/, DMessage */*retMsg*/) { return true; }
    virtual void afterDelete(const QVariantMap &/*oldData*/) {}
    virtual bool beforeRestore(const QVariantMap &/*oldData*/, DMessage */*msg*/, DMessage */*retMsg*/) { return true; }
    virtual void afterRestore(const QVariantMap &/*data*/) {}

    bool hasFlag(int flag);
};


#endif // APPDBACTION_H
