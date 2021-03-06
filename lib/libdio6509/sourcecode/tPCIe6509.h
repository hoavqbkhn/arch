// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tPCIe6509_h___
#define ___tPCIe6509_h___

// includes
#include "osiTypes.h"
#include "osiBus.h"
#include "tStaticDio.h"
#include "tChpServices.h"
#include "tCHInCh.h"


#ifndef ___tPCIe6509Values_h___
#include "tPCIe6509Values.h"
#endif

class tPCIe6509
{
public:
   tStaticDio StaticDio;
   tChpServices ChpServicesLo;
   tChpServices ChpServicesHi;
   tCHInCh CHInCh;

   //---------------------------------------------------------------------------
   // IO Strategies
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Register Groups
   //---------------------------------------------------------------------------

   //----------------------------------------
   // Register/Field Ids
   //----------------------------------------
   typedef enum {

      kMaxRegisterId = -1

   } tId;

   tPCIe6509(tBusSpaceReference addrSpace, nMDBG::tStatus2* statusChain = NULL);
   void reset(nMDBG::tStatus2* statusChain = NULL);
   virtual ~tPCIe6509();

   inline tBusSpaceReference getBusSpaceReference(void) const;

   inline void setAddressOffset(u32 value, nMDBG::tStatus2* statusChain = NULL);
   inline u32  getAddressOffset(nMDBG::tStatus2* statusChain = NULL);
private:
   void _initialize(nMDBG::tStatus2* statusChain = NULL);
   tBusSpaceReference _addrSpace;
   u32 _addressOffset;

};

#ifndef ___tPCIe6509_ipp___
#ifndef ___tPCIe6509_h_no_inline___
#include "tPCIe6509.ipp"
#endif

#endif

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

