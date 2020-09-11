// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tPfiPortsValues_h___
#define ___tPfiPortsValues_h___

namespace nPfiPorts {
   typedef enum {
      kPFI_DO                            = 16,
   } tPFI_Output_Select_t;

   typedef enum {
      kWDT_Disabled                      = 0,
      kWDT_Freeze                        = 1,
      kWDT_Tristate                      = 2,
      kWDT_SafeValue                     = 3,
   } tPFI_WDT_Mode_t;

   typedef enum {
      kNo_Filter                         = 0,
      kSmall_Filter                      = 2,
      kMedium_Filter                     = 3,
      kLarge_Filter                      = 4,
   } tPFI_Filter_Select_t;

   namespace nPFI_ChangeDetectLatched_Register {
      namespace nPFI_ChangeDetectLatched_Port0 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

      namespace nPFI_ChangeDetectLatched_Port1 {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   namespace nPFI_ChangeIrq_Register {
      namespace nPFI_ChangeIrqRE_Port0 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

      namespace nPFI_ChangeIrqRE_Port1 {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

      namespace nPFI_ChangeIrqFE_Port0 {
         enum {
            kMask = 0xff0000,
            kOffset = 0x10,
         };
      }

      namespace nPFI_ChangeIrqFE_Port1 {
         enum {
            kMask = 0xff000000,
            kOffset = 0x18,
         };
      }

   }

   namespace nStatic_Digital_Input_Register {
      namespace nPFI_StaticInputValue_Port0 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

      namespace nPFI_StaticInputValue_Port1 {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   namespace nStatic_Digital_Output_Register {
      namespace nPFI_StaticOutputValue_Port0 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

      namespace nPFI_StaticOutputValue_Port1 {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   namespace nPFI_Direction_Register {
      namespace nPFIDirection_Port0 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

      namespace nPFIDirection_Port1 {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   namespace nPFI_OutputSelectRegister_t {
      namespace nPFI_i_Output_Select {
         enum {
            kMask = 0x7f,
            kOffset = 0,
         };
      }

   }

   namespace nPFI_Filter_Register_Port0Lo {
      namespace nPFI_Filter_Select_Port0_Line0 {
         enum {
            kMask = 0x7,
            kOffset = 0,
         };
      }

      namespace nPFI_Filter_Select_Port0_Line1 {
         enum {
            kMask = 0x70,
            kOffset = 0x4,
         };
      }

      namespace nPFI_Filter_Select_Port0_Line2 {
         enum {
            kMask = 0x700,
            kOffset = 0x8,
         };
      }

      namespace nPFI_Filter_Select_Port0_Line3 {
         enum {
            kMask = 0x7000,
            kOffset = 0xc,
         };
      }

   }

   namespace nPFI_Filter_Register_Port0Hi {
      namespace nPFI_Filter_Select_Port0_Line4 {
         enum {
            kMask = 0x7,
            kOffset = 0,
         };
      }

      namespace nPFI_Filter_Select_Port0_Line5 {
         enum {
            kMask = 0x70,
            kOffset = 0x4,
         };
      }

      namespace nPFI_Filter_Select_Port0_Line6 {
         enum {
            kMask = 0x700,
            kOffset = 0x8,
         };
      }

      namespace nPFI_Filter_Select_Port0_Line7 {
         enum {
            kMask = 0x7000,
            kOffset = 0xc,
         };
      }

   }

   namespace nPFI_Filter_Register_Port1Lo {
      namespace nPFI_Filter_Select_Port1_Line0 {
         enum {
            kMask = 0x7,
            kOffset = 0,
         };
      }

      namespace nPFI_Filter_Select_Port1_Line1 {
         enum {
            kMask = 0x70,
            kOffset = 0x4,
         };
      }

      namespace nPFI_Filter_Select_Port1_Line2 {
         enum {
            kMask = 0x700,
            kOffset = 0x8,
         };
      }

      namespace nPFI_Filter_Select_Port1_Line3 {
         enum {
            kMask = 0x7000,
            kOffset = 0xc,
         };
      }

   }

