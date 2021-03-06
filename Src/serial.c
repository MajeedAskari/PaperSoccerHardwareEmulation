#include "../stdafx.h"

//====================================================================================================//
// Serial Port Programming using Win32 API in C                                                       //
// (Reads data from serial port)                                                                      //
//====================================================================================================//

//====================================================================================================//
// www.xanthium.in										                                              //
// Copyright (C) 2014 Rahul.S                                                                         //
//====================================================================================================//

//====================================================================================================//
// The Program runs on the PC side and uses Win32 API to communicate with the serial port or          //
// USB2SERIAL board and reads the data from it.                                                       //
//----------------------------------------------------------------------------------------------------//
// Program runs on the PC side (Windows) and receives a string of characters.                         //
// Program uses CreateFile() function to open a connection serial port(COMxx).                        //
// Program then sets the parameters of Serial Comm like Baudrate,Parity,Stop bits in the DCB struct.  //
// After setting the Time outs,the Program waits for the reception of string of characters by setting-//
// -up the  WaitCommEvent().                                                                          //
// When a character is reeived bythe PC UART WaitCommEvent() returns and the received string is read- //
// -using ReadFile(); function.The characters are then displayed on the Console.                      //
//----------------------------------------------------------------------------------------------------//
// BaudRate     -> 9600                                                                               //
// Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              //
// Flow Control -> None                                                                               //
//----------------------------------------------------------------------------------------------------//

//====================================================================================================//
// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)            //
//               :  gcc 4.8.1 (MinGW)                                                                 //
//                                                                                                    //
// Library       :  Win32 API,windows.h,                                                              //
// Commands      :  gcc -o USB2SERIAL_Read_W32 USB2SERIAL_Read_W32.c                                  //
// OS            :	Windows(Windows 7)                                                                //
// Programmer    :	Rahul.S                                                                           //
// Date	         :	30-November-2014                                                                  //
//====================================================================================================//

//====================================================================================================//
// Sellecting the COM port Number                                                                     //
//----------------------------------------------------------------------------------------------------//
// Use "Device Manager" in Windows to find out the COM Port number allotted to USB2SERIAL converter-  //
// -in your Computer and substitute in the  "ComPortName[]" array.                                    //
//                                                                                                    //
// for eg:-                                                                                           //
// If your COM port number is COM32 in device manager(will change according to system)                //
// then                                                                                               //
//			char   ComPortName[] = "\\\\.\\COM32";                                                    //
//====================================================================================================//

#include "../Inc/serial.h"

BOOL Status;       // Status of the various operations
HANDLE hComm;      // Handle to the Serial port
DWORD dwEventMask; // Event mask to trigger

void serialOpen(char ComPortName[])
{
    //char ComPortName[] = "\\\\.\\COM24"; // Name of the Serial port(May Change) to be opened,
    serialClose();
    int i = 0;
    /*---------------------------------- Opening the Serial Port -------------------------------------------*/
    hComm = CreateFile(ComPortName,                  // Name of the Port to be Opened
                       GENERIC_READ | GENERIC_WRITE, // Read/Write Access
                       0,                            // No Sharing, ports cant be shared
                       NULL,                         // No Security
                       OPEN_EXISTING,                // Open existing port only
                       0,                            // Non Overlapped I/O
                       NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
    {
        return;
    }

    /*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
    DCB dcbSerialParams = {0}; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    Status = GetCommState(hComm, &dcbSerialParams); //retreives  the current settings

    if (Status == FALSE)
        return;

    dcbSerialParams.BaudRate = CBR_115200; // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;          // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT; // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;     // Setting Parity = None

    Status = SetCommState(hComm, &dcbSerialParams); //Configuring the port according to settings in DCB

    if (Status == FALSE)
    {
        return;
    }

    /*------------------------------------ Setting Timeouts --------------------------------------------------*/

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 500;
    timeouts.ReadTotalTimeoutConstant = 500;
    timeouts.ReadTotalTimeoutMultiplier = 100;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE)
        return;

    /*------------------------------------ Setting Receive Mask ----------------------------------------------*/

    Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

    if (Status == FALSE)
        return;
}

void serialRead(char SerialBuffer[])
{
    int i = 0;
    char TempChar;     // Temperory Character
    DWORD NoBytesRead; // Bytes read by ReadFile()
    /*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

    Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received

    /*-------------------------- Program will Wait here till a Character is received ------------------------*/

    if (Status == FALSE)
    {
        return;
    }
    else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
    {
        do
        {
            Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
            SerialBuffer[i] = TempChar;
            i++;
        } while (NoBytesRead > 0);

        // /*------------Printing the RXed String to Console----------------------*/
        // printf("\n\n    ");
        // int j = 0;
        // for (j = 0; j < i - 1; j++) // j < i-1 to remove the dupliated last character
        //     printf("%c", SerialBuffer[j]);
    }
} //End of Main()

void serialWrite(char lpBuffer[])
{
    /*----------------------------- Writing a Character to Serial Port----------------------------------------*/
    // lpBuffer should be  char or byte array, otherwise write wil fail
    DWORD dNoOFBytestoWrite;     // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0; // No of bytes written to the port

    dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

    Status = WriteFile(hComm,              // Handle to the Serialport
                       lpBuffer,           // Data to be written to the port
                       dNoOFBytestoWrite,  // No of bytes to write into the port
                       &dNoOfBytesWritten, // No of bytes written to the port
                       NULL);

    // if (Status == TRUE)
    //     printf("\n\n    %s - Written", lpBuffer);
    // else
    //     printf("\n\n   Error %d in Writing to Serial Port", GetLastError());
}

void serialClose()
{
    if (hComm == INVALID_HANDLE_VALUE)
    {
        return;
    }
    CloseHandle(hComm); //Closing the Serial Port
}