/*
 * eepromHelper.cpp
 *
 * Reads information from the EEPROM of the device.
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "eepromHelper.h"

// Chip Objects
#include "tPCIe6509.h"

namespace nNISTC3
{

   eepromHelper::eepromHelper( tPCIe6509&         pcie6509,
                               const tDeviceInfo* deviceInfo,
                               nMDBG::tStatus2&   status ) :
      _eeprom(pcie6509.getBusSpaceReference() + nCHInCh::kEEPROMOffset),
      _pcie6509(pcie6509),
      _numberOfPorts(deviceInfo->numPorts),
      _baseAddress(0),
      _serialNumber(0),
      _stc3Revision(0),
      _powerupState(NULL),
      _pullDirection(NULL),
      _hasProgrammableResistors(kFalse),
      _deviceInfo(deviceInfo)
   {
      u32 capabilitiesListFlagPtr = _readU32(kCapabilitiesListFlagPtrOffset);
      u32 capabilitiesListFlag = _readU32(capabilitiesListFlagPtr);
      u32 capabilitiesListOffset = 0;
      if (capabilitiesListFlag & 0x1)
      {
         capabilitiesListOffset = _readU32(kCapabilitiesListBPtrOffset);
      }
      else
      {
         capabilitiesListOffset = _readU32(kCapabilitiesListAPtrOffset);
      }

      _powerupState = new tDigitalPowerupState[_numberOfPorts];
      _pullDirection = new u8[_numberOfPorts];
      _traverseCapabilitiesList(capabilitiesListOffset, status);
   }

   eepromHelper::~eepromHelper()
   {
      delete[] _powerupState;
      _powerupState = NULL;

      delete[] _pullDirection;
      _pullDirection = NULL;
   }

   tPCIe6509Port eepromHelper::_createPort( tStc3Configuration configuration,
                                            tPortType          portType,
                                            tStc3PortNumber    portNumber )
   {
      tPCIe6509Port returnValue;

      returnValue.stc3Configuration = configuration;
      returnValue.portType = portType;
      returnValue.stc3PortNumber = portNumber;

      return returnValue;
   }

   void eepromHelper::getPowerUpStates(tMapIndex portNumber, tDigitalPowerupState& powerupState, nMDBG::tStatus2& status)
   {
      if (portNumber < _numberOfPorts)
      {
         powerupState = _powerupState[portNumber];
      }
      else
      {
         status.setCode(kStatusBadSelector);
      }
   }

   void eepromHelper::getPullDirection(tMapIndex portNumber, u8& pullDirection, nMDBG::tStatus2& status)
   {
      if (portNumber < _numberOfPorts)
      {
         if (_hasProgrammableResistors)
         {
            pullDirection = _pullDirection[portNumber];
         }
      }
      else
      {
         status.setCode(kStatusBadSelector);
      }
   }

   void eepromHelper::_traverseCapabilitiesList(u32 nodeAddress, nMDBG::tStatus2& status)
   {
      u16 nextNodeAddress = 0;
      u16 currentNodeId = 0;

      while (nodeAddress != 0)
      {
         nextNodeAddress = _readU16(nodeAddress);
         currentNodeId = _readU16(nodeAddress + 2);

         switch (currentNodeId)
         {
            case kSerialNumberNodeID:
               _parseSerialNumberNode(nodeAddress, status);
               break;
            case kDeviceSpecificNodeID:
               _parseDeviceSpecificNode(nodeAddress, status);
               break;
            // Don't know what this is, just ignore it.
         }

         // Otherwise, keep going.  The last two bits of the next node ptr are
         // used to indicate whether the address read is absolute or relative.
         const u32 addressOptions = nextNodeAddress & 0x3;
         nextNodeAddress &= 0xFFFC;

         switch(addressOptions)
         {
            case 0:
               // Address is a 16-bit, absolute address.
               nodeAddress = nextNodeAddress;
               break;
            case 2:
               // Address is a 16-bit, relative address. The pointer is realive from the start of
               // the current node.
               nodeAddress += nextNodeAddress;
               break;
            default:
               // This should never happen (we do not support 32 bit addressing (relative = 1))
               status.setCode(kStatusBadSelector);
               return;
         }
      }
   }

   void eepromHelper::_parseSerialNumberNode(u32 nodeAddress, nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);

      _serialNumber = _readU32(nodeAddress + kSerialNumberOffset);
   }

   void eepromHelper::_parseDeviceSpecificNode(u32 nodeAddress, nMDBG::tStatus2& status)
   {
      u32 dsnSize = _readU32(nodeAddress + kDSNSizeOffset);
      u32 dsnBodyFormat = _readU32(nodeAddress + kDSNBodyFormatOffset);
      // size includes the format and the trailing CRC
      u32 dsnBodySize = dsnSize - 2*sizeof(u32);

      for (u32 i=0; i<dsnBodySize;)
      {
         u32 value = 0;
         u32 id = 0;
         switch (dsnBodyFormat)
         {
            case kDSNBodyFormat16BitValueID:
               value = _readU16(nodeAddress + kDSNBodyOffset + i);
               id = _readU16(nodeAddress + kDSNBodyOffset + i + sizeof(u16));
               i += 2 * sizeof(u16);
               break;
            case kDSNBodyFormat32BitValueID:
               value = _readU32(nodeAddress + kDSNBodyOffset + i);
               id = _readU32(nodeAddress + kDSNBodyOffset + i + sizeof(u32));
               i += 2 * sizeof(u32);
               break;
            case kDSNBodyFormat16BitIDValue:
               id = _readU16(nodeAddress + kDSNBodyOffset + i);
               value = _readU16(nodeAddress + kDSNBodyOffset + i + sizeof(u16));
               i += 2 * sizeof(u16);
               break;
            case kDSNBodyFormat32BitIDValue:
               id = _readU32(nodeAddress + kDSNBodyOffset + i);
               value = _readU32(nodeAddress + kDSNBodyOffset + i + sizeof(u32));
               i += 2 * sizeof(u32);
               break;
            default:
               //This should never happen
               status.setCode(kStatusBadSelector);
               return;
         }

         u32 portOffset;

         u32 output;
         u32 highImpedanceMask;

         switch (id)
         {
            case kASIC_RevisionID:
               _stc3Revision = value;
               break;
            case kMasterPowerUpPort0ID:
               portOffset = _deviceInfo->getPortNumber(_createPort(kStc3Master, kDIO_Port, kStc3Port0), status);

               output = _readU32(value);
               highImpedanceMask = _readU32(value + sizeof(u32));
               for (u32 i = 0; i < sizeof(u32); ++i)
               {
                  _powerupState[i + portOffset].outputValue = (output>>(i*kBitsPerByte) & 0xff);
                  // High Impedance is inverted from the contents of the EEPROM
                  _powerupState[i + portOffset].highImp = ~(highImpedanceMask>>(i*kBitsPerByte) & 0xff);
               }
               break;
            case kMasterPowerUpPort1and2ID:
               portOffset = portOffset = _deviceInfo->getPortNumber(_createPort(kStc3Master, kPFI_Port, kStc3Port0), status);

               output = _readU16(value);
               highImpedanceMask = _readU16(value + sizeof(u16));
               for (u32 i = 0; i < sizeof(u16); ++i)
               {
                  _powerupState[i + portOffset].outputValue = (output>>(i*kBitsPerByte) & 0xff);
                  // High Impedance is inverted from the contents of the EEPROM
                  _powerupState[i + portOffset].highImp = ~(highImpedanceMask>>(i*kBitsPerByte) & 0xff);
               }
               break;
            case kMasterPullDirectionID:
               _hasProgrammableResistors = kTrue;
               for (u32 pulldown = 0; pulldown < kPortsPerStc3; ++pulldown)
               {
                  _pullDirection[pulldown + kMasterIndex*kPortsPerStc3] = _readU8(value + pulldown);
               }
               break;
            case kSlavePowerUpPort0ID:
               portOffset = portOffset = _deviceInfo->getPortNumber(_createPort(kStc3Slave, kDIO_Port, kStc3Port0), status);;

               output = _readU32(value);
               highImpedanceMask = _readU32(value + sizeof(u32));
               for (u32 i = 0; i < sizeof(u32); ++i)
               {
                  _powerupState[i + portOffset].outputValue = (output>>(i*kBitsPerByte) & 0xff);
                  // High Impedance is inverted from the contents of the EEPROM
                  _powerupState[i + portOffset].highImp = ~(highImpedanceMask>>(i*kBitsPerByte) & 0xff);
               }
               break;
            case kSlavePowerUpPort1and2ID:
               portOffset = portOffset = _deviceInfo->getPortNumber(_createPort(kStc3Slave, kPFI_Port, kStc3Port0), status);

               output = _readU16(value);
               highImpedanceMask = _readU16(value + sizeof(u16));
               for (u32 i = 0; i < sizeof(u16); ++i)
               {
                  _powerupState[i + portOffset].outputValue = (output>>(i*kBitsPerByte) & 0xff);
                  // High Impedance is inverted from the contents of the EEPROM
                  _powerupState[i + portOffset].highImp = ~(highImpedanceMask>>(i*kBitsPerByte) & 0xff);
               }
               break;
            case kSlavePullDirectionID:
               _hasProgrammableResistors = kTrue;
               for (u32 pulldown = 0; pulldown < kPortsPerStc3; ++pulldown)
               {
                  _pullDirection[pulldown + kSlaveIndex*kPortsPerStc3] = _readU8(value + pulldown);
               }
               break;
            // Don't know what this is, just ignore it.
         }
      }
   }

   u8 eepromHelper::_readU8(u32 address)
   {
      return _eeprom.read8(address - _baseAddress);
   }

   u16 eepromHelper::_readU16(u32 address)
   {
      return _eeprom.read16(address - _baseAddress);
   }

   u32 eepromHelper::_readU32(u32 address)
   {
      return _eeprom.read32(address - _baseAddress);
   }
} // nNISTC3
