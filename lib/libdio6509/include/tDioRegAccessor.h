/*
 * tDioRegAccessor.h
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dio_tDioRegAccessor_h___
#define ___dio_tDioRegAccessor_h___

#include "iRegAccessor.h"
#include "tDioPorts.h"

namespace nNISTC3
{

   class tDioRegAccessor: public iRegAccessor
   {
   public:
      tDioRegAccessor( tDioPorts&       portsRef,
                       tStc3PortNumber  dioPortNumber,
                       nMDBG::tStatus2& status );

      virtual ~tDioRegAccessor();

      // Returns the current value being sensed on the lines specified in the lineMask
      virtual tDigDataType staticRead(nMDBG::tStatus2& status) const;

      // Drives the value in newValue onto the lines specified by the lineMask
      virtual void staticWrite( tDigDataType     newValue,
                                nMDBG::tStatus2& status );

      // Configures the lines specified in the lineMask for the desired direction
      virtual void staticDirection( tDigDataType     lineMask,
                                    nMDBG::tStatus2& status );

      // If the static direction register softcopy has been modified without writing to hardware
      // this method returns true
      virtual tBoolean staticDirectionIsDirty() const;

      // Set the watchdog timer safe state for the port
      virtual void setSafeState( tDigDataType     safeState,
                                 nMDBG::tStatus2& status );

      // Set the watchdog timer event response for the specified line
      virtual void setWDTMode( tLine            line,
                               tWDTMode         mode,
                               nMDBG::tStatus2& status );

      // Set the digital filter to be used by the line
      virtual void setFilterType( tLine            line,
                                  tFilterType      filter,
                                  nMDBG::tStatus2& status );

      // Set the lines that can cause a change detection event with a rising edge
      virtual void setREChangeDetection( tDigDataType     mask,
                                         nMDBG::tStatus2& status );

      // Set the lines that can cause a change detection event with a falling edge
      virtual void setFEChangeDetection( tDigDataType     mask,
                                         nMDBG::tStatus2& status );

      // Get the port value latched at the last change detection event
      virtual tDigDataType getChangeDetectionLatchedValue(nMDBG::tStatus2& status) const;

   private:
      static nDioPorts::tDI_Filter_Select_t genericFilterToChipFilterMap[kNumFilters];

      void _setWDTModePort0( tLine            line,
                             tWDTMode         mode,
                             nMDBG::tStatus2& status );

      void _setWDTModePort1( tLine            line,
                             tWDTMode         mode,
                             nMDBG::tStatus2& status );

      void _setWDTModePort2( tLine            line,
                             tWDTMode         mode,
                             nMDBG::tStatus2& status );

      void _setWDTModePort3( tLine            line,
                             tWDTMode         mode,
                             nMDBG::tStatus2& status );

      void _setFilterTypePort0( tLine            line,
                                tFilterType      filter,
                                nMDBG::tStatus2& status );

      void _setFilterTypePort1( tLine            line,
                                tFilterType      filter,
                                nMDBG::tStatus2& status );

      void _setFilterTypePort2( tLine            line,
                                tFilterType      filter,
                                nMDBG::tStatus2& status );

      void _setFilterTypePort3( tLine            line,
                                tFilterType      filter,
                                nMDBG::tStatus2& status );

      tStc3PortNumber _dioPortNumber;
      tDioPorts&      _dioPortsRef;

      // Usage guidelines
      tDioRegAccessor& operator=(const tDioRegAccessor& rhs);
      tDioRegAccessor(const tDioRegAccessor& rhs);
   };

} // nNISTC3

#endif //___dio_tDioRegAccessor_h___
