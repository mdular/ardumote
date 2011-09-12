#ifndef sensormodule_h
#define sensormodule_h

class SensorModule {
  
  public:
    virtual bool available();
    virtual long getValue();

};

#endif