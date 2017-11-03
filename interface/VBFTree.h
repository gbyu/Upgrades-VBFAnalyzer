#ifndef UPGRADES_VBFANALYZER_VBFTTREE_HH
#define UPGRADES_VBFANALYZER_VBFTTREE_HH

#include <string>
#include <vector>
#include <TTree.h>
#include <TLorentzVector.h>

class VBFEventInfoBranches {
  public:

    int    runno ;
    int    lumisec ; 
    int    evtno;    
    int    bcno;
    int    time;
    double htHat; 
    double ptHat; 
    int    npv;
    int    npuTrue;
    double ht ; 

    void RegisterTree(TTree* tree, std::string name="SelectedEvents") {
      tree->Branch((name+"_runno").c_str(), &runno, (name+"_runno/I").c_str());
      tree->Branch((name+"_lumisec").c_str(), &lumisec, (name+"_lumisec/I").c_str());
      tree->Branch((name+"_evtno").c_str(), &evtno, (name+"_evtno/I").c_str());
      tree->Branch((name+"_bcno").c_str(), &bcno, (name+"_bcno/I").c_str());
      tree->Branch((name+"_time").c_str(), &time, (name+"_time/I").c_str());
      tree->Branch((name+"_htHat").c_str(), &htHat, (name+"_htHat/D").c_str()) ; 
      tree->Branch((name+"_ptHat").c_str(), &ptHat, (name+"_ptHat/D").c_str()) ; 
      tree->Branch((name+"_npv").c_str(), &npv, "npv/I");
      tree->Branch((name+"_npuTrue").c_str(), &npuTrue, "npuTrue/I");
      tree->Branch((name+"_ht").c_str(), &ht, "ht/D");
    }
};

class VBFGenParticleInfoBranches {
  public:
    std::vector<int>    genpid;
    std::vector<double> genpt ; 
    std::vector<double> geneta ; 
    std::vector<double> genphi ; 
    std::vector<double> genmass ; 
    std::vector<int>    gencharge ; 
    std::vector<int>    genstatus ; 
    std::vector<int>    mom0pid ; 
    std::vector<double> mom0pt ; 
    std::vector<double> mom0eta ; 
    std::vector<double> mom0phi ; 
    std::vector<double> mom0mass ; 
    std::vector<int>    mom0status ; 
    std::vector<int>    mom1pid ; 
    std::vector<double> mom1pt ; 
    std::vector<double> mom1eta ; 
    std::vector<double> mom1phi ; 
    std::vector<double> mom1mass ; 
    std::vector<int>    mom1status ; 
    std::vector<int>    dau0pid ; 
    std::vector<double> dau0pt ; 
    std::vector<double> dau0eta ; 
    std::vector<double> dau0phi ; 
    std::vector<double> dau0mass ; 
    std::vector<int>    dau0status ; 
    std::vector<int>    dau1pid ; 
    std::vector<double> dau1pt ; 
    std::vector<double> dau1eta ; 
    std::vector<double> dau1phi ; 
    std::vector<double> dau1mass ; 
    std::vector<int>    dau1status ; 

    void RegisterTree(TTree* tree, std::string name="GenPartInfo") {
      tree->Branch((name+"_genpid"    ).c_str(), &genpid    ) ; 
      tree->Branch((name+"_genpt"     ).c_str(), &genpt     ) ; 
      tree->Branch((name+"_geneta"    ).c_str(), &geneta    ) ; 
      tree->Branch((name+"_genphi"    ).c_str(), &genphi    ) ; 
      tree->Branch((name+"_genmass"   ).c_str(), &genmass   ) ; 
      tree->Branch((name+"_gencharge" ).c_str(), &gencharge ) ; 
      tree->Branch((name+"_genstatus" ).c_str(), &genstatus ) ; 
      tree->Branch((name+"_mom0pt"    ).c_str(), &mom0pt    ) ; 
      tree->Branch((name+"_mom1pt"    ).c_str(), &mom1pt    ) ; 
      tree->Branch((name+"_dau0pt"    ).c_str(), &dau0pt    ) ; 
      tree->Branch((name+"_dau1pt"    ).c_str(), &dau1pt    ) ; 
      tree->Branch((name+"_mom0eta"   ).c_str(), &mom0eta   ) ; 
      tree->Branch((name+"_mom1eta"   ).c_str(), &mom1eta   ) ; 
      tree->Branch((name+"_dau0eta"   ).c_str(), &dau0eta   ) ; 
      tree->Branch((name+"_dau1eta"   ).c_str(), &dau1eta   ) ; 
      tree->Branch((name+"_mom0phi"   ).c_str(), &mom0phi   ) ; 
      tree->Branch((name+"_mom1phi"   ).c_str(), &mom1phi   ) ; 
      tree->Branch((name+"_dau0phi"   ).c_str(), &dau0phi   ) ; 
      tree->Branch((name+"_dau1phi"   ).c_str(), &dau1phi   ) ; 
      tree->Branch((name+"_mom0pid"   ).c_str(), &mom0pid   ) ; 
      tree->Branch((name+"_mom1pid"   ).c_str(), &mom1pid   ) ; 
      tree->Branch((name+"_dau0pid"   ).c_str(), &dau0pid   ) ; 
      tree->Branch((name+"_dau1pid"   ).c_str(), &dau1pid   ) ; 
      tree->Branch((name+"_mom0status").c_str(), &mom0status) ; 
      tree->Branch((name+"_mom1status").c_str(), &mom1status) ; 
      tree->Branch((name+"_dau0status").c_str(), &dau0status) ; 
      tree->Branch((name+"_dau1status").c_str(), &dau1status) ; 
    }

};

