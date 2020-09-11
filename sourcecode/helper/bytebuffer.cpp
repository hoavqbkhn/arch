/*
 * File:   ByteBuffer.cpp
 * Author: ducls@viettel.com.vn
 *
 * Created on January 2, 2019, 11:09 AM
 */

#include "bytebuffer.h"

ByteBuffer::ByteBuffer()
{
    this->m_data = new byte[bufferSize];
    this->rPos = 0;
    this->wPos = 0;
    this->leng = bufferSize;
}

ByteBuffer::~ByteBuffer()
{
    delete[] m_data;
    rPos = 0;
    wPos = 0;
    leng = 0;
    m_data = NULL;
}

//put

void ByteBuffer::putInt8(int8_t p)
{
    if (availableLength() >= 1)
    {
        memcpy(this->m_data + wPos, (byte*) & p, 1);
        this->wPos += 1;
    }
    else
    {
        shrink();

        if (availableLength() >= 1)
        {
            memcpy(this->m_data + wPos, (byte*) & p, 1);
            this->wPos += 1;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & p, 1);
            this->wPos += 1;
        }
    }
}

void ByteBuffer::putUInt8(uint8_t p)
{
    if (availableLength() >= 1)
    {
        memcpy(this->m_data + wPos, (byte*) & p, 1);
        this->wPos += 1;
    }
    else
    {
        shrink();

        if (availableLength() >= 1)
        {
            memcpy(this->m_data + wPos, (byte*) & p, 1);
            this->wPos += 1;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & p, 1);
            this->wPos += 1;
        }
    }
}

void ByteBuffer::putInt16(int16_t p, bool bigEndian)
{
    int16_t temp = 0;

    if (bigEndian)
    {
        temp = htobe16(p);
    }
    else
    {
        temp = htole16(p);
    }

    if (availableLength() >= 2)
    {
        memcpy(this->m_data + wPos, (byte*) & temp, 2);
        this->wPos += 2;
    }
    else
    {
        shrink();

        if (availableLength() >= 2)
        {
            memcpy(this->m_data + wPos, (byte*) & temp, 2);
            this->wPos += 2;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & temp, 2);
            this->wPos += 2;
        }
    }
}

void ByteBuffer::putUInt16(uint16_t p, bool bigEndian)
{
    uint16_t temp = 0;

    if (bigEndian)
    {
        temp = htobe16(p);
    }
    else
    {
        temp = htole16(p);
    }

    if (availableLength() >= 2)
    {
        memcpy(this->m_data + wPos, (byte*) & temp, 2);
        this->wPos += 2;
    }
    else
    {
        shrink();

        if (availableLength() >= 2)
        {
            memcpy(this->m_data + wPos, (byte*) & temp, 2);
            this->wPos += 2;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & temp, 2);
            this->wPos += 2;
        }
    }
}

void ByteBuffer::putInt32(int32_t p, bool bigEndian)
{
    int32_t temp = 0;

    if (bigEndian)
    {
        temp = htobe32(p);
    }
    else
    {
        temp = htole32(p);
    }

    if (availableLength() >= 4)
    {
        memcpy(this->m_data + wPos, (byte*) & temp, 4);
        wPos += 4;
    }
    else
    {
        shrink();

        if (availableLength() >= 4)
        {
            memcpy(this->m_data + wPos, (byte*) & temp, 4);
            this->wPos += 4;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & temp, 4);
            this->wPos += 4;
        }
    }
}

void ByteBuffer::putUInt32(uint32_t p, bool bigEndian)
{
    uint32_t temp = 0;

    if (bigEndian)
    {
        temp = htobe32(p);
    }
    else
    {
        temp = htole32(p);
    }

    if (availableLength() >= 4)
    {
        memcpy(this->m_data + wPos, (byte*) & temp, 4);
        wPos += 4;
    }
    else
    {
        shrink();

        if (availableLength() >= 4)
        {
            memcpy(this->m_data + wPos, (byte*) & temp, 4);
            this->wPos += 4;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & temp, 4);
            this->wPos += 4;
        }
    }
}

void ByteBuffer::putInt64(int64_t p, bool bigEndian)
{
    int64_t temp = 0;

    if (bigEndian)
    {
        temp = htobe64(p);
    }
    else
    {
        temp = htole64(p);
    }

    if (availableLength() >= 8)
    {
        memcpy(this->m_data + wPos, (byte*) & temp, 8);
        wPos += 8;
    }
    else
    {
        shrink();

        if (availableLength() >= 8)
        {
            memcpy(this->m_data + wPos, (byte*) & temp, 8);
            this->wPos += 8;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & temp, 8);
            this->wPos += 8;
        }
    }
}

