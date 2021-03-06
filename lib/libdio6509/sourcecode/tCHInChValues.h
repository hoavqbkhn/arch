// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tCHInChValues_h___
#define ___tCHInChValues_h___

namespace nCHInCh {
   typedef enum {
      kCHInChSignature                   = -1072661808,
   } tCHInCh_Signature_t;

   typedef enum {
      kEEPROMOffset                      = 20480,
   } tConfiguration_Values_t;

   namespace nScrap_Register_t {
      namespace nSDATA {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nCHInCh_Identification_Register {
      namespace nID {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nInterrupt_Mask_Register {
      namespace nClear_STC3_Int {
         enum {
            kMask = 0x400,
            kOffset = 0xa,
         };
      }

      namespace nSet_STC3_Int {
         enum {
            kMask = 0x800,
            kOffset = 0xb,
         };
      }

      namespace nClear_CPU_Int {
         enum {
            kMask = 0x40000000,
            kOffset = 0x1e,
         };
      }

      namespace nSet_CPU_Int {
         enum {
            kMask = 0x80000000,
            kOffset = 0x1f,
         };
      }

   }

   namespace nInterrupt_Status_Register {
      namespace nSTC3_Int {
         enum {
            kMask = 0x800,
            kOffset = 0xb,
         };
      }

      namespace nExternal {
         enum {
            kMask = 0x20000000,
            kOffset = 0x1d,
         };
      }

      namespace nAdditional_Int {
         enum {
            kMask = 0x40000000,
            kOffset = 0x1e,
         };
      }

      namespace nInt {
         enum {
            kMask = 0x80000000,
            kOffset = 0x1f,
         };
      }

   }

   namespace nVolatile_Interrupt_Status_Register {
      namespace nVol_STC3_Int {
         enum {
            kMask = 0x800,
            kOffset = 0xb,
         };
      }

      namespace nVol_External {
         enum {
            kMask = 0x20000000,
            kOffset = 0x1d,
         };
      }

      namespace nVol_Additional_Int {
         enum {
            kMask = 0x40000000,
            kOffset = 0x1e,
         };
      }

      namespace nVol_Int {
         enum {
            kMask = 0x80000000,
            kOffset = 0x1f,
         };
      }

   }

   namespace nPCI_SubSystem_ID_Access_Register {
      namespace nSubSystem_Vendor_ID {
         enum {
            kMask = 0xffff,
            kOffset = 0,
         };
      }

      namespace nSubSystem_Product_ID {
         enum {
            kMask = 0xffff0000,
            kOffset = 0x10,
         };
      }

   }

   using namespace nScrap_Register_t;
   using namespace nCHInCh_Identification_Register;
   using namespace nInterrupt_Mask_Register;
   using namespace nInterrupt_Status_Register;
   using namespace nVolatile_Interrupt_Status_Register;
   using namespace nPCI_SubSystem_ID_Access_Register;
}

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

