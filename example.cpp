#include <iostream>
#include <unistd.h>
#include <string.h>

#include "USBPort.h"

int main( int argn, char **argv )
{
    if(argn<2)
    {
        dprintf(2,"ERROR: No got USB device path. Exemple: \"./exec /dev/ttyUSB0\" \n");
        return -1;
    }

    USBPort *usbp = new USBPort();
    usbp->setUSBPath(argv[1]);

    if( usbp->connect() )
    {
        dprintf(2, "ERROR: Cennot open USB device. Non permission (need root) or bad device path. \n");
        
        delete usbp;
        return -1;
    }

    char *buffor = new char[256];

    dprintf(1, "Write \"end\" to break loop.\n");

    while(true)
    {
        memset( buffor, 0, 256 ); //clear buffor
        dprintf(1, "Send:");
        read(0, buffor, 256);
        if( strcmp( buffor, "end\n") == 0 ) 
            break;
        
        if( usbp->sendDate( buffor, 256 ) < 0  )
        {
            dprintf(2, "ERROR: Unsucces send date to USB device.\n");
            continue;
        }

        int rc = usbp->getDate( buffor, 256 );
        if(  rc <=0 )
        {
            dprintf(2, "ERROR: Unsucces read date from USB device.\n");
            continue;
        }

        write(1, buffor, rc );
    }

    delete usbp;
    return 0;
}
