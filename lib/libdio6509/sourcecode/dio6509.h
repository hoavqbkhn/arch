#ifndef ___NIDIO6509_H___
#define ___NIDIO6509_H___

#include <vector>
#include "tPortHelper.h"
#include "tPortHelperFactory.h"
#include "osiBus.h"
#include <stdint.h>



#define DIO6509_BUS_NUMBER "01"
#define DIO6509_DEVICE_NUMBER "00"


class Dio6509 
{
public:
	Dio6509();
	virtual ~Dio6509();
	bool open();
	bool close();

	enum PortId {
		DIO_Port0 = 0,
		DIO_Port1,
		DIO_Port2,
		DIO_Port3,
		DIO_Port4,
		DIO_Port5,
		DIO_Port6,
		DIO_Port7,
		DIO_Port8,
		DIO_Port9,
		DIO_Port10,
		DIO_Port11,
		DIO_PortUnkown
	};

	enum PortType {
		DIO_Input,
		DIO_Output,
		DIO_NotConfig
	};

	bool configPort(PortId port, PortType type);
	bool resetConfigPort(PortId port);
	
	bool writeDoPort(PortId port, uint8_t value);
	bool resetDoPort(PortId port);

	bool readDiPort(PortId port, uint8_t &returalVal);
	bool readDoPort(PortId port, uint8_t &returnVal);
private:
	std::vector<nNISTC3::tPortHelper*> mlistPort;
	std::vector<PortType> mlistPortType;
	iBus *mBus;
	tPCIe6509 *mDevice;
	nNISTC3::tPortHelperFactory *mFactory;
	bool mIsOpened;
};
#endif //___NIDIO6509_H___
