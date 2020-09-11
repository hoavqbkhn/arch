/*
 * File:   ByteBuffer.h
 * Author: ducls@viettel.com.vn
 *
 * Created on January 2, 2019, 11:09 AM
 */

#ifndef VTX_BYTEBUFFER_H
#define VTX_BYTEBUFFER_H
#include <assert.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "stdendian.h"

typedef unsigned char byte;
const int bufferSize = 4096;

template <typename To, typename From>
static inline To bitwise_cast(From from)
{
    assert(sizeof(From) == sizeof(To));
    union
    {
        From f;
        To t;
    } u;
    u.f = from;
    return u.t;
}

class ByteBuffer
{
    public:
        ByteBuffer();
        virtual ~ByteBuffer();
        //put
        virtual void putInt8(int8_t p);
        virtual void putUInt8(uint8_t p);
        virtual void putInt16(int16_t p, bool bigEndian = true);
        virtual void putUInt16(uint16_t p, bool bigEndian = true);
        virtual void putInt32(int32_t p, bool bigEndian = true);
        virtual void putUInt32(uint32_t p, bool bigEndian = true);
        virtual void putInt64(int64_t p, bool bigEndian = true);
        virtual void putUInt64(uint64_t p, bool bigEndian = true);
        virtual void putFloat(float p, bool bigEndian = true);
        virtual void putDouble(double p, bool bigEndian = true);
        virtual void putBytes(const byte* data, int length);

        // get
        virtual bool getInt8(int8_t& p);
        virtual bool getUInt8(uint8_t& p);
        virtual bool getInt16(int16_t& p);
        virtual bool getUInt16(uint16_t& p);
        virtual bool getInt32(int32_t& p);
        virtual bool getUInt32(uint32_t& p);
        virtual bool getInt64(int64_t& p);
        virtual bool getUInt64(uint64_t& p);
        virtual bool getFloat(float& p);
        virtual bool getDouble(double& p);
        virtual bool getBytes(byte* data, int length);
        // copy
        /**
         * Just do copy bytes to data array and not erase them in buffer
         * @param data
         * @param length
         * @return
         */
        virtual bool copyBytes(byte* data, int length);
        /**
         *
         * @return number of bytes currently in Buffer
         */
        virtual int getTotalLength();
        //    virtual bool getTotalByte(byte* data);
        // control
        virtual void shrink();
        virtual void rewindRead(int numberByte);
        /**
         * delete head from beginning to @param pos
         * @param pos
         */
        virtual void removeHead(int pos);
        virtual void position(int rPos);
        virtual int getCurrentPositionRead();
        /**
         *
         * @return the max size of current buffer.
         * It may change when expand buffer
         */
        virtual int length();
        /**
         * clear buffer
         */
        virtual void clear();
        /**
         * expand buffer to the length
         * @param length
         */
        virtual void adjust(int length);
        /**
         *
         * @return the number of bytes which Buffer can store
         */
        virtual int availableLength();
        /**
         * TOtally same as @getTotalLength()
         * @return number of bytes currently in Buffer
         */
        virtual int readableLength();

        /**
         * Return a string in hex format
         * @param data
         * @param length
         * @return std::string
         */
        virtual std::string printHex(int length);
    private:
        byte* m_data;
        int leng;
        int rPos;
        int wPos;

};
#endif /* VTX_BYTEBUFFER_H */

