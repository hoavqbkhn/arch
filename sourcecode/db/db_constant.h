#ifndef DB_CONSTANT_H
#define DB_CONSTANT_H

namespace COMPARE {
    const int EQUAL             = 0;
    const int NEQUAL            = 1;
    const int LESS              = 2;
    const int GREATER           = 3;
    const int LESS_EQUAL        = 4;
    const int GREATER_EQUAL     = 5;
    const int ISNULL            = 6;
    const int ISNOTNULL         = 7;
    const int LIKE              = 8;
    const int IGNORE            = 10;
    const int LIKE_NATIVE       = 11;
    const int FLAG_ENABLE       = 12;
    const int FLAG_DISABLE      = 13;
    const int FLAG_ALL          = 14;
    const int USER_DEFINE       = 100;
}

class DB_CONSTANT
{
public:
    DB_CONSTANT();
};

#endif // DB_CONSTANT_H
