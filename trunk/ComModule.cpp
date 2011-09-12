#include "ComModule.h"

bool ComModule::available() { return false; }
char* ComModule::read() { return "null"; }
bool ComModule::send(char* sCommand) { return false; }
