#include "appdbaction.h"
#include "dbmanager.h"
#include "queryhelper.h"
#include <QStringBuilder>
#include <QDateTime>
#include <QDebug>

static QString TAG {"[APPDBACTION]"};

AppDBAction::AppDBAction(const QString& tableName, const QString idfield):
    mDb(DBManager::createInstance()),
    mTableName(tableName),
    mIdField(idfield)
{
    mFunctionMap.insert(MSG_COMMAND_CORE::INSERT, std::bind(&AppDBAction::insert, this, std::placeholders::_1));
    mFunctionMap.insert(MSG_COMMAND_CORE::UPDATE, std::bind(&AppDBAction::update, this, std::placeholders::_1));
    mFunctionMap.insert(MSG_COMMAND_CORE::DEL, std::bind(&AppDBAction::del, this, std::placeholders::_1));
    mFunctionMap.insert(MSG_COMMAND_CORE::GET, std::bind(&AppDBAction::get, this, std::placeholders::_1));
    mFunctionMap.insert(MSG_COMMAND_CORE::QUERY, std::bind(&AppDBAction::query, this, std::placeholders::_1));
    mFunctionMap.insert(MSG_COMMAND_CORE::RESTORE_DELETED, std::bind(&AppDBAction::restoreDelete, this, std::placeholders::_1));
}

AppDBAction::~AppDBAction()
{
    delete mDb;
}

DMessage AppDBAction::exec(DMessage* msg)
{
    if (!mDb)
    {
        qCritical() << TAG << "DBManager is null : " << msg->command() << " with type : " << msg->type();
        DMessage message = *msg;
        message.setError("DBManager is null");
        return message;
    }
    else
    {
        if (mFunctionMap.contains(msg->command()))
        {
            return mFunctionMap[msg->command()](msg);
        }

        qCritical() << TAG << "Command not available : " << msg->command() << " with type : " << msg->type();
        DMessage message = *msg;
        message.setError("Command not available");
        return message;
    }
}

DMessage AppDBAction::insert(DMessage* msg)
{
    DMessage message(msg);

    if (hasFlag(HAS_UPDATE_FIELD))
    {
        msg->addData("updated_at", QDateTime::currentDateTime());
    }

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        mDb->beginTransaction();
    }

    if (hasFlag(BEFORE_INSERT))
    {
        if (!beforeInsert(msg->data(), &message))
        {
            return message;
        }
    }

    if (!mDb->insert(mTableName, msg->data()))
    {
        message.setError(mDb->lastError().text());
    }
    else
    {
        DbResult res = mDb->where("id = ", mDb->lastInsertedId())->get(mTableName);
        const QVariantMap d = res.first();

        if (hasFlag(AFTER_INSERT))
        {
            afterInsert(d);
        }

        message.setData(d);
    }

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        if (!mDb->commit())
        {
            mDb->roolback();
            message.setError(mDb->lastError().text());
        }
    }

    return message;
}

DMessage AppDBAction::update(DMessage* msg)
{
    DMessage message(msg);
    mDb->where(mIdField % " = ", msg->data(mIdField));
    QVariantMap d = msg->data("data").toMap();

    if (hasFlag(HAS_UPDATE_FIELD))
    {
        d.insert("updated_at", QDateTime::currentDateTime());
    }

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        mDb->beginTransaction();
    }

    DbResult oldRes = mDb->clone()->get(mTableName);
    const QVariantMap& oldData = oldRes.first();

    if (hasFlag(BEFORE_UPDATE))
    {
        if (!beforeUpdate(oldData, msg, &message))
        {
            return message;
        }
    }

    if (!mDb->clone()->update(mTableName, d))
    {
        message.setError(mDb->lastError().text());
    }
    else
    {
        DbResult res = mDb->get(mTableName);
        const QVariantMap d = res.first();

        if (hasFlag(AFTER_UPDATE))
        {
            afterUpdate(oldData, d);
        }

        message.setData(d);
    }

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        if (!mDb->commit())
        {
            mDb->roolback();
            message.setError(mDb->lastError().text());
        }
    }

    return message;
}

