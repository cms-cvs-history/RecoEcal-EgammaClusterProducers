#ifndef RecoEcal_EgammaClusterProducers_PiZeroDiscriminatorProducer_h
#define RecoEcal_EgammaClusterProducers_PiZeroDiscriminatorProducer_h

// $Author: futyand $
// $Id: PiZeroDiscriminatorProducer.h,v 1.1 2006/09/11 12:21:31 futyand Exp $
// $Date: 2006/09/11 12:21:31 $

#include <memory>

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

#include "RecoEcal/EgammaClusterAlgos/interface/EndcapPiZeroDiscriminatorAlgo.h"

#include "TH1.h"
class TFile;


class PiZeroDiscriminatorProducer : public edm::EDProducer {

 public:

  typedef math::XYZPoint Point;

  explicit PiZeroDiscriminatorProducer (const edm::ParameterSet& ps);

  ~PiZeroDiscriminatorProducer();

  virtual void produce( edm::Event& evt, const edm::EventSetup& es);

 private:

  int nEvt_;         // internal counter of events

  //clustering parameters:
  std::string endcapHitProducer_;
  std::string endcapHitCollection_;

  std::string preshHitProducer_;   // name of module/plugin/producer producing hits
  std::string preshHitCollection_; // secondary name given to collection of hits by hitProducer
  std::string endcapSClusterCollection_;
  std::string endcapSClusterProducer_;

  bool clustershape_logweighted;
  float clustershape_x0;
  float clustershape_t0;
  float clustershape_w0;

  std::string endcapPiZeroDiscriminatorCollection_;
  std::string barrelPiZeroDiscriminatorCollection_;

  EndcapPiZeroDiscriminatorAlgo * presh_pi0_algo; // algorithm doing the real work

  EndcapPiZeroDiscriminatorAlgo::DebugLevel_pi0 debugL_pi0;
};
#endif

