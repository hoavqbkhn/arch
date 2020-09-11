/*
 * rtsiResetHelper.h
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

#ifndef ___rtsiResetHelper_h___
#define ___rtsiResetHelper_h___

#include "osiBus.h"

// Forward declarations
class tChpServices;

namespace nNISTC3
{
   class rtsiResetHelper
   {
   public:
      // Constructor
      // triggers:            the trigger object
      // preserveOutputState: RTSI lines should not be changed to input during reset
      // status
      rtsiResetHelper( tChpServices&    chpServices,
                       tBoolean         preserveOutputState,
                       nMDBG::tStatus2& status );

      ~rtsiResetHelper();

      // Changes the direction of all RTSI lines to input status
      void reset(nMDBG::tStatus2& status);

   private:
      // Usage guidelines
      rtsiResetHelper(const rtsiResetHelper&);
      rtsiResetHelper& operator=(const rtsiResetHelper&);

      tChpServices&           _chpServices;
      tBoolean                _preserveOutputState;
      const nMDBG::tStatus2&  _exampleStatus;
   };
}

#endif // ___rtsiResetHelper_h___
