/*
   Macro for SubJet

   root -l SubJetSoftDropped_DM.C'(200, 0, 10,"output_1.root")'
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
   // if ( f.IsOpen() ) printf("File opened successfully\n");
    //f.ls();
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
           //cout<<"test1....."<<eff<<endl;
          }
        }
      }
    }
  return eff; 
  
}


bool isBTagged(const double pt, const double eta, const int pu, const int fl=5) {
  bool isBTagged(0);

  if (fl == 5) {
    double eff = getEff_b(pt, eta, pu);  
    double rand = r->Rndm();
    // std::cout << " pt = " << pt << " eta = " << eta << " eff = " << eff << " rand = " << rand << std::endl;
    if (eff > rand) isBTagged = 1;
    else isBTagged = 0;
  }

  return isBTagged;

} 

//------------------------------------------------------------------------------

void SubJetSoftDropped_DM(const int pu, const int nmin, const int nmax, const char *output)
{
  gSystem->Load("libDelphes");
  // HH_SM samples
  TString file[60]={"root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_2.root"};
  // HH_node2 samples
  TString file_nd2[60]={"root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_1_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_1_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_1_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_2_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_2_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_2_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_3_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_4_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_4_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_4_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_5_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_5_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_5_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_6_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_6_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_6_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_7_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_7_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_7_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_8_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_8_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_8_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_9_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_9_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_9_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_10_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_10_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_2_14TeV-madgraph_200PU/GluGluToHHTo4B_node_2_14TeV-madgraph_10_2.root"};
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
  TFile* fout = new TFile(output, "RECREATE");
  fout->cd();

  // Book histograms
  TH1F *h_cutflow           = new TH1F("h_cutflow"          , "", 10, 0.5, 10.5);
  TH1F *h_events            = new TH1F("h_events"           , "", 10, 0.5, 10.5);
  TH1F *h_cutflow_2	    = new TH1F("h_cutflow_2"        , "", 5 , 0.5,  5.5);
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
  TH1F *inv_M_HH_3b	    = new TH1F("h_mjj_3b"       , ";M(HH) [GeV]; Events;;", 100, 0, 2000);
  TH1F *inv_M_HH_4b	    = new TH1F("h_mjj_4b"	, ";M(HH) [GeV]; Events;;", 100, 0, 2000);
  TH2F *pt_vs_eff	    = new TH2F("pt_vs_eff"	, ";p_{T};eff;;", 10, 0., 1000., 10, 0., 1.);
  TH2F *t21_j1_j2_sdcut     = new TH2F("t21_j1_j2_sdcut", ";t21(J1);t21(J2);;", 10, 0., 1., 10, 0., 1.);
  
  h_cutflow->GetXaxis()->SetBinLabel(1 ,"All");
  h_cutflow->GetXaxis()->SetBinLabel(2 ,"AK8>1");
  h_cutflow->GetXaxis()->SetBinLabel(3 ,"p_{T}");
  h_cutflow->GetXaxis()->SetBinLabel(4 ,"#eta");
  h_cutflow->GetXaxis()->SetBinLabel(5 ,"#tau_{21}");
  h_cutflow->GetXaxis()->SetBinLabel(6 ,"M(J)");
  h_cutflow->GetXaxis()->SetBinLabel(7 ,"sjBTag>0");
  h_cutflow->GetXaxis()->SetBinLabel(8 ,"sjBTag>1");
  h_cutflow->GetXaxis()->SetBinLabel(9 ,"sjBTag>2");
  h_cutflow->GetXaxis()->SetBinLabel(10 ,"sjBTag>3");

  h_cutflow_2->GetXaxis()->SetBinLabel(1 ,"All");
  h_cutflow_2->GetXaxis()->SetBinLabel(2 ,"sjBTag=1");
  h_cutflow_2->GetXaxis()->SetBinLabel(3 ,"sjBTag=2");
  h_cutflow_2->GetXaxis()->SetBinLabel(4 ,"sjBTag=3");
  h_cutflow_2->GetXaxis()->SetBinLabel(5 ,"sjBTag=4");
  
  h_events->GetXaxis()->SetBinLabel(1 ,"All");
  h_events->GetXaxis()->SetBinLabel(2 ,"AK8>1");
  h_events->GetXaxis()->SetBinLabel(3 ,"p_{T}");
  h_events->GetXaxis()->SetBinLabel(4 ,"#eta");
  h_events->GetXaxis()->SetBinLabel(5 ,"#tau_{21}");
  h_events->GetXaxis()->SetBinLabel(6 ,"#M(J)");
  h_events->GetXaxis()->SetBinLabel(7 ,"sjBTag>0");
  h_events->GetXaxis()->SetBinLabel(8 ,"sjBTag>1");
  h_events->GetXaxis()->SetBinLabel(9 ,"sjBTag>2");
  h_events->GetXaxis()->SetBinLabel(10 ,"sjBTag>3");

  float total_events =0 ,num1 =0, num2=0, num3=0, num4=0, num5=0,num6=0,total_events_AK4=0,num7=0,num8=0,num9=0,num10=0,num11=0,w_4b=0.;
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    ++total_events;
    h_cutflow->Fill(1);
    h_events->Fill(1);
    h_cutflow_2->Fill(1);
    // If event contains at least 2 jets
    if(branchJetAK8->GetEntries() >= 2)
    {
     h_cutflow->Fill(2);
     h_events->Fill(2);
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
        h_cutflow->Fill(3);
	h_events->Fill(3);
        
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
          h_cutflow->Fill(4);
	  h_events->Fill(4);
         
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
            h_cutflow->Fill(5);
	    h_events->Fill(5);
	
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
              h_cutflow->Fill(6);
	      h_events->Fill(6);

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
	      
	      //###### At least b-tagged jets #### 
	      if(one_btagged == 1){
                h_cutflow->Fill(7);
                h_events->Fill(7); 	
 	        if(two_btagged == 1){
		   h_cutflow->Fill(8);
		   h_events->Fill(8);

                   if(three_btagged == 1){
		     h_cutflow->Fill(9);
		     h_events->Fill(9);
                     inv_M_HH_3b->Fill((p4_ak8jet0+p4_ak8jet1).M());
                     inv_M_HH_3b->SetYTitle("Events");
                     inv_M_HH_3b->SetXTitle("M_{HH},[GeV]");
                     inv_M_HH_3b->SetLineWidth(3);

		     if(four_btagged==1){ 
		       h_cutflow->Fill(10);
		       h_events->Fill(10);
   		       inv_M_HH_4b->Fill((p4_ak8jet0+p4_ak8jet1).M());
                       inv_M_HH_4b->SetYTitle("Events");
                       inv_M_HH_4b->SetXTitle("M_{HH},[GeV]");
                       inv_M_HH_4b->SetLineWidth(3);
		    }
		  }
                }
              } //// AK8 jet subjet b-tagging
            
            //#### exact no. of the b-tagged jets #####
              if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==1){
 		h_cutflow_2->Fill(2);
		}
	      if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==2){
 	        h_cutflow_2->Fill(3);
                }
	      if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==3){
 	        h_cutflow_2->Fill(4);
                }
	      if((sj00BTagged+sj01BTagged+sj10BTagged+sj11BTagged)==4){
 	        h_cutflow_2->Fill(5);
                }	
            
            } //// AK8 jet tau21
          } /// AK8 jet soft drop mass
        } //// AK8 jet eta
      } //// AK8 jet pt
    } //// Start Higgs jet selections

  } //// End event loop 
 

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
