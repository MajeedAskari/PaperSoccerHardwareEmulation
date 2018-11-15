#ifndef SERIAL_H_
#define SERIAL_H_
#include <Windows.h>
#include <stdio.h>
void serialOpen(char ComPortName[]);
void serialRead(char SerialBuffer[]);
void serialWrite(char lpBuffer[4]);
void serialClose();
#endif