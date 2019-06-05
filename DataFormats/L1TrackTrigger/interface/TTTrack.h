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
    unsigned int theSector;
    unsigned int theWedge;
    double       theStubPtConsistency;
    double       theChi2;
    unsigned int NumFitPars;
    unsigned int theHitMask;
    float        an_MVA_Value;
    float        another_MVA_Value;

  public:
    /// Constructors
    TTTrack();
    TTTrack( std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > aStubs );

    /// Destructor
    ~TTTrack();

    /// Track components
    std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > getStubRefs() const        { return theStubRefs; }
    void addStubRef( edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > aStub )                  { theStubRefs.push_back( aStub ); }
    void setStubRefs( std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > aStubs ) { theStubRefs = aStubs; }

    /// Track momentum
    GlobalVector getMomentum() const;
    void         setMomentum( GlobalVector aMomentum);

    /// Track curvature
    double getRInv() const;
    void   setRInv( double aRInv );

    /// POCA
    GlobalPoint getPOCA() const;
    void        setPOCA( GlobalPoint aPOCA );

    /// Sector
    unsigned int getSector() const                 { return theSector; }
    void         setSector( unsigned int aSector ) { theSector = aSector; }
    unsigned int getWedge() const                  { return theWedge; }
    void         setWedge( unsigned int aWedge )   { theWedge = aWedge; }

    /// Chi2
    double       getChi2() const;
    double       getChi2Red() const;
    void         setChi2( double aChi2 );

    /// Stub Pt consistency
    double       getStubPtConsistency() const;
    void         setStubPtConsistency( double aPtConsistency );

    void         setFitParNo( unsigned int aFitParNo );

    void         setTrackWordBits();

/*
    /// Superstrip
    /// Here to prepare inclusion of AM L1 Track finding
    uint32_t getSuperStrip() const { return 0; }
*/
    /// Duplicate identification
    bool isTheSameAs( TTTrack< T > aTrack ) const;

    /// Additional quality criteria
    bool hasStubInBarrel( unsigned int aLayer ) const;

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
  theSector   = 0;
  theWedge    = 0;
  theChi2     = 0.0;
  theStubPtConsistency = 0.0;
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
  theSector   = 0;
  theWedge    = 0;
  theChi2     = 0.0;
  theStubPtConsistency = 0.0;
  NumFitPars  = 0;
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
GlobalVector TTTrack< T >::getMomentum() const{

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
double TTTrack< T >::getRInv() const {

  if (NumFitPars==5 || NumFitPars ==4) {
    return theRInv;
  }
  else return 0.0;

}


template< typename T >
void TTTrack< T >::setPOCA(GlobalPoint aPOCA){

  thePOCA=aPOCA;

  return;

}

template< typename T >
GlobalPoint TTTrack< T >::getPOCA() const
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
double TTTrack< T >::getChi2() const
{

  if (NumFitPars==5 || NumFitPars ==4) {
    return theChi2;
  }
  else return 0.0;

}



/// Chi2 reduced
template< typename T >
double TTTrack< T >::getChi2Red() const
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
double TTTrack< T >::getStubPtConsistency() const
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

  setTrackWord( theMomentum, thePOCA, theRInv, theChi2, theStubPtConsistency, theHitMask, sparebits );

  return;

}




/// Duplicate identification
template< typename T>
bool TTTrack< T >::isTheSameAs( TTTrack< T > aTrack ) const
{
  /// Take the other stubs
  std::vector< edm::Ref< edmNew::DetSetVector< TTStub< T > >, TTStub< T > > > otherStubRefs = aTrack.getStubRefs();

  /// Count shared stubs
  unsigned int nShared = 0;
  for ( unsigned int i = 0; i < theStubRefs.size() && nShared < 2; i++)
  {
    for ( unsigned int j = 0; j < otherStubRefs.size() && nShared < 2; j++)
    {
      if ( theStubRefs.at(i) == otherStubRefs.at(j) )
      {
        nShared++;
      }
    }
  }

  /// Same track if 2 shared stubs
  return ( nShared > 1 );
}

/// Quality criteria: does it have a Stub in a specific Barrel Layer?
template< typename T >
bool TTTrack< T >::hasStubInBarrel( unsigned int aLayer ) const
{
  for ( unsigned int i = 0; i < theStubRefs.size(); i++)
  {
    DetId detid =  theStubRefs.at(i)->getDetId();
    if ( detid.subdetId()==StripSubdetector::TOB )
    {
      return true;
    }
  }

  return false;
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
