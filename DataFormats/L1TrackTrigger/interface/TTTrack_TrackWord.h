////////
//
// class to store the 96-bit track word produced by the L1 Track Trigger.  Intended to be inherited by L1 TTTrack. 
// packing scheme given below.
//
// author: Mike Hildreth
// date:   April 9, 2019
//
///////

#ifndef L1_TRACK_TRIGGER_TRACK_WORD_H
#define L1_TRACK_TRIGGER_TRACK_WORD_H

#include <iostream>
#include <string>
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

class TTTrack_TrackWord {

 public:
  // Constructors:

  TTTrack_TrackWord() {}
  TTTrack_TrackWord(  const GlobalVector& Momentum, const GlobalPoint& POCA, double theRinv, double theChi2, 
                      double theBendChi2, unsigned int theHitMask, unsigned int iSpare );

  void setTrackWord (const GlobalVector& Momentum, const GlobalPoint& POCA, double theRinv, double theChi2,
		     double theBendChi2, unsigned int theHitMask, unsigned int iSpare );


  // getters for unpacked and converted values
  
  float get_iRinv();
  float get_iphi();
  float get_ieta();
  float get_iz0();
  float get_id0();
  float get_ichi2();
  float get_iBchi2();

  // getters for packed bits
  
  unsigned int get_hitmask();
  unsigned int get_spare();  // will need a converter(s) when spare bits are defined

  unsigned int get_RinvBits();
  unsigned int get_phiBits();
  unsigned int get_etaBits();
  unsigned int get_z0Bits();
  unsigned int get_d0Bits();
  unsigned int get_chi2Bits();
  unsigned int get_Bchi2Bits();
 
 private:

  void initialize();

  unsigned int TrackWord1;
  unsigned int TrackWord2;
  unsigned int TrackWord3;

  float LSBCurv;
  float LSBPhi;
  float LSBEta;
  float LSBZ0;
  float LSBD0;

  float chi2Bins[15];
  float Bchi2Bins[7];

  unsigned int Nchi2;
  unsigned int NBchi2;


  
}; // end of class def


#endif