class VBFJetInfoBranches {
  public:
    std::vector<int>  idx; 
    std::vector<double> genjetpt;
    std::vector<double> pt;
    std::vector<double> eta;
    std::vector<double> phi;
    std::vector<double> energy;
    std::vector<double> mass;
    std::vector<double> ptCHS;
    std::vector<double> etaCHS;
    std::vector<double> phiCHS;
    std::vector<double> massCHS;
    std::vector<double> softDropMassCHS;
    std::vector<double> prunedMassCHS;
    std::vector<double> tau1CHS;
    std::vector<double> tau2CHS;
    std::vector<double> tau3CHS;
    std::vector<double> softDropMassPuppi;
    std::vector<double> tau1Puppi;
    std::vector<double> tau2Puppi;
    std::vector<double> tau3Puppi;
    std::vector<double> csvv2;
    std::vector<double> deepcsv;
    std::vector<double> pujetid;
    std::vector<double> partonFlavour; 
    std::vector<double> hadronFlavour; 
    std::vector<double> sj0csvv2;
    std::vector<double> sj1csvv2;
    std::vector<double> sj0deepcsv;
    std::vector<double> sj1deepcsv;
    std::vector<double> sj0partonFlavour; 
    std::vector<double> sj1partonFlavour; 
    std::vector<double> sj0hadronFlavour; 
    std::vector<double> sj1hadronFlavour; 
    std::vector<double> sj0pt;
    std::vector<double> sj1pt;
    std::vector<double> sj0eta;
    std::vector<double> sj1eta;
    std::vector<double> sj0phi;
    std::vector<double> sj1phi;

    void RegisterTree(TTree* tree, std::string name="JetInfo") {
      tree->Branch((name+"_idx").c_str(), &idx); 
      tree->Branch((name+"_genjetpt").c_str(), &genjetpt); 
      tree->Branch((name+"_pt").c_str(), &pt); 
      tree->Branch((name+"_eta").c_str(), &eta);
      tree->Branch((name+"_phi").c_str(), &phi);
      tree->Branch((name+"_energy").c_str(), &energy);
      tree->Branch((name+"_mass").c_str(), &mass);
      tree->Branch((name+"_csvv2").c_str(), &csvv2);
      tree->Branch((name+"_deepcsv").c_str(), &deepcsv);
      tree->Branch((name+"_pujetid").c_str(), &pujetid);

      if ( name.find("AK8Jets") != std::string::npos ) {
        tree->Branch((name+"_ptCHS").c_str(), &ptCHS);
        tree->Branch((name+"_etaCHS").c_str(), &etaCHS);
        tree->Branch((name+"_phiCHS").c_str(), &phiCHS);
        tree->Branch((name+"_massCHS").c_str(), &massCHS);
        tree->Branch((name+"_softDropMassCHS").c_str(), &softDropMassCHS);
        tree->Branch((name+"_prunedCHS").c_str(), &prunedMassCHS);
        tree->Branch((name+"_tau1CHS").c_str(), &tau1CHS);
        tree->Branch((name+"_tau2CHS").c_str(), &tau2CHS);
        tree->Branch((name+"_tau3CHS").c_str(), &tau3CHS);
        tree->Branch((name+"_softDropMassPuppi").c_str(), &softDropMassPuppi);
        tree->Branch((name+"_tau1Puppi").c_str(), &tau1Puppi);
        tree->Branch((name+"_tau2Puppi").c_str(), &tau2Puppi);
        tree->Branch((name+"_tau3Puppi").c_str(), &tau3Puppi);
        tree->Branch((name+"_partonFlavour").c_str(), &partonFlavour);
        tree->Branch((name+"_hadronFlavour").c_str(), &hadronFlavour);
        tree->Branch((name+"_sj0csvv2").c_str(),&sj0csvv2);
        tree->Branch((name+"_sj1csvv2").c_str(),&sj1csvv2);
        tree->Branch((name+"_sj0deepcsv").c_str(),&sj0deepcsv);
        tree->Branch((name+"_sj1deepcsv").c_str(),&sj1deepcsv);
        tree->Branch((name+"_sj0partonflavour").c_str(),&sj0partonFlavour);
        tree->Branch((name+"_sj1partonflavour").c_str(),&sj1partonFlavour);
        tree->Branch((name+"_sj0hadronflavour").c_str(),&sj0hadronFlavour);
        tree->Branch((name+"_sj1hadronflavour").c_str(),&sj1hadronFlavour);
        tree->Branch((name+"_sj0pt").c_str(),&sj0pt);
        tree->Branch((name+"_sj1pt").c_str(),&sj1pt);
        tree->Branch((name+"_sj0eta").c_str(),&sj0eta);
        tree->Branch((name+"_sj1eta").c_str(),&sj1eta);
        tree->Branch((name+"_sj0phi").c_str(),&sj0phi);
        tree->Branch((name+"_sj1phi").c_str(),&sj1phi);
      }

    }

};

#endif
