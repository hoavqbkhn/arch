/*
 * dataHelper.h
 *
 * Generate and print device data.
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dataHelper_h___
#define ___dataHelper_h___

#include <vector>

// OS Interface (for basic datatype names)
#include "osiTypes.h"

namespace nNISTC3
{
   void printHeaderPad(const char* label);

   void printHeader( u32         numPorts,
                     const char* label,
                     const char* subsystem);

   namespace nDIODataHelper
   {
      typedef enum
      {
         kSquarePattern = 0,
         kTrianglePattern,
         kSawtoothPattern
      } tSignalType;

      // Print header
      //   numPorts: number of ports to be displayed in the header
      //   label:    label to be used in the header
      void printHeader( u32          numPorts,
                        const char*  label );

      // Generate signal
      //   signalType:       pattern to use when generating the signal
      //   minValue:         minimum value of the generated signal
      //   maxValue:         maximum value of the generated signal
      //   signalData:       buffer to store the generated signal
      //   signalDataLength: the length of the signal to be generated
      void generateSignal( tSignalType      signalType,
                           u8               minValue,
                           u8               maxValue,
                           std::vector<u8>& signalData,
                           u32              signalDataLength );

      // Print data
      //   data:          vector buffer that contains data to print
      //   dataLength:    number of samples in the buffer
      //   numberOfPorts: number of ports represented in the buffer
      //   label:         label to be displayed (usually "Sample" or "Update")
      void printData( const std::vector<u8>& data,
                      u32                    dataLength,
                      u32                    numberOfPorts,
                      const char*            label );

      // Interleave data
      //   sampsPerPort:  number of samples in the data1 and data2 buffers
      //   numberOfPorts: number of ports represented in the buffer
      //   jointData:     buffer to store the interleaved data from data1 and data2
      //   data1:         data to be output from the first port in the operation
      //   data2:         data to be output from the second port in the operation
      void interleaveData( u32                    sampsPerPort,
                           u32                    numberOfPorts,
                           std::vector<u8>&       jointData,
                           const std::vector<u8>& data1,
                           const std::vector<u8>& data2 );
   } // nDIODataHelper
} // nNISTC3

#endif // ___dataHelper_h___
