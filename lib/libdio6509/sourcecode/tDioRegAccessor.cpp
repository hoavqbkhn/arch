/*
 * tDioRegAccessor.cpp
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "tDioRegAccessor.h"

namespace nNISTC3
{
   nDioPorts::tDI_Filter_Select_t tDioRegAccessor::genericFilterToChipFilterMap[kNumFilters] =
      { nDioPorts::kNo_Filter, nDioPorts::kSmall_Filter, nDioPorts::kMedium_Filter, nDioPorts::kLarge_Filter};

   tDioRegAccessor::tDioRegAccessor( tDioPorts&       portsRef,
                                     tStc3PortNumber  dioPortNumber,
                                     nMDBG::tStatus2& status ) :
      iRegAccessor(),
      _dioPortsRef(portsRef),
      _dioPortNumber(dioPortNumber)
   {
      if (status.isFatal()) return;
   }

   tDioRegAccessor::~tDioRegAccessor()
   {
   }

   tDigDataType tDioRegAccessor::staticRead(nMDBG::tStatus2& status) const
   {
      tDigDataType readValue;

      switch (_dioPortNumber)
      {
      case kStc3Port0:
         readValue = _dioPortsRef.Static_Digital_Input_Register.readDIO_StaticInputValue_Port0(&status);
         break;
      case kStc3Port1:
         readValue = _dioPortsRef.Static_Digital_Input_Register.readDIO_StaticInputValue_Port1(&status);
         break;
      case kStc3Port2:
         readValue = _dioPortsRef.Static_Digital_Input_Register.readDIO_StaticInputValue_Port2(&status);
         break;
      case kStc3Port3:
         readValue = _dioPortsRef.Static_Digital_Input_Register.readDIO_StaticInputValue_Port3(&status);
         break;
      }

      return readValue;
   }

   void tDioRegAccessor::staticWrite( tDigDataType     newValue,
                                      nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _dioPortsRef.Static_Digital_Output_Register.writeDIO_StaticOutputValue_Port0(newValue, &status);
         break;
      case kStc3Port1:
         _dioPortsRef.Static_Digital_Output_Register.writeDIO_StaticOutputValue_Port1(newValue, &status);
         break;
      case kStc3Port2:
         _dioPortsRef.Static_Digital_Output_Register.writeDIO_StaticOutputValue_Port2(newValue, &status);
         break;
      case kStc3Port3:
         _dioPortsRef.Static_Digital_Output_Register.writeDIO_StaticOutputValue_Port3(newValue, &status);
         break;
      }
   }

   void tDioRegAccessor::staticDirection( tDigDataType     lineMask,
                                          nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _dioPortsRef.DIO_Direction_Register.writeDIODirection_Port0(lineMask, &status);
         break;
      case kStc3Port1:
         _dioPortsRef.DIO_Direction_Register.writeDIODirection_Port1(lineMask, &status);
         break;
      case kStc3Port2:
         _dioPortsRef.DIO_Direction_Register.writeDIODirection_Port2(lineMask, &status);
         break;
      case kStc3Port3:
         _dioPortsRef.DIO_Direction_Register.writeDIODirection_Port3(lineMask, &status);
         break;
      }
   }

   tBoolean tDioRegAccessor::staticDirectionIsDirty() const
   {
      return _dioPortsRef.DIO_Direction_Register.isDirty();
   }

   void tDioRegAccessor::setSafeState( tDigDataType     safeState,
                                       nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _dioPortsRef.DO_WDT_SafeStateRegister.writeDO_WDT_SafeStateValue_Port0(safeState);
         break;
      case kStc3Port1:
         _dioPortsRef.DO_WDT_SafeStateRegister.writeDO_WDT_SafeStateValue_Port1(safeState);
         break;
      case kStc3Port2:
         _dioPortsRef.DO_WDT_SafeStateRegister.writeDO_WDT_SafeStateValue_Port2(safeState);
         break;
      case kStc3Port3:
         _dioPortsRef.DO_WDT_SafeStateRegister.writeDO_WDT_SafeStateValue_Port3(safeState);
         break;
      default:
         break;
      }
   }

   void tDioRegAccessor::setWDTMode( tLine            line,
                                     tWDTMode         mode,
                                     nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _setWDTModePort0(line, mode, status);
         break;
      case kStc3Port1:
         _setWDTModePort1(line, mode, status);
         break;
      case kStc3Port2:
         _setWDTModePort2(line, mode, status);
         break;
      case kStc3Port3:
         _setWDTModePort3(line, mode, status);
         break;
      }
   }

   void tDioRegAccessor::setFilterType ( tLine            line,
                                         tFilterType      filter,
                                         nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _setFilterTypePort0(line, filter, status);
         break;
      case kStc3Port1:
         _setFilterTypePort1(line, filter, status);
         break;
      case kStc3Port2:
         _setFilterTypePort2(line, filter, status);
         break;
      case kStc3Port3:
         _setFilterTypePort3(line, filter, status);
         break;
      }
   }

   // Set the lines that can cause a change detection event with a rising edge
   void tDioRegAccessor::setREChangeDetection ( tDigDataType     mask,
                                                nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _dioPortsRef.DI_ChangeIrqRE_Register.writeDI_ChangeIrqRE_Port0(mask, &status);
         break;
      case kStc3Port1:
         _dioPortsRef.DI_ChangeIrqRE_Register.writeDI_ChangeIrqRE_Port1(mask, &status);
         break;
      case kStc3Port2:
         _dioPortsRef.DI_ChangeIrqRE_Register.writeDI_ChangeIrqRE_Port2(mask, &status);
         break;
      case kStc3Port3:
         _dioPortsRef.DI_ChangeIrqRE_Register.writeDI_ChangeIrqRE_Port3(mask, &status);
         break;
      }
   }

   // Set the lines that can cause a change detection event with a falling edge
   void tDioRegAccessor::setFEChangeDetection ( tDigDataType     mask,
                                                nMDBG::tStatus2& status )
   {
      switch (_dioPortNumber)
      {
      case kStc3Port0:
         _dioPortsRef.DI_ChangeIrqFE_Register.writeDI_ChangeIrqFE_Port0(mask, &status);
         break;
      case kStc3Port1:
         _dioPortsRef.DI_ChangeIrqFE_Register.writeDI_ChangeIrqFE_Port1(mask, &status);
         break;
      case kStc3Port2:
         _dioPortsRef.DI_ChangeIrqFE_Register.writeDI_ChangeIrqFE_Port2(mask, &status);
         break;
      case kStc3Port3:
         _dioPortsRef.DI_ChangeIrqFE_Register.writeDI_ChangeIrqFE_Port3(mask, &status);
         break;
      }
   }

   // Get the port value latched at the last change detection event
   tDigDataType tDioRegAccessor::getChangeDetectionLatchedValue(nMDBG::tStatus2& status) const
   {
      tDigDataType readValue;

      switch (_dioPortNumber)
      {
      case kStc3Port0:
         readValue = _dioPortsRef.DI_ChangeDetectLatched_Register.readDI_ChangeDetectLatched_Port0(&status);
         break;
      case kStc3Port1:
         readValue = _dioPortsRef.DI_ChangeDetectLatched_Register.readDI_ChangeDetectLatched_Port1(&status);
         break;
      case kStc3Port2:
         readValue = _dioPortsRef.DI_ChangeDetectLatched_Register.readDI_ChangeDetectLatched_Port2(&status);
         break;
      case kStc3Port3:
         readValue = _dioPortsRef.DI_ChangeDetectLatched_Register.readDI_ChangeDetectLatched_Port3(&status);
         break;
      }

      return readValue;
   }

   void tDioRegAccessor::_setWDTModePort0( tLine            line,
                                           tWDTMode         mode,
                                           nMDBG::tStatus2& status )
   {
      switch (line)
      {
      case kLine0:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line0(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine1:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line1(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine2:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line2(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine3:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line3(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine4:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line4(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine5:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line5(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine6:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line6(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine7:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort0_Line7(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setWDTModePort1( tLine            line,
                                           tWDTMode         mode,
                                           nMDBG::tStatus2& status )
   {
      switch (line)
      {
      case kLine0:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line0(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine1:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line1(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine2:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line2(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine3:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line3(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine4:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line4(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine5:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line5(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine6:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line6(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine7:
         _dioPortsRef.DO_WDT_ModeSelect_Port0and1_Register.writeDO_WDT_ModePort1_Line7(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setWDTModePort2( tLine            line,
                                           tWDTMode         mode,
                                           nMDBG::tStatus2& status )
   {
      switch (line)
      {
      case kLine0:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line0(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine1:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line1(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine2:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line2(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine3:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line3(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine4:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line4(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine5:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line5(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine6:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line6(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine7:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort2_Line7(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setWDTModePort3( tLine            line,
                                           tWDTMode         mode,
                                           nMDBG::tStatus2& status )
   {
      switch (line)
      {
      case kLine0:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line0(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine1:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line1(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine2:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line2(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine3:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line3(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine4:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line4(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine5:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line5(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine6:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line6(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      case kLine7:
         _dioPortsRef.DO_WDT_ModeSelect_Port2and3_Register.writeDO_WDT_ModePort3_Line7(
            static_cast<nDioPorts::tDO_WDT_Mode_t>(mode),
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setFilterTypePort0( tLine            line,
                                              tFilterType      filter,
                                              nMDBG::tStatus2& status )
   {
      nDioPorts::tDI_Filter_Select_t chipFilter = genericFilterToChipFilterMap[filter];

      switch (line)
      {
      case kLine0:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line0(
            chipFilter,
            &status );
         break;
      case kLine1:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line1(
            chipFilter,
            &status );
         break;
      case kLine2:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line2(
            chipFilter,
            &status );
         break;
      case kLine3:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line3(
            chipFilter,
            &status );
         break;
      case kLine4:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line4(
            chipFilter,
            &status );
         break;
      case kLine5:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line5(
            chipFilter,
            &status );
         break;
      case kLine6:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line6(
            chipFilter,
            &status );
         break;
      case kLine7:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port0_Line7(
            chipFilter,
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setFilterTypePort1( tLine            line,
                                              tFilterType      filter,
                                              nMDBG::tStatus2& status )
   {
      nDioPorts::tDI_Filter_Select_t chipFilter = genericFilterToChipFilterMap[filter];

      switch (line)
      {
      case kLine0:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line0(
            chipFilter,
            &status );
         break;
      case kLine1:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line1(
            chipFilter,
            &status );
         break;
      case kLine2:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line2(
            chipFilter,
            &status );
         break;
      case kLine3:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line3(
            chipFilter,
            &status );
         break;
      case kLine4:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line4(
            chipFilter,
            &status );
         break;
      case kLine5:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line5(
            chipFilter,
            &status );
         break;
      case kLine6:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line6(
            chipFilter,
            &status );
         break;
      case kLine7:
         _dioPortsRef.DI_FilterRegister_Port0and1.writeDI_Filter_Select_Port1_Line7(
            chipFilter,
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setFilterTypePort2( tLine            line,
                                              tFilterType      filter,
                                              nMDBG::tStatus2& status )
   {
      nDioPorts::tDI_Filter_Select_t chipFilter = genericFilterToChipFilterMap[filter];

      switch (line)
      {
      case kLine0:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line0(
            chipFilter,
            &status );
         break;
      case kLine1:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line1(
            chipFilter,
            &status );
         break;
      case kLine2:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line2(
            chipFilter,
            &status );
         break;
      case kLine3:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line3(
            chipFilter,
            &status );
         break;
      case kLine4:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line4(
            chipFilter,
            &status );
         break;
      case kLine5:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line5(
            chipFilter,
            &status );
         break;
      case kLine6:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line6(
            chipFilter,
            &status );
         break;
      case kLine7:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port2_Line7(
            chipFilter,
            &status );
         break;
      }
   }

   void tDioRegAccessor::_setFilterTypePort3( tLine            line,
                                              tFilterType      filter,
                                              nMDBG::tStatus2& status )
   {
      nDioPorts::tDI_Filter_Select_t chipFilter = genericFilterToChipFilterMap[filter];

      switch (line)
      {
      case kLine0:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line0(
            chipFilter,
            &status );
         break;
      case kLine1:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line1(
            chipFilter,
            &status );
         break;
      case kLine2:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line2(
            chipFilter,
            &status );
         break;
      case kLine3:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line3(
            chipFilter,
            &status );
         break;
      case kLine4:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line4(
            chipFilter,
            &status );
         break;
      case kLine5:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line5(
            chipFilter,
            &status );
         break;
      case kLine6:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line6(
            chipFilter,
            &status );
         break;
      case kLine7:
         _dioPortsRef.DI_FilterRegister_Port2and3.writeDI_Filter_Select_Port3_Line7(
            chipFilter,
            &status );
         break;
      }
   }
} // nNISTC3
