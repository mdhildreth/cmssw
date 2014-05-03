#ifndef GctDigiToRaw_h
#define GctDigiToRaw_h

// -*- C++ -*-
//
// Package:    GctDigiToRaw
// Class:      GctDigiToRaw
// 
/**\class GctDigiToRaw GctDigiToRaw.cc EventFilter/GctRawToDigi/src/GctDigiToRaw.cc

 Description: Produce fake GCT raw data from digis

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Jim Brooke
//         Created:  Wed Nov  1 11:57:10 CET 2006
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/FEDRawData/interface/FEDRawData.h"

// GCT input data formats
#include "DataFormats/L1CaloTrigger/interface/L1CaloEmCand.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegionDetId.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"

#include "EventFilter/GctRawToDigi/src/GctFormatTranslateMCLegacy.h"

//
// class decleration
//

class GctDigiToRaw : public edm::EDProducer {
 public:
  explicit GctDigiToRaw(const edm::ParameterSet&);
  ~GctDigiToRaw();
  
 private: // methods
  virtual void beginJob();
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void print(FEDRawData& data);

 private:  // members

  // input tags
  edm::InputTag rctInputLabel_;
  edm::InputTag gctInputLabel_;

  // consumes tokens

  edm::EDGetTokenT<L1GctEmCandCollection> isoEm_token_;
  edm::EDGetTokenT<L1GctEmCandCollection> nonIsoEm_token_;
  edm::EDGetTokenT<L1GctJetCandCollection> cenJets_token_;
  edm::EDGetTokenT<L1GctJetCandCollection> forJets_token_;
  edm::EDGetTokenT<L1GctJetCandCollection> tauJets_token_;
  edm::EDGetTokenT<L1GctEtTotalCollection> etTotal_token_;
  edm::EDGetTokenT<L1GctEtHadCollection> etHad_token_;
  edm::EDGetTokenT<L1GctEtMissCollection> etMiss_token_;
  edm::EDGetTokenT<L1GctHFRingEtSumsCollection> hfRingSums_token_;
  edm::EDGetTokenT<L1GctHFBitCountsCollection> hfBitCounts_token_;
  edm::EDGetTokenT<L1GctHtMissCollection> htMiss_token_;
  edm::EDGetTokenT<L1GctJetCountsCollection> jetCounts_token_;
  edm::EDGetTokenT<L1CaloEmCollection> rctEm_token_;
  edm::EDGetTokenT<L1CaloRegionCollection> rctCalo_token_;

  // pack flags
  bool packRctEm_;
  bool packRctCalo_;

  // FED numbers
  int fedId_;            

  // print out for each event
  bool verbose_;

  // counter events
  int counter_;          
  
  // digi to block converter
  GctFormatTranslateMCLegacy formatTranslator_;

};

#endif
