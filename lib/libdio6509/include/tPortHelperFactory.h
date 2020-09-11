/*
 * tPortHelperFactory.h
 *
 * Copyright (c) 2012 National Instruments.
 * All rights reserved.
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dio_tPortHelperFactory_h___
#define ___dio_tPortHelperFactory_h___

#include <vector>

#include "tPortHelper.h"

// Forward declarations
class tPCIe6509;
class tDioPorts;
class tPfiPorts;

namespace nNISTC3
{

   class tPortHelperFactory
   {
   public:
      tPortHelperFactory( tPCIe6509&         device,
                          const tDeviceInfo* deviceInfo,
                          nMDBG::tStatus2&   status );
      virtual ~tPortHelperFactory();

      tPortHelper* getPortHelper( tMapIndex        portMapIndex,
                                  nMDBG::tStatus2& status );

   private:
      enum
      {
         numChipObjectConfigurations = 2,
      };

      typedef struct
      {
         tStc3Configuration stc3Configuration;
         tDioPorts*         dioPorts;
         tPfiPorts*         pfiPorts;
      } tChipObjectConfiguration;

      static tChipObjectConfiguration _createChipObjectConfiguration( tStc3Configuration arg_Stc3Configuration,
                                                                      tDioPorts*         arg_DioPorts,
                                                                      tPfiPorts*         arg_PfiPorts );

      std::vector<tPortHelper*>  _portHelper;
      std::vector<iRegAccessor*> _regAccessor;

      // Usage guidelines
      tPortHelperFactory& operator=(const tPortHelperFactory& rhs);
      tPortHelperFactory(const tPortHelperFactory& rhs);
   };
} // nNISTC3

#endif // ___dio_tPortHelperFactory_h___
