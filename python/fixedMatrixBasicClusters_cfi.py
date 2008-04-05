import FWCore.ParameterSet.Config as cms

# FixedMatrix BasicCluster producer
fixedMatrixBasicClusters = cms.EDProducer("FixedMatrixClusterProducer",
    posCalc_x0 = cms.double(0.89),
    endcapHitProducer = cms.string('ecalRecHit'),
    posCalc_t0_endcPresh = cms.double(1.2),
    barrelClusterCollection = cms.string('fixedMatrixBarrelBasicClusters'),
    IslandEndcapSeedThr = cms.double(0.18),
    posCalc_t0_endc = cms.double(3.1),
    barrelShapeAssociation = cms.string('fixedMatrixBarrelShapeAssoc'),
    posCalc_w0 = cms.double(4.2),
    posCalc_logweight = cms.bool(True),
    clustershapecollectionEE = cms.string('fixedMatrixEndcapShape'),
    clustershapecollectionEB = cms.string('fixedMatrixBarrelShape'),
    VerbosityLevel = cms.string('ERROR'),
    endcapHitCollection = cms.string('EcalRecHitsEE'),
    barrelHitProducer = cms.string('ecalRecHit'),
    endcapShapeAssociation = cms.string('fixedMatrixEndcapShapeAssoc'),
    barrelHitCollection = cms.string('EcalRecHitsEB'),
    posCalc_t0_barl = cms.double(7.4),
    endcapClusterCollection = cms.string('fixedMatrixEndcapBasicClusters'),
    IslandBarrelSeedThr = cms.double(0.5)
)

