/*
 * tPfiRegAccessor.cpp
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "tPfiRegAccessor.h"

namespace nNISTC3
{
   nPfiPorts::tPFI_Filter_Select_t tPfiRegAccessor::genericFilterToChipFilterMap[kNumFilters] =
      { nPfiPorts::kNo_Filter, nPfiPorts::kSmall_Filter, nPfiPorts::kMedium_Filter, nPfiPorts::kLarge_Filter};

   tPfiRegAccessor::tPfiRegAccessor( tPfiPorts&       portsRef,
                                     tStc3PortNumber  pfiPortNumber,
                                     nMDBG::tStatus2& status ) :
      iRegAccessor(),
      _pfiPortsRef(portsRef),
      _pfiPortNumber(pfiPortNumber)
   {
      if (status.isFatal()) return;

      switch (_pfiPortNumber)
      {
      case kStc3Port0:
      case kStc3Port1:
         break;
      default:
         status.setCode(kStatusBadParameter);
         break;
      }

      _writePFIOutputSelect(0xFF, status, kTrue);
   }

   tPfiRegAccessor::~tPfiRegAccessor()
   {
   }

   tDigDataType tPfiRegAccessor::staticRead(nMDBG::tStatus2& status) const
   {
      tDigDataType readValue;

      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         readValue = _pfiPortsRef.Static_Digital_Input_Register.readPFI_StaticInputValue_Port0(&status);
         break;
      case kStc3Port1:
         readValue = _pfiPortsRef.Static_Digital_Input_Register.readPFI_StaticInputValue_Port1(&status);
         break;
      }

      return readValue;
   }

   void tPfiRegAccessor::staticWrite( tDigDataType     newValue,
                                      nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _pfiPortsRef.Static_Digital_Output_Register.writePFI_StaticOutputValue_Port0(newValue, &status);
         break;
      case kStc3Port1:
         _pfiPortsRef.Static_Digital_Output_Register.writePFI_StaticOutputValue_Port1(newValue, &status);
         break;
      }
   }

   void tPfiRegAccessor::staticDirection( tDigDataType     lineMask,
                                          nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _pfiPortsRef.PFI_Direction_Register.writePFIDirection_Port0(lineMask, &status);
         break;
      case kStc3Port1:
         _pfiPortsRef.PFI_Direction_Register.writePFIDirection_Port1(lineMask, &status);
         break;
      }
   }

   tBoolean tPfiRegAccessor::staticDirectionIsDirty() const
   {
      return _pfiPortsRef.PFI_Direction_Register.isDirty();
   }

   void tPfiRegAccessor::setSafeState( tDigDataType     safeState,
                                       nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _pfiPortsRef.PFI_WDT_SafeStateRegister.writePFI_WDT_SafeStateValue_Port0(safeState);
         break;
      case kStc3Port1:
         _pfiPortsRef.PFI_WDT_SafeStateRegister.writePFI_WDT_SafeStateValue_Port1(safeState);
         break;
      }
   }

   void tPfiRegAccessor::setWDTMode( tLine            line,
                                     tWDTMode         mode,
                                     nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _setWDTModePort0(line, mode, status);
         break;
      case kStc3Port1:
         _setWDTModePort1(line, mode, status);
         break;
      }
   }

   void tPfiRegAccessor::setFilterType ( tLine            line,
                                         tFilterType      filter,
                                         nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _setFilterTypePort0(line, filter, status);
         break;
      case kStc3Port1:
         _setFilterTypePort1(line, filter, status);
         break;
      }
   }

   // Set the lines that can cause a change detection event with a rising edge
   void tPfiRegAccessor::setREChangeDetection ( tDigDataType     mask,
                                                nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _pfiPortsRef.PFI_ChangeIrq_Register.writePFI_ChangeIrqRE_Port0(mask, &status);
         break;
      case kStc3Port1:
         _pfiPortsRef.PFI_ChangeIrq_Register.writePFI_ChangeIrqRE_Port1(mask, &status);
         break;
      }
   }

   // Set the lines that can cause a change detection event with a falling edge
   void tPfiRegAccessor::setFEChangeDetection ( tDigDataType     mask,
                                                nMDBG::tStatus2& status )
   {
      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         _pfiPortsRef.PFI_ChangeIrq_Register.writePFI_ChangeIrqFE_Port0(mask, &status);
         break;
      case kStc3Port1:
         _pfiPortsRef.PFI_ChangeIrq_Register.writePFI_ChangeIrqFE_Port1(mask, &status);
         break;
      }
   }

   // Get the port value latched at the last change detection event
   tDigDataType tPfiRegAccessor::getChangeDetectionLatchedValue(nMDBG::tStatus2& status) const
   {
      tDigDataType readValue;

      switch (_pfiPortNumber)
      {
      case kStc3Port0:
         readValue = _pfiPortsRef.PFI_ChangeDetectLatched_Register.readPFI_ChangeDetectLatched_Port0(&status);
         break;
      case kStc3Port1:
         readValue = _pfiPortsRef.PFI_ChangeDetectLatched_Register.readPFI_ChangeDetectLatched_Port1(&status);
         break;
      }

      return readValue;
   }

   void tPfiRegAccessor::_writePFIOutputSelect( tDigDataType     lineMask,
                                                nMDBG::tStatus2& status,
                                                tBoolean         force )
   {
      if (status.isFatal()) return;

      u16 pfiLineMask = (lineMask<<(_pfiPortNumber*kLinesPerPort));
      u32 pfiLineNum = 0;
      u32 currentBitMask = 1;
      for(; pfiLineNum < kPfiLinesPerStc3; ++pfiLineNum, currentBitMask <<= 1)
      {
         if (pfiLineMask & currentBitMask)
         {
            _pfiPortsRef.PFI_OutputSelectRegister_i[pfiLineNum].writePFI_i_Output_Select(nPfiPorts::kPFI_DO, &status, force);
         }
      }
   }

   void tPfiRegAccessor::_setWDTModePort0( tLine            line,
                                           tWDTMode         mode,
                                           nMDBG::tStatus2& status )
   {
      switch (line)
      {
      case kLine0:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line0(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine1:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line1(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine2:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line2(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine3:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line3(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine4:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line4(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine5:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line5(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine6:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line6(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine7:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort0_Line7(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      }
   }

   void tPfiRegAccessor::_setWDTModePort1( tLine            line,
                                           tWDTMode         mode,
                                           nMDBG::tStatus2& status )
   {
      switch (line)
      {
      case kLine0:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line0(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine1:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line1(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine2:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line2(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine3:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line3(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine4:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line4(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine5:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line5(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine6:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line6(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine7:
         _pfiPortsRef.PFI_WDT_ModeSelect_Register.writePFI_WDT_ModePort1_Line7(
            static_cast<nPfiPorts::tPFI_WDT_Mode_t>(mode),
            &status );
         break;
      }
   }

   void tPfiRegAccessor::_setFilterTypePort0( tLine            line,
                                              tFilterType      filter,
                                              nMDBG::tStatus2& status )
   {
      nPfiPorts::tPFI_Filter_Select_t chipFilter = genericFilterToChipFilterMap[filter];

      switch (line)
      {
      case kLine0:
         _pfiPortsRef.PFI_Filter_Register_Port0Lo.writePFI_Filter_Select_Port0_Line0(
            chipFilter,
            &status );
         break;
      case kLine1:
         _pfiPortsRef.PFI_Filter_Register_Port0Lo.writePFI_Filter_Select_Port0_Line1(
            chipFilter,
            &status );
         break;
      case kLine2:
         _pfiPortsRef.PFI_Filter_Register_Port0Lo.writePFI_Filter_Select_Port0_Line2(
            chipFilter,
            &status );
         break;
      case kLine3:
         _pfiPortsRef.PFI_Filter_Register_Port0Lo.writePFI_Filter_Select_Port0_Line3(
            chipFilter,
            &status );
         break;
      case kLine4:
         _pfiPortsRef.PFI_Filter_Register_Port0Hi.writePFI_Filter_Select_Port0_Line4(
            chipFilter,
            &status );
         break;
      case kLine5:
         _pfiPortsRef.PFI_Filter_Register_Port0Hi.writePFI_Filter_Select_Port0_Line5(
            chipFilter,
            &status );
         break;
      case kLine6:
         _pfiPortsRef.PFI_Filter_Register_Port0Hi.writePFI_Filter_Select_Port0_Line6(
            chipFilter,
            &status );
         break;
      case kLine7:
         _pfiPortsRef.PFI_Filter_Register_Port0Hi.writePFI_Filter_Select_Port0_Line7(
            chipFilter,
            &status );
         break;
      }
   }

   void tPfiRegAccessor::_setFilterTypePort1( tLine            line,
                                              tFilterType      filter,
                                              nMDBG::tStatus2& status )
   {
      nPfiPorts::tPFI_Filter_Select_t chipFilter = genericFilterToChipFilterMap[filter];

      switch (line)
      {
      case kLine0:
         _pfiPortsRef.PFI_Filter_Register_Port1Lo.writePFI_Filter_Select_Port1_Line0(
            chipFilter,
            &status );
         break;
      case kLine1:
         _pfiPortsRef.PFI_Filter_Register_Port1Lo.writePFI_Filter_Select_Port1_Line1(
            chipFilter,
            &status );
         break;
      case kLine2:
         _pfiPortsRef.PFI_Filter_Register_Port1Lo.writePFI_Filter_Select_Port1_Line2(
            chipFilter,
            &status );
         break;
      case kLine3:
         _pfiPortsRef.PFI_Filter_Register_Port1Lo.writePFI_Filter_Select_Port1_Line3(
            chipFilter,
            &status );
         break;
      case kLine4:
         _pfiPortsRef.PFI_Filter_Register_Port1Hi.writePFI_Filter_Select_Port1_Line4(
            chipFilter,
            &status );
         break;
      case kLine5:
         _pfiPortsRef.PFI_Filter_Register_Port1Hi.writePFI_Filter_Select_Port1_Line5(
            chipFilter,
            &status );
         break;
      case kLine6:
         _pfiPortsRef.PFI_Filter_Register_Port1Hi.writePFI_Filter_Select_Port1_Line6(
            chipFilter,
            &status );
         break;
      case kLine7:
         _pfiPortsRef.PFI_Filter_Register_Port1Hi.writePFI_Filter_Select_Port1_Line7(
            chipFilter,
            &status );
         break;
      }
   }
} // nNISTC3
