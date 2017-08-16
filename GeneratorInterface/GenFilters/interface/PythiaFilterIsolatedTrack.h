#ifndef PythiaFilterIsolatedTrack_h
#define PythiaFilterIsolatedTrack_h

/** \class PythiaFilterIsolatedTrack
 *
 *  PythiaFilterGammaJet filter implements generator-level preselections 
 *  for ChargedHadron+jet like events to be used in jet energy calibration.
 *  Ported from fortran code written by V.Konoplianikov.
 * 
 * \author O.Kodolova, SINP
 *
 * Cleaned up code
 * \author J.P. Chou, Brown University
 *
 ************************************************************/

// system include files
#include <memory>

// Root objects
#include "TH1F.h"      

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

class PythiaFilterIsolatedTrack : public edm::EDFilter {
public:
  explicit PythiaFilterIsolatedTrack(const edm::ParameterSet&);
  ~PythiaFilterIsolatedTrack();

  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  // helper functions
  std::pair<double,double> GetEtaPhiAtEcal(double etaIP, double phiIP, double pT, int charge, double vtxZ);
  double getDistInCM(double eta1, double phi1, double eta2, double phi2);

private:
      
  // parameters
  std::string ModuleLabel_; // label to get the generated particles
  double MaxSeedEta_;       // maximum eta of the isolated track seed
  double MinSeedMom_;       // minimum momentum of the isolated track seed
  double MinIsolTrackMom_;  // minimum prohibited momentum of a nearby track
  double IsolCone_;         // cone size (in mm) around the seed to consider a track "nearby"
  bool   onlyHadrons_;      // select only isolated hadrons

  unsigned int nAll_, nGood_;
  double ecDist_;           //distance to ECAL andcap from IP (cm)
  double ecRad_;            //radius of ECAL barrel (cm)
};
#endif
