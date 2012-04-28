/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#ifndef actormodule_h
#define actormodule_h

class ActorModule {
  
  public: 
    void setName(char* name);
    char* getName();
    virtual bool exec(char* p1);
    int nDeviceTypeID;
  protected:
    char sName[21];
};

#endif