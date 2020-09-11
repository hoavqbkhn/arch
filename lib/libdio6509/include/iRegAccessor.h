/*
 * iRegAccessor.h
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dio_iRegAccessor_h___
#define ___dio_iRegAccessor_h___

#include "devices.h"

namespace nNISTC3
{
   typedef u8 tDigDataType;

   typedef enum
   {
      kLine0 = 0,
      kLine1,
      kLine2,
      kLine3,
      kLine4,
      kLine5,
      kLine6,
      kLine7,
   } tLine;

   typedef enum
   {
      kDisable,
      kFreeze,
      kTristate,
      kSafeState,
   } tWDTMode;

   typedef enum
   {
      kNo_Filter,
      kSmall_Filter,
      kMedium_Filter,
      kLarge_Filter,
   } tFilterType;

   enum
   {
      kNumFilters = 4,
   };

   class iRegAccessor
   {
   public:
      virtual ~iRegAccessor()
      {
      }

      // Returns the current value being sensed on the lines specified in the lineMask
      virtual tDigDataType staticRead(nMDBG::tStatus2& status) const = 0;

      // Drives the value in newValue onto the lines specified by the lineMask
      virtual void staticWrite( tDigDataType     newValue,
                                nMDBG::tStatus2& status ) = 0;

      // Configures the lines specified in the lineMask for the desired direction
      virtual void staticDirection( tDigDataType     lineMask,
                                    nMDBG::tStatus2& status ) = 0;

      // If the static direction register softcopy has been modified without writing to hardware
      // this method returns true
      virtual tBoolean staticDirectionIsDirty() const = 0;

      // Set the watchdog timer safe state for the port
      virtual void setSafeState( tDigDataType     safeState,
                                 nMDBG::tStatus2& status ) = 0;

      // Set the watchdog timer event response for the specified line
      virtual void setWDTMode( tLine            line,
                               tWDTMode         mode,
                               nMDBG::tStatus2& status ) = 0;

      // Set the digital filter to be used by the line
      virtual void setFilterType( tLine            line,
                                  tFilterType      filter,
                                  nMDBG::tStatus2& status ) = 0;

      // Set the lines that can cause a change detection event with a rising edge
      virtual void setREChangeDetection( tDigDataType     mask,
                                         nMDBG::tStatus2& status ) = 0;

      // Set the lines that can cause a change detection event with a falling edge
      virtual void setFEChangeDetection( tDigDataType     mask,
                                         nMDBG::tStatus2& status ) = 0;

      // Get the port value latched at the last change detection event
      virtual tDigDataType getChangeDetectionLatchedValue(nMDBG::tStatus2& status) const = 0;

   };

} // nNISTC3

#endif //___iRegAccessor_h___