void ByteBuffer::putUInt64(uint64_t p, bool bigEndian)
{
    uint64_t temp = 0;

    if (bigEndian)
    {
        temp = htobe64(p);
    }
    else
    {
        temp = htole64(p);
    }

    if (availableLength() >= 8)
    {
        memcpy(this->m_data + wPos, (byte*) & temp, 8);
        wPos += 8;
    }
    else
    {
        shrink();

        if (availableLength() >= 8)
        {
            memcpy(this->m_data + wPos, (byte*) & temp, 8);
            this->wPos += 8;
        }
        else
        {
            adjust(bufferSize + leng);
            memcpy(this->m_data + wPos, (byte*) & temp, 8);
            this->wPos += 8;
        }
    }
}

void ByteBuffer::putFloat(float p, bool bigEndian)
{
    uint32_t temp = bitwise_cast<uint32_t>(p);

    if (bigEndian)
    {
        temp = htobe32(temp);
    }
    else
    {
        temp = htole32(temp);
    }

    this->putBytes((byte*) & temp, 4);
    //  if(availableLength() >=4)
    //      {
    //          memcpy(this->m_data+wPos, (byte*)&p, 4);
    //          wPos+=4;
    //      }
    //      else
    //      {
    //          adjust(bufferSize+leng);
    //          memcpy(this->m_data+wPos, (byte*)&p, 4);
    //          wPos+=4;
    //      }
}

void ByteBuffer::putDouble(double p, bool bigEndian)
{
    uint64_t temp = bitwise_cast<uint64_t>(p);

    if (bigEndian)
    {
        temp = htobe64(temp);
    }
    else
    {
        temp = htole64(temp);
    }

    this->putBytes((byte*) & temp, 8);
    //  if(availableLength() >=8)
    //          {
    //              memcpy(this->m_data+wPos, (byte*)&p, 8);
    //              wPos+=8;
    //          }
    //          else
    //          {
    //              adjust(bufferSize+leng);
    //              memcpy(this->m_data+wPos, (byte*)&p, 8);
    //              wPos+=8;
    //          }
}

void ByteBuffer::putBytes(const byte* data, int length)
{
    if (availableLength() >= (length))
    {
        memcpy(this->m_data + wPos, data, length);
        this->wPos += length;
    }
    else
    {
        shrink();

        if (availableLength() >= (length))
        {
            memcpy(this->m_data + wPos, data, length);
            this->wPos += length;
        }
        else
        {
            adjust(2 * (leng + length));
            memcpy(this->m_data + wPos, data, length);
            this->wPos += length;
        }
    }
}
// get

bool ByteBuffer::getInt8(int8_t& p)
{
    if (rPos < wPos)
    {
        memcpy((byte*) & p, m_data + rPos, 1);
        rPos++;
        return true;
    }

    return false;
}

bool ByteBuffer::getUInt8(uint8_t& p)
{
    if (rPos < wPos)
    {
        memcpy((byte*) & p, m_data + rPos, 1);
        rPos++;
        return true;
    }

    return false;
}

