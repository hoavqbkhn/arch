// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tCHInCh_ipp___
#define ___tCHInCh_ipp___

#ifndef ___tCHInCh_h___
#include "tCHInCh.h"
#endif

#ifndef ___nNIMXRegistermap_tStatus2Ptr_ipp___
#define ___nNIMXRegistermap_tStatus2Ptr_ipp___

typedef nMDBG::tStatus2 nNIMXRegisterMap120_tStatus2;


namespace nNIMXRegisterMap120 {
namespace {

typedef nNIMXRegisterMap120_tStatus2 tStatus2;

inline void setStatus(tStatus2* s, tStatus newStatus)
{
   if (s) s->setCode(newStatus);
}

inline tStatus* toPALStatusPtr(tStatus2* s)
{
   return s ? s->operator tStatus*() : ((tStatus*)NULL);
}

inline tBoolean statusIsFatal(tStatus2* s)
{
   return s && s->isFatal();
}

} // unnamed namespace
} // namespace nNIMXRegisterMap120

#endif // ___nNIMXRegistermap_tStatus2Ptr_ipp___


inline void tCHInCh::tReg32IODirect32::write(
   tBusSpaceReference addrSpace,
   u32 offset,
   u32 value,
   nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   addrSpace.write32(offset, value);
}

inline u32 tCHInCh::tReg32IODirect32::read(
   tBusSpaceReference addrSpace,
   u32 offset,
   nMDBG::tStatus2* s)
{
   u32 value = (u32)~0;
   if (s && s->isFatal()) return value;
   value = addrSpace.read32(offset);
   return value;
}

inline tBusSpaceReference tCHInCh::getBusSpaceReference(void) const
{
   return _addrSpace;
}

inline void tCHInCh::setAddressOffset(u32 value, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   _addressOffset = value;
}
inline u32 tCHInCh::getAddressOffset(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return 0UL;
   return _addressOffset;
}
inline tBoolean tCHInCh::isDirty(tId id, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return kFalse;
   u32 regId = id&0x01FFFFFF;
   if (regId > kMaxRegisterId) {
      nNIMXRegisterMap120::setStatus(s, kStatusBadSelector);
      return kFalse;
   }

   return _dirtyVector[regId];
}

inline void tCHInCh::markDirty(tId id, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   u32 regId = id&0x01FFFFFF;

   if (regId > kMaxRegisterId) {
      nNIMXRegisterMap120::setStatus(s, kStatusBadSelector);
      return;
   }

   _dirtyVector[regId] = 1;
}

inline void tCHInCh::markClean(tId id, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   u32 regId = id&0x01FFFFFF;

   if (regId > kMaxRegisterId) {
      nNIMXRegisterMap120::setStatus(s, kStatusBadSelector);
      return;
   }

   _dirtyVector[regId] = 0;
}

inline void tCHInCh::markDirty(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   unsigned int i;
   for (i = 0; i < sizeof(_dirtyVector)/sizeof(_dirtyVector[0]); i++) {
      _dirtyVector[i] = 1;
   }
}

inline void tCHInCh::markClean(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   for (unsigned int i = 0; i < sizeof(_dirtyVector)/sizeof(_dirtyVector[0]); i++) {
      _dirtyVector[i] = 0;
   }
}

inline tCHInCh::tCHInCh_Identification_Register::tCHInCh_Identification_Register()
{
   _softCopy = u32(0x0);
}

inline tCHInCh::tCHInCh_Identification_Register::tRegisterMap* tCHInCh::tCHInCh_Identification_Register::registerMap(void)
{
   return _regMap;
}

inline void tCHInCh::tCHInCh_Identification_Register::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tCHInCh::tCHInCh_Identification_Register& tCHInCh::tCHInCh_Identification_Register::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   _softCopy = fieldValue;
   return *this;
}

inline u32 tCHInCh::tCHInCh_Identification_Register::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tCHInCh::tCHInCh_Identification_Register::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tCHInCh::tCHInCh_Identification_Register::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tCHInCh::tCHInCh_Identification_Register& tCHInCh::tCHInCh_Identification_Register::setID(nCHInCh::tCHInCh_Signature_t fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0x0) | ((u32(fieldValue) << 0x0) & ~0x0);
   setRegister(newValue, s);
   return *this;
}

