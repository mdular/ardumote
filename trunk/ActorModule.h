#ifndef actormodule_h
#define actormodule_h

class ActorModule {
  
  public: 
    virtual bool exec(long p1);
    virtual bool exec(long p1, long p2);
    virtual bool exec(long p1, long p2, long p3);
    virtual bool exec(long p1, long p2, long p3, long p4);
    virtual bool exec(long p1, long p2, long p3, long p4, long p5);

};

#endif