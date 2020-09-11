/*
 * eepromHelper.h
 *
 * Reads information from the EEPROM of the device.
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___eepromHelper_h___
#define ___eepromHelper_h___

#include <time.h>

#include "osiBus.h"
#include "tPortHelper.h"

// Forward declarations
class tPCIe6509;

namespace nNISTC3
{

   class eepromHelper
   {
   public:
      eepromHelper( tPCIe6509&         pcie6509,
                    const tDeviceInfo* deviceInfo,
                    nMDBG::tStatus2&   status );
      ~eepromHelper();

      u32 getSerialNumber() { return _serialNumber; }
      u32 getSTC3_Revision() { return _stc3Revision; }
      tBoolean getHasProgrammableResistors() { return _hasProgrammableResistors; }

      void getPowerUpStates(tMapIndex portNumber, tDigitalPowerupState& powerupState, nMDBG::tStatus2& status);
      void getPullDirection(tMapIndex portNumber, u8& pullDirection, nMDBG::tStatus2& status);

   private:
      static const u32 kCapabilitiesListFlagPtrOffset = 0x0C;
      static const u32 kCapabilitiesListAPtrOffset    = 0x10;
      static const u32 kCapabilitiesListBPtrOffset    = 0x14;

      static const u32 kASIC_RevisionID               = 0x0002;
      static const u32 kMasterPowerUpPort0ID          = 0x0010;
      static const u32 kMasterPowerUpPort1and2ID      = 0x0011;
      static const u32 kMasterPullDirectionID         = 0x0012;
      static const u32 kSlavePowerUpPort0ID           = 0x0020;
      static const u32 kSlavePowerUpPort1and2ID       = 0x0021;
      static const u32 kSlavePullDirectionID          = 0x0022;

      static const u32 kSerialNumberNodeID            = 0x0004;
      static const u32 kSerialNumberOffset            = 0x4;

      static const u32 kDeviceSpecificNodeID          = 0x0001;
      static const u32 kDSNSizeOffset                 = 0x4;
      static const u32 kDSNBodyFormatOffset           = 0x8;
      static const u32 kDSNBodyFormat16BitValueID     = 0x1;
      static const u32 kDSNBodyFormat32BitValueID     = 0x2;
      static const u32 kDSNBodyFormat16BitIDValue     = 0x3;
      static const u32 kDSNBodyFormat32BitIDValue     = 0x4;
      static const u32 kDSNBodyOffset                 = 0xC;

      static const u32 kPortsPerStc3                  = 6;
      static const u32 kMasterIndex                   = 0;
      static const u32 kSlaveIndex                    = 1;

      static const u32 kBitsPerByte                   = 8;

      static tPCIe6509Port _createPort( tStc3Configuration configuration,
                                        tPortType          portType,
                                        tStc3PortNumber    portNumber );

      void _traverseCapabilitiesList(u32 nodeAddress, nMDBG::tStatus2& status);
      void _parseSerialNumberNode(u32 nodeAddress, nMDBG::tStatus2& status);
      void _parseDeviceSpecificNode(u32 nodeAddress, nMDBG::tStatus2& status);

      u8   _readU8(u32 address);
      u16  _readU16(u32 address);
      u32  _readU32(u32 address);

      // Static information
      tBusSpaceReference _eeprom;
      tPCIe6509&         _pcie6509;
      u32                _baseAddress;
      u32                _numberOfPorts;

      u32 _serialNumber;
      u32 _stc3Revision;

      tDigitalPowerupState* _powerupState;
      u8*                   _pullDirection;
      tBoolean              _hasProgrammableResistors;

      const tDeviceInfo*    _deviceInfo;

      // Usage guidelines
      eepromHelper(const eepromHelper&);
      eepromHelper& operator=(const eepromHelper&);
   };
}

#endif // ___eepromHelper_h___