   namespace nPFI_Filter_Register_Port1Hi {
      namespace nPFI_Filter_Select_Port1_Line4 {
         enum {
            kMask = 0x7,
            kOffset = 0,
         };
      }

      namespace nPFI_Filter_Select_Port1_Line5 {
         enum {
            kMask = 0x70,
            kOffset = 0x4,
         };
      }

      namespace nPFI_Filter_Select_Port1_Line6 {
         enum {
            kMask = 0x700,
            kOffset = 0x8,
         };
      }

      namespace nPFI_Filter_Select_Port1_Line7 {
         enum {
            kMask = 0x7000,
            kOffset = 0xc,
         };
      }

   }

   namespace nPFI_WDT_SafeStateRegister {
      namespace nPFI_WDT_SafeStateValue_Port0 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

      namespace nPFI_WDT_SafeStateValue_Port1 {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   namespace nPFI_WDT_ModeSelect_Register {
      namespace nPFI_WDT_ModePort0_Line0 {
         enum {
            kMask = 0x3,
            kOffset = 0,
         };
      }

      namespace nPFI_WDT_ModePort0_Line1 {
         enum {
            kMask = 0xc,
            kOffset = 0x2,
         };
      }

      namespace nPFI_WDT_ModePort0_Line2 {
         enum {
            kMask = 0x30,
            kOffset = 0x4,
         };
      }

      namespace nPFI_WDT_ModePort0_Line3 {
         enum {
            kMask = 0xc0,
            kOffset = 0x6,
         };
      }

      namespace nPFI_WDT_ModePort0_Line4 {
         enum {
            kMask = 0x300,
            kOffset = 0x8,
         };
      }

      namespace nPFI_WDT_ModePort0_Line5 {
         enum {
            kMask = 0xc00,
            kOffset = 0xa,
         };
      }

      namespace nPFI_WDT_ModePort0_Line6 {
         enum {
            kMask = 0x3000,
            kOffset = 0xc,
         };
      }

      namespace nPFI_WDT_ModePort0_Line7 {
         enum {
            kMask = 0xc000,
            kOffset = 0xe,
         };
      }

      namespace nPFI_WDT_ModePort1_Line0 {
         enum {
            kMask = 0x30000,
            kOffset = 0x10,
         };
      }

      namespace nPFI_WDT_ModePort1_Line1 {
         enum {
            kMask = 0xc0000,
            kOffset = 0x12,
         };
      }

      namespace nPFI_WDT_ModePort1_Line2 {
         enum {
            kMask = 0x300000,
            kOffset = 0x14,
         };
      }

      namespace nPFI_WDT_ModePort1_Line3 {
         enum {
            kMask = 0xc00000,
            kOffset = 0x16,
         };
      }

      namespace nPFI_WDT_ModePort1_Line4 {
         enum {
            kMask = 0x3000000,
            kOffset = 0x18,
         };
      }

      namespace nPFI_WDT_ModePort1_Line5 {
         enum {
            kMask = 0xc000000,
            kOffset = 0x1a,
         };
      }

      namespace nPFI_WDT_ModePort1_Line6 {
         enum {
            kMask = 0x30000000,
            kOffset = 0x1c,
         };
      }

      namespace nPFI_WDT_ModePort1_Line7 {
         enum {
            kMask = 0xc0000000,
            kOffset = 0x1e,
         };
      }

   }

   using namespace nPFI_ChangeDetectLatched_Register;
   using namespace nPFI_ChangeIrq_Register;
   using namespace nStatic_Digital_Input_Register;
   using namespace nStatic_Digital_Output_Register;
   using namespace nPFI_Direction_Register;
   using namespace nPFI_OutputSelectRegister_t;
   using namespace nPFI_Filter_Register_Port0Lo;
   using namespace nPFI_Filter_Register_Port0Hi;
   using namespace nPFI_Filter_Register_Port1Lo;
   using namespace nPFI_Filter_Register_Port1Hi;
   using namespace nPFI_WDT_SafeStateRegister;
   using namespace nPFI_WDT_ModeSelect_Register;
}

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
