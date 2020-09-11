// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tStaticDio_ipp___
#define ___tStaticDio_ipp___

#ifndef ___tStaticDio_h___
#include "tStaticDio.h"
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


inline tBusSpaceReference tStaticDio::getBusSpaceReference(void) const
{
   return _addrSpace;
}

inline void tStaticDio::setAddressOffset(u32 value, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   _addressOffset = value;
}
inline u32 tStaticDio::getAddressOffset(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return 0UL;
   return _addressOffset;
}
#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

