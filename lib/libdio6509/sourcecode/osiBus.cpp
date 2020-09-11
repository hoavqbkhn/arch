// Linux specific headers
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include "osiBus.h"


iBus* acquireBoard(tChar* brdLocation)
{
    iBus *bus;

    unsigned long physicalBar0;
    unsigned long bar0Size;
    void *mem0 = NULL;
    #ifndef kBAR0Only
    unsigned long physicalBar1;
    unsigned long bar1Size;
    void *mem1 = NULL;
    #endif

    u32 busNumber = 0;
    u32 devNumber = 0;
    i32 brdId;

    sscanf (brdLocation,"PXI%d::%d::INSTR", &busNumber, &devNumber);

    brdId = getBoardId (busNumber, devNumber);

    if (brdId < 0)
    {
        printf ("invalid device descriptor: %s\n", brdLocation);
        return NULL;
    }

    int fd = 0;
    char file[32];

    sprintf(file, "/dev/nirlpk%d", brdId);

    fd = open (file, O_RDWR);
    if (fd <= 0 )
    {
        printf ("fail to open %s\n", file);
        return NULL;
    }

    physicalBar0 = 0;
    if ( ioctl (fd, NIRLP_IOCTL_GET_PHYSICAL_ADDRESS, &physicalBar0) < 0 )
    {
       close(fd);
       return NULL;
    }

    bar0Size = 0;
    if ( ioctl (fd, NIRLP_IOCTL_GET_BAR_SIZE, &bar0Size) < 0 )
    {
       close(fd);
       return NULL;
    }

    #ifndef kBAR0Only
    physicalBar1 = 1;
    if ( ioctl (fd, NIRLP_IOCTL_GET_PHYSICAL_ADDRESS, &physicalBar1) < 0 )
    {
       close(fd);
       return NULL;
    }

    bar1Size = 1;
    if ( ioctl (fd, NIRLP_IOCTL_GET_BAR_SIZE, &bar1Size) < 0 )
    {
       close(fd);
       return NULL;
    }
    #endif

    mem0 = mmap (NULL, bar0Size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, physicalBar0);
    if ( MAP_FAILED == mem0)
    {
        close (fd);
        return NULL;
    }
    #ifndef kBAR0Only
    mem1 = mmap (NULL, bar1Size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, physicalBar1);
    if ( MAP_FAILED == mem1)
    {
        close (fd);
        return NULL;
    }
    #endif

    // Create a new iBus
    #ifndef kBAR0Only
    bus = new iBus(0, 0, mem0, mem1);
    #else
    bus = new iBus(0, 0, mem0, NULL);
    #endif

    bus->_physBar[0] = (u32)physicalBar0;
    #ifndef kBAR0Only
    bus->_physBar[1] = (u32)physicalBar1;
    #else
    bus->_physBar[1] = (u32)NULL;
    #endif
    bus->_physBar[2] = (u32)NULL;
    bus->_physBar[3] = (u32)NULL;
    bus->_physBar[4] = (u32)NULL;
    bus->_physBar[5] = (u32)NULL;

    tLinuxSpecific *specific =  new tLinuxSpecific;
    specific->fileDescriptor = fd;
    specific->mappedMemory0 = mem0;
    specific->bar0Size = bar0Size;
    #ifndef kBAR0Only
    specific->mappedMemory1 = mem1;
    specific->bar1Size = bar1Size;
    #endif

    bus->_osSpecific = reinterpret_cast<void*> (specific);
    return bus;
}

void releaseBoard(iBus *&bus)
{
    tLinuxSpecific *specific = reinterpret_cast <tLinuxSpecific *> ( bus->_osSpecific );

    munmap (specific->mappedMemory0, specific->bar0Size);
    #ifndef kBAR0Only
    munmap (specific->mappedMemory1, specific->bar1Size);
    #endif

    close (specific->fileDescriptor);

    delete specific;
    delete bus;
}

i32 getBoardId (u32 bus, u32 dev)
{
    FILE *fp;
    i32 minor = -1;

    fp = fopen("/proc/nirlpk/nirlpk", "r");
    if (NULL == fp)
        return minor;

    u32 _bus;
    u32 _dev;
    i32 _major;
    i32 _minor;

    while (EOF != fscanf(fp, "%*d %d %d %d:%d\n", &_bus, &_dev, &_major, &_minor))
    {
        if ((bus == _bus) && (dev == _dev))
        {
            minor = _minor;
            break;
        }
    }

    fclose (fp);
    return minor;
}