#include "USBPort.h"

USBPort::~USBPort()
{
    disconnect();
}

void USBPort::setUSBPath( char * _usbPath )
{
    USBPath = _usbPath;
}

int USBPort::connect()
{
    fileDescriptor = open( USBPath, O_RDWR);

    if(fileDescriptor<0)
        return fileDescriptor;

    fcntl(fileDescriptor, F_SETFL, ( fcntl( fileDescriptor, F_GETFL, 0 ) | O_NONBLOCK ) );

    connected = true;
    return 0;
}

void USBPort::disconnect()
{
    if(connected)
        close(fileDescriptor);
}

int USBPort::sendDate( char * _date, int _dateSize )
{
    if(!connected)
        return -1;

    return write(fileDescriptor, _date, _dateSize );
}

int USBPort::getDate( char * _date, int _dateMaxSize )
{   
    return read(fileDescriptor, _date, _dateMaxSize);
}

int USBPort::getDate( char * _date, int _dateMaxSize,  time_t _timeout)
{
    time_t currentTime;
    time( &currentTime );
    _timeout+=currentTime;

    while(true)
    {
        int rc = read(fileDescriptor, _date, _dateMaxSize);
        if( rc > 0 )
            return rc;

        time( &currentTime );
        if( currentTime > _timeout )
        {
            return 0;
        }


    }
}