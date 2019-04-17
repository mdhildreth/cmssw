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

//Constructor - turn track parameters into 96-bit word

TTTrack_TrackWord::TTTrack_TrackWord( const GlobalVector& Momentum, const GlobalPoint& POCA, double theRinv, double theChi2, double theBendChi2, unsigned int theHitMask, unsigned int iSpare  ) {

  // first, derive quantities to be packed

  float rPhi = Momentum.phi();  // this needs to be phi relative to center of sector ****
  float rEta = Momentum.eta();
  float rZ0 = POCA.z();
  float rD0 = POCA.perp();

  // bin, convert to integers, and pack

   /*
    Current packing scheme. Any changes here ripple everywhere!
    
    uint word1 = 16 (eta) + 12 (z0) + 4 (chi2) = 32 bits
    uint word2 = 12 (phi) + 13 (d0) + 7 (hitmask) = 32 bits
    uint word3 = 15 (pT) + 3 (bend chi2) + 14 (spare/TMVA) = 32 bits
   */
  

  int isign;
  unsigned int seg1, seg2, seg3;
  seg1 = 0; seg2 = 0; seg3 = 0;

  // first 32-bit word

  //eta
  isign = (rEta<0);

  int myEta = int(fabs(rEta)/LSBEta);
  if(myEta > 0x7FFF) myEta = 0x7FFF;
  if(isign>0) isign = (isign<<15);
  myEta = isign+myEta;
  seg1 = (myEta << 16);

  //z0
  isign = (rZ0<0);

  int myZ0 = int(fabs(rZ0)/LSBZ0);
  if(myZ0 > 0x7FF) myZ0 = 0x7FF;
  if(isign>0) isign = (isign<<11);
  myZ0 = isign+myZ0;
  seg2 = (myZ0 << 4);

    //chi2 has non-linear bins
  
  unsigned int myChi2 = 0;
  
  for(unsigned int ibin=0; ibin<Nchi2; ++ibin) {
    myChi2 = ibin; 
    if(theChi2<chi2Bins[ibin]) break;
  }

  seg3 = myChi2;

    //set bits
  
  TrackWord1 = seg1 + seg2 + seg3;
  seg1 = 0; seg2 = 0; seg3 = 0;
  
  //second 32-bit word

  //phi
  isign = (rPhi<0);

  int myPhi = int(fabs(rPhi)/LSBPhi);
  if(myPhi > 0x7FF) myPhi = 0x7FF;
  if(isign>0) isign = (isign<<11);
  myPhi = isign+myPhi;
  seg1 = (myPhi << 20);

  isign = (rD0<0);

  //d0
  int myD0 = int(fabs(rD0)/LSBD0);
  if(myD0 > 0xFFF) myD0 = 0xFFF;
  if(isign>0) isign = (isign<<12);
  myD0 = isign+myD0;
  seg2 = (myD0 << 7);

  //HitMask
  seg3 = theHitMask;

    //set bits

  TrackWord2 = seg1 + seg2 + seg3;
  seg1 = 0; seg2 = 0; seg3 = 0;

  //third 32-bit word

  //Rinv
  isign = (theRinv<0);
  
  int myCurv = int(fabs(theRinv)/LSBCurv);
  if(myCurv > 0x3FFF) myCurv = 0x3FFF;
  if(isign>0) isign = (isign<<14);
  myCurv = isign+myCurv;
  seg1 = (myCurv << 17);

  //bend chi2 - non-linear bins
  unsigned int myBchi2 = 0;
  
  for(unsigned int ibin=0; ibin<NBchi2; ++ibin) {
    myBchi2 = ibin; 
    if(theBendChi2<Bchi2Bins[ibin]) break;
  }

  seg2 = (myBchi2<<14);

  // spare bits
  if(iSpare > 0x3FFF) iSpare = 0x3FFF;
  seg3 = iSpare;

     //set bits

  TrackWord3 = seg1 + seg2 + seg3;
  
}
  // unpack

float TTTrack_TrackWord::get_ieta(){
  int isign = 1;
  unsigned int bits =  (TrackWord1 & 0xFFFF0000) >> 16;
  float unpEta = (bits & 0x7FFF)*LSBEta;
  if (bits - (bits & 0x7FFF) > 0 ) isign = -1;
  unpEta = isign * unpEta;
  return unpEta;
}

unsigned int TTTrack_TrackWord::get_etaBits(){
  unsigned int bits =  (TrackWord1 & 0xFFFF0000) >> 16;
  return bits;
}

float TTTrack_TrackWord::get_iz0(){
  int isign = 1;
  unsigned int bits =   (TrackWord1 & 0x0000FFF0) >> 4;
  float unpZ0 = (bits & 0x7FF)*LSBZ0;
  if (bits - (bits & 0x7FF) > 0 ) isign = -1;
  unpZ0 = isign * unpZ0;
  return unpZ0;
}

