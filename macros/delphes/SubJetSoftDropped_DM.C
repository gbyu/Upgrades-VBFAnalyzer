/*
   Macro for SubJet

   root -l SubJetSoftDropped_DM.C'("/afs/cern.ch/user/l/lata/public/VBF_50k_2500_0PU.root", 0)'
   */

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

  TRandom3* r = new TRandom3();

  double getEff_b(double ptin, double etain, const int pu) {

    double pt=0.,eta=0.,ptwidth=0.,etawidth=0.,eff=0.; 
    
    etain = abs(etain);
    if (ptin > 3000.) ptin = 2999.99;

    TFile f("effs/beff_200PU_WPM.root");
    TH1F *heff = (TH1F*)f.Get("heff");
    int x_range=(heff->GetNbinsX());
    int y_range=(heff->GetNbinsY());
    for(int i=1; i < x_range+1; i++){
       for(int j=1; j < y_range+1; j++){
         pt       = heff->GetXaxis()->GetBinLowEdge(i);
         eta      = heff->GetYaxis()->GetBinLowEdge(j);
         ptwidth  = heff->GetXaxis()->GetBinWidth(i);
         etawidth = heff->GetYaxis()->GetBinWidth(j);
         if (pt <= ptin && ptin < (pt+ptwidth)){
           if (eta <= etain && etain < (eta+etawidth)){
           
           eff=heff->GetBinContent(i,j);
          }
        }
      }
    }
  return eff; 
  
}

double getEff_c(double ptin, double etain, const int pu) {

    double pt=0.,eta=0.,ptwidth=0.,etawidth=0.,eff=0.; 
    
    etain = abs(etain);
    if (ptin > 3000.) ptin = 2999.99;

    TFile f("effs/ceff_200PU_WPM.root");
    TH1F *heff = (TH1F*)f.Get("heff");
    int x_range=(heff->GetNbinsX());
    int y_range=(heff->GetNbinsY());
    for(int i=1; i < x_range+1; i++){
       for(int j=1; j < y_range+1; j++){
         pt       = heff->GetXaxis()->GetBinLowEdge(i);
         eta      = heff->GetYaxis()->GetBinLowEdge(j);
         ptwidth  = heff->GetXaxis()->GetBinWidth(i);
         etawidth = heff->GetYaxis()->GetBinWidth(j);
         if (pt <= ptin && ptin < (pt+ptwidth)){
           if (eta <= etain && etain < (eta+etawidth)){
           
           eff=heff->GetBinContent(i,j);
          }
        }
      }
    }
  return eff; 
  
}

double getEff_l(double ptin, double etain, const int pu) {

    double pt=0.,eta=0.,ptwidth=0.,etawidth=0.,eff=0.; 
    
    etain = abs(etain);
    if (ptin > 3000.) ptin = 2999.99;

    TFile f("effs/lighteff_200PU_WPM.root");
    TH1F *heff = (TH1F*)f.Get("heff");
    int x_range=(heff->GetNbinsX());
    int y_range=(heff->GetNbinsY());
    for(int i=1; i < x_range+1; i++){
       for(int j=1; j < y_range+1; j++){
         pt       = heff->GetXaxis()->GetBinLowEdge(i);
         eta      = heff->GetYaxis()->GetBinLowEdge(j);
         ptwidth  = heff->GetXaxis()->GetBinWidth(i);
         etawidth = heff->GetYaxis()->GetBinWidth(j);
         if (pt <= ptin && ptin < (pt+ptwidth)){
           if (eta <= etain && etain < (eta+etawidth)){
           
           eff=heff->GetBinContent(i,j);
          }
        }
      }
    }
  return eff; 
  
}


bool isBTagged(const double pt, const double eta, const int pu, const int fl) {
  bool isBTagged(0);

  if (fl == 5) {
    double eff = getEff_b(pt, eta, pu);  
    double rand = r->Rndm();
    // std::cout << " pt = " << pt << " eta = " << eta << " eff = " << eff << " rand = " << rand << std::endl;
    if (eff > rand) isBTagged = 1;
    else isBTagged = 0;
  }
  else if (fl == 4) {
    double eff = getEff_c(pt, eta, pu);  
    double rand = r->Rndm();
    // std::cout << " pt = " << pt << " eta = " << eta << " eff = " << eff << " rand = " << rand << std::endl;
    if (eff < rand) isBTagged = 1;
    else isBTagged = 0;
  }
  else
  {
    double eff = getEff_l(pt, eta, pu);  
    double rand = r->Rndm();
    // std::cout << " pt = " << pt << " eta = " << eta << " eff = " << eff << " rand = " << rand << std::endl;
    if (eff < rand) isBTagged = 1;
    else isBTagged = 0;
  }

  return isBTagged;

} 

