/*! \class   TTTrack
 *  \brief   Class to store the L1 Track Trigger tracks
 *  \details After moving from SimDataFormats to DataFormats,
 *           the template structure of the class was maintained
 *           in order to accomodate any types other than PixelDigis
 *           in case there is such a need in the future.
 *
 *  \author Nicola Pozzobon
 *  \date   2013, Jul 12
 *
 */

#ifndef L1_TRACK_TRIGGER_TRACK_FORMAT_H
#define L1_TRACK_TRIGGER_TRACK_FORMAT_H

#include "DataFormats/L1TrackTrigger/interface/TTStub.h"
#include "DataFormats/L1TrackTrigger/interface/TTTrack_TrackWord.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/Phase2TrackerDigi/interface/Phase2TrackerDigi.h"

template< typename T >
class TTTrack : public TTTrack_TrackWord
{
  private:
    /// Data members
    std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > >
                 theStubRefs;
    GlobalVector theMomentum;
    GlobalPoint  thePOCA;
    double       theRInv;
    double       thePhi;
    double       theTanL;
    double       theD0;
    double       theZ0;
    unsigned int thePhiSector;
    double       theStubPtConsistency;
    double       theChi2;
    unsigned int NumFitPars;
    unsigned int theHitPattern;
    float        an_MVA_Value;
    float        another_MVA_Value;
    int          theTrackSeed;
    
  public:
    /// Constructors
    TTTrack();
    TTTrack( std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > aStubs );

    TTTrack( double aRinv, double aphi, double aeta, double az0, double ad0, double aChi2, unsigned int theHitpattern, unsigned int nPar);

    /// Destructor
    ~TTTrack();

    /// Track components
    std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > getStubRefs() const        { return theStubRefs; }
    void addStubRef( edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > aStub )                  { theStubRefs.push_back( aStub ); }
    void setStubRefs( std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > aStubs ) { theStubRefs = aStubs; }

    /// Track momentum
    GlobalVector Momentum() const;
    void         setMomentum( GlobalVector aMomentum);

    /// Track curvature
    double RInv() const;
    
    /// Track phi
    double phi() const;

    /// Track tanL
    double TanL() const;
    
    /// Track d0
    double d0() const;
    
    /// Track z0
    double z0() const;

    /// Track eta
    double eta() const;

    void   setRInv( double aRInv );

    /// POCA
    GlobalPoint POCA() const;
    void        setPOCA( GlobalPoint aPOCA );

    /// Phi Sector
    unsigned int PhiSector() const                 { return thePhiSector; }
    void         setPhiSector( unsigned int aSector ) { thePhiSector = aSector; }

    /// Track seeding (for debugging)
    unsigned int TrackSeed() const                 { return theTrackSeed; }
    void         setTrackSeed( int aSeed ) { theTrackSeed = aSeed; }
    
    
    /// Chi2
    double       Chi2() const;
    double       Chi2Red() const;
    void         setChi2( double aChi2 );

    /// Stub Pt consistency
    double       StubPtConsistency() const;
    void         setStubPtConsistency( double aPtConsistency );

    void         setFitParNo( unsigned int aFitParNo );

    void         setTrackWordBits();
    void         testTrackWordBits();

    /// Information
    std::string print( unsigned int i = 0 ) const;
  

}; /// Close class

/*! \brief   Implementation of methods
 *  \details Here, in the header file, the methods which do not depend
 *           on the specific type <T> that can fit the template.
 *           Other methods, with type-specific features, are implemented
 *           in the source file.
 */
 
/// Default Constructor
template< typename T >
TTTrack< T >::TTTrack()
{
  theStubRefs.clear();
  theMomentum = GlobalVector(0.0,0.0,0.0);
  theRInv     = 0.0;
  thePOCA     = GlobalPoint(0.0,0.0,0.0);
  thePhiSector   = 0;
  theTrackSeed   = 0;
  theChi2     = 0.0;  theStubPtConsistency = 0.0;
  NumFitPars  = 0;
}

/// Another Constructor
template< typename T >
TTTrack< T >::TTTrack( std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > aStubs )
{
  theStubRefs     = aStubs;
  theMomentum = GlobalVector(0.0,0.0,0.0);
  theRInv     = 0.0;
  thePOCA     = GlobalPoint(0.0,0.0,0.0);
  thePhiSector   = 0;
  theTrackSeed   = 0;
  theChi2     = 0.0;
  theStubPtConsistency = 0.0;
  NumFitPars  = 0;
}


template< typename T >
TTTrack< T >::TTTrack( double aRinv, double aphi, double aeta, double az0, double ad0, double aChi2, unsigned int aHitPattern, unsigned int nPar)
{
  theStubRefs.clear();
  theMomentum = GlobalVector(0.0,0.0,0.0);
  theRInv     = aRinv;
  thePOCA     = GlobalPoint(ad0*cos(aphi),ad0*sin(aphi),az0);
  thePhiSector   = 0;
  theTrackSeed   = 0;
  theChi2     = aChi2;
  theStubPtConsistency = 0.0;
  NumFitPars  = nPar;
  theHitPattern = aHitPattern;
  // should probably fill the momentum vectur
}


/// Destructor
template< typename T >
TTTrack< T >::~TTTrack(){}

