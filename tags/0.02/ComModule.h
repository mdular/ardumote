/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#ifndef commodule_h
#define commodule_h

class ComModule {
  
  public:
    virtual bool available();
    virtual char* read();
    virtual bool send(char* sCommand); 

};

#endif