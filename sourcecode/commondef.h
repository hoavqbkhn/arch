#ifndef COMMONDEF_H
#define COMMONDEF_H
#include <string>
#include <stdint.h>
#include <QTimer>
#include <atomic>

const unsigned int TIME_INTERVAL_RECONNECT = 1000;
static std::atomic<unsigned int> APPLICATION_ID;
#endif // COMMONDEF_H
