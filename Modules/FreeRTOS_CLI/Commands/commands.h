#ifndef COMMANDS_H
#define COMMANDS_H



#include <FreeRTOS.h>
#include <task.h>
#include <FreeRTOS_CLI.h>



BaseType_t taskListCommand( char *pcWriteBuffer,
                            size_t xWriteBufferLen,
                            const char *pcCommandString );						

BaseType_t memCommand( char *pcWriteBuffer,
                            size_t xWriteBufferLen,
                            const char *pcCommandString );	

#endif
