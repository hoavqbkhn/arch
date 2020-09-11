/*
 * rtsiResetHelper.cpp
 *
 * Reset for RTSI lines results in all pins set to input.
 * The reset can be called explicitly or by letting the helper go out of scope (destructor).
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "rtsiResetHelper.h"

// Chip Objects
#include "tChpServices.h"

namespace nNISTC3
{
   rtsiResetHelper::rtsiResetHelper( tChpServices&    chpServices,
                                     tBoolean         preserveOutputState,
                                     nMDBG::tStatus2& status ) :
      _chpServices(chpServices),
      _preserveOutputState(preserveOutputState),
      _exampleStatus(status)
   {
   }

   rtsiResetHelper::~rtsiResetHelper()
   {
      nMDBG::tStatus2 status;

      reset(status);
   }

   void rtsiResetHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      if (!_preserveOutputState || _exampleStatus.isFatal())
      {
         _chpServices.RTSI_Trig_Direction_Register.writeRegister(0, &status);
      }
   }
}
