import FWCore.ParameterSet.Config as cms

def customiseForPremixingInput(process):
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag

    # Replace TrackingParticles and TrackingVertices globally
    for s in process.paths_().keys():
        massSearchReplaceAnyInputTag(getattr(process, s), cms.InputTag("mix", "MergedTrackTruth"), cms.InputTag("mixData", "MergedTrackTruth"), skipLabelTest=True)
    for s in process.endpaths_().keys():
        massSearchReplaceAnyInputTag(getattr(process, s), cms.InputTag("mix", "MergedTrackTruth"), cms.InputTag("mixData", "MergedTrackTruth"), skipLabelTest=True)

    # Replace Pixel/StripDigiSimLinks only for the known modules
    def replaceInputTag(tag, old, new):
        if tag.value() == old:
            tag.setValue(new)

    def replacePixelDigiSimLink(tag):
        replaceInputTag(tag, "simSiPixelDigis", "mixData:PixelDigiSimLink")
    def replaceStripDigiSimLink(tag):
        replaceInputTag(tag, "simSiStripDigis", "mixData:StripDigiSimLink")

    for label, producer in process.producers_().iteritems():
        if producer.type_() == "ClusterTPAssociationProducer":
            replacePixelDigiSimLink(producer.pixelSimLinkSrc)
            replaceStripDigiSimLink(producer.stripSimLinkSrc)

    return process
