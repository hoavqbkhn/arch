#include "dmessage.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>


DMessage::DMessage()
{
}

DMessage::DMessage(int type, int command, int status)
{
    setType(type);
    setCommand(command);
    setStatus(status);
}

DMessage::DMessage(const QByteArray &ba)
{
    fromByteArray(ba);
}

DMessage::DMessage(DMessage *other)
{
    this->mFlag = other->mFlag;
    this->mUniqueId = other->mUniqueId;
}

void DMessage::setType(int type)
{
    mFlag &= ~0xFF;
    mFlag |= (type & 0xFF);
}

void DMessage::setCommand(int command)
{
    mFlag &= ~0xFF00;
    mFlag |= ((command << 8) & 0xFF00);
}

void DMessage::setStatus(int status)
{
    mFlag &= ~0xF0000;
    mFlag |= ((status << 16) & 0xF0000);
}

void DMessage::setFlag(int flag)
{
    mFlag &= ~0xFF00000;
    mFlag |= ((flag << 20) & 0xFF00000);
}

bool DMessage::isCommand(int command)
{
    return this->command() == command;
}

bool DMessage::isType(int type)
{
    return this->type() == type;
}

bool DMessage::isTypeCommand(int type, int command)
{
    return (this->type() == type && this->command() == command);
}

bool DMessage::isSuccess()
{
    return this->status() == STATUS::OK;
}

void DMessage::addData(const QString &key, const QVariant &data)
{
    mData.insert(key, data);
}

void DMessage::removeData(const QString &key)
{
    mData.remove(key);
}

QVariant DMessage::takeData(const QString &key)
{
    const QVariant data = mData[key];
    mData.remove(key);
    return data;
}

void DMessage::clearData()
{
    mData.clear();
}

void DMessage::setData(const QVariantMap &data)
{
    mData = data;
}

QVariantMap DMessage::data()
{
    return mData;
}

QVariant DMessage::data(const QString &key)
{
    return mData[key];
}

bool DMessage::hasData(const QString &key)
{
    return mData.contains(key);
}

void DMessage::setError(const QString &error, bool clearData)
{
    setStatus(STATUS::ERROR);
    if(clearData) mData.clear();
    mData.insert("error", error);
}

QJsonObject DMessage::toJsonObject()
{
    QJsonObject root;
    root.insert(QStringLiteral("_u"), QJsonValue(mUniqueId));
    root.insert(QStringLiteral("_f"), QJsonValue(mFlag));
    root.insert(QStringLiteral("_d"), QJsonValue(QJsonObject::fromVariantMap(mData)));
    return root;
}

QString DMessage::toJsonString()
{
    const QJsonObject &root = toJsonObject();
    QJsonDocument doc(root);
    return QLatin1String(doc.toJson(QJsonDocument::Compact));
}

QByteArray DMessage::toByteArray()
{
    const QJsonObject &root = toJsonObject();
    QJsonDocument doc(root);
    return qCompress(doc.toBinaryData());
}

void DMessage::fromByteArray(const QByteArray &ba)
{
    QJsonDocument doc = QJsonDocument::fromBinaryData(qUncompress(ba));
    fromJsonDoc(doc);
}

void DMessage::fromJsonDoc(const QJsonDocument &jsonDoc)
{
    QJsonObject obj = jsonDoc.object();
    mFlag = obj.value(QStringLiteral("_f")).toInt();
    mData = obj.value(QStringLiteral("_d")).toObject().toVariantMap();
    mUniqueId = obj.value(QStringLiteral("_u")).toInt();
}

void DMessage::resetQuery()
{
    mData.remove(QStringLiteral("filter"));
    mData.remove(QStringLiteral("sort"));
    mData.remove(QStringLiteral("limit"));
    mData.remove(QStringLiteral("start"));
}

void DMessage::setSort(const QString &sort)
{
    mData.insert(QStringLiteral("sort"), sort);
}

void DMessage::setStart(const int &start)
{
    mData.insert(QStringLiteral("start"), start);
}

void DMessage::setLimit(const int &limit)
{
    mData.insert(QStringLiteral("limit"), limit);
}

void DMessage::addFilter(const QString &key, int type, const QVariant &data)
{
    QVariantMap m;
    m.insert(QStringLiteral("type"), type);
    m.insert(QStringLiteral("value"), data);
    QVariantMap filter;
    if(mData.contains(QStringLiteral("filter"))) {
        filter = mData[QStringLiteral("filter")].toMap();
    }
    filter.insert(key, m);
    mData[QStringLiteral("filter")] = filter;
}

QVariant DMessage::getFilter(const QString &key)
{
    const QVariantMap f = mData["filter"].toMap();
    return f[key].toMap()["value"];
}

void DMessage::keepFilter(const QStringList &list)
{
    const QVariantMap f = mData["filter"].toMap();
    QVariantMap newFilter;
    QMapIterator<QString, QVariant> i(f);
    while (i.hasNext()) {
        i.next();
        for(int a = 0; a < list.size(); a++) {
            if(!list[a].compare(i.key()))
                newFilter.insert(i.key(), i.value());
        }
    }
    mData["filter"] = newFilter;
}

QString DMessage::getErrorString()
{
    return mData["error"].toString();
}
