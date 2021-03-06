import FWCore.ParameterSet.Config as cms

impactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    jetTracks = cms.InputTag("ak5JetTracksAssociatorAtVertex"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    computeProbabilities = cms.bool(True),
    computeGhostTrack = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumNumberOfHits = cms.int32(8),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumTransverseMomentum = cms.double(1.0),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    jetDirectionUsingTracks = cms.bool(False),
    jetDirectionUsingGhostTrack = cms.bool(False),
    useTrackQuality = cms.bool(False),
)
