/*
 * dataHelper.cpp
 *
 * Generate and print device data.
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include <stdio.h>

#include "dataHelper.h"

namespace nNISTC3
{
   void printHeaderPad(const char* label)
   {
      printf("%-12s     ", label);
   }

   void printHeader( u32         numPorts,
                     const char* label,
                     const char* subsystem )
   {
      printHeaderPad(label);

      for (u32 k=0; k<numPorts; ++k)
      {
         printf(" %2s%-2u", subsystem, k);
      }
   }

   namespace nDIODataHelper
   {
      void printHeader( u32          numPorts,
                        const char*  label )
      {
         nNISTC3::printHeader(numPorts, label, "port");
      }

      void generateSignal( tSignalType      signalType,
                           u8               minValue,
                           u8               maxValue,
                           std::vector<u8>& signalData,
                           u32              signalDataLength )
      {
         if (signalData.size() < signalDataLength)
         {
            signalData.resize(signalDataLength);
         }

         u8 value;
         u8 amplitude = maxValue - minValue;
         const u32 halfLength = signalDataLength/2;

         for (u32 dataPoint=0; dataPoint<signalDataLength; ++dataPoint)
         {
            switch (signalType)
            {
            case kSquarePattern:
               value = minValue + (dataPoint/halfLength)*(amplitude);
               break;
            case kTrianglePattern:
               {
                  if (dataPoint < halfLength)
                  {
                     // Algebra line equation in slope-intercept form
                     value = minValue + (amplitude*dataPoint)/halfLength;
                  }
                  else
                  {
                     // Algebra line equation in slope-point form
                     value = maxValue - (amplitude*(dataPoint-halfLength))/halfLength;
                  }
               }
               break;
            case kSawtoothPattern:
               value = minValue + (amplitude*dataPoint)/signalDataLength;
               break;
            default:
               value = 0;
               break;
            }
            signalData[dataPoint] = value;
         }
      }

      void printData( const std::vector<u8>& data,
                      u32                    dataLength,
                      u32                    numberOfPorts,
                      const char*            label )
      {
         static u32 samplesCount = 0;
         u32 portCount = 0;

         for (u32 i=0; i<dataLength ; ++i)
         {
            if (portCount%numberOfPorts == 0)
            {
               printf("\n");
               printf("  %6s %6d: ", label, samplesCount+1);
               portCount = 0;
               ++samplesCount;
            }
            ++portCount;

            printf(" 0x%02X  ", data[i]);
         }
      }

      void interleaveData( u32                    sampsPerPort,
                           u32                    numberOfPorts,
                           std::vector<u8>&       jointData,
                           const std::vector<u8>& data1,
                           const std::vector<u8>& data2 )
      {
         jointData.clear();
         jointData.reserve(numberOfPorts*sampsPerPort);

         // Prepare data to be generated from separate, single waveforms. When
         // there are more than 2 output channels, repeat the data in the
         // higher channels.
         //   Example: interleave data1 and data2 with numberOfPorts == 3
         //     1.0 1.1 1.2 1.3 ...
         //     2.0 2.1 2.2 2.3 ...
         //   to make
         //     1.0 2.0 1.0 1.1 2.1 1.1 1.2 2.2 1.2 1.3 2.3 1.3 ...
         if ( (data1.size() < sampsPerPort) || (data2.size() < sampsPerPort) )
         {
            printf("Warning: Not interleaving because data vectors do not have the minimum number of elements.\n");
            return;
         }

         for (u32 i=0; i<sampsPerPort; ++i)
         {
            for (u32 j=0; j<numberOfPorts; ++j)
            {
               if(j%2 == 0)
               {
                  jointData.push_back(data1[i]);
               }
               else
               {
                  jointData.push_back(data2[i]);
               }
            }
         }
      }
   } // nDIODataHelper
} // nNISTC3
