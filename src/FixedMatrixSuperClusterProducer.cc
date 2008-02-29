// C/C++ headers
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

// Framework
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/Exception.h"

// Reconstruction Classes
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

// Class header file
#include "RecoEcal/EgammaClusterProducers/interface/FixedMatrixSuperClusterProducer.h"


FixedMatrixSuperClusterProducer::FixedMatrixSuperClusterProducer(const edm::ParameterSet& ps)
{
  // The verbosity level
  std::string verbosityString = ps.getParameter<std::string>("VerbosityLevel");
  if      (verbosityString == "DEBUG")   verbosity = FixedMatrixBremRecoveryClusterAlgo::pDEBUG;
  else if (verbosityString == "WARNING") verbosity = FixedMatrixBremRecoveryClusterAlgo::pWARNING;
  else if (verbosityString == "INFO")    verbosity = FixedMatrixBremRecoveryClusterAlgo::pINFO;
  else                                   verbosity = FixedMatrixBremRecoveryClusterAlgo::pERROR;

  endcapClusterProducer_ = ps.getParameter<std::string>("endcapClusterProducer");
  barrelClusterProducer_ = ps.getParameter<std::string>("barrelClusterProducer");

  endcapClusterCollection_ = ps.getParameter<std::string>("endcapClusterCollection");
  barrelClusterCollection_ = ps.getParameter<std::string>("barrelClusterCollection");

  endcapSuperclusterCollection_ = ps.getParameter<std::string>("endcapSuperclusterCollection");
  barrelSuperclusterCollection_ = ps.getParameter<std::string>("barrelSuperclusterCollection");

  doBarrel_ = ps.getParameter<bool>("doBarrel");
  doEndcaps_ = ps.getParameter<bool>("doEndcaps");

  barrelEtaSearchRoad_ = ps.getParameter<double>("barrelEtaSearchRoad");
  barrelPhiSearchRoad_ = ps.getParameter<double>("barrelPhiSearchRoad");
  endcapEtaSearchRoad_ = ps.getParameter<double>("endcapEtaSearchRoad");
  endcapPhiSearchRoad_ = ps.getParameter<double>("endcapPhiSearchRoad");
  seedTransverseEnergyThreshold_ = ps.getParameter<double>("seedTransverseEnergyThreshold");

  const edm::ParameterSet bremRecoveryPset = ps.getParameter<edm::ParameterSet>("bremRecoveryPset");
  bool dynamicPhiRoad = ps.getParameter<bool>("dynamicPhiRoad");

  bremAlgo_p = new FixedMatrixBremRecoveryClusterAlgo(barrelEtaSearchRoad_, barrelPhiSearchRoad_, 
					 endcapEtaSearchRoad_, endcapPhiSearchRoad_, 
                                         dynamicPhiRoad, bremRecoveryPset, seedTransverseEnergyThreshold_, verbosity);

  produces< reco::SuperClusterCollection >(endcapSuperclusterCollection_);
  produces< reco::SuperClusterCollection >(barrelSuperclusterCollection_);

  totalE = 0;
  noSuperClusters = 0;
  nEvt_ = 0;
}


FixedMatrixSuperClusterProducer::~FixedMatrixSuperClusterProducer()
{
  delete bremAlgo_p;
}

void
FixedMatrixSuperClusterProducer::endJob() {
  double averEnergy = 0.;
  std::ostringstream str;
  str << "FixedMatrixSuperClusterProducer::endJob()\n"
      << "  total # reconstructed super clusters: " << noSuperClusters << "\n"
      << "  total energy of all clusters: " << totalE << "\n";
  if(noSuperClusters>0) { 
    averEnergy = totalE / noSuperClusters;
    str << "  average SuperCluster energy = " << averEnergy << "\n";
  }
  edm::LogInfo("FixedMatrixSuperClusterProducerInfo") << str.str() << "\n";

}


void FixedMatrixSuperClusterProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  if(doEndcaps_)
    produceSuperclustersForECALPart(evt, endcapClusterProducer_, endcapClusterCollection_, endcapSuperclusterCollection_);

  if(doBarrel_)
    produceSuperclustersForECALPart(evt, barrelClusterProducer_, barrelClusterCollection_, barrelSuperclusterCollection_);

  nEvt_++;
}


void FixedMatrixSuperClusterProducer::produceSuperclustersForECALPart(edm::Event& evt, 
							   std::string clusterProducer, 
							   std::string clusterCollection,
							   std::string superclusterCollection)
{
  // get the cluster collection out and turn it to a BasicClusterRefVector:
  reco::BasicClusterRefVector *clusterRefVector_p = new reco::BasicClusterRefVector;
  getClusterRefVector(evt, clusterProducer, clusterCollection, clusterRefVector_p);

  // run the brem recovery and get the SC collection
  std::auto_ptr<reco::SuperClusterCollection> 
    superclusters_ap(new reco::SuperClusterCollection(bremAlgo_p->makeSuperClusters(*clusterRefVector_p)));

  // count the total energy and the number of superclusters
  reco::SuperClusterCollection::iterator it;
  for (it = superclusters_ap->begin(); it != superclusters_ap->end(); it++)
    {
      totalE += it->energy();
      noSuperClusters++;
    }

  // put the SC collection in the event
  evt.put(superclusters_ap, superclusterCollection);

  delete clusterRefVector_p;
}


void FixedMatrixSuperClusterProducer::getClusterRefVector(edm::Event& evt, std::string clusterProducer_, std::string clusterCollection_, reco::BasicClusterRefVector *clusterRefVector_p)
{  
  edm::Handle<reco::BasicClusterCollection> bccHandle;
  try
    {
      evt.getByLabel(clusterProducer_, clusterCollection_, bccHandle);
      if (!(bccHandle.isValid()))
	{
	  edm::LogError("FixedMatrixSuperClusterProducerError") << "could not get a handle on the BasicCluster Collection!";
	  clusterRefVector_p = 0;
	}
    } 
  catch ( cms::Exception& ex )
    {
      edm::LogError("FixedMatrixSuperClusterProducerError") << "Error! can't get the product " << clusterCollection_.c_str(); 
      clusterRefVector_p = 0;
    }

  const reco::BasicClusterCollection *clusterCollection_p = bccHandle.product();
  for (unsigned int i = 0; i < clusterCollection_p->size(); i++)
    {
      clusterRefVector_p->push_back(reco::BasicClusterRef(bccHandle, i));
    }
}                               




