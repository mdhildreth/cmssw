// CMSDAS_PileupStudy.h
// Description: A basic analyzer for pileup reweighting studies
// Author: Mike Hildreth
// Date: January 8, 2012

#include "PhysicsTools/Examples/interface/CMSDAS_PileupStudy.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include <TH1D.h>

CMSDAS_PileupStudy::CMSDAS_PileupStudy(edm::ParameterSet const& params) :
  edm::EDAnalyzer(),
  vertexSrc_(params.getParameter<edm::InputTag>("vertexSrc"))
{
  // setup file service
  edm::Service<TFileService> fs;

  // setup histograms
  TNPUInTime_ = fs->make<TH1D>("TNPUInTime","No. in-time pileup interactions",60,0.,60.);
  TNPUTrue_ = fs->make<TH1D>("TNPUTrue","True pileup interactions",60,0.,60.);
  TNVTX_ = fs->make<TH1D>("TNVTX","No. reconstructed vertices",60,0.,60.);
}

void CMSDAS_PileupStudy::analyze(const edm::Event & iEvent, const edm::EventSetup & iSetup) {

  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;


  float npT=-1.;
  float npIT=-1.;


  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {

    int BX = PVI->getBunchCrossing();

    if(BX == 0) {
      npT = PVI->getTrueNumInteractions();
      npIT = PVI->getPU_NumInteractions();
    }
  }

  TNPUTrue_->Fill(npT);
  TNPUInTime_->Fill(npIT);   

  edm::Handle< std::vector<reco::Vertex> > vertices_h;
  iEvent.getByLabel(vertexSrc_, vertices_h);
  if (!vertices_h.isValid()) {
    std::cout<<"Didja hear the one about the empty vertex collection?\n";
    return;
  }
  
  // require in the event that there is at least one reconstructed vertex
  if(vertices_h->size()<=0) return;

  // pick the first (i.e. highest sum pt) verte
  const reco::Vertex* theVertex=&(vertices_h->front());

  // require that the vertex meets certain criteria
  if(theVertex->ndof()<5) return;
  if(fabs(theVertex->z())>24.0) return;
  if(fabs(theVertex->position().rho())>2.0) return;

  std::vector<reco::Vertex>::const_iterator itv;

  int NVtx = 0;

  // now, count vertices

  for (itv = vertices_h->begin(); itv != vertices_h->end(); ++itv) {

    // require that the vertex meets certain criteria
    if(itv->ndof()<5) continue;
    if(fabs(itv->z())>50.0) continue;
    if(fabs(itv->position().rho())>2.0) continue;

    ++NVtx;
  }

  TNVTX_->Fill(float(NVtx));
  return;
}

void CMSDAS_PileupStudy::endJob() {
}

DEFINE_FWK_MODULE(CMSDAS_PileupStudy);
