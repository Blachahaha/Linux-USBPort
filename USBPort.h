#ifndef __USBPort_h_
#define __USBPort_h_

#include <ctime>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 

#include <iostream>

class USBPort
{
public:

    ~USBPort();

    void setUSBPath( char * _usbPath );
    int connect();

    void disconnect();
    int sendDate( char * _date, int _dateSize );
    int getDate( char * _date, int _dateMaxSize );
    int getDate( char * _date, int _dateMaxSize,  time_t _timeout);

private:
    bool connected=false;
    char * USBPath;
    int fileDescriptor;
    fd_set fd_in;
};

#endif //__USBPort_h_
