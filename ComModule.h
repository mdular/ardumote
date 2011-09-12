#ifndef commodule_h
#define commodule_h

class ComModule {
  
  public:
    virtual bool available();
    virtual char* read();
    virtual bool send(char* sCommand); 

};

#endif