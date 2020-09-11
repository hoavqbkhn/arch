/*
 * tPortHelperFactory.cpp
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "tPortHelperFactory.h"

// Chip Objects
#include "tPCIe6509.h"
#include "tPfiRegAccessor.h"
#include "tDioRegAccessor.h"

namespace nNISTC3
{
   tPortHelperFactory::tPortHelperFactory( tPCIe6509&         device,
                                           const tDeviceInfo* deviceInfo,
                                           nMDBG::tStatus2&   status )
   {
      if (status.isFatal()) return;

      tChipObjectConfiguration dioLo(_createChipObjectConfiguration(kStc3Master, &device.StaticDio.DioPortsLo, &device.StaticDio.PfiPortsLo));
      tChipObjectConfiguration dioHi(_createChipObjectConfiguration(kStc3Slave,  &device.StaticDio.DioPortsHi, &device.StaticDio.PfiPortsHi));

      // Construct the chip object map from the private members that were initialized
      std::vector<tChipObjectConfiguration> chipObjectMap;
      chipObjectMap.reserve(numChipObjectConfigurations);
      chipObjectMap.push_back(dioLo);
      chipObjectMap.push_back(dioHi);

      _regAccessor.reserve(deviceInfo->numPorts);
      _portHelper.reserve(deviceInfo->numPorts);

      u32 portMapIterator;

      for( portMapIterator = kMapIndexPort0; portMapIterator < deviceInfo->numPorts; ++portMapIterator )
      {
         // Use the deviceInfo to get the port information
         const nNISTC3::tPCIe6509Port* portInfo = deviceInfo->getPCIe6509Port(
            static_cast<nNISTC3::tMapIndex>(portMapIterator),
            status);

         // Cycle through the chip object map to find a chip object that meets this port's STC3 configuration
         std::vector<tChipObjectConfiguration>::const_iterator chipObjectIterator = chipObjectMap.begin();
         for( ; chipObjectIterator != chipObjectMap.end(); ++chipObjectIterator )
         {
            if (portInfo->stc3Configuration == chipObjectIterator->stc3Configuration)
            {
               switch (portInfo->portType)
               {
               case kDIO_Port:
                  {
                     _regAccessor.push_back(
                        new tDioRegAccessor(*chipObjectIterator->dioPorts, portInfo->stc3PortNumber, status) );
                  }
                  break;
               case kPFI_Port:
                  {
                     _regAccessor.push_back(
                        new tPfiRegAccessor(*chipObjectIterator->pfiPorts, portInfo->stc3PortNumber, status) );
                  }
                  break;
               default:
                  {
                     status.setCode(kStatusUnknownDevice);
                     return;
                  }
                  break;
               }
               break;
            }
         }

         if (chipObjectIterator == chipObjectMap.end())
         {
            // The port helper factory does not support the requested board
            status.setCode(kStatusUnknownDevice);
            return;
         }

         _portHelper.push_back( new tPortHelper(*_regAccessor.back(), status) );
      }
   }

   tPortHelperFactory::~tPortHelperFactory()
   {
      if( !_regAccessor.empty() )
      {
         std::vector<tPortHelper*>::iterator portHelperIterator = _portHelper.begin();
         for( ; portHelperIterator != _portHelper.end(); ++portHelperIterator )
         {
            tPortHelper* temp = *portHelperIterator;
            delete temp;
         }
         _portHelper.clear();

         std::vector<iRegAccessor*>::iterator regAccessorIterator = _regAccessor.begin();
         for( ; regAccessorIterator != _regAccessor.end(); ++regAccessorIterator )
         {
            iRegAccessor* temp = *regAccessorIterator;
            delete temp;
         }
         _regAccessor.clear();
      }
   }

   tPortHelper* tPortHelperFactory::getPortHelper( tMapIndex        portMapIndex,
                                                   nMDBG::tStatus2& status )
   {
      return _portHelper[portMapIndex];
   }

   tPortHelperFactory::tChipObjectConfiguration
      tPortHelperFactory::_createChipObjectConfiguration( tStc3Configuration arg_Stc3Configuration,
                                                          tDioPorts*         arg_DioPorts,
                                                          tPfiPorts*         arg_PfiPorts )
   {
      tChipObjectConfiguration retVal;
      retVal.stc3Configuration = arg_Stc3Configuration;
      retVal.dioPorts = arg_DioPorts;
      retVal.pfiPorts = arg_PfiPorts;

      return retVal;
   }

}
