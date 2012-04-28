/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#ifndef sensormodule_h
#define sensormodule_h

class SensorModule {
  
  public:
    virtual bool available();
    virtual char* getValue();
    char* getName();
    int nDeviceTypeID;

  protected:
    char sName[21];
    void setName(char* name);
};

#endif