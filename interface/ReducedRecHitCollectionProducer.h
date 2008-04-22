#ifndef _REDUCEDRECHITPRODUCER_H
#define _REDUCEDRECHITPRODUCER_H

// -*- C++ -*-
//
// Package:    ReducedRecHitCollectionProducer
// Class:      ReducedRecHitCollectionProducer
// 
/**\class ReducedRecHitCollectionProducer ReducedRecHitCollectionProducer.cc Calibration/EcalAlCaRecoProducers/src/ReducedRecHitCollectionProducer.cc

Original author: Paolo Meridiani PH/CMG
 
Implementation:
 <Notes on implementation>
*/



// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


class CaloTopology;

class ReducedRecHitCollectionProducer : public edm::EDProducer {
   public:
      //! ctor
      explicit ReducedRecHitCollectionProducer(const edm::ParameterSet&);
      ~ReducedRecHitCollectionProducer();
      void beginJob (const edm::EventSetup&);
      //! producer
      virtual void produce(edm::Event &, const edm::EventSetup&);

   private:
      // ----------member data ---------------------------
      edm::InputTag recHitsLabel_;
      edm::InputTag basicClusters_;
      std::string reducedHitsCollection_;
      int minimalEtaSize_;
      int minimalPhiSize_;
      const CaloTopology* caloTopology_;

};

#endif
