// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tPCIe6509_h___
#include "tPCIe6509.h"
#endif

tPCIe6509::tPCIe6509(tBusSpaceReference addrSpace, nMDBG::tStatus2* s)
 : StaticDio()
,
   ChpServicesLo()
,
   ChpServicesHi()
,
   CHInCh()

{
   _addressOffset = 0;
   _addrSpace = addrSpace;

   _initialize(s);
}

void tPCIe6509::reset(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;

}

void tPCIe6509::_initialize(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;

   StaticDio.initialize(_addrSpace, 0x0 + getAddressOffset(s), s);
   ChpServicesLo.initialize(_addrSpace, 0x20000 + getAddressOffset(s), s);
   ChpServicesHi.initialize(_addrSpace, 0x40000 + getAddressOffset(s), s);
   CHInCh.initialize(_addrSpace, 0x0 + getAddressOffset(s), s);



   //----------------------------------------
   // set register maps of all registers
   //----------------------------------------

   //----------------------------------------
   // reset registers
   //----------------------------------------
   reset(s);
}

tPCIe6509::~tPCIe6509()
{
}



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

