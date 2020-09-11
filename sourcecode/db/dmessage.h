#ifndef DMESSAGE_H
#define DMESSAGE_H

#include <QVariantMap>
#include "messageabs/innermessage.h"

namespace STATUS
{
    const int OK = 0;
    const int ERROR = 1;
}

namespace MSG_COMMAND_CORE
{
    const int INSERT                    = 0;
    const int UPDATE                    = 1;
    const int DEL                       = 2;
    const int GET                       = 3;
    const int QUERY                     = 4;
    const int RESTORE_DELETED           = 5;
}

class DMessage : public InnerMessage
{
    private:
        /*
         * Flag are use to store type, status, and request/answer
         * type : 8bit
         * command : 8bit
         * status : 4bit    -> Code = 0: success; 1: error;
         * flag : 8bit
         * */
        int mFlag;

        QVariantMap mData;

        int mUniqueId;

    public:
        DMessage();
        DMessage(int type, int command, int status = 0);
        DMessage(const QByteArray& ba);
        DMessage(DMessage* other);

        void setType(int type);
        void setCommand(int command);
        void setStatus(int status);
        void setFlag(int flag);
        inline int type()
        {
            return (mFlag & 0xFF);
        }
        inline int command()
        {
            return ((mFlag >> 8) & 0xFF);
        }
        inline int status()
        {
            return ((mFlag >> 16) & 0xF);
        }
        inline int flag()
        {
            return ((mFlag >> 20) & 0xFF);
        }
        inline int getUniqueId()
        {
            return mUniqueId;
        }
        inline void setUniqueId(int id)
        {
            mUniqueId = id;
        }
        bool isCommand(int command);
        bool isType(int type);
        bool isTypeCommand(int type, int command);
        bool isSuccess();

        void addData(const QString& key, const QVariant& data);
        void removeData(const QString& key);
        QVariant takeData(const QString& key);
        void clearData();
        void setData(const QVariantMap& data);
        QVariantMap data();
        QVariant data(const QString& key);
        bool hasData(const QString& key);

        void setError(const QString& error, bool clearData = true);

        QJsonObject toJsonObject();
        QString toJsonString();
        QByteArray toByteArray();
        void fromByteArray(const QByteArray& ba);
        void fromJsonDoc(const QJsonDocument& doc);
        void resetQuery();
        void setSort(const QString& sort);
        void setStart(const int& start);
        void setLimit(const int& limit);
        void addFilter(const QString& key, int type, const QVariant& data);
        QVariant getFilter(const QString& key);
        void keepFilter(const QStringList& list);

        QString getErrorString();
};

#endif // DMESSAGE_H
