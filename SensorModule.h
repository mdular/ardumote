#ifndef sensormodule_h
#define sensormodule_h

class SensorModule {
  
  public:
    virtual bool available();
    virtual char* getValue();
    char* getName();
    int nDeviceTypeID;

  protected:
    char sName[11];
    void setName(char* name);
};

#endif