inline nCHInCh::tCHInCh_Signature_t tCHInCh::tCHInCh_Identification_Register::getID(nMDBG::tStatus2*) const
{
   return nCHInCh::tCHInCh_Signature_t((_softCopy & ~0x0) >> 0x0);
}

inline nCHInCh::tCHInCh_Signature_t tCHInCh::tCHInCh_Identification_Register::readID(nMDBG::tStatus2* s)
{
   refresh(s);
   return getID(s);
}

inline tCHInCh::tInterrupt_Mask_Register::tInterrupt_Mask_Register()
{
   _softCopy = u32(0x0);
}

inline tCHInCh::tInterrupt_Mask_Register::tRegisterMap* tCHInCh::tInterrupt_Mask_Register::registerMap(void)
{
   return _regMap;
}

inline void tCHInCh::tInterrupt_Mask_Register::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tBoolean tCHInCh::tInterrupt_Mask_Register::isDirty(nMDBG::tStatus2* s)
{
   return _regMap->isDirty((tCHInCh::tId)kId, s);
}

inline void tCHInCh::tInterrupt_Mask_Register::markDirty(nMDBG::tStatus2* s)
{
   _regMap->markDirty((tCHInCh::tId)kId, s);
}

inline void tCHInCh::tInterrupt_Mask_Register::markClean(nMDBG::tStatus2* s)
{
   _regMap->markClean((tCHInCh::tId)kId, s);
}

inline tCHInCh::tInterrupt_Mask_Register& tCHInCh::tInterrupt_Mask_Register::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   if (_softCopy != fieldValue) {
      _softCopy = fieldValue;
      markDirty(s);
   }
   return *this;
}

inline u32 tCHInCh::tInterrupt_Mask_Register::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tCHInCh::tInterrupt_Mask_Register::flush(nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   if (force || isDirty(s)) {
      tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), _softCopy, s);
      _softCopy &= u32(0xffffffff);
      _softCopy |= u32(0x0);
      markClean(s);
   }
}

inline void tCHInCh::tInterrupt_Mask_Register::writeRegister(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   force = force || (_softCopy != fieldValue);
   _softCopy = fieldValue;
   flush(s, force);
}

inline void tCHInCh::tInterrupt_Mask_Register::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tCHInCh::tInterrupt_Mask_Register::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tCHInCh::tInterrupt_Mask_Register& tCHInCh::tInterrupt_Mask_Register::setClear_STC3_Int(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xfffffbff) | ((u32(fieldValue) << 0xa) & ~0xfffffbff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tInterrupt_Mask_Register::getClear_STC3_Int(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xfffffbff) >> 0xa);
}

inline void tCHInCh::tInterrupt_Mask_Register::writeClear_STC3_Int(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setClear_STC3_Int(fieldValue, s);
   flush(s, force);
}
inline u32 tCHInCh::tInterrupt_Mask_Register::readClear_STC3_Int(nMDBG::tStatus2* s)
{
   refresh(s);
   return getClear_STC3_Int(s);
}

inline tCHInCh::tInterrupt_Mask_Register& tCHInCh::tInterrupt_Mask_Register::setSet_STC3_Int(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xfffff7ff) | ((u32(fieldValue) << 0xb) & ~0xfffff7ff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tInterrupt_Mask_Register::getSet_STC3_Int(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xfffff7ff) >> 0xb);
}

inline void tCHInCh::tInterrupt_Mask_Register::writeSet_STC3_Int(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setSet_STC3_Int(fieldValue, s);
   flush(s, force);
}
inline u32 tCHInCh::tInterrupt_Mask_Register::readSet_STC3_Int(nMDBG::tStatus2* s)
{
   refresh(s);
   return getSet_STC3_Int(s);
}

inline tCHInCh::tInterrupt_Mask_Register& tCHInCh::tInterrupt_Mask_Register::setClear_CPU_Int(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xbfffffff) | ((u32(fieldValue) << 0x1e) & ~0xbfffffff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tInterrupt_Mask_Register::getClear_CPU_Int(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xbfffffff) >> 0x1e);
}

