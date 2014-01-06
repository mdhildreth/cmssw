# PYTHON configuration file for class: CMSDAS_PileupStudy.cc
# Description:  Example of simple EDAnalyzer for Pileup Studying
# Author: Mike Hildreth
# Date:  08 - January - 2012
import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")
process.load("FWCore.MessageService.MessageLogger_cfi")


#############   Set the number of events #############
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
#############   Define the source file ###############
process.source = cms.Source("PoolSource",
                             fileNames = cms.untracked.vstring(
#    '/store/data/Run2012C/BJetPlusX/AOD/PromptReco-v2/000/200/228/5A5AACA3-14E0-E111-99E6-5404A63886EF.root',
#    '/store/data/Run2012C/BJetPlusX/AOD/PromptReco-v2/000/200/228/94B45359-0FE0-E111-9CEB-001D09F23A20.root'
     '/store/mc/Summer12/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/AODSIM/PU_S7_START52_V9-v1/00000/FE8C611E-41F3-E111-A54B-001A928116D0.root',
     '/store/mc/Summer12/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph/AODSIM/PU_S7_START52_V9-v1/00000/FE1E2D03-4AF3-E111-8E54-002618943982.root'
                                         )
                            )          

##-------------------- Communicate with the DB -----------------------
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'START38_V13::All'
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

#############   Correct Calo Jets on the fly #########
process.PUStudy = cms.EDAnalyzer("CMSDAS_PileupStudy",
                                  vertexSrc = cms.InputTag("offlinePrimaryVertices")
)

#############   Path       ###########################
process.p = cms.Path(process.PUStudy)


#############   Format MessageLogger #################
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#############  This is how CMS handles output ROOT files #################
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("PU_histos.root")
 )
