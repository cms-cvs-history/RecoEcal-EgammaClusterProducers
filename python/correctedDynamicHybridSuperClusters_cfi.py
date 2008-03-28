import FWCore.ParameterSet.Config as cms

# Energy scale correction for Hybrid SuperClusters
correctedDynamicHybridSuperClusters = cms.EDFilter("EgammaSCCorrectionMaker",
    corectedSuperClusterCollection = cms.string(''),
    sigmaElectronicNoise = cms.double(0.03),
    superClusterAlgo = cms.string('DynamicHybrid'),
    etThresh = cms.double(0.0),
    rawSuperClusterProducer = cms.InputTag("dynamicHybridSuperClusters"),
    applyEnergyCorrection = cms.bool(True),
    VerbosityLevel = cms.string('ERROR'),
    # energy correction
    dyn_fCorrPset = cms.PSet(
        brLinearThr = cms.double(12.0),
        fBremVec = cms.vdouble(-0.01762, 0.04224, 0.9793, 0.0008075, 1.774),
        fEtEtaVec = cms.vdouble(0.9929, -0.01751, -4.636, 5.945, 737.9, 4.057, 1.023, 8.0)
    ),
    recHitProducer = cms.InputTag("ecalRecHit","EcalRecHitsEB")
)


