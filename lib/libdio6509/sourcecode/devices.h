/*
 * devices.h
 *
 * Given a PCIe-6509, find the information we care about for it.
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___devices_h___
#define ___devices_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// Forward declarations
class tPCIe6509;

namespace nNISTC3
{
   typedef enum
   {
      kStc3Master,
      kStc3Slave,
   } tStc3Configuration;

   typedef enum
   {
      kDIO_Port,
      kPFI_Port,
   } tPortType;

   typedef enum
   {
      kStc3Port0 = 0,
      kStc3Port1 = 1,
      kStc3Port2 = 2,
      kStc3Port3 = 3,
   }  tStc3PortNumber;

   typedef struct
   {
      tStc3Configuration stc3Configuration;
      tPortType          portType;
      tStc3PortNumber    stc3PortNumber;
   } tPCIe6509Port;

   typedef enum
   {
      kMapIndexPort0 = 0,
      kMapIndexPort1,
      kMapIndexPort2,
      kMapIndexPort3,
      kMapIndexPort4,
      kMapIndexPort5,
      kMapIndexPort6,
      kMapIndexPort7,
      kMapIndexPort8,
      kMapIndexPort9,
      kMapIndexPort10,
      kMapIndexPort11,
   } tMapIndex;

   struct tDeviceInfo
   {
      const tPCIe6509Port* getPCIe6509Port(tMapIndex pcie6509Port, nMDBG::tStatus2& status) const;
      tMapIndex getPortNumber(const tPCIe6509Port& pcie6509, nMDBG::tStatus2& status) const;

      u32 productID;
      const char* deviceName;
      u32 numPorts;
      const tPCIe6509Port** tPCIe6509PortMap;
   };

   const tDeviceInfo* getDeviceInfo(tPCIe6509& pcie6509, nMDBG::tStatus2& status);
}

#endif // ___devices_h___
