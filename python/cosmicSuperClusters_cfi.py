import FWCore.ParameterSet.Config as cms

#
# $Id: islandSuperClusters_cfi.py,v 1.2 2008/04/21 03:24:12 rpw Exp $
#
# Island SuperCluster producer
islandSuperClusters = cms.EDProducer("SuperClusterProducer",
    VerbosityLevel = cms.string('ERROR'),
    endcapClusterProducer = cms.string('cosmicBasicClusters'),
    barrelClusterProducer = cms.string('cosmicBasicClusters'),
    endcapClusterCollection = cms.string('CosmicEndcapBasicClusters'),
    barrelClusterCollection = cms.string('CosmicBarrelBasicClusters'),
    endcapSuperclusterCollection = cms.string('CosmicEndcapSuperClusters'),                                 
    barrelSuperclusterCollection = cms.string('CosmicBarrelSuperClusters'),
    barrelEtaSearchRoad = cms.double(0.20),
    barrelPhiSearchRoad = cms.double(0.55),                                 
    endcapEtaSearchRoad = cms.double(0.14),
    endcapPhiSearchRoad = cms.double(0.6),
    seedTransverseEnergyThreshold = cms.double(0.0),
    doBarrel = cms.bool(True),
    doEndcaps = cms.bool(False)
)


