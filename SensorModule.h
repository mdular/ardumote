#ifndef sensormodule_h
#define sensormodule_h

class SensorModule {
  
  public:
    virtual bool available();
    virtual long getValue();
    char* getName();
    int nDeviceTypeID;

  protected:
    char sName[21];
    void setName(char* name);
};

#endif