#include "dio6509.h"

// OS Interface
#include "osiBus.h"

// Chip Objects
#include "tPCIe6509.h"

// Chip Object Helpers
#include "devices.h"
#include "tPortHelperFactory.h"

// Data types
#include "osiTypes.h"

#include <stdint.h>



Dio6509::Dio6509() {
	mBus = NULL;
	mDevice = NULL;
	mIsOpened = false;
	mFactory = NULL;
}

Dio6509::~Dio6509() {
	delete mFactory;
	delete mDevice;
}

bool Dio6509::open() {

   if(mIsOpened == true) {
   		return true;
   }

   const tBoolean tristateOnExit = kTrue;

   tChar brdLocation[256];
   sprintf(brdLocation, "PXI%s::%s::INSTR", DIO6509_BUS_NUMBER, DIO6509_DEVICE_NUMBER);

   mBus = acquireBoard(brdLocation);
   if(mBus == NULL)
   {
      printf("Could not access PCI device. Exiting.\n");
      return 1;
   }

    // Bookkeeping
   nMDBG::tStatus2 status;
   tAddressSpace bar0;
   bar0 = mBus->createAddressSpace(kPCI_BAR0);

   /*********************************************************************\
   |
   |   Initialize the operation
   |
   \*********************************************************************/

   //
   // Open, detect, and initialize the PCIe-6509
   //

   mDevice = new tPCIe6509(bar0, &status);

   const nNISTC3::tDeviceInfo* deviceInfo = nNISTC3::getDeviceInfo(*mDevice, status);
   if (status.isFatal())
   {
      printf("Error: Cannot identify device (%d).\n", status.statusCode);
      return false;
   }

   mFactory = new nNISTC3::tPortHelperFactory(*mDevice, deviceInfo, status);
   

   nNISTC3::tPortHelper* port0 = mFactory->getPortHelper(nNISTC3::kMapIndexPort0, status);
   port0->setTristate(tristateOnExit, status);
   mlistPort.push_back(port0);

 	
   nNISTC3::tPortHelper* port1 = mFactory->getPortHelper(nNISTC3::kMapIndexPort1, status);
   port1->setTristate(tristateOnExit, status);
   mlistPort.push_back(port1);

   nNISTC3::tPortHelper* port2 = mFactory->getPortHelper(nNISTC3::kMapIndexPort2, status);
   port2->setTristate(tristateOnExit, status);
   mlistPort.push_back(port2);
   
   nNISTC3::tPortHelper* port3 = mFactory->getPortHelper(nNISTC3::kMapIndexPort3, status);
   port3->setTristate(tristateOnExit, status);
   mlistPort.push_back(port3);

   nNISTC3::tPortHelper* port4 = mFactory->getPortHelper(nNISTC3::kMapIndexPort4, status);
   port4->setTristate(tristateOnExit, status);   
   mlistPort.push_back(port4);
   
   nNISTC3::tPortHelper* port5 = mFactory->getPortHelper(nNISTC3::kMapIndexPort5, status);
   port5->setTristate(tristateOnExit, status);   
   mlistPort.push_back(port5);

   nNISTC3::tPortHelper* port6 = mFactory->getPortHelper(nNISTC3::kMapIndexPort6, status);
   port6->setTristate(tristateOnExit, status);   
   mlistPort.push_back(port6);

   nNISTC3::tPortHelper* port7 = mFactory->getPortHelper(nNISTC3::kMapIndexPort7, status);
   port7->setTristate(tristateOnExit, status);   
   mlistPort.push_back(port7);

   nNISTC3::tPortHelper* port8 = mFactory->getPortHelper(nNISTC3::kMapIndexPort8, status);
   port8->setTristate(tristateOnExit, status);   
   mlistPort.push_back(port8);

   nNISTC3::tPortHelper* port9 = mFactory->getPortHelper(nNISTC3::kMapIndexPort9, status);
   port9->setTristate(tristateOnExit, status);
   mlistPort.push_back(port9);

   nNISTC3::tPortHelper* port10 = mFactory->getPortHelper(nNISTC3::kMapIndexPort10, status);
   port10->setTristate(tristateOnExit, status);
   mlistPort.push_back(port10);

   nNISTC3::tPortHelper* port11 = mFactory->getPortHelper(nNISTC3::kMapIndexPort11, status);
   port11->setTristate(tristateOnExit, status);   
   mlistPort.push_back(port11);

   if (status.isFatal())
   {
      printf("Error: Cannot create port helpers (%d).\n", status.statusCode);
      return false;
   }

   for( int i=0; i < mlistPort.size(); ++i) {
   		mlistPort[i]->reset(NULL, 0, status);
   		mlistPortType.push_back(DIO_NotConfig);
   }

   mIsOpened = true;
   return true;


}

bool Dio6509::close() {
	if( mIsOpened == false) {
		return false;
	}
	// Bookkeeping
    nMDBG::tStatus2 status;

	for( int i=0; i < mlistPort.size(); ++i) {
			mlistPort[i]->reset(NULL, 0, status);
	}
	mlistPortType.clear();
	mlistPort.clear();
	releaseBoard(mBus);

	mIsOpened = false;
	return true;
}

bool Dio6509::configPort(PortId port, PortType type) {
	
	if( mIsOpened == false || port >= DIO_PortUnkown) {
		return false;
	}
	// Bookkeeping
    nMDBG::tStatus2 status;

    switch(type) {
    	case DIO_Input:
    		mlistPort[port]->configureLines(0xFF, nNISTC3::kInput, status);
    		mlistPortType[port] = DIO_Input;
    		break;
    	case DIO_Output:
    		mlistPort[port]->configureLines(0xFF, nNISTC3::kOutput, status);
    		mlistPortType[port] = DIO_Output;
    		break;
    	default:
    		
    		return false;

    }

	

	if (status.isFatal())
    {
      printf("Error: Cannot program digital subsystem (configPort) (%d).\n", status.statusCode);
      return false;
    }

    return true;

}
bool Dio6509::resetConfigPort(PortId port) {
	if( mIsOpened == false || port >= DIO_PortUnkown) {
		return false;
	}
	nMDBG::tStatus2 status;
	mlistPort[port]->reset(NULL, 0, status);
	mlistPortType[port] = DIO_NotConfig;

	if (status.isFatal())
    {
      printf("Error: Cannot program digital subsystem (reset configuration of port) (%d).\n", status.statusCode);
      return false;
    }
    return true;
}

bool Dio6509::writeDoPort(PortId port, uint8_t value) {
	if( mIsOpened == false || port >= DIO_PortUnkown || mlistPortType[port] != DIO_Output) {
		printf("Error: Cannot program digital subsystem (writeDoPort): Invalid port");
		return false;
	}
	nMDBG::tStatus2 status;

	mlistPort[port]->write(0xFF, value, status);
	if (status.isFatal())
    {
      printf("Error: Cannot program digital subsystem (writeDoPort) (%d).\n", status.statusCode);
      return false;
    }
    return true;

}

bool Dio6509::resetDoPort(PortId port) {
	return writeDoPort(port, 0x00);
}

bool Dio6509::readDiPort(PortId port, uint8_t &returalVal) {
	if( mIsOpened == false || port >= DIO_PortUnkown || mlistPortType[port] != DIO_Input) {
		printf("Error: Cannot program digital subsystem (writeDoPort): Invalid port");
		return false;
	}
	nMDBG::tStatus2 status;

	mlistPort[port]->read(0xFF, returalVal, status);
	
	if (status.isFatal())
    {
      printf("Error: Cannot program digital subsystem (readDiPort) (%d).\n", status.statusCode);
      return false;
    }
    return true;

}

bool Dio6509::readDoPort(PortId port, uint8_t &returnVal) {
  if( mIsOpened == false || port >= DIO_PortUnkown || mlistPortType[port] != DIO_Output) {
    printf("Error: Cannot program digital subsystem (readDoPort): Invalid port");
    return false;
  }
  nMDBG::tStatus2 status;

  mlistPort[port]->read(0xFF, returnVal, status);
  
  if (status.isFatal())
    {
      printf("Error: Cannot program digital subsystem (readDoPort) (%d).\n", status.statusCode);
      return false;
    }
    return true;

}