inline void tCHInCh::tInterrupt_Mask_Register::writeClear_CPU_Int(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setClear_CPU_Int(fieldValue, s);
   flush(s, force);
}
inline u32 tCHInCh::tInterrupt_Mask_Register::readClear_CPU_Int(nMDBG::tStatus2* s)
{
   refresh(s);
   return getClear_CPU_Int(s);
}

inline tCHInCh::tInterrupt_Mask_Register& tCHInCh::tInterrupt_Mask_Register::setSet_CPU_Int(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0x7fffffff) | ((u32(fieldValue) << 0x1f) & ~0x7fffffff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tInterrupt_Mask_Register::getSet_CPU_Int(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0x7fffffff) >> 0x1f);
}

inline void tCHInCh::tInterrupt_Mask_Register::writeSet_CPU_Int(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setSet_CPU_Int(fieldValue, s);
   flush(s, force);
}
inline u32 tCHInCh::tInterrupt_Mask_Register::readSet_CPU_Int(nMDBG::tStatus2* s)
{
   refresh(s);
   return getSet_CPU_Int(s);
}

inline tCHInCh::tInterrupt_Status_Register::tInterrupt_Status_Register()
{
}

inline tCHInCh::tInterrupt_Status_Register::tRegisterMap* tCHInCh::tInterrupt_Status_Register::registerMap(void)
{
   return _regMap;
}

inline void tCHInCh::tInterrupt_Status_Register::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline u32 tCHInCh::tInterrupt_Status_Register::readRegister(nMDBG::tStatus2* s)
{
   u32 fieldValue;
   fieldValue = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
   return fieldValue;
}

inline u32 tCHInCh::tInterrupt_Status_Register::readSTC3_Int(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffff7ff) >> 0xb);
}

inline u32 tCHInCh::tInterrupt_Status_Register::readExternal(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xdfffffff) >> 0x1d);
}

inline u32 tCHInCh::tInterrupt_Status_Register::readAdditional_Int(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xbfffffff) >> 0x1e);
}

inline u32 tCHInCh::tInterrupt_Status_Register::readInt(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0x7fffffff) >> 0x1f);
}

inline tCHInCh::tVolatile_Interrupt_Status_Register::tVolatile_Interrupt_Status_Register()
{
}

inline tCHInCh::tVolatile_Interrupt_Status_Register::tRegisterMap* tCHInCh::tVolatile_Interrupt_Status_Register::registerMap(void)
{
   return _regMap;
}

inline void tCHInCh::tVolatile_Interrupt_Status_Register::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline u32 tCHInCh::tVolatile_Interrupt_Status_Register::readRegister(nMDBG::tStatus2* s)
{
   u32 fieldValue;
   fieldValue = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
   return fieldValue;
}

inline u32 tCHInCh::tVolatile_Interrupt_Status_Register::readVol_STC3_Int(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffff7ff) >> 0xb);
}

inline u32 tCHInCh::tVolatile_Interrupt_Status_Register::readVol_External(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xdfffffff) >> 0x1d);
}

inline u32 tCHInCh::tVolatile_Interrupt_Status_Register::readVol_Additional_Int(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xbfffffff) >> 0x1e);
}

inline u32 tCHInCh::tVolatile_Interrupt_Status_Register::readVol_Int(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0x7fffffff) >> 0x1f);
}

inline tCHInCh::tScrap_Register_t::tScrap_Register_t(u32 offset, u32 id)
 : kOffset(offset),
   kId(id)
{
   _softCopy = u32(0x0);
}

inline tCHInCh::tScrap_Register_t::tScrap_Register_t()
 : kOffset((u32)~0),
   kId((u32)~0)
{
   _softCopy = u32(0x0);
}

inline void tCHInCh::tScrap_Register_t::initialize(u32 offset, u32 id)
{
   u32* mutableOffset = const_cast<u32*>(&this->kOffset);
   u32* mutableId     = const_cast<u32*>(&this->kId);
   *mutableOffset = offset;
   *mutableId = id;
}

inline tCHInCh::tScrap_Register_t::tRegisterMap* tCHInCh::tScrap_Register_t::registerMap(void)
{
   return _regMap;
}