template< typename T >
void TTTrack< T >::setFitParNo(unsigned int nPar) {

  NumFitPars = nPar;

  return;

}



template< typename T >
void TTTrack< T >::setMomentum( GlobalVector aMomentum ) {

  theMomentum=aMomentum;

  return;
} 


template< typename T >
GlobalVector TTTrack< T >::Momentum() const{

  if (NumFitPars==5 || NumFitPars ==4) {
    return theMomentum;
  }
  else return GlobalVector(0.0,0.0,0.0);

} 


template< typename T >
void TTTrack< T >::setRInv(double aRInv) {

  theRInv=aRInv;

  return;

}


template< typename T >
double TTTrack< T >::RInv() const {

  if (NumFitPars==5 || NumFitPars ==4) {
    return theRInv;
  }
  else return 0.0;

}

template< typename T >
double TTTrack< T >::TanL() const {

  if (NumFitPars==5 || NumFitPars ==4) {
    return theTanL;
  }
  else return 0.0;

}

template< typename T >
double TTTrack< T >::phi() const {

  if (NumFitPars==5 || NumFitPars ==4) {
    return thePhi;
  }
  else return 0.0;

}

template< typename T >
double TTTrack< T >::d0() const {

  if (NumFitPars==5 || NumFitPars ==4) {
    return theD0;
  }
  else return 0.0;

}

template< typename T >
double TTTrack< T >::z0() const {

  if (NumFitPars==5 || NumFitPars ==4) {
    return theZ0;
  }
  else return 0.0;

}


template< typename T >
void TTTrack< T >::setPOCA(GlobalPoint aPOCA){

  thePOCA=aPOCA;

  return;

}

template< typename T >
GlobalPoint TTTrack< T >::POCA() const
{

  if (NumFitPars==5 || NumFitPars ==4) {
    return thePOCA;
  }
  else return GlobalPoint(0.0,0.0,0.0);

}

/// Chi2 
template< typename T >
void TTTrack< T >::setChi2(double aChi2) {

  theChi2=aChi2;

  return;

}



/// Chi2 
template< typename T >
double TTTrack< T >::Chi2() const
{

  if (NumFitPars==5 || NumFitPars ==4) {
    return theChi2;
  }
  else return 0.0;

}



/// Chi2 reduced
template< typename T >
double TTTrack< T >::Chi2Red() const
{

  if (NumFitPars==5 || NumFitPars ==4) {
    return theChi2/( 2*theStubRefs.size() - NumFitPars );
  }
  else return 0.0;

}


/// StubPtConsistency 
template< typename T >
void TTTrack< T >::setStubPtConsistency(double aStubPtConsistency) {

  theStubPtConsistency=aStubPtConsistency;

  return;

}



/// StubPtConsistency 
template< typename T >
double TTTrack< T >::StubPtConsistency() const
{

  if (NumFitPars==5 || NumFitPars ==4) {
    return theStubPtConsistency;
  }
  else return 0.0;
}

/// Set bits in 96-bit Track word
template< typename T >
void TTTrack< T >::setTrackWordBits() 
{
  if (!(NumFitPars==4||NumFitPars==5)) {
    edm::LogError("TTTrack") << " setTrackWordBits method is called with NumFitPars="<<NumFitPars<< " only possible values are 4/5" << std::endl;
    return;
  }

  unsigned int sparebits = 0;

  // missing conversion of global phi to difference from sector center phi

  setTrackWord( theMomentum, thePOCA, theRInv, theChi2, theStubPtConsistency, theHitPattern, sparebits );

  return;

}

/// Test bits in 96-bit Track word
template< typename T >
void TTTrack< T >::testTrackWordBits() 
{


  float rPhi = theMomentum.phi();  // this needs to be phi relative to center of sector **** 
  float rEta = theMomentum.eta();
  float rZ0 = thePOCA.z();
  float rD0 = thePOCA.perp();
  
  std::cout << " phi " <<  rPhi << " " << get_iphi() << std::endl;
  std::cout << " eta " <<  rEta << " " << get_ieta() << std::endl; 
  std::cout << " Z0 " <<  rZ0 << " " << get_iz0() << std::endl; 
  std::cout << " D0 " << rD0 << " " << get_id0() << std::endl; 
  std::cout << " Rinv " << theRInv << " " << get_iRinv() << std::endl; 
  std::cout << " chi2 " <<  theChi2 << " " << get_ichi2() << std::endl; 

  return;

}



/// Information
template< typename T >
std::string TTTrack< T >::print( unsigned int i ) const
{
  std::string padding("");
  for ( unsigned int j = 0; j != i; ++j )
  {
    padding+="\t";
  }

  std::stringstream output;
  output<<padding<<"TTTrack:\n";
  padding+='\t';
  output << '\n';
  unsigned int iStub = 0;

  typename std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > >::const_iterator stubIter;
  for ( stubIter = theStubRefs.begin();
        stubIter!= theStubRefs.end();
        ++stubIter )
  {
    output << padding << "stub: " << iStub++ << ", DetId: " << ((*stubIter)->getDetId()).rawId() << '\n';
  }

  return output.str();
}


template< typename T >
std::ostream& operator << ( std::ostream& os, const TTTrack< T >& aTTTrack ) { return ( os << aTTTrack.print() ); }


#endif