DMessage AppDBAction::del(DMessage* msg)
{
    DMessage message(msg);

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        mDb->beginTransaction();
    }

    QVariantList ids;

    if (msg->data(mIdField).canConvert<QString>())
    {
        ids.append(msg->data(mIdField));
    }
    else
    {
        ids = msg->data(mIdField).toList();
    }

    for (int i = 0; i < ids.size(); i++)
    {
        DbResult res = mDb->where(mIdField % " = ", ids[i])->get(mTableName);

        if (hasFlag(BEFORE_DELETE))
        {
            if (!res.isEmpty() && !beforeDelete(res.first(), &message))
            {
                return message;
            }
        }

        mDb->where(mIdField % " = ", ids[i]);

        if (hasFlag(SOFT_DELETE))
        {
            if (!mDb->update(mTableName, QVariantMap {{"deleted_at", QDateTime::currentDateTime()}}))
            {
                message.setError(mDb->lastError().text());
            }
        }
        else
        {
            if (!mDb->del(mTableName))
            {
                message.setError(mDb->lastError().text());
            }
        }

        if (hasFlag(AFTER_DELETE))
        {
            if (!res.isEmpty())
            {
                afterDelete(res.first());
            }
        }
    }

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        if (!mDb->commit())
        {
            mDb->roolback();
            message.setError(mDb->lastError().text());
        }
    }

    return message;
}

DMessage AppDBAction::restoreDelete(DMessage* msg)
{
    DMessage message(msg);

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        mDb->beginTransaction();
    }

    DbResult res = mDb->where(mIdField % " = ", msg->data(mIdField))->get(mTableName);
    const QVariantMap& oldData = res.first();

    if (hasFlag(BEFORE_RESTORE))
    {
        if (!beforeRestore(oldData, msg, &message))
        {
            return message;
        }
    }

    mDb->where(mIdField % " = ", msg->data(mIdField));

    if (hasFlag(SOFT_DELETE))
    {
        if (!mDb->update(mTableName, QVariantMap {{"deleted_at", QVariant(QVariant::DateTime)}}))
        {
            message.setError(mDb->lastError().text());
        }
    }

    if (hasFlag(AFTER_RESTORE))
    {
        if (!res.isEmpty())
        {
            afterRestore(res.first());
        }
    }

    message.setData(oldData);

    if (hasFlag(USE_TRANSACTION) && mDb->isSupportTransaction())
    {
        if (!mDb->commit())
        {
            mDb->roolback();
            message.setError(mDb->lastError().text());
        }
    }

    return message;
}

DMessage AppDBAction::get(DMessage* msg)
{
    DMessage message(msg);
    selectAndJoin();

    if (hasFlag(SOFT_DELETE) && !msg->hasData("withdeleted"))
    {
        mDb->where(mTableName % ".deleted_at IS NULL");
    }

    DbResult res = mDb->where(mTableName % "." % mIdField % " = ", msg->data(mIdField))->get(mTableName);

    if (res.isEmpty())
    {
        message.setError("Data not found");
    }
    else
    {
        message.setData(res.first());
    }

    return message;
}

DMessage AppDBAction::query(DMessage* msg)
{
    DMessage message(msg);
    mDb->table(mTableName);
    selectAndJoin();

    if (hasFlag(SOFT_DELETE) && !msg->hasData("withdeleted"))
    {
        mDb->where(mTableName % ".deleted_at IS NULL");
    }

    mDb = QueryHelper::filter(mDb, msg->data(), fieldMap());

    if (!(msg->data().contains(QStringLiteral("start")) && msg->data().value(QStringLiteral("start")).toInt() > 0))
    {
        message.addData(QStringLiteral("total"), mDb->count());
    }

    setStart(&message, msg);
    mDb = QueryHelper::limitOffset(mDb, msg->data());
    mDb = QueryHelper::sort(mDb, msg->data());
    message.addData(QStringLiteral("data"), mDb->exec().data());
    return message;
}

void AppDBAction::setStart(DMessage* msg, DMessage* src)
{
    if (src->data().contains(QStringLiteral("start")))
    {
        msg->addData(QStringLiteral("start"), src->data(QStringLiteral("start")).toInt());
    }
}

QMap<QString, QString> AppDBAction::fieldMap() const
{
    return QMap<QString, QString>();
}

bool AppDBAction::hasFlag(int flag)
{
    return (mFlag & flag) != 0;
}