inline void tCHInCh::tScrap_Register_t::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tBoolean tCHInCh::tScrap_Register_t::isDirty(nMDBG::tStatus2* s)
{
   return _regMap->isDirty((tCHInCh::tId)kId, s);
}

inline void tCHInCh::tScrap_Register_t::markDirty(nMDBG::tStatus2* s)
{
   _regMap->markDirty((tCHInCh::tId)kId, s);
}

inline void tCHInCh::tScrap_Register_t::markClean(nMDBG::tStatus2* s)
{
   _regMap->markClean((tCHInCh::tId)kId, s);
}

inline tCHInCh::tScrap_Register_t& tCHInCh::tScrap_Register_t::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   if (_softCopy != fieldValue) {
      _softCopy = fieldValue;
      markDirty(s);
   }
   return *this;
}

inline u32 tCHInCh::tScrap_Register_t::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tCHInCh::tScrap_Register_t::flush(nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   if (force || isDirty(s)) {
      tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), _softCopy, s);
      _softCopy &= u32(0xffffffff);
      _softCopy |= u32(0x0);
      markClean(s);
   }
}

inline void tCHInCh::tScrap_Register_t::writeRegister(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   force = force || (_softCopy != fieldValue);
   _softCopy = fieldValue;
   flush(s, force);
}

inline void tCHInCh::tScrap_Register_t::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tCHInCh::tScrap_Register_t::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tCHInCh::tScrap_Register_t& tCHInCh::tScrap_Register_t::setSDATA(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0x0) | ((u32(fieldValue) << 0x0) & ~0x0);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tScrap_Register_t::getSDATA(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0x0) >> 0x0);
}

inline void tCHInCh::tScrap_Register_t::writeSDATA(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setSDATA(fieldValue, s);
   flush(s, force);
}
inline u32 tCHInCh::tScrap_Register_t::readSDATA(nMDBG::tStatus2* s)
{
   refresh(s);
   return getSDATA(s);
}

inline tCHInCh::tPCI_SubSystem_ID_Access_Register::tPCI_SubSystem_ID_Access_Register()
{
   _softCopy = u32(0x0);
}

inline tCHInCh::tPCI_SubSystem_ID_Access_Register::tRegisterMap* tCHInCh::tPCI_SubSystem_ID_Access_Register::registerMap(void)
{
   return _regMap;
}

inline void tCHInCh::tPCI_SubSystem_ID_Access_Register::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tCHInCh::tPCI_SubSystem_ID_Access_Register& tCHInCh::tPCI_SubSystem_ID_Access_Register::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   _softCopy = fieldValue;
   return *this;
}

inline u32 tCHInCh::tPCI_SubSystem_ID_Access_Register::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tCHInCh::tPCI_SubSystem_ID_Access_Register::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tCHInCh::tPCI_SubSystem_ID_Access_Register::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tCHInCh::tPCI_SubSystem_ID_Access_Register& tCHInCh::tPCI_SubSystem_ID_Access_Register::setSubSystem_Vendor_ID(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffff0000) | ((u32(fieldValue) << 0x0) & ~0xffff0000);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tPCI_SubSystem_ID_Access_Register::getSubSystem_Vendor_ID(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffff0000) >> 0x0);
}

inline u32 tCHInCh::tPCI_SubSystem_ID_Access_Register::readSubSystem_Vendor_ID(nMDBG::tStatus2* s)
{
   refresh(s);
   return getSubSystem_Vendor_ID(s);
}

inline tCHInCh::tPCI_SubSystem_ID_Access_Register& tCHInCh::tPCI_SubSystem_ID_Access_Register::setSubSystem_Product_ID(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffff) | ((u32(fieldValue) << 0x10) & ~0xffff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tCHInCh::tPCI_SubSystem_ID_Access_Register::getSubSystem_Product_ID(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffff) >> 0x10);
}

inline u32 tCHInCh::tPCI_SubSystem_ID_Access_Register::readSubSystem_Product_ID(nMDBG::tStatus2* s)
{
   refresh(s);
   return getSubSystem_Product_ID(s);
}

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

