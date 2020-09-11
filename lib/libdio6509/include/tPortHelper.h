/*
 * tPortHelper.h
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dio_tPortHelper_h___
#define ___dio_tPortHelper_h___

#include "iRegAccessor.h"

namespace nNISTC3
{
   enum tDigConfiguration
   {
      kInput = 0,         // Static input
      kOutput = 1,        // Static output
      kNotConfigured = 2,
   };

   enum tChangeDetectionMode
   {
      kRisingEdge,
      kFallingEdge,
   };

   struct tDigitalPowerupState
   {
      tBoolean     enable;
      tDigDataType highImp;     // Mask
      tDigDataType outputValue; // Value
   };

   class tPortHelper
   {
   public:
      tPortHelper( iRegAccessor&    registers,
                   nMDBG::tStatus2& status );
      virtual ~tPortHelper();

      // Drives the power up states onto the lines
      void reset( tDigitalPowerupState const* powerupStates,
                  u32                         numPowerupStates,
                  nMDBG::tStatus2&            status );

      void setTristate(tBoolean tristateOnExit, nMDBG::tStatus2& status);

      // Returns the current value being sensed on the lines specified in the lineMask
      void read( tDigDataType     lineMask,
                 tDigDataType&    value,
                 nMDBG::tStatus2& status ) const;

      // Drives the value in newValue onto the lines specified by the lineMask
      void write( tDigDataType     lineMask,
                  tDigDataType     newValue,
                  nMDBG::tStatus2& status );

      // Configures the lines specified in the lineMask for the desired direction
      void configureLines( tDigDataType      lineMask,
                           tDigConfiguration configuration,
                           nMDBG::tStatus2&  status );

      // Configure the lines that should be in a safe state during a watchdog timer event
      void configureWDTSafeState( tDigDataType     safeState,
                                  tDigDataType     safeStateMask,
                                  nMDBG::tStatus2& status );

      // Configure the lines that should freeze during a watchdog timer event
      void configureWDTFreeze( tDigDataType     freezeMask,
                               nMDBG::tStatus2& status );

      // Configure the lines that should tristate during a watchdog timer event
      void configureWDTTristate( tDigDataType     tristateMask,
                                 nMDBG::tStatus2& status );

      // Set the digital filter to be used by the lines in mask
      void configureFilter( tDigDataType     mask,
                            tFilterType      filter,
                            nMDBG::tStatus2& status );

      // Set the lines that can cause a change detection event
      virtual void setChangeDetection( tDigDataType         mask,
                                       tChangeDetectionMode mode,
                                       nMDBG::tStatus2&     status );

      // Get the port value latched at the last change detection event
      void getChangeDetectionLatchedValue( tDigDataType     lineMask,
                                           tDigDataType&    value,
                                           nMDBG::tStatus2& status ) const;

   private:
      enum
      {
         kLinesPerPort = 8,
      };

      void _setWDTMode( tDigDataType     mask,
                        tWDTMode         mode,
                        nMDBG::tStatus2& status );

      iRegAccessor& _registers;

      tDigDataType  _outMask;
      tDigDataType  _outSoftCopy;

      tBoolean      _tristate;
      const nMDBG::tStatus2& _exampleStatus;

      // Usage guidelines
      tPortHelper& operator=(const tPortHelper& rhs);
      tPortHelper(const tPortHelper& rhs);
   };

} // nNISTC3

#endif //___dio_tPortHelper_h___
