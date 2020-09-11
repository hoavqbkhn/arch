/*
 * devices.cpp
 *
 * Given bar0 of a PCIe-6509, find the information we care about for it.
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "devices.h"

// Chip Objects
#include "tPCIe6509.h"

namespace nNISTC3
{
   static const tPCIe6509Port kPCIe6509Port0  = {kStc3Master, kDIO_Port, kStc3Port0};
   static const tPCIe6509Port kPCIe6509Port1  = {kStc3Master, kDIO_Port, kStc3Port1};
   static const tPCIe6509Port kPCIe6509Port2  = {kStc3Master, kDIO_Port, kStc3Port2};
   static const tPCIe6509Port kPCIe6509Port3  = {kStc3Master, kDIO_Port, kStc3Port3};
   static const tPCIe6509Port kPCIe6509Port4  = {kStc3Master, kPFI_Port, kStc3Port0};
   static const tPCIe6509Port kPCIe6509Port5  = {kStc3Master, kPFI_Port, kStc3Port1};
   static const tPCIe6509Port kPCIe6509Port6  = {kStc3Slave,  kPFI_Port, kStc3Port0};
   static const tPCIe6509Port kPCIe6509Port7  = {kStc3Slave,  kPFI_Port, kStc3Port1};
   static const tPCIe6509Port kPCIe6509Port8  = {kStc3Slave,  kDIO_Port, kStc3Port0};
   static const tPCIe6509Port kPCIe6509Port9  = {kStc3Slave,  kDIO_Port, kStc3Port1};
   static const tPCIe6509Port kPCIe6509Port10 = {kStc3Slave,  kDIO_Port, kStc3Port2};
   static const tPCIe6509Port kPCIe6509Port11 = {kStc3Slave,  kDIO_Port, kStc3Port3};

   static const tPCIe6509Port* kPCIe6509Map[] = {
      &kPCIe6509Port0,
      &kPCIe6509Port1,
      &kPCIe6509Port2,
      &kPCIe6509Port3,
      &kPCIe6509Port4,
      &kPCIe6509Port5,
      &kPCIe6509Port6,
      &kPCIe6509Port7,
      &kPCIe6509Port8,
      &kPCIe6509Port9,
      &kPCIe6509Port10,
      &kPCIe6509Port11};

   static const tDeviceInfo kDevices[] = {
      { 0x7326, "PCIe-6509", 12, kPCIe6509Map },
   };
   static const u32 kNumberOfDevices = sizeof(kDevices) / sizeof(kDevices[0]);

   const tPCIe6509Port* tDeviceInfo::getPCIe6509Port(tMapIndex pcie6509Port, nMDBG::tStatus2& status) const
   {
      if (status.isFatal()) return NULL;

      return tPCIe6509PortMap[pcie6509Port];
   }

   tMapIndex tDeviceInfo::getPortNumber(const tPCIe6509Port& pcie6509Port, nMDBG::tStatus2& status) const
   {
      if (status.isFatal()) return kMapIndexPort0;

      for (u32 port = kMapIndexPort0; port < numPorts; ++port)
      {
         if ( pcie6509Port.stc3Configuration == tPCIe6509PortMap[port]->stc3Configuration
              && pcie6509Port.portType == tPCIe6509PortMap[port]->portType
              && pcie6509Port.stc3PortNumber == tPCIe6509PortMap[port]->stc3PortNumber )
         {
            return static_cast<tMapIndex>(port);
         }
      }

      status.setCode(kStatusBadSelector);
      return kMapIndexPort0;
   }

   const tDeviceInfo* getDeviceInfo(tPCIe6509& pcie6509, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return NULL;

      // Read the CHInCh signature register
      u32 CHInChSig = pcie6509.CHInCh.CHInCh_Identification_Register.readRegister(&status);
      if (CHInChSig != nCHInCh::kCHInChSignature)
      {
         // Device does not have a CHInCh
         status.setCode(kStatusUnknownCHInCh);
      }

      // Read the STC3 signature register
      u32 STC3Signature = pcie6509.ChpServicesLo.Signature_Register.readRegister(&status);
      if (STC3Signature != nChpServices::kSTC3_RevASignature && STC3Signature != nChpServices::kSTC3_RevBSignature)
      {
         // Device does not have an STC3
         status.setCode(kStatusUnknownSTC3);
      }

      u32 productID = pcie6509.CHInCh.PCI_SubSystem_ID_Access_Register.readSubSystem_Product_ID(&status);

      for (u32 i=0; i<kNumberOfDevices; ++i)
      {
         if (kDevices[i].productID == productID)
         {
            return &kDevices[i];
         }
      }

      status.setCode(kStatusUnknownDevice);
      return NULL;
   }
}
