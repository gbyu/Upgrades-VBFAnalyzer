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

    double pt,eta,ptwidth,etawidth,eff; 
    
    etain = abs(etain);
    if (ptin > 3000.) ptin = 2999.99;

    TFile f("effs/beff_200PU_WPM.root");
    TH1F *heff = (TH1F*)f.Get("heff");
    int x_range=(heff->GetNbinsX())+2;
    int y_range=(heff->GetNbinsY())+1;
    for(int i=0; i < x_range; i++){
       for(int j=0; i < y_range; j++){
         pt       = heff->GetXaxis()->GetBinLowEdge(i);
         eta      = heff->GetYaxis()->GetBinLowEdge(j);
         ptwidth  = heff->GetXaxis()->GetBinWidth(i);
         etawidth = heff->GetYaxis()->GetBinWidth(j);
	 if (pt <= ptin < pt+ptwidth && eta <= etain < eta+etawidth){
           eff=heff->GetBinContent(i,j);
           cout<<"test1....."<<endl;
         }
         else {
        eff = 0;
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

void SubJetSoftDropped_DM(const int pu)
{
  gSystem->Load("libDelphes");
  
  TString file[60]={"root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_5.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_0.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_1.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_2.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_3.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_4.root","root://cmseos.fnal.gov//store/user/snowmass/noreplica/YR_Delphes_prod-luca-split/Delphes342pre14_split/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_5.root"};
  // Create chain of root trees
    TChain chain("Delphes");
    for(int i=0; i<1; i++){
    chain.Add(file[i]);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Int_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJetAK8 = treeReader->UseBranch("JetPUPPIAK8"); ////DM changing to PUPPIAK8 jets
  TClonesArray *branchJetAK4 = treeReader->UseBranch("JetPUPPI"); ////DM AK4 jets for VBF tagging

  TFile* fout = new TFile("output.root", "RECREATE");
  fout->cd();

  // Book histograms
  TH1F *h_cutflow           = new TH1F("h_cutflow"          , "", 11, 0.5, 11.5);
  TH1F *h_ak80pt            = new TH1F("h_ak80pt"        , "p_{T} of leading AK8_Jet",100,0,3000);
  TH1F *h_ak81pt            = new TH1F("h_ak81pt"        , "p_{T} of 2nd leading AK8_Jet",100,0,3000);
  TH1F *h_ak80eta           = new TH1F("h_ak80eta"       , "#eta of leading AK8_Jet", 40, -4, 4);
  TH1F *h_ak81eta           = new TH1F("h_ak81eta"       , "#eta of 2nd leading AK8_Jet", 40, -4, 4);
  TH1F *h_sdmass_ak80       = new TH1F("h_sdmass_ak80"        , ";M_{soft drop} of leading AK8_Jet;[GeV];", 100, 0, 200);
  TH1F *h_sdmass_ak81       = new TH1F("h_sdmass_ak81"        , ";M_{soft drop} of 2nd leading AK8_Jet;[GeV];", 100, 0, 200);
  TH1F *Minv_fatjet1        = new TH1F("Minv_fatjet1"       , ";Mass of leading AK8_Jet;[GeV];", 100, 0, 200);
  TH1F *Minv_fatjet2        = new TH1F("Minv_fatjet2"       , ";Mass of 2nd leading AK8_Jet;[GeV];", 100, 0, 200);
  TH1F *eta_SubJet1_fatjet1 = new TH1F("eta_SubJet1_fatjet1","#eta of SubJet_1 (leading AK8_Jet)",40,-4 ,4);
  TH1F *eta_SubJet2_fatjet1 = new TH1F("eta_SubJet2_fatjet1","#eta of SubJet_2 (leading AK8_Jet)",40,-4 ,4);
  TH1F *eta_SubJet1_fatjet2 = new TH1F("eta_SubJet1_fatjet2","#eta of SubJet_1 (2nd leading AK8_Jet)",40,-4 ,4);
  TH1F *eta_SubJet2_fatjet2 = new TH1F("eta_SubJet2_fatjet2","#eta of SubJet_2 (2nd leading AK8_Jet",40,-4 ,4);
  TH1F *pt_SubJet1_fatjet1  = new TH1F("pt_SubJet1_fatjet1" ,"p_{T} of SubJet_1 (leading AK8_Jet)",100,0,1000);
  TH1F *pt_SubJet2_fatjet1  = new TH1F("pt_SubJet2_fatjet1" ,"p_{T} of SubJet_2 (leading AK8_Jet)",100,0,1000);
  TH1F *pt_SubJet1_fatjet2  = new TH1F("pt_SubJet1_fatjet2" ,"p_{T} of SubJet_1 (2nd leading AK8_Jet)",100,0,1000);
  TH1F *pt_SubJet2_fatjet2  = new TH1F("pt_SubJet2_fatjet2" ,"p_{T} of SubJet_2 (2nd leading AK8_Jet",100,0,1000);
  TH1F *M_SubJets_fatjet1   = new TH1F("M_SubJets_fatjet1"  , "Inv_Mass of SubJets (leading AK8_jet)", 100, 0, 500);
  TH1F *M_SubJets_fatjet2   = new TH1F("M_SubJets_fatjet2"  , "Inv_Mass of SubJets (2nd leading AK8_Jet)", 100, 0, 500);
  TH1D *NSubJet_fatjet1     = new TH1D("NSubJet_fatjet1"    , "no. of SubJets(leading Jet)",5,0,5);
  TH1D *NSubJet_fatjet2     = new TH1D("NSubJet_fatjet2"    , "no. of SubJets(2nd leading Jet)",5,0,5);
  TH1F *h_ak80_tau2_tau1    = new TH1F("h_ak80_tau2_tau1" ,"#tau_{2}/#tau_{1}(leading AK8_Jet)", 50,0,1);
  TH1F *h_ak81_tau2_tau1    = new TH1F("h_ak81_tau2_tau1" ,"#tau_{2}/#tau_{1}(2nd leading AK8_Jet)", 50,0,1);

  h_cutflow->GetXaxis()->SetBinLabel(1 ,"All");
  h_cutflow->GetXaxis()->SetBinLabel(2 ,"AK8Pt");
  h_cutflow->GetXaxis()->SetBinLabel(3 ,"AK8Eta");
  h_cutflow->GetXaxis()->SetBinLabel(3 ,"AK8Eta");
  h_cutflow->GetXaxis()->SetBinLabel(4 ,"AK8SDMass");
  h_cutflow->GetXaxis()->SetBinLabel(5 ,"AK8#tau_{21}");
  h_cutflow->GetXaxis()->SetBinLabel(6 ,"AK8SubjetBTag");

  float total_events =0 ,num1 =0, num2=0, num3=0, num4=0, num5=0,num6=0,total_events_AK4=0,num7=0,num8=0,num9=0,num10=0,num11=0;
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    ++total_events;
    h_cutflow->Fill(1);

    // If event contains at least 2 jets
    if(branchJetAK8->GetEntries() >= 2)
    {

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

      int nsjBTagged = 
        int(isBTagged(p4_sj0_ak8jet0.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) + 
        int(isBTagged(p4_sj0_ak8jet1.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) + 
        int(isBTagged(p4_sj1_ak8jet0.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) + 
        int(isBTagged(p4_sj1_ak8jet1.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) ; 

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
        h_cutflow->Fill(2);
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
          h_cutflow->Fill(3);
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
            ++num4;
            h_cutflow->Fill(4);
            h_ak80_tau2_tau1->Fill(1.0*tau2_1/tau1_1);
            h_ak80_tau2_tau1->SetYTitle("Events");
            h_ak80_tau2_tau1->SetXTitle("#tau_{2}/#tau_{1}");
            h_ak80_tau2_tau1->SetLineWidth(3);

            h_ak81_tau2_tau1->Fill(1.0*tau2_2/tau1_2);
            h_ak81_tau2_tau1->SetYTitle("Events");
            h_ak81_tau2_tau1->SetXTitle("#tau_{2}/#tau_{1}");
            h_ak81_tau2_tau1->SetLineWidth(3);

            if(tau2_1/tau1_1 < 0.6 && tau2_2/tau1_2 < 0.6){
              ++num5;
              h_cutflow->Fill(5);
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

	      

              if(nsjBTagged >= 3){    //////////////// selection cut of b-tagging for subjets///////
                ++num6;
                h_cutflow->Fill(6);
                M_SubJets_fatjet1->Fill((p4_sj0_ak8jet0+p4_sj1_ak8jet0).M());
                M_SubJets_fatjet1->SetYTitle("Events");
                M_SubJets_fatjet1->SetXTitle("inv_mass,[GeV]");
                M_SubJets_fatjet1->SetLineWidth(3);

                M_SubJets_fatjet2->Fill((p4_sj0_ak8jet1+p4_sj1_ak8jet1).M());
                M_SubJets_fatjet2->SetYTitle("Events");
                M_SubJets_fatjet2->SetXTitle("inv_mass,[GeV]");
                M_SubJets_fatjet2->SetLineWidth(3);

                          h_cutflow->Fill(7); 

              } //// AK8 jet subjet b-tagging 
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
  
  delete c; 

  h_cutflow->Scale(1./h_cutflow->GetBinContent(1)); 

  fout->cd();
  fout->Write();
  fout->Close();
 } 
}