bool ByteBuffer::getInt16(int16_t& p)
{
    int16_t temp;

    if (rPos <= (wPos - 2))
    {
        memcpy((byte*) & temp, m_data + rPos, 2);
        rPos += 2;
        p = be16toh(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getUInt16(uint16_t& p)
{
    uint16_t temp;

    if (rPos <= (wPos - 2))
    {
        memcpy((byte*) & temp, m_data + rPos, 2);
        rPos += 2;
        p = be16toh(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getInt32(int32_t& p)
{
    int32_t temp;

    if (rPos <= (wPos - 4))
    {
        memcpy((byte*) & temp, this->m_data + rPos, 4);
        rPos += 4;
        p = be32toh(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getUInt32(uint32_t& p)
{
    uint32_t temp;

    if (rPos <= (wPos - 4))
    {
        memcpy((byte*) & temp, this->m_data + rPos, 4);
        rPos += 4;
        p = be32toh(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getInt64(int64_t& p)
{
    int64_t temp;

    if (rPos <= (wPos - 8))
    {
        memcpy((byte*) & temp, this->m_data + rPos, 8);
        rPos += 8;
        p = be64toh(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getUInt64(uint64_t& p)
{
    uint64_t temp;

    if (rPos <= (wPos - 8))
    {
        memcpy((byte*) & temp, this->m_data + rPos, 8);
        rPos += 8;
        p = be64toh(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getFloat(float& p)
{
    uint32_t temp;

    if (rPos <= (wPos - 4))
    {
        memcpy((byte*) & temp, this->m_data + rPos, 4);
        rPos += 4;
        temp = be32toh(temp);
        p = bitwise_cast<float>(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getDouble(double& p)
{
    uint64_t temp;

    if (rPos <= (wPos - 8))
    {
        memcpy((byte*) & temp, this->m_data + rPos, 8);
        rPos += 8;
        temp = be64toh(temp);
        p = bitwise_cast<double>(temp);
        return true;
    }

    return false;
}

bool ByteBuffer::getBytes(byte* data, int length)
{
    if (rPos >= wPos)
    {
        return false;
    }

    if (rPos <= (wPos - length))
    {
        memcpy(data, this->m_data + rPos, length);
        rPos += length;
        //        shrink();
        return true;
    }

    //  else
    //  {
    //      length=wPos-rPos;
    //      memcpy(data, this->m_data+rPos, length);
    //      rPos+=length;
    //  }
    return false;
}

bool ByteBuffer::copyBytes(byte* data, int length)
{
    if (rPos >= wPos)
    {
        return false;
    }

    if (rPos <= (wPos - length))
    {
        memcpy(data, this->m_data + rPos, length);
        return true;
    }

    //  else
    //  {
    //      length=wPos-rPos;
    //      memcpy(data, this->m_data+rPos, length);
    //      rPos+=length;
    //  }
    return false;
}

/**
 *
 * @return number of bytes in Buffer
 */
int ByteBuffer::getTotalLength()
{
    return (wPos - rPos);
}

void ByteBuffer::removeHead(int pos)
{
    if (pos <= rPos)
    {
        rPos -= pos;
        wPos -= pos;
        memmove(this->m_data, this->m_data + pos, wPos - rPos);
    }
    else if ((rPos < pos) && (pos <= wPos))
    {
        rPos = 0;
        wPos -= pos;
        memmove(this->m_data, this->m_data + pos, wPos - rPos);
    }
    else
    {
        this->clear();
    }
}

void ByteBuffer::shrink()
{
    //    _LOG_DEBUG("DO SHRINK rpos = %d, wpos = %d", rPos, wPos);
    if (rPos >= 2 * (wPos - rPos))
    {
        removeHead(rPos);
        position(0);
    }
}

void ByteBuffer::rewindRead(int numberByte)
{
    if (numberByte <= 0)
    {
        return;
    }

    if (numberByte >= rPos)
    {
        rPos = 0;
    }
    else
    {
        rPos -= numberByte;
    }
}

/**
 * Change the position of read position index
 * @param rPos - the position of read position index
 * if rPos > length -> do nothing
 */
void ByteBuffer::position(int rPos)
{
    if (rPos > leng)
    {
    }
    else
    {
        this->rPos = rPos;
    }
}

int ByteBuffer::getCurrentPositionRead()
{
    return rPos;
}

/**
 *
 * @return the max size of buffer. This is constant
 */
int ByteBuffer::length()
{
    return this->leng;
}

void ByteBuffer::clear()
{
    this->rPos = 0;
    this->wPos = 0;
    memset(this->m_data, 0, leng);
}

/**
 *
 * @return the number of bytes which Buffer can now store
 */
int ByteBuffer::availableLength()
{
    return (leng - wPos);
}

void ByteBuffer::adjust(int length)
{
    //    shrink();
    byte* tempData = (byte*) realloc(this->m_data, length);

    if (tempData == NULL) // error in reallocating memory
    {
        byte* temp = new byte[length];
        memcpy(temp, this->m_data, this->leng);
        delete[] this->m_data;
        this->m_data = temp;
        this->leng = length;
    }
    else
    {
        this->m_data = tempData;
        this->leng = length;
    }
}

/**
 * TOtally same as @getTotalLength function
 * @return number of bytes currently in Buffer
 */
int ByteBuffer::readableLength()
{
    return (wPos - rPos);
}

std::string ByteBuffer::printHex(int length)
{
    int tmp = length;

    if (length > readableLength())
    {
        tmp = readableLength();
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (int i = rPos; i < rPos + tmp; i++)
    {
        ss << std::setw(2) << static_cast<unsigned>(m_data[i]) << " ";
    }

    std::string str = ss.str();
    return str;
}