//------------------------------------------------------------------------------

void SubJetSoftDropped_test(const int pu, const int nmin, const int nmax, const char *output)
{
  gSystem->Load("libDelphes");
  
  TString file[300]={"root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_1_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_2_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_3_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_4_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_5_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_6_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_7_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_8_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_9_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_10_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_11_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_12_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_13_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_14_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_15_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_16_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_17_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_18_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_19_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_20_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_21_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_22_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_23_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_24_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_25_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_26_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_27_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_28_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_29_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_30_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_31_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_32_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_33_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_34_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_35_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_36_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_37_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_38_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_39_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_40_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_41_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_42_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_43_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_44_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_45_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_46_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_47_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_48_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_49_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_50_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_51_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_52_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_53_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_54_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_55_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_56_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_57_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_58_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_59_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_60_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_61_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_62_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_63_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_64_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_65_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_66_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_67_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_68_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_69_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_70_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_71_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_72_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_73_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_74_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_75_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_76_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_77_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_78_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_79_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_80_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_81_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_82_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_83_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_84_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_85_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_86_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_87_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_88_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_89_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_90_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_91_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_92_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_93_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_94_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_95_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_96_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_97_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_98_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_99_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_100_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_101_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_102_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_103_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_104_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_105_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_106_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_107_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_108_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_109_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_110_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_111_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_112_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_113_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_114_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_115_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_116_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_117_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_118_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_119_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_120_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_121_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_122_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_123_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_124_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_125_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_126_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_127_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_128_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_129_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_130_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_131_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_132_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_133_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_134_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_135_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_136_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_137_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_138_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_139_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_140_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_141_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_142_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_143_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_144_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_145_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_146_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_147_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_148_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_149_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_150_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_151_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_152_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_153_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_154_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_155_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_156_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_157_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_158_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_159_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_160_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_161_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_162_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_163_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_164_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_165_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_166_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_167_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_168_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_169_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_170_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_171_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_172_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_173_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_174_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_175_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_176_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_177_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_178_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_179_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_180_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_181_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_182_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_183_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_184_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_185_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_186_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_187_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_188_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_189_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_190_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_191_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_192_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_193_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_194_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_195_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_196_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_197_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_198_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_199_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_201_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_202_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_203_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_204_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_205_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_206_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_207_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_208_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_209_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_210_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_211_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_212_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_213_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_214_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_215_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_216_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_217_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_218_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_219_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_220_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_221_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_222_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_223_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_224_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_225_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_226_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_227_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_228_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_229_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_230_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_231_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_232_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_233_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_234_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_235_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_236_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_237_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_238_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_239_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_240_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_241_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_242_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_243_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_244_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_245_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_246_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_247_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_248_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_249_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_250_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_251_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_252_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_253_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_254_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_255_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_256_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_257_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_258_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_259_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_260_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_261_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_262_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_263_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_264_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_265_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_266_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_267_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_268_0.root","root://cms-xrd-global.cern.ch//store/group/snowmass/noreplica/YR_Delphes/Delphes342pre15/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_200PU/QCD_bEnriched_HT700to1000_TuneCUETP8M1_14TeV-madgraphMLM-pythia8_269_0.root"};
  // Create chain of root trees
    TChain chain("Delphes");
    for(int i=nmin; i<nmax; i++){
    chain.Add(file[i]);
    cout << "now processing " << file[i] << endl;
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Int_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJetAK8 = treeReader->UseBranch("JetPUPPIAK8"); ////DM changing to PUPPIAK8 jets
  TClonesArray *branchJetAK4 = treeReader->UseBranch("JetPUPPI"); ////DM AK4 jets for VBF tagging
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TFile* fout = new TFile(output, "RECREATE");
  fout->cd();
  TLorentzVector genJetMomentum;
  GenParticle *particle1,*particle2,*particle3,*mother1,*mother2;
  Int_t index, motherPID_1, motherPID_2;
  // Book histograms
  TH1F *h_cutflow           = new TH1F("h_cutflow"          , "", 11, 0.5, 11.5);
  TH1F *h_events            = new TH1F("h_events"           , "", 11, 0.5, 11.5);
  TH1F *h_cutflow_2	    = new TH1F("h_cutflow_2"        , "", 11, 0.5, 11.5);
  TH1D *h_nak8		    = new TH1D("h_nak8"         ,";N(AK8) [GeV]; Events;;" ,11   ,-0.5  ,10.5 );
  TH1F *h_ak80pt            = new TH1F("h_ak80pt"        , ";p_{T} leading AK8_Jet;Events;;",300,0,3000);
  TH1F *h_ak81pt            = new TH1F("h_ak81pt"        , ";p_{T} 2nd leading AK8_Jet;Events;;",300,0,3000);
  TH1F *h_ak80eta           = new TH1F("h_ak80eta"       , ";#eta leading AK8_Jet;Events;;", 200, -5, 5);
  TH1F *h_ak81eta           = new TH1F("h_ak81eta"       , ";#eta 2nd leading AK8_Jet;Events;;", 200, -5, 5);
  TH1F *h_sdmass_ak80       = new TH1F("h_sdmass_ak80"        , ";M_{soft drop}leading AK8_Jet[GeV];Events;;", 100, 0, 200);
  TH1F *h_sdmass_ak81       = new TH1F("h_sdmass_ak81"        , ";M_{soft drop}2nd leading AK8_Jet[GeV];Events;;", 100, 0, 200);
  TH1F *Minv_fatjet1        = new TH1F("Minv_fatjet1"       , ";Mass of leading AK8_Jet[GeV];Events;;", 100, 0, 200);
  TH1F *Minv_fatjet2        = new TH1F("Minv_fatjet2"       , ";Mass of 2nd leading AK8_Jet[GeV];Events;;", 100, 0, 200);
  TH1F *eta_SubJet1_fatjet1 = new TH1F("h_sj00_eta",";#eta SubJet_1 (leading AK8_Jet);Events;;",200,-5 ,5);
  TH1F *eta_SubJet2_fatjet1 = new TH1F("h_sj10_eta",";#eta SubJet_2 (leading AK8_Jet);Events;;",200,-5 ,5);
  TH1F *eta_SubJet1_fatjet2 = new TH1F("h_sj01_eta",";#eta SubJet_1 (2nd leading AK8_Jet);Events;;",200,-5 ,5);
  TH1F *eta_SubJet2_fatjet2 = new TH1F("h_sj11_eta",";#eta SubJet_2 (2nd leading AK8_Jet);Events;;",200,-5 ,5);
  TH1F *pt_SubJet1_fatjet1  = new TH1F("h_sj00_pt" ,";p_{T}SubJet_1 (leading AK8_Jet);Events;;",100,0,1000);
  TH1F *pt_SubJet2_fatjet1  = new TH1F("h_sj10_pt" ,";p_{T}SubJet_2 (leading AK8_Jet);Events;;",100,0,1000);
  TH1F *pt_SubJet1_fatjet2  = new TH1F("h_sj01_pt" ,";p_{T}SubJet_1 (2nd leading AK8_Jet);Events;;",100,0,1000);
  TH1F *pt_SubJet2_fatjet2  = new TH1F("h_sj11_pt" ,";p_{T}SubJet_2 (2nd leading AK8_Jet);Events;;",100,0,1000);
  TH1F *M_SubJets_fatjet1   = new TH1F("M_SubJets_fatjet1"  , "Inv_Mass of SubJets (leading AK8_jet)", 100, 0, 500);
  TH1F *M_SubJets_fatjet2   = new TH1F("M_SubJets_fatjet2"  , "Inv_Mass of SubJets (2nd leading AK8_Jet)", 100, 0, 500);
  TH1D *NSubJet_fatjet1     = new TH1D("NSubJet_fatjet1"    , "no. of SubJets(leading Jet)",5,0,5);
  TH1D *NSubJet_fatjet2     = new TH1D("NSubJet_fatjet2"    , "no. of SubJets(2nd leading Jet)",5,0,5);
  TH1F *h_ak80_tau2_tau1    = new TH1F("h_ak80_t2byt1" ,";#tau_{2}/#tau_{1}(leading AK8_Jet);Events;;", 100,0,1);
  TH1F *h_ak81_tau2_tau1    = new TH1F("h_ak81_t2byt1" ,";#tau_{2}/#tau_{1}(2nd leading AK8_Jet);Events;;", 100,0,1);
  TH1F *inv_M_4b	    = new TH1F("h_mass_4sj"     , ";M(4b) [GeV]; Events;;", 100, 0, 2000);
  TH1F *inv_M_HH_3b	    = new TH1F("mjj_3b"       , ";M(HH) [GeV]; Events;;", 100, 0, 2000);
  TH1F *inv_M_HH_4b	    = new TH1F("mjj_4b"	, ";M(HH) [GeV]; Events;;", 100, 0, 2000);
  TH2F *pt_vs_eff	    = new TH2F("pt_vs_eff"	, ";p_{T};eff;;", 10, 0., 1000., 10, 0., 1.);
  TH2F *t21_j1_j2_sdcut     = new TH2F("t21_j1_j2_sdcut", ";t21(J1);t21(J2);;", 10, 0., 1., 10, 0., 1.);
  TH1F *M_HH_3b             = new TH1F("h_mjj_3b"       , ";M(HH) [GeV]; Events;;", 100, 0, 2000);
  TH1F *M_HH_4b             = new TH1F("h_mjj_4b"       , ";M(HH) [GeV]; Events;;", 100, 0, 2000);
  TH1F *inv_M_qq            = new TH1F("h_mass_qq"     , ";#hat{M}_{qq} [GeV]; Events;;", 100, 0, 5000);
  TH1F *inv_HT_qq           = new TH1F("h_HT_qq"     , ";H_{T} [GeV]; Events;;", 100, 0, 2500);
  h_cutflow->GetXaxis()->SetBinLabel(1 ,"All");
  h_cutflow->GetXaxis()->SetBinLabel(3 ,"AK8>1");
  h_cutflow->GetXaxis()->SetBinLabel(4 ,"p_{T}");
  h_cutflow->GetXaxis()->SetBinLabel(5 ,"#eta");
  h_cutflow->GetXaxis()->SetBinLabel(6 ,"#tau_{21}");
  h_cutflow->GetXaxis()->SetBinLabel(7 ,"M(J)");
  h_cutflow->GetXaxis()->SetBinLabel(2 ,"M_{qq}");
  h_cutflow->GetXaxis()->SetBinLabel(8 ,"sjBTag>0");
  h_cutflow->GetXaxis()->SetBinLabel(9 ,"sjBTag>1");
  h_cutflow->GetXaxis()->SetBinLabel(10 ,"sjBTag>2");
  h_cutflow->GetXaxis()->SetBinLabel(11 ,"sjBTag>3");

  h_cutflow_2->GetXaxis()->SetBinLabel(1 ,"All");
  h_cutflow_2->GetXaxis()->SetBinLabel(3 ,"AK8>1");
  h_cutflow_2->GetXaxis()->SetBinLabel(4 ,"p_{T}");
  h_cutflow_2->GetXaxis()->SetBinLabel(5 ,"#eta");
  h_cutflow_2->GetXaxis()->SetBinLabel(6 ,"#tau_{21}");
  h_cutflow_2->GetXaxis()->SetBinLabel(7 ,"M(J)");
  h_cutflow_2->GetXaxis()->SetBinLabel(2 ,"M_{qq}");
  h_cutflow_2->GetXaxis()->SetBinLabel(8 ,"sjBTag=1");
  h_cutflow_2->GetXaxis()->SetBinLabel(9 ,"sjBTag=2");
  h_cutflow_2->GetXaxis()->SetBinLabel(10 ,"sjBTag=3");
  h_cutflow_2->GetXaxis()->SetBinLabel(11 ,"sjBTag=4");
  
  h_events->GetXaxis()->SetBinLabel(1 ,"All");
  h_events->GetXaxis()->SetBinLabel(3 ,"AK8>1");
  h_events->GetXaxis()->SetBinLabel(4 ,"p_{T}");
  h_events->GetXaxis()->SetBinLabel(5 ,"#eta");
  h_events->GetXaxis()->SetBinLabel(6 ,"#tau_{21}");
  h_events->GetXaxis()->SetBinLabel(7 ,"M(J)");
  h_events->GetXaxis()->SetBinLabel(2 ,"M_{qq}");
  h_events->GetXaxis()->SetBinLabel(8 ,"sjBTag>0");
  h_events->GetXaxis()->SetBinLabel(9 ,"sjBTag>1");
  h_events->GetXaxis()->SetBinLabel(10 ,"sjBTag>2");
  h_events->GetXaxis()->SetBinLabel(11 ,"sjBTag>3");

  float total_events =0 ,num1 =0, num2=0, num3=0, num4=0, num5=0,num6=0,total_events_AK4=0,num7=0,num8=0,num9=0,num10=0,num11=0, w_4b=0., count1=0., count2=0., countqq=0, HT=0;
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  //for(Int_t entry = 0; entry < 5000; ++entry)
  {
    // Load selected branches with data from specified event
  treeReader->ReadEntry(entry);
  ++total_events;
  h_cutflow->Fill(1);
  h_events->Fill(1);
  h_cutflow_2->Fill(1);
 
  //#### parton mass cut ######
//  if(branchParticle->GetEntries() >= 2){
   for(i = 0; i < branchParticle->GetEntries(); i++){
     particle1 = (GenParticle*) branchParticle->At(i);
     if (particle1->Status == 23)
     {
      countqq++;
      if(countqq==1){
       count1=i; 
       }	
      else if(countqq==2){
        count2=i;
        particle2 = (GenParticle*) branchParticle->At(count1);
        particle3 = (GenParticle*) branchParticle->At(count2);
        countqq=0;
        cout << "entry==" << entry << endl;
        cout << "p1_status==" << particle1->Status << "p2_status==" << particle2->Status << endl;
        mother1 = (GenParticle*) branchParticle->At(particle2->M1);
        motherPID_1 = mother1->PID;
        mother2 = (GenParticle*) branchParticle->At(particle3->M1);
        motherPID_2 = mother2->PID;
        cout << "p1_mother==" << motherPID_1  << " and particle1== " << particle2->PID << " status1==" << particle2->Status << endl;
        cout << "p2_mother==" << motherPID_2  << " and particle2== " << particle3->PID << " status2==" << particle3->Status << endl;
        genJetMomentum = particle2->P4()+particle3->P4();
        inv_M_qq->Fill(genJetMomentum.M());
        if(genJetMomentum.M() < 1000.){
          h_cutflow->Fill(2);
          h_events->Fill(2);
          h_cutflow_2->Fill(2);
          
    // If event contains at least 2 jets
    if(branchJetAK8->GetEntries() >= 2)
    {
      h_cutflow->Fill(3);
      h_events->Fill(3);
      h_cutflow_2->Fill(3);
      Jet *ak8jet0 = (Jet*) branchJetAK8->At(0);
      Jet *ak8jet1 = (Jet*) branchJetAK8->At(1);

      TLorentzVector p4_ak8jet0(ak8jet0->SoftDroppedP4[0]);
      TLorentzVector p4_ak8jet1(ak8jet1->SoftDroppedP4[0]);

      unsigned int nsj_ak8jet0(ak8jet0->NSubJetsSoftDropped);
      unsigned int nsj_ak8jet1(ak8jet1->NSubJetsSoftDropped);

      TLorentzVector p4_sj0_ak8jet0(ak8jet0->SoftDroppedP4[1]); ////DM 1st soft drop subjet of leading AK8 jet
      TLorentzVector p4_sj0_ak8jet1(ak8jet1->SoftDroppedP4[1]); ////DM 1st soft drop subjet of 2nd-leading AK8 jet

      TLorentzVector p4_sj1_ak8jet0(ak8jet0->SoftDroppedP4[2]); ////DM 2nd soft drop subjet of leading AK8 jet
      TLorentzVector p4_sj1_ak8jet1(ak8jet1->SoftDroppedP4[2]); ////DM 2nd soft drop subjet of leading AK8 jet

      float tau1_1(ak8jet0->Tau[0]);
      float tau2_1(ak8jet0->Tau[1]);

      float tau1_2(ak8jet1->Tau[0]);
      float tau2_2(ak8jet1->Tau[1]);
      int sj00BTagged =  int(isBTagged(p4_sj0_ak8jet0.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5));
      int sj10BTagged =  int(isBTagged(p4_sj1_ak8jet0.Pt(), p4_sj1_ak8jet0.Eta(), pu, 5));
      int sj01BTagged =  int(isBTagged(p4_sj0_ak8jet1.Pt(), p4_sj0_ak8jet1.Eta(), pu, 5));
      int sj11BTagged =  int(isBTagged(p4_sj1_ak8jet1.Pt(), p4_sj1_ak8jet1.Eta(), pu, 5));
      
      int btag_01 = sj00BTagged || sj10BTagged;  
      int btag_11 = sj01BTagged || sj11BTagged;
      int btag_02 = sj00BTagged && sj10BTagged;
      int btag_12 = sj01BTagged	&& sj11BTagged;

      int one_btagged = btag_01 || btag_11;
      int two_btagged = btag_01 && btag_11;
      int three_btagged_1 = btag_02 && btag_11;
      int three_btagged_2 = btag_12 && btag_01;
      int three_btagged = three_btagged_1 || three_btagged_2;
      int four_btagged  = btag_02 && btag_12;
      
      h_ak80pt->Fill(p4_ak8jet0.Pt());
      h_ak80pt->SetYTitle("Events");
      h_ak80pt->SetXTitle("p_{T},[GeV/c]");
      h_ak80pt->SetLineWidth(3);

      h_ak81pt->Fill(p4_ak8jet1.Pt());
      h_ak81pt->SetYTitle("Events");
      h_ak81pt->SetXTitle("p_{T},[GeV/c]");
      h_ak81pt->SetLineWidth(3);


      //// Starting selections on AK8 jets 
      if( p4_ak8jet0.Pt() > 300 && p4_ak8jet1.Pt() > 300 ){
        ++num1; 
        h_cutflow->Fill(4);
	h_events->Fill(4);
        h_cutflow_2->Fill(4);
        
        h_ak80eta->Fill(p4_ak8jet0.Eta());
        h_ak80eta->SetYTitle("Events");
        h_ak80eta->SetXTitle("#eta");
        h_ak80eta->SetLineWidth(3);

        h_ak81eta->Fill(p4_ak8jet1.Eta());
        h_ak81eta->SetYTitle("Events");
        h_ak81eta->SetXTitle("#eta");
        h_ak81eta->SetLineWidth(3);

        if( abs(ak8jet0->Eta)<3 &&  abs(ak8jet1->Eta)<3 ){
          ++num2;
          h_cutflow->Fill(5);
	  h_events->Fill(5);
          h_cutflow_2->Fill(5);
         
          h_ak80_tau2_tau1->Fill(1.0*tau2_1/tau1_1);
          h_ak80_tau2_tau1->SetYTitle("Events");
          h_ak80_tau2_tau1->SetXTitle("#tau_{2}/#tau_{1}");
          h_ak80_tau2_tau1->SetLineWidth(3);

          h_ak81_tau2_tau1->Fill(1.0*tau2_2/tau1_2);
          h_ak81_tau2_tau1->SetYTitle("Events");
          h_ak81_tau2_tau1->SetXTitle("#tau_{2}/#tau_{1}");
          h_ak81_tau2_tau1->SetLineWidth(3);

          if(tau2_1/tau1_1 < 0.6 && tau2_2/tau1_2 < 0.6){
            ++num4;
            h_cutflow->Fill(6);
	    h_events->Fill(6);
            h_cutflow_2->Fill(6);
	
	    h_sdmass_ak80->Fill(p4_ak8jet0.M());
            h_sdmass_ak80->SetYTitle("Events");
            h_sdmass_ak80->SetXTitle("inv_mass,[GeV]");
            h_sdmass_ak80->SetLineWidth(3);
            h_sdmass_ak81->Fill(p4_ak8jet1.M());
            h_sdmass_ak81->SetYTitle("Events");
            h_sdmass_ak81->SetXTitle("inv_mass,[GeV]");
            h_sdmass_ak81->SetLineWidth(3);
            Minv_fatjet1->Fill(ak8jet0->Mass);
            Minv_fatjet2->Fill(ak8jet1->Mass);

	    if( p4_ak8jet0.M() > 90 && p4_ak8jet0.M() < 140 &&
              p4_ak8jet1.M() > 90 &&  p4_ak8jet1.M() < 140 ){
              ++num5;
              h_cutflow->Fill(7);
	      h_events->Fill(7);
              h_cutflow_2->Fill(7);

	      eta_SubJet1_fatjet1->Fill(p4_sj0_ak8jet0.Eta());
              eta_SubJet1_fatjet1->SetYTitle("Events");
              eta_SubJet1_fatjet1->SetXTitle("#eta");
              eta_SubJet1_fatjet1->SetLineWidth(3);

              eta_SubJet2_fatjet1->Fill(p4_sj1_ak8jet0.Eta());
              eta_SubJet2_fatjet1->SetYTitle("Events");
              eta_SubJet2_fatjet1->SetXTitle("#eta");
              eta_SubJet2_fatjet1->SetLineWidth(3);

              pt_SubJet1_fatjet1->Fill(p4_sj0_ak8jet0.Pt());
              pt_SubJet1_fatjet1->SetYTitle("Events");
              pt_SubJet1_fatjet1->SetXTitle("p_{T},[GeV/c]");
              pt_SubJet1_fatjet1->SetLineWidth(3);

              pt_SubJet2_fatjet1->Fill(p4_sj1_ak8jet0.Pt());
              pt_SubJet2_fatjet1->SetYTitle("Events");
              pt_SubJet2_fatjet1->SetXTitle("p_{T},[GeV/c]");
              pt_SubJet2_fatjet1->SetLineWidth(3);

              eta_SubJet1_fatjet2->Fill(p4_sj0_ak8jet1.Eta());
              eta_SubJet1_fatjet2->SetYTitle("Events");
              eta_SubJet1_fatjet2->SetXTitle("#eta");
              eta_SubJet1_fatjet2->SetLineWidth(3);

              eta_SubJet2_fatjet2->Fill(p4_sj1_ak8jet1.Eta());
              eta_SubJet2_fatjet2->SetYTitle("Events");
              eta_SubJet2_fatjet2->SetXTitle("#eta");
              eta_SubJet2_fatjet2->SetLineWidth(3);

              pt_SubJet1_fatjet2->Fill(p4_sj0_ak8jet1.Pt());
              pt_SubJet1_fatjet2->SetYTitle("Events");
              pt_SubJet1_fatjet2->SetXTitle("p_{T},[GeV/c]");
              pt_SubJet1_fatjet2->SetLineWidth(3);

              pt_SubJet2_fatjet2->Fill(p4_sj1_ak8jet1.Pt());
              pt_SubJet2_fatjet2->SetYTitle("Events");
              pt_SubJet2_fatjet2->SetXTitle("p_{T},[GeV/c]");
              pt_SubJet2_fatjet2->SetLineWidth(3);

              NSubJet_fatjet1->Fill(nsj_ak8jet0);
              NSubJet_fatjet1->SetYTitle("Events");
              NSubJet_fatjet1->SetXTitle("no. of subjets");
              NSubJet_fatjet1->SetLineWidth(3);

              NSubJet_fatjet2->Fill(nsj_ak8jet1);
              NSubJet_fatjet2->SetYTitle("Events");
              NSubJet_fatjet2->SetXTitle("no. of subjets");
              NSubJet_fatjet2->SetLineWidth(3);
              
	          
	      //######  b-tagged jets #### 
	      if(one_btagged == 1){
                h_cutflow->Fill(8);       
                h_events->Fill(8);
                
 	        if(two_btagged == 1){
                 
		    h_cutflow->Fill(9);
		    h_events->Fill(9);
		
                   if(three_btagged == 1){
		     h_cutflow->Fill(10);
		     h_events->Fill(10);
                
                     inv_M_HH_3b->Fill((p4_ak8jet0+p4_ak8jet1).M());
                     inv_M_HH_3b->SetYTitle("Events");
                     inv_M_HH_3b->SetXTitle("M_{HH},[GeV]");
                     inv_M_HH_3b->SetLineWidth(3);

		     if(four_btagged==1){ 
		       h_cutflow->Fill(11);
		       h_events->Fill(11);
		
   		       inv_M_HH_4b->Fill((p4_ak8jet0+p4_ak8jet1).M());
                       inv_M_HH_4b->SetYTitle("Events");
                       inv_M_HH_4b->SetXTitle("M_{HH},[GeV]");
                       inv_M_HH_4b->SetLineWidth(3);
		    }
		   }
		  }
                                 
              } //// AK8 jet subjet b-tagging
            
            //#### exact b-tagged jets #####
              if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==1){
 		h_cutflow_2->Fill(8);
		}
	      if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==2){
 	        h_cutflow_2->Fill(9);
                }
	      if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==3){
 	        h_cutflow_2->Fill(10);
                M_HH_3b->Fill((p4_ak8jet0+p4_ak8jet1).M());
		M_HH_3b->SetYTitle("Events");
		M_HH_3b->SetXTitle("M_{HH},[GeV]");
		M_HH_3b->SetLineWidth(3);
                }
	      if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==4){
 	        h_cutflow_2->Fill(11);
                M_HH_4b->Fill((p4_ak8jet0+p4_ak8jet1).M());
		M_HH_4b->SetYTitle("Events");
		M_HH_4b->SetXTitle("M_{HH},[GeV]");
		M_HH_4b->SetLineWidth(3);
	      }	
	    }
	  }
	}
      }
}	//}
     break;    
     }
}      
     }
   }
  }   
   
  

  
 
  TString newdir = "mkdir -p MyHistos" ;
  system(newdir);

  // Show resulting histograms
  TCanvas* c = new TCanvas();
  c->SetLogy();
  h_sdmass_ak81->Draw();
  c->SaveAs("MyHistos/h_sdmass_ak81.png");
  h_sdmass_ak80->Draw();
  c->SaveAs("MyHistos/h_sdmass_ak80.png");
  M_SubJets_fatjet2->Draw();
  c->SaveAs("MyHistos/M_SubJets_fatjet2.png");
  M_SubJets_fatjet1->Draw();
  c->SaveAs("MyHistos/M_SubJets_fatjet1.png");
  h_ak80eta->Draw();
  c->SaveAs("MyHistos/h_ak80eta.png");
  h_ak81eta->Draw();
  c->SaveAs("MyHistos/h_ak81eta.png");
  eta_SubJet2_fatjet2->Draw();
  c->SaveAs("MyHistos/eta_SubJet2_fatjet2.png");
  eta_SubJet1_fatjet2->Draw();
  c->SaveAs("MyHistos/eta_SubJet1_fatjet2.png");
  eta_SubJet2_fatjet1->Draw();
  c->SaveAs("MyHistos/eta_SubJet2_fatjet1.png");
  eta_SubJet1_fatjet1->Draw();
  c->SaveAs("MyHistos/eta_SubJet1_fatjet1.png");
  h_ak80pt->Draw();
  c->SaveAs("MyHistos/h_ak80pt.png");
  h_ak81pt->Draw();
  c->SaveAs("MyHistos/h_ak81pt.png");
  pt_SubJet2_fatjet2->Draw();
  c->SaveAs("MyHistos/pt_SubJet2_fatjet2.png");
  pt_SubJet1_fatjet2->Draw();
  c->SaveAs("MyHistos/pt_SubJet1_fatjet2.png");
  pt_SubJet2_fatjet1->Draw();
  c->SaveAs("MyHistos/pt_SubJet2_fatjet1.png");
  pt_SubJet1_fatjet1->Draw();
  c->SaveAs("MyHistos/pt_SubJet1_fatjet1.png");
  NSubJet_fatjet1->Draw();
  c->SaveAs("MyHistos/NSubJet_fatjet1.png");
  NSubJet_fatjet2->Draw();
  c->SaveAs("MyHistos/NSubJet_fatjet2.png");
  h_ak80_tau2_tau1->Draw();
  c->SaveAs("MyHistos/h_ak80_tau2_tau1.png");
  h_ak81_tau2_tau1->Draw();
  c->SaveAs("MyHistos/h_ak81_tau2_tau1.png");
  inv_M_HH_3b->Draw();
  c->SaveAs("MyHistos/inv_M_HH_3b.png");
  inv_M_HH_4b->Draw();
  c->SaveAs("MyHistos/inv_M_HH_4b.png");  
  delete c; 
  cout << "events in cutflow first bin==" << h_cutflow->GetBinContent(1) << endl;
  h_cutflow->Scale(1./h_cutflow->GetBinContent(1)); 
  fout->cd();
  fout->Write();
  fout->Close();
  cout << "total_events==" << total_events << endl;
  }  
    }

