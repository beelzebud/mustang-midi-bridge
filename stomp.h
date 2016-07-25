// -*-c++-*-

#ifndef _STOMP_H
#define _STOMP_H

#include <cstring>

class Mustang;

class StompCC {

protected:
  Mustang * amp;
  unsigned char model[2];
  unsigned char slot;
  
  int continuous_control( int parm5, int parm6, int parm7, int value );
  int discrete_control( int parm5, int parm6, int parm7, int value );

public:
  StompCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : 
    amp(theAmp), 
    slot(theSlot) 
  {
    memcpy( this->model, model, 2 );
  }

  int dispatch( int cc, int value );
  const unsigned char *getModel( void ) { return model;}
  const unsigned char getSlot( void ) { return slot;}

private:
  virtual int cc29( int value ) = 0;
  virtual int cc30( int value ) = 0;
  virtual int cc31( int value ) = 0;
  virtual int cc32( int value ) = 0;
  virtual int cc33( int value ) = 0;
 };


class OverdriveCC : public StompCC {
public:
  OverdriveCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Gain
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Low
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x01, value );}
  // Mid
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x03, 0x01, value );}
  // High
  virtual int cc33( int value ) { return continuous_control( 0x04, 0x04, 0x01, value );}
};


class WahCC : public StompCC {
public:
  WahCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Mix
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Freq
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Heel Freq
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x01, value );}
  // Toe Freq
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x03, 0x01, value );}
  // High Q
  virtual int cc33( int value ) { 
    if ( value > 1 ) return 0;
    else             return discrete_control( 0x04, 0x04, 0x81, value );
  }
};


class FuzzCC : public StompCC {
public:
  FuzzCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Gain
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Octave
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x01, value );}
  // Low
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x03, 0x01, value );}
  // High
  virtual int cc33( int value ) { return continuous_control( 0x04, 0x04, 0x01, value );}
};


class FuzzTouchWahCC : public StompCC {
public:
  FuzzTouchWahCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Gain
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Sens
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x01, value );}
  // Octave
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x03, 0x01, value );}
  // Peak
  virtual int cc33( int value ) { return continuous_control( 0x04, 0x04, 0x01, value );}
};


class SimpleCompCC : public StompCC {
public:
  SimpleCompCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Type
  virtual int cc29( int value ) { 
    if ( value > 3 ) return 0;
    else             return discrete_control( 0x00, 0x05, 0x92, value );
  }
  virtual int cc30( int value ) { return 0;}
  virtual int cc31( int value ) { return 0;}
  virtual int cc32( int value ) { return 0;}
  virtual int cc33( int value ) { return 0;}
};


class CompCC : public StompCC {
public:
  CompCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Thresh
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Ratio
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x04, value );}
  // Attack
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x03, 0x01, value );}
  // Release
  virtual int cc33( int value ) { return continuous_control( 0x04, 0x04, 0x01, value );}
};


class RangerCC : public StompCC {
public:
  RangerCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Gain
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Lo-Cut
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x03, 0x01, value );}
  // Bright
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x02, 0x01, value );}
  // n/a
  virtual int cc33( int value ) { return 0;}
};


class GreenBoxCC : public StompCC {
public:
  GreenBoxCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Gain
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Tone
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x01, value );}
  // Bright
  virtual int cc32( int value ) { return continuous_control( 0x03, 0x03, 0x12, value );}
  // n/a
  virtual int cc33( int value ) { return 0;}
};


class OrangeBoxCC : public StompCC {
public:
  OrangeBoxCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Dist
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x02, 0x01, value );}
  // Tone
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x01, 0x01, value );}
  // n/a
  virtual int cc32( int value ) { return 0;}
  // n/a
  virtual int cc33( int value ) { return 0;}
};


class BlackBoxCC : public StompCC {
public:
  BlackBoxCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Dist
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x02, 0x01, value );}
  // Filter
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x01, 0x01, value );}
  // n/a
  virtual int cc32( int value ) { return 0;}
  // n/a
  virtual int cc33( int value ) { return 0;}
};


class BigFuzzCC : public StompCC {
public:
  BigFuzzCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  // Level
  virtual int cc29( int value ) { return continuous_control( 0x00, 0x00, 0x01, value );}
  // Tone
  virtual int cc30( int value ) { return continuous_control( 0x01, 0x01, 0x01, value );}
  // Sustain
  virtual int cc31( int value ) { return continuous_control( 0x02, 0x02, 0x01, value );}
  // n/a
  virtual int cc32( int value ) { return 0;}
  // n/a
  virtual int cc33( int value ) { return 0;}
};


class NullStompCC : public StompCC {
public:
  NullStompCC( Mustang * theAmp, const unsigned char *model, const unsigned char theSlot ) : StompCC(theAmp,model,theSlot) {}
private:
  virtual int cc29( int value ) { return 0;}
  virtual int cc30( int value ) { return 0;}
  virtual int cc31( int value ) { return 0;}
  virtual int cc32( int value ) { return 0;}
  virtual int cc33( int value ) { return 0;}
};


#endif
