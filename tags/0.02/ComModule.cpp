/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "ComModule.h"

bool ComModule::available() { return false; }
char* ComModule::read() { return "null"; }
bool ComModule::send(char* sCommand) { return false; }
