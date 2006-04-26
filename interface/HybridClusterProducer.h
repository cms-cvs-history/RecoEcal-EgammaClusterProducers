#ifndef RecoEcal_EgammaClusterProducers_HybridClusterProducer_h_
#define RecoEcal_EgammaClusterProducers_HybridClusterProducer_h_

#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "RecoEcal/EgammaClusterAlgos/interface/HybridClusterAlgo.h"


//


class HybridClusterProducer : public edm::EDProducer 
{
  
  public:

      HybridClusterProducer(const edm::ParameterSet& ps);

      ~HybridClusterProducer();

      virtual void produce(edm::Event&, const edm::EventSetup&);

   private:

      int nMaxPrintout_; // max # of printouts
      int nEvt_;         // internal counter of events
 
      std::string basicclusterCollection_;
      std::string superclusterCollection_;
      HybridClusterAlgo * hybrid_p;

      bool counterExceeded() const { return ((nEvt_ > nMaxPrintout_) || (nMaxPrintout_ < 0));}
};


#endif


