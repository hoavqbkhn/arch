// Copyright (c) 2012 National Instruments.
// All rights reserved.
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tChpServicesValues_h___
#define ___tChpServicesValues_h___

namespace nChpServices {
   typedef enum {
      kSTC3_RevBSignature                = 134546689,
      kSTC3_RevASignature                = 134546697,
   } tSTC3_Signature_t;

   typedef enum {
      kIF_MasterSTC3                     = 0,
      kIF_SlaveSTC3                      = 24,
   } tIntForwarding_Destination_t;

   typedef enum {
      kWdtSrc_RTSI0                      = 0,
      kWdtSrc_RTSI1                      = 1,
      kWdtSrc_RTSI2                      = 2,
      kWdtSrc_RTSI3                      = 3,
      kWdtSrc_RTSI4                      = 4,
      kWdtSrc_RTSI5                      = 5,
      kWdtSrc_RTSI6                      = 6,
      kWdtSrc_RTSI7                      = 7,
   } tChpSrv_WatchdogTimerExtSrcSel_t;

   typedef enum {
      kWdtSt_SynchReset                  = 0,
      kWdtSt_CountDownFeed               = 1,
      kWdtSt_CountDownFood               = 2,
      kWdtSt_Sleeping                    = 3,
      kWdtSt_ExpiredPulse                = 5,
      kWdtSt_Expired                     = 6,
   } tChpSrv_WatchdogTimerStateMachineSt_t;

   typedef enum {
      kRTSI_DIO_ChangeDetect             = 13,
      kRTSI_WatchdogExpiredPulse         = 14,
   } tRTSI_Output_Select_t;

   namespace nGlobalInterruptStatus_Register {
      namespace nDI_Interrupt_Status {
         enum {
            kMask = 0x40,
            kOffset = 0x6,
         };
      }

      namespace nWatchdogTimer_Interrupt_Status {
         enum {
            kMask = 0x400,
            kOffset = 0xa,
         };
      }

   }

   namespace nGlobalInterruptEnable_Register {
      namespace nDI_Interrupt_Enable {
         enum {
            kMask = 0x40,
            kOffset = 0x6,
         };
      }

      namespace nWatchdogTimer_Interrupt_Enable {
         enum {
            kMask = 0x400,
            kOffset = 0xa,
         };
      }

      namespace nDI_Interrupt_Disable {
         enum {
            kMask = 0x400000,
            kOffset = 0x16,
         };
      }

      namespace nWatchdogTimerInterrupt_Disable {
         enum {
            kMask = 0x4000000,
            kOffset = 0x1a,
         };
      }

   }

   namespace nDI_Interrupt_Status_Register {
      namespace nChangeDetectionIrqSt {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nChangeDetectionErrorIrqSt {
         enum {
            kMask = 0x2,
            kOffset = 0x1,
         };
      }

   }

   namespace nWatchdogTimer_Interrupt_Status_Register {
      namespace nWatchdogTimerTriggerSt {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

   }

   namespace nWatchdogTimer_Interrupt1_Register {
      namespace nWDT_TriggerIRQ_Enable {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nWDT_TriggerIRQ_Ack {
         enum {
            kMask = 0x10000,
            kOffset = 0x10,
         };
      }

   }

   namespace nWatchdogTimer_Interrupt2_Register {
      namespace nWDT_TriggerIRQ_Disable {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nWDT_TriggerIRQ_Ack2 {
         enum {
            kMask = 0x10000,
            kOffset = 0x10,
         };
      }

   }

   namespace nChangeDetectStatusRegister {
      namespace nChangeDetectStatus {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nChangeDetectError {
         enum {
            kMask = 0x2,
            kOffset = 0x1,
         };
      }

   }

   namespace nChangeDetectIRQ_Register {
      namespace nChangeDetectIRQ_Acknowledge {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nChangeDetectErrorIRQ_Acknowledge {
         enum {
            kMask = 0x2,
            kOffset = 0x1,
         };
      }

      namespace nChangeDetectIRQ_Disable {
         enum {
            kMask = 0x10,
            kOffset = 0x4,
         };
      }

      namespace nChangeDetectIRQ_Enable {
         enum {
            kMask = 0x20,
            kOffset = 0x5,
         };
      }

      namespace nChangeDetectErrorIRQ_Disable {
         enum {
            kMask = 0x40,
            kOffset = 0x6,
         };
      }

      namespace nChangeDetectErrorIRQ_Enable {
         enum {
            kMask = 0x80,
            kOffset = 0x7,
         };
      }

   }

   namespace nIntForwarding_ControlStatus {
      namespace nIntForwarding_Enable {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nIntForwarding_Reset {
         enum {
            kMask = 0x2,
            kOffset = 0x1,
         };
      }

   }

   namespace nIntForwarding_DestinationReg {
      namespace nIntForwarding_Destination {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

   }

   namespace nScratchPadRegister {
      namespace nScratch_Pad {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nSignature_Register {
      namespace nSTC3_Revision {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nJoint_Reset_Register {
      namespace nSoftware_Reset {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

   }

   namespace nTimeSincePowerUpRegister {
      namespace nTimeSincePowerUpValue {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nWatchdogStatusRegister {
      namespace nWatchdogSM_State {
         enum {
            kMask = 0x7,
            kOffset = 0,
         };
      }

      namespace nWatchdogExpiredCnt {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   namespace nWatchdogTimeoutRegister {
      namespace nWatchdogTimeoutValue {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nWatchdogConfiguration {
      namespace nWatchdogExtTrigSel {
         enum {
            kMask = 0x7,
            kOffset = 0,
         };
      }

      namespace nWatchdogExtTrigPol {
         enum {
            kMask = 0x80,
            kOffset = 0x7,
         };
      }

      namespace nWatchdogExtTrigEn {
         enum {
            kMask = 0x100,
            kOffset = 0x8,
         };
      }

      namespace nWatchdogIntTrigEn {
         enum {
            kMask = 0x200,
            kOffset = 0x9,
         };
      }

   }

   namespace nWatchdogControl {
      namespace nWatchdogCommand {
         enum {
            kMask = 0xffff,
            kOffset = 0,
         };
      }

   }

   namespace nRTSI_OutputSelectRegister_t {
      namespace nRTSI_i_Output_Select {
         enum {
            kMask = 0x7f,
            kOffset = 0,
         };
      }

   }

   namespace nRTSI_Trig_Direction_Register {
      namespace nRTSIDirection {
         enum {
            kMask = 0xff00,
            kOffset = 0x8,
         };
      }

   }

   using namespace nGlobalInterruptStatus_Register;
   using namespace nGlobalInterruptEnable_Register;
   using namespace nDI_Interrupt_Status_Register;
   using namespace nWatchdogTimer_Interrupt_Status_Register;
   using namespace nWatchdogTimer_Interrupt1_Register;
   using namespace nWatchdogTimer_Interrupt2_Register;
   using namespace nChangeDetectStatusRegister;
   using namespace nChangeDetectIRQ_Register;
   using namespace nIntForwarding_ControlStatus;
   using namespace nIntForwarding_DestinationReg;
   using namespace nScratchPadRegister;
   using namespace nSignature_Register;
   using namespace nJoint_Reset_Register;
   using namespace nTimeSincePowerUpRegister;
   using namespace nWatchdogStatusRegister;
   using namespace nWatchdogTimeoutRegister;
   using namespace nWatchdogConfiguration;
   using namespace nWatchdogControl;
   using namespace nRTSI_OutputSelectRegister_t;
   using namespace nRTSI_Trig_Direction_Register;
}

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