unsigned int TTTrack_TrackWord::get_z0Bits(){
  unsigned int bits =   (TrackWord1 & 0x0000FFF0) >> 4;
  return bits;
}

float TTTrack_TrackWord::get_ichi2(){
  unsigned int bits = (TrackWord1 & 0x0000000F);
  float unpChi2 = chi2Bins[bits];
  return unpChi2;
}

unsigned int TTTrack_TrackWord::get_chi2Bits(){
  unsigned int bits = (TrackWord1 & 0x0000000F);
  return bits;
}

float TTTrack_TrackWord::get_iphi(){
  int isign = 1;
  unsigned int bits =   (TrackWord2 & 0xFFF00000) >> 20;
  float unpPhi = (bits & 0x7FF)*LSBPhi;
  if (bits - (bits & 0x7FF) > 0 ) isign = -1;
  unpPhi = isign * unpPhi;
  return unpPhi;
}

unsigned int TTTrack_TrackWord::get_phiBits(){
  unsigned int bits =   (TrackWord2 & 0xFFF00000) >> 20;
  return bits;
}

float TTTrack_TrackWord::get_id0(){
  int isign = 1;
  unsigned int bits =   (TrackWord2 & 0x000FFF80) >> 7;
  float unpD0 = (bits & 0xFFF)*LSBD0;
  if (bits - (bits & 0xFFF) > 0 ) isign = -1;
  unpD0 = isign * unpD0;
  return unpD0;
}

unsigned int TTTrack_TrackWord::get_d0Bits(){
  unsigned int bits =   (TrackWord2 & 0x000FFF80) >> 7;
  return bits;
}

unsigned int TTTrack_TrackWord::get_hitmask(){
  unsigned int bits = (TrackWord2 & 0x0000007F);
  return bits;
}

float TTTrack_TrackWord::get_iRinv(){
  int isign = 1;
  unsigned int bits =   (TrackWord3 & 0xFFFE0000) >> 17;
  float unpCurv = (bits & 0x3FFF)*LSBCurv;
  if (bits - (bits & 0x3FFF) > 0 ) isign = -1;
  unpCurv = isign * unpCurv;
  return unpCurv;
}

float TTTrack_TrackWord::get_iBchi2(){
  unsigned int bits =   (TrackWord3 & 0x0001C000) >> 14;
  float unpBChi2 = Bchi2Bins[bits];
  return unpBChi2;
}

unsigned int TTTrack_TrackWord::get_Bchi2Bits(){
  unsigned int bits =   (TrackWord3 & 0x0001C000) >> 14;
  return bits;
}

unsigned int TTTrack_TrackWord::get_spare(){
  unsigned int bits =   (TrackWord3 & 0x00003FFF);
  return bits;
}


void TTTrack_TrackWord::initialize(){

  /* bits for packing:

  signed quantities (one bit for sign):
  
  q/R = 14+1
  phi = 11+1  (relative to sector center)
  eta = 15+1
  z0  = 11+1
  d0  = 12+1

  unsigned:

  chi2     = 4
  BendChi2 = 3
  hitmask  = 7
  Spare    = 14

  */

  // define bits, 1<<N = 2^N

  unsigned int CurvBins = (1<<14);
  unsigned int phiBins  = (1<<11);
  unsigned int etaBins  = (1<<15);
  unsigned int z0Bins   = (1<<11);
  unsigned int d0Bins   = (1<<12);
  Nchi2    = (1<<4);
  NBchi2   = (1<<3);

  
  // establish binning

  float maxCurv = 0.5;  // 2 GeV pT
  float maxPhi  = 0.35; // relative to the center of the sector
  float maxEta  = 2.5;
  float maxZ0   = 20.;
  float maxD0   = 15.;

  LSBCurv = maxCurv/float(CurvBins);
  LSBPhi  = maxPhi/float(phiBins);
  LSBEta  = maxEta/float(etaBins);
  LSBZ0   = maxZ0/float(z0Bins);
  LSBD0   = maxD0/float(d0Bins);

  chi2Bins[0] = 0.25;
  chi2Bins[1] = 0.5;
  chi2Bins[2] = 1.0;
  chi2Bins[3] = 2.;
  chi2Bins[4] = 3.;
  chi2Bins[5] = 5.;
  chi2Bins[6] = 7.;
  chi2Bins[7] = 10.;
  chi2Bins[8] = 15.;
  chi2Bins[9] = 20.;
  chi2Bins[10] = 40.;
  chi2Bins[11] = 60.;
  chi2Bins[12] = 100.;
  chi2Bins[13] = 200.;
  chi2Bins[14] = 500.;
    
  Bchi2Bins[0] = 0.5;
  Bchi2Bins[1] = 1.25;
  Bchi2Bins[2] = 2.0;
  Bchi2Bins[3] = 3.0;
  Bchi2Bins[4] = 5.0;
  Bchi2Bins[5] = 10.;
  Bchi2Bins[6] = 50.;
  
};

#endif
