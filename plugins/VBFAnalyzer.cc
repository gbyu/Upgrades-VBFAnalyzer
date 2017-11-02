// -*- C++ -*-
//
// Package:    FS_ROOT/VBFAnalyzer
// Class:      VBFAnalyzer
// 
/**\class VBFAnalyzer VBFAnalyzer.cc FS_ROOT/VBFAnalyzer/plugins/VBFAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Lata Panwar
//         Created:  Tue, 24 Oct 2017 18:28:14 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class declaration
//
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"

#include "DataFormats/MuonReco/interface/MuonCocktails.h"

#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

using namespace std;

class VBFAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit VBFAnalyzer(const edm::ParameterSet&);
      ~VBFAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<edm::View<pat::Muon> >     muonToken_;
  edm::EDGetTokenT<edm::View<pat::Electron> > elecToken_;
  edm::EDGetTokenT<edm::View<pat::Jet> >      jetToken_;
  const std::vector<std::string> bDiscriminators_;
  edm::EDGetTokenT<edm::View<pat::Jet> >      jetak8Token_;
  edm::EDGetTokenT<edm::View<pat::Jet> >      subjetak8Token_;
  edm::EDGetTokenT<edm::View<pat::MET> >      metToken_;
  edm::EDGetTokenT<reco::VertexCollection >   vtxToken_;
  edm::EDGetTokenT<reco::GenParticleCollection> mcLabel_;

  TTree * ttree_;
//  std::unique_ptr<TTree>;
  int b_nmuon, Jet_size,JetAK8_size;
  float b_jet_ak8_pt;
  bool runOnMC_;
};

//
// constants, enums and typedefs
//
// Define some simple structures
    typedef struct {Float_t Jet_PT,Jet_Eta,Jet_Phi,Jet_Mass, Jet_Tau1,Jet_Tau2,Jet_Tau3,Jet_BTag,Jet_sd_mass,Jet_pruned_mass,b_discr_sd_sub1; } JET;
    static JET Jet,JetAK8,JetPUPPI,JetAK8PUPPI;
//
// static data member definitions
//

//
// constructors and destructor
//
VBFAnalyzer::VBFAnalyzer(const edm::ParameterSet& iConfig):
bDiscriminators_(iConfig.getParameter<std::vector<std::string> >("bDiscriminators"))

{
   //now do what ever initialization is needed
   usesResource("TFileService");
  muonToken_ = consumes<edm::View<pat::Muon> >(iConfig.getParameter<edm::InputTag>("muons"));
  elecToken_ = consumes<edm::View<pat::Electron> >(iConfig.getParameter<edm::InputTag>("elecs"));
  jetToken_  = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jets"));
  jetak8Token_  = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jets_ak8"));
  subjetak8Token_  = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("subjets_ak8"));
  metToken_  = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag>("mets"));     
  vtxToken_  = consumes<reco::VertexCollection >(iConfig.getParameter<edm::InputTag>("vertices"));
  mcLabel_   = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("mcLabel"));

  edm::Service<TFileService> fs;
  ttree_ = fs->make<TTree>("delphes", "delphes");
  ttree_->Branch("Jet", &Jet, "Jet.PT/F:Jet.Eta/F:Jet.Phi/F:Jet.Mass/F:Jet.Tau1/F:Jet.Tau2/F:Jet.Tau3/F:Jet.BTag/F");
  ttree_->Branch("Jet_size",&Jet_size,"Jet_size/I");
  ttree_->Branch("JetAK8",&JetAK8,"JetAK8.PT/F:JetAK8.Eta/F:JetAK8.Phi/F:JetAK8.Mass/F:JetAK8.Tau1/F:JetAK8.Tau2/F:JetAK8.Tau3/F:JetAK8.BTag/F:JetAK8.sd_mass/F:JetAK8.pruned_mass/F:b_discr_sd_sub1/F");
  ttree_->Branch("JetAK8_size",&JetAK8_size,"JetAK8_size/I");
}


VBFAnalyzer::~VBFAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
VBFAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  



  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return; // skip the event if no PV found
  const reco::Vertex &pv = vertices->front();

  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByToken(muonToken_, muons);

  edm::Handle<edm::View<pat::Electron> > elecs;
  iEvent.getByToken(elecToken_, elecs);

  edm::Handle<edm::View<pat::Jet> > jets;
  iEvent.getByToken(jetToken_, jets);
  for (const pat::Jet & g : *jets){
       Jet.Jet_PT  = g.pt();
       Jet.Jet_Mass   = g.mass();
       Jet.Jet_Eta = g.eta();
       Jet.Jet_Phi = g.phi();
       for( const std::string &bDiscr : bDiscriminators_ )
        Jet.Jet_BTag=( g.bDiscriminator(bDiscr) );
     }
  Jet_size = jets->size();


  edm::Handle<edm::View<pat::Jet> > jets_ak8;
  iEvent.getByToken(jetak8Token_, jets_ak8);
  for (const pat::Jet & g1 : *jets_ak8){
       JetAK8.Jet_PT  = g1.pt();
       JetAK8.Jet_Mass   = g1.mass();
       JetAK8.Jet_Eta = g1.eta();
       JetAK8.Jet_Phi = g1.phi();
       JetAK8.Jet_Tau1= g1.userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau1");
       JetAK8.Jet_Tau2= g1.userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau2"); 
       JetAK8.Jet_Tau3= g1.userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau3");
       JetAK8.Jet_sd_mass = g1.userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSSoftDropMass"); // access to soft drop mass
       JetAK8.Jet_pruned_mass = g1.userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass");     // access to pruned mass
    
  for( const std::string &bDiscr : bDiscriminators_ )
        JetAK8.Jet_BTag=( g1.bDiscriminator(bDiscr) );
     
   TLorentzVector softdrop, softdrop_subjet;
   auto const & sdSubjets = g1.subjets("SoftDropPuppi");
   for ( auto const & it : sdSubjets ) {
   softdrop_subjet.SetPtEtaPhiM(it->correctedP4(0).pt(),it->correctedP4(0).eta(),it->correctedP4(0).phi(),it->correctedP4(0).mass());
   softdrop+=softdrop_subjet;
   for( const std::string &bDiscr : bDiscriminators_ )
   JetAK8.b_discr_sd_sub1=it->bDiscriminator(bDiscr);

        }  
     }

/*  edm::Handle<edm::View<pat::Jet> > subjets_ak8;
  iEvent.getByToken(subjetak8Token_, subjets_ak8);

   TLorentzVector softdrop, softdrop_subjet;
  // auto const & sdSubjetsPuppi = g1.subjets("SpftDropPuppi");
   for ( const pat::Jet & it : *subjets_ak8 ) {
   softdrop_subjet.SetPtEtaPhiM(it.correctedP4(0).pt(),it.correctedP4(0).eta(),it.correctedP4(0).phi(),it.correctedP4(0).mass());
   softdrop+=softdrop_subjet;
   for( const std::string &bDiscr : bDiscriminators_ )
   JetAK8.b_discr_sd_sub1=it.bDiscriminator(bDiscr);
}*/

  JetAK8_size = jets_ak8->size();
 
  edm::Handle<edm::View<pat::MET> > mets;
  iEvent.getByToken(metToken_, mets);
  

ttree_->Fill();

}
// ------------ method called once each job just before starting event loop  ------------
void 
VBFAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VBFAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
VBFAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(VBFAnalyzer);
