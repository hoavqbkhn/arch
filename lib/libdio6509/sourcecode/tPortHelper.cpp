/*
 * tPortHelper.cpp
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "tPortHelper.h"

namespace nNISTC3
{
   tPortHelper::tPortHelper( iRegAccessor& registers,
                             nMDBG::tStatus2& status ) :
      _registers(registers),
      _tristate(kTrue),
      _outMask(0),
      _outSoftCopy(0),
      _exampleStatus(status)
   {
      if (status.isFatal()) return;
   }

   tPortHelper::~tPortHelper()
   {
      if (_tristate || _exampleStatus.isFatal())
      {
         nMDBG::tStatus2 status;
         reset(NULL, 0, status);
      }
   }

   void tPortHelper::setTristate(tBoolean tristateOnExit, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _tristate = tristateOnExit;
   }

   static const tDigitalPowerupState sDefaultPowerupStates[] = {
      {kTrue, 0xFF, 0x00},
   };

   void tPortHelper::reset( tDigitalPowerupState const* powerupStates,
                            u32                         numPowerupStates,
                            nMDBG::tStatus2&            status )
   {
      if (status.isFatal()) return;

      if (numPowerupStates == 0)
      {
         powerupStates = sDefaultPowerupStates;
         numPowerupStates = sizeof(sDefaultPowerupStates)/sizeof(sDefaultPowerupStates[0]);
      }

      tDigDataType readValue;
      read(0xFF, readValue, status);
      _outSoftCopy = ((readValue & powerupStates->highImp) |
                     (powerupStates->outputValue & ~(powerupStates->highImp)));

      _outMask = ~(powerupStates->highImp);

      // Force hardware to a known state
      write(_outMask, _outSoftCopy, status);
      _registers.staticDirection(_outMask, status);

      // Disable watchdog timer response
      _setWDTMode(0xFF, kDisable, status);

      // Halt change detection
      _registers.setREChangeDetection(0x00, status);
      _registers.setFEChangeDetection(0x00, status);
   }

   void tPortHelper::read( tDigDataType     lineMask,
                           tDigDataType&    value,
                           nMDBG::tStatus2& status ) const
   {
      value = 0;

      if (status.isFatal()) return;

      value = (_registers.staticRead(status) & lineMask & ~_outMask);
   }

   void tPortHelper::write( tDigDataType     lineMask,
                            tDigDataType     newValue,
                            nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      // Invert the line mask, AND it with the soft copy, OR it with the new
      // value to be written (in other words, zero the bits for the lines of
      // interest and OR them with the new value for those lines).
      _outSoftCopy = ((_outSoftCopy & (~lineMask)) | (lineMask & newValue & _outMask));
      _registers.staticWrite(_outSoftCopy, status);
   }

   void tPortHelper::configureLines( tDigDataType      lineMask,
                                     tDigConfiguration configuration,
                                     nMDBG::tStatus2&  status )
   {
      if (status.isFatal()) return;

      // Check to see if the lines need to be configured.
      // If the soft copies match the requested configuration and the registers
      // are not dirty, no action required.
      if ( ((configuration == kInput && lineMask == ~_outMask) || (configuration == kOutput && lineMask == _outMask))
            && !_registers.staticDirectionIsDirty() )
      {
         return;
      }

      // Set and clear the bits in the appropriate masks.
      // The in/out mask should be compliments of each other.
      switch (configuration)
      {
      case kInput:
         {
            _outMask &= ~(lineMask);
         }
         break;

      case kOutput:
         {
            _outMask |= lineMask;
         }
         break;

      default:
         {
            return;
         }
      }

      _registers.staticDirection(_outMask, status);

      return;
   }

   void tPortHelper::configureWDTSafeState( tDigDataType     safeState,
                                            tDigDataType     safeStateMask,
                                            nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _registers.setSafeState(safeState, status);
      _setWDTMode(safeStateMask, kSafeState, status);
   }

   void tPortHelper::configureWDTFreeze( tDigDataType     freezeMask,
                                         nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _setWDTMode(freezeMask, kFreeze, status);
   }

   void tPortHelper::configureWDTTristate( tDigDataType     tristateMask,
                                           nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _setWDTMode(tristateMask, kTristate, status);
   }

   void tPortHelper::_setWDTMode( tDigDataType     mask,
                                  tWDTMode         mode,
                                  nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      for (int line = 0; line < kLinesPerPort; ++line)
      {
         if ((1<<line) & mask)
         {
            _registers.setWDTMode(static_cast<tLine>(line), mode, status);
         }
      }
   }

   void tPortHelper::configureFilter( tDigDataType     mask,
                                      tFilterType      filter,
                                      nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      for (int line = 0; line < kLinesPerPort; ++line)
      {
         if ((1<<line) & mask)
         {
            _registers.setFilterType(static_cast<tLine>(line), filter, status);
         }
      }
   }

   void tPortHelper::setChangeDetection( tDigDataType         mask,
                                         tChangeDetectionMode mode,
                                         nMDBG::tStatus2&     status )
   {
      if (status.isFatal()) return;

      switch (mode)
      {
      case kRisingEdge:
         _registers.setREChangeDetection(mask, status);
         break;
      case kFallingEdge:
         _registers.setFEChangeDetection(mask, status);
         break;
      }
   }

   // Get the port value latched at the last change detection event
   void tPortHelper::getChangeDetectionLatchedValue( tDigDataType     lineMask,
                                                     tDigDataType&    value,
                                                     nMDBG::tStatus2& status ) const
   {
      value = 0;

      if (status.isFatal()) return;

      value = (_registers.getChangeDetectionLatchedValue(status) & lineMask & ~_outMask);
   }
} // nNISTC3
