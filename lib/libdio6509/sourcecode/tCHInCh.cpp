// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tCHInCh_h___
#include "tCHInCh.h"
#endif

tCHInCh::tCHInCh(tBusSpaceReference addrSpace, nMDBG::tStatus2* s)

{
   _addressOffset = 0;
   _addrSpace = addrSpace;

   _initialize(s);
}

tCHInCh::tCHInCh()

{
   _addressOffset = 0;

}

void tCHInCh::initialize(tBusSpaceReference addrSpace, u32 addressOffset, nMDBG::tStatus2* s)
{

   _addrSpace = addrSpace;
   _addressOffset = addressOffset;

   _initialize(s);
}

void tCHInCh::reset(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;

   CHInCh_Identification_Register.setRegister(u32(0x0), s);
   Interrupt_Mask_Register.setRegister(u32(0x0), s);
   Interrupt_Mask_Register.markDirty(s);
   unsigned int i;
   for(i = 0; i < 1; ++i) {
      Scrap_Register[i].setRegister(u32(0x0), s);
      Scrap_Register[i].markDirty(s);
   }
   PCI_SubSystem_ID_Access_Register.setRegister(u32(0x0), s);
}

void tCHInCh::_initialize(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;

   {
      unsigned int i;
      for (i=0; i<1; ++i) {
         Scrap_Register[i].initialize(0x200 + (0x4 * i), 0x4 + i);
      }
   }


   //----------------------------------------
   // set register maps of all registers
   //----------------------------------------
   CHInCh_Identification_Register.setRegisterMap(this);
   Interrupt_Mask_Register.setRegisterMap(this);
   Interrupt_Status_Register.setRegisterMap(this);
   Volatile_Interrupt_Status_Register.setRegisterMap(this);
   {
      unsigned int i;
      for(i = 0; i < 1; ++i) {
         Scrap_Register[i].setRegisterMap(this);
      }
   }
   PCI_SubSystem_ID_Access_Register.setRegisterMap(this);

   //----------------------------------------
   // initialize dirty flags
   //----------------------------------------
   for (unsigned int i = 0; i < sizeof(_dirtyVector)/sizeof(_dirtyVector[0]); i++) {
      _dirtyVector[i] = 0;
   }

   //----------------------------------------
   // reset registers
   //----------------------------------------
   reset(s);
}

tCHInCh::~tCHInCh()
{
}



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

