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

double getBSM_weight(double Mass, double cosine, const int node) {
//TFile *f = TFile::Open("Coefficients_14TeV.root");
//f->Print();
//TH2D *A1_14TeV = (TH2D*)f->Get("A1_14TeV");
//TH2D *h_node1=A1_14TeV->Clone();
//TFile *f1 = TFile::Open("Denom.root");
//h_node1->Divide(h_total);
//TH2D *h_denom = (TH2D*)f->Get("h_denom");
//A1_14TeV->Divide(h_denom);
//A1_14TeV->SaveAs("node1_w.png");

TFile *f = TFile::Open("Distros_5p_500000ev_12sam_13TeV_JHEP_500K.root");
f->Print();
TH2D *h_w_nd1 = (TH2D*)f->Get("0_bin1");
TH2D *h_w_nd2 = (TH2D*)f->Get("1_bin1");
double mHH=0., cosHH=0., weight=0.;

h_w_nd1->Divide(h_w_nd2);
h_w_nd1->SaveAs("map.root");
int x_range=(h_w_nd1->GetNbinsX());
int y_range=(h_w_nd1->GetNbinsY());

for(int i=1; i < x_range+1; i++){
    for(int j=1; j < y_range+1; j++){
    mHH= h_w_nd1->GetXaxis()->GetBinLowEdge(i);
    cosHH= abs(h_w_nd1->GetYaxis()->GetBinLowEdge(j));
    mHHwidth  = h_w_nd1->GetXaxis()->GetBinWidth(i);
    cosHHwidth = abs(h_w_nd1->GetYaxis()->GetBinWidth(j));
    cout << "mHH==" << mHH << "  cosHH==" << cosHH  << endl;
    cout << "mHH+width==" << mHH+mHHwidth << "  cosHH+width==" << cosHH+cosHHwidth  << endl;
   // cout << "weight1=="  << h_w_nd1->GetBinContent(i,j) << endl;
    cout << "Mass==" << Mass << "  cosine==" << cosine  << endl;    
    if (mHH <= Mass && Mass < (mHH+mHHwidth)){
     if (abs(cosHH) <= abs(cosine) && abs(cosine) < abs(cosHH+cosHHwidth)){
      cout << "mHH==" << mHH << "  cosHH==" << cosHH  << endl;
      cout << "Mass==" << Mass << "  cosine==" << cosine  << endl;
      weight = h_w_nd1->GetBinContent(i,j);
      cout << "weight2=="  << weight << endl;
    }
    }
   }
  }
cout << "weight3=="  << weight << endl;
return weight;	
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

void SM_2Dmap(const int pu, const int nmin, const int nmax, const char *output)
{
  gSystem->Load("libDelphes");
  
  TString file[300]={"root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_1_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_2_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_3_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_4_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_5_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_6_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_7_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_8_2.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_0.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_1.root","root://cms-xrd-global.cern.ch//store/group/upgrade/delphes_output/YR_Delphes/Delphes342pre15/GluGluToHHTo4B_node_SM_14TeV-madgraph_200PU/GluGluToHHTo4B_node_SM_14TeV-madgraph_9_2.root"};	
  // Create chain of root trees
    TChain chain("Delphes");
    int fileno=0;
    for(int i=nmin; i<nmax; i++){
    fileno++;
    if(fileno == 1){
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
  TLorentzVector genHHMomentum;
  GenParticle *particle1,*particle2,*particle3,*mother1,*mother2;
  Int_t index, motherPID_1, motherPID_2;
  double mHH=0., cosHH=0.,weight=0.;

  // Book histograms
  TH1F *h_cutflow           = new TH1F("h_cutflow"          , "", 10, 0.5, 10.5);
  TH1F *h_events            = new TH1F("h_events"           , "", 10, 0.5, 10.5);
  TH1F *h_cutflow_2	    = new TH1F("h_cutflow_2"        , "", 10, 0.5, 10.5);
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
  TH1F *inv_M_qq            = new TH1F("h_mass_qq"      , ";#hat{M}_{qq} [GeV]; Events;;", 100, 0, 1000);
  TH1F *inv_HT_qq           = new TH1F("h_HT_qq"        , ";H_{T} [GeV]; Events;;", 100, 0, 2500);
  TH1F *M_genHH             = new TH1F("h_M_genHH"     ,";gen {M}_{HH} [GeV]; Events;;", 100, 0, 2000);
  TH1F *cos_genHH           = new TH1F("h_cos_genHH"   ,"; cos#theta; Events;;", 100, 0., 1.0);
  TH2D *M_vs_cos	    = new TH2D("h_m_vs_cos"    ,";m_{HH};cos#theta;;",90, 0, 1800, 10, -1.0, 1.0);
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
  h_cutflow_2->GetXaxis()->SetBinLabel(2 ,"AK8>1");
  h_cutflow_2->GetXaxis()->SetBinLabel(3 ,"p_{T}");
  h_cutflow_2->GetXaxis()->SetBinLabel(4 ,"#eta");
  h_cutflow_2->GetXaxis()->SetBinLabel(5 ,"#tau_{21}");
  h_cutflow_2->GetXaxis()->SetBinLabel(6 ,"M(J)");
  h_cutflow_2->GetXaxis()->SetBinLabel(7 ,"sjBTag=1");
  h_cutflow_2->GetXaxis()->SetBinLabel(8 ,"sjBTag=2");
  h_cutflow_2->GetXaxis()->SetBinLabel(9 ,"sjBTag=3");
  h_cutflow_2->GetXaxis()->SetBinLabel(10,"sjBTag=4");
  
  h_events->GetXaxis()->SetBinLabel(1 ,"All");
  h_events->GetXaxis()->SetBinLabel(2 ,"AK8>1");
  h_events->GetXaxis()->SetBinLabel(3 ,"p_{T}");
  h_events->GetXaxis()->SetBinLabel(4 ,"#eta");
  h_events->GetXaxis()->SetBinLabel(5 ,"#tau_{21}");
  h_events->GetXaxis()->SetBinLabel(6 ,"M(J)");
  h_events->GetXaxis()->SetBinLabel(7 ,"sjBTag>0");
  h_events->GetXaxis()->SetBinLabel(8 ,"sjBTag>1");
  h_events->GetXaxis()->SetBinLabel(9 ,"sjBTag>2");
  h_events->GetXaxis()->SetBinLabel(10 ,"sjBTag>3");

  float total_events =0 ,num1 =0, num2=0, num3=0, num4=0, num5=0,num6=0,total_events_AK4=0,num7=0,num8=0,num9=0,num10=0,num11=0, w_4b=0., count1=0., count2=0., countqq=0, HT=0;
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  //for(Int_t entry = 0; entry < 10; ++entry)
  {
    // Load selected branches with data from specified event
  treeReader->ReadEntry(entry);
  ++total_events;
  h_cutflow->Fill(1);
  h_events->Fill(1);
  h_cutflow_2->Fill(1);
  
  for(i = 0; i < branchParticle->GetEntries(); i++){
     particle1 = (GenParticle*) branchParticle->At(i);
     if (particle1->PID == 25 && particle1->Status == 22){
     countqq++;
      if(countqq==1){
       count1=i; 
       }	
      else if(countqq==2){
        count2=i;
      particle2 = (GenParticle*) branchParticle->At(count1);
      particle3 = (GenParticle*) branchParticle->At(count2);
      countqq=0;
      genHHMomentum = particle2->P4()+particle3->P4();
      
             
	      mHH = genHHMomentum.M();
	      TLorentzVector HH_cm = genHHMomentum;
	      auto boostv = genHHMomentum.BoostVector();
	      HH_cm.Boost(-boostv);
	      TLorentzVector p1_cm = particle2->P4();
              TLorentzVector p2_cm = particle3->P4();
	      p1_cm.Boost(-boostv);
              p2_cm.Boost(-boostv);
              cosHH = p1_cm.CosTheta();
              int node=1;
	      M_genHH->Fill(mHH);
	      cos_genHH->Fill(cosHH);
	      M_vs_cos->Fill(mHH,cosHH);
             // weight=getBSM_weight(mHH, cosHH, node);
             // cout << "weight==" << weight << endl;
            
     break;    
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
}
