/*
   Macro for SubJet

   root -l SubJetSoftDropped_DM.C'("/afs/cern.ch/user/l/lata/public/VBF_50k_2500_0PU.root", 0)'
   */

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif

  TRandom3* r = new TRandom3();

  double getEff_b(double pt, double eta, const int pu) {

    double eff(0); 

    eta = abs(eta);
    if (pt > 3000.) pt = 2999.99;

    if (pt < 20.) { return eff; }

    float x[30], ex[30];
    x[0]  =  25.; ex[0]  =  5.; 
    x[1]  =  35.; ex[1]  =  5.; 
    x[2]  =  45.; ex[2]  =  5.; 
    x[3]  =  55.; ex[3]  =  5.; 
    x[4]  =  65.; ex[4]  =  5.; 
    x[5]  =  75.; ex[5]  =  5.; 
    x[6]  =  85.; ex[6]  =  5.; 
    x[7]  =  95.; ex[7]  =  5.; 
    x[8]  = 110.; ex[8]  = 10.; 
    x[9]  = 130.; ex[9]  = 10.; 
    x[10] = 150.; ex[10] = 10.; 
    x[11] = 170.; ex[11] = 10.; 
    x[12] = 190.; ex[12] = 10.; 
    x[13] = 225.; ex[13] = 25.; 
    x[14] = 275.; ex[14] = 25.; 
    x[15] = 325.; ex[15] = 25.; 
    x[16] = 375.; ex[16] = 25.; 
    x[17] = 450.; ex[17] = 50.; 
    x[18] = 550.; ex[18] = 50.; 
    x[19] = 650.; ex[19] = 50.; 
    x[20] = 750.; ex[20] = 50.; 
    x[21] = 900.; ex[21] =100.; 
    x[22] =1200.; ex[22] =200.; 
    x[23] =1700.; ex[23] =300.; 
    x[24] =2500.; ex[24] =500.; 

    int pti;
    for (int ii=0; ii < 25; ++ii) {
      if ( pt >= x[ii]-ex[ii] && pt < x[ii]+ex[ii]  ) {
        pti = ii;
        break;
      } 
      else pti = 24;
    } 

    float effB_etaLT15_PU0[] = {
      0.7237, 0.7747, 0.7934, 0.7973, 0.7973, 0.7891, 0.7843, 0.7719, 0.767, 0.7474, 
      0.7291, 0.7102, 0.6993, 0.6707, 0.6493, 0.6054, 0.574, 0.5194, 0.4488, 0.3867, 
      0.331, 0.2663, 0.216, 0.1264, 0.1538 };

    float effB_15eta25_PU0[] = {
      0.5769, 0.6107, 0.6405, 0.6448, 0.6494, 0.6403, 0.6316, 0.6327, 0.6324, 0.6053, 
      0.6033, 0.5815, 0.5647, 0.5427, 0.503, 0.4672, 0.4532, 0.39, 0.3571, 0.3499, 
      0.3043, 0.2796, 0.1308, 0, 0 };

    float effB_25eta35_PU0[] = {
      0.3799, 0.4388, 0.4858, 0.4885, 0.4825, 0.5008, 0.4845, 0.4613, 0.4889, 0.4754, 
      0.4646, 0.4424, 0.4065, 0.3468, 0.3546, 0.2533, 0.2352, 0.317, 0, 0, 
      0, 0, 0, 0, 0 };

    float effB_etaLT15_PU200[] = {
      0.6266, 0.6982, 0.7382, 0.7447, 0.7522, 0.7472, 0.7519, 0.7424, 0.7334, 0.7274, 
      0.7195, 0.6937, 0.6833, 0.6631, 0.6356, 0.5949, 0.5648, 0.5019, 0.4436, 0.3986, 
      0.3232, 0.2569, 0.2136, 0.1115, 0.1658 };

    float effB_15eta25_PU200[] = {
      0.4318, 0.5274, 0.565, 0.5873, 0.6031, 0.611, 0.6038, 0.5949, 0.5926, 0.6003, 
      0.5845, 0.5587, 0.5504, 0.5306, 0.4872, 0.4508, 0.4224, 0.3845, 0.324, 0.3601, 
      0.3449, 0.2864, 0.2, 0, 0 };

    float effB_25eta35_PU200[] = {
      0.2461, 0.3278, 0.3705, 0.3946, 0.4111, 0.4281, 0.4055, 0.4406, 0.4372, 0.4157, 
      0.4017, 0.413, 0.3913, 0.3388, 0.3043, 0.2283, 0.3275, 0.1363, 0, 0, 
      0, 0, 0, 0, 0 };

    if (pu == 0) {
      if (eta >= 0 && eta < 1.5) {
        eff = effB_etaLT15_PU0[pti] ; 
      } 
      else if (eta >= 1.5 && eta < 2.5) {
        eff = effB_15eta25_PU0[pti] ; 
      } 
      else if (eta >= 2.5 && eta < 3.5) {
        eff = effB_25eta35_PU0[pti] ;
      } 
      else {
        eff = 0;
      } 
    } 
    else if (pu == 200) {
      if (eta >= 0 && eta < 1.5) {
        eff = effB_etaLT15_PU200[pti] ; 
      } 
      else if (eta >= 1.5 && eta < 2.5) {
        eff = effB_15eta25_PU200[pti] ; 
      } 
      else if (eta >= 2.5 && eta < 3.5) {
        eff = effB_25eta35_PU200[pti] ;
      } 
      else {
        eff = 0;
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

void SubJetSoftDropped_DM(const char *inputFile, const int pu)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

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
  TH1F *pt_fatjet_1         = new TH1F("pt_fatjet_1"        , "p_{T} of leading AK8_Jet",100,0,3000);
  TH1F *pt_fatjet_2         = new TH1F("pt_fatjet_2"        , "p_{T} of 2nd leading AK8_Jet",100,0,3000);
  TH1F *eta_fatjet_1        = new TH1F("eta_fatjet_1"       , "#eta of leading AK8_Jet", 40, -4, 4);
  TH1F *eta_fatjet_2        = new TH1F("eta_fatjet_2"       , "#eta of 2nd leading AK8_Jet", 40, -4, 4);
  TH1F *Msd_fatjet1         = new TH1F("Msd_fatjet1"        , ";M_{soft drop} of leading AK8_Jet;[GeV];", 100, 0, 200);
  TH1F *Msd_fatjet2         = new TH1F("Msd_fatjet2"        , ";M_{soft drop} of 2nd leading AK8_Jet;[GeV];", 100, 0, 200);
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
  TH1F *tau2bytau1_fatjet1  = new TH1F("tau2bytau1_fatjet1" ,"#tau_{2}/#tau_{1}(leading AK8_Jet)", 50,0,1);
  TH1F *tau2bytau1_fatjet2  = new TH1F("tau2bytau1_fatjet2" ,"#tau_{2}/#tau_{1}(2nd leading AK8_Jet)", 50,0,1);
  TH1F *DeltaEta            = new TH1F("DeltaEta"           ,"#delta#eta for VBF jets",20,0,10);
  TH1F *eta1_x_eta2         = new TH1F("eta1_x_eta2"        , "#eta_{j1}*#eta_{j2} (VBF)",4, -2, 2);
  TH1F *inv_M_graviton      = new TH1F("inv_M_graviton"     , "Inv_Mass of 4 SubJets", 100, 0, 5000);
  TH1F *inv_M_add_jets      = new TH1F("inv_M_add_jets"     , "Inv_Mass of additional jets (VBF)", 100, 0, 5000);

  h_cutflow->GetXaxis()->SetBinLabel(1 ,"All");
  h_cutflow->GetXaxis()->SetBinLabel(2 ,"AK8Pt");
  h_cutflow->GetXaxis()->SetBinLabel(3 ,"AK8Eta");
  h_cutflow->GetXaxis()->SetBinLabel(3 ,"AK8Eta");
  h_cutflow->GetXaxis()->SetBinLabel(4 ,"AK8SDMass");
  h_cutflow->GetXaxis()->SetBinLabel(5 ,"AK8#tau_{21}");
  h_cutflow->GetXaxis()->SetBinLabel(6 ,"AK8SubjetBTag");
  h_cutflow->GetXaxis()->SetBinLabel(7 ,"VBFPt");
  h_cutflow->GetXaxis()->SetBinLabel(8 ,"VBFEta");
  h_cutflow->GetXaxis()->SetBinLabel(9 ,"VBFOppEta");
  h_cutflow->GetXaxis()->SetBinLabel(10,"VBFDeEta");
  h_cutflow->GetXaxis()->SetBinLabel(11,"VBFMInv");

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

      int tau1_1(ak8jet0->Tau[0]);
      int tau2_1(ak8jet0->Tau[1]);

      int tau1_2(ak8jet1->Tau[0]);
      int tau2_2(ak8jet1->Tau[1]);

      int nsjBTagged = 
        int(isBTagged(p4_sj0_ak8jet0.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) + 
        int(isBTagged(p4_sj0_ak8jet1.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) + 
        int(isBTagged(p4_sj1_ak8jet0.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) + 
        int(isBTagged(p4_sj1_ak8jet1.Pt(), p4_sj0_ak8jet0.Eta(), pu, 5)) ; 

      pt_fatjet_1->Fill(p4_ak8jet0.Pt());
      pt_fatjet_1->SetYTitle("Events");
      pt_fatjet_1->SetXTitle("p_{T},[GeV/c]");
      pt_fatjet_1->SetLineWidth(3);

      pt_fatjet_2->Fill(p4_ak8jet1.Pt());
      pt_fatjet_2->SetYTitle("Events");
      pt_fatjet_2->SetXTitle("p_{T},[GeV/c]");
      pt_fatjet_2->SetLineWidth(3);

      //// Starting selections on AK8 jets 
      if( p4_ak8jet0.Pt() > 300 && p4_ak8jet1.Pt() > 300 ){
        ++num1; 
        h_cutflow->Fill(2);
        eta_fatjet_1->Fill(p4_ak8jet0.Eta());
        eta_fatjet_1->SetYTitle("Events");
        eta_fatjet_1->SetXTitle("#eta");
        eta_fatjet_1->SetLineWidth(3);

        eta_fatjet_2->Fill(p4_ak8jet1.Eta());
        eta_fatjet_2->SetYTitle("Events");
        eta_fatjet_2->SetXTitle("#eta");
        eta_fatjet_2->SetLineWidth(3);

        if( abs(ak8jet0->Eta)<3 &&  abs(ak8jet1->Eta)<3 ){
          ++num2;
          h_cutflow->Fill(3);
          Msd_fatjet1->Fill(p4_ak8jet0.M());
          Msd_fatjet1->SetYTitle("Events");
          Msd_fatjet1->SetXTitle("inv_mass,[GeV]");
          Msd_fatjet1->SetLineWidth(3);
          Msd_fatjet2->Fill(p4_ak8jet1.M());
          Msd_fatjet2->SetYTitle("Events");
          Msd_fatjet2->SetXTitle("inv_mass,[GeV]");
          Msd_fatjet2->SetLineWidth(3);
          Minv_fatjet1->Fill(ak8jet0->Mass);
          Minv_fatjet2->Fill(ak8jet1->Mass);

	 

          if( p4_ak8jet0.M() > 80 && p4_ak8jet0.M() < 160 &&
              p4_ak8jet1.M() > 80 &&  p4_ak8jet1.M() < 160 ){
            ++num4;
            h_cutflow->Fill(4);
            tau2bytau1_fatjet1->Fill(1.0*tau2_1/tau1_1);
            tau2bytau1_fatjet1->SetYTitle("Events");
            tau2bytau1_fatjet1->SetXTitle("#tau_{2}/#tau_{1}");
            tau2bytau1_fatjet1->SetLineWidth(3);

            tau2bytau1_fatjet2->Fill(1.0*tau2_2/tau1_2);
            tau2bytau1_fatjet2->SetYTitle("Events");
            tau2bytau1_fatjet2->SetXTitle("#tau_{2}/#tau_{1}");
            tau2bytau1_fatjet2->SetLineWidth(3);

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

                int nak4(branchJetAK4->GetEntries());
                if (nak4 >= 2) { 
                  for (int ii = 0; ii < nak4; ++ii) { 
                    for (int jj = ii+1; jj < nak4; ++jj) {
                      Jet* jet0 = (Jet*) branchJetAK4->At(ii);
                      Jet* jet1 = (Jet*) branchJetAK4->At(jj);
                      if ( jet0->PT > 50. && jet1->PT > 50.) {
                        ++num7;

                        if ( abs(jet0->Eta) < 5. && abs(jet1->Eta) < 5. ) {
                          ++num8;
                          eta1_x_eta2-> Fill ( jet0->Eta * jet1->Eta );
                          eta1_x_eta2-> SetYTitle("Events");
                          eta1_x_eta2-> SetXTitle("#eta_{j1}*#eta_{j2}");
                          eta1_x_eta2-> SetLineWidth(3);

                          if ( (jet0->Eta)*(jet1->Eta) < 0) {
                            ++num9;
                            DeltaEta->Fill(abs(jet0->Eta-jet1->Eta));
                            DeltaEta->SetYTitle("Events");
                            DeltaEta->SetXTitle("#delta#eta");
                            DeltaEta->SetLineWidth(3);

                            if ( abs((jet0->Eta) - (jet1->Eta)) > 4. ) {
                              ++num10;
                              inv_M_add_jets->Fill((jet0->P4()+jet1->P4()).M());
                              inv_M_add_jets->SetYTitle("Events");
                              inv_M_add_jets->SetXTitle("Inv mass AK4 jets,[GeV]");
                              inv_M_add_jets->SetLineWidth(3);

                              if (( jet0->P4() + jet1->P4()).M() > 300.){
                                ++num11;
                              } //// VBF jet inv. mass sel
                            } //// VBF jet DEta sel
                          } //// AK4 jet eta in opposite hemisphere sel
                        } //// AK4 jet pT sel 
                      } //// AK4 jet eta sel 
                    } //// Loop over 2nd AK4 jet 
                  } //// Loop over 1st AK4 jet 
                } //// End VBF jet selections

                if (num7 > 0) {
                  h_cutflow->Fill(7); 
                  if (num8 > 0) {
                    h_cutflow->Fill(8); 
                    if (num9 > 0) {
                      h_cutflow->Fill(9); 
                      if (num10 > 0) {
                        h_cutflow->Fill(10); 
                        if (num11 > 0) {
                          h_cutflow->Fill(11); 
                          inv_M_graviton->Fill((p4_sj0_ak8jet0+p4_sj1_ak8jet0+p4_sj0_ak8jet1+p4_sj1_ak8jet1).M());
                          inv_M_graviton->SetYTitle("Events");
                          inv_M_graviton->SetXTitle("M_{Gr},[GeV]");
                          inv_M_graviton->SetLineWidth(3);
                        }
                      }
                    }
                  }
                } //// Selecting events containing VBF jets

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
  Msd_fatjet2->Draw();
  c->SaveAs("MyHistos/Msd_fatjet2.png");
  Msd_fatjet1->Draw();
  c->SaveAs("MyHistos/Msd_fatjet1.png");
  inv_M_graviton->Draw();
  c->SaveAs("MyHistos/inv_M_graviton.png");
  M_SubJets_fatjet2->Draw();
  c->SaveAs("MyHistos/M_SubJets_fatjet2.png");
  M_SubJets_fatjet1->Draw();
  c->SaveAs("MyHistos/M_SubJets_fatjet1.png");
  eta_fatjet_1->Draw();
  c->SaveAs("MyHistos/eta_fatjet_1.png");
  eta_fatjet_2->Draw();
  c->SaveAs("MyHistos/eta_fatjet_2.png");
  eta_SubJet2_fatjet2->Draw();
  c->SaveAs("MyHistos/eta_SubJet2_fatjet2.png");
  eta_SubJet1_fatjet2->Draw();
  c->SaveAs("MyHistos/eta_SubJet1_fatjet2.png");
  eta_SubJet2_fatjet1->Draw();
  c->SaveAs("MyHistos/eta_SubJet2_fatjet1.png");
  eta_SubJet1_fatjet1->Draw();
  c->SaveAs("MyHistos/eta_SubJet1_fatjet1.png");
  pt_fatjet_1->Draw();
  c->SaveAs("MyHistos/pt_fatjet_1.png");
  pt_fatjet_2->Draw();
  c->SaveAs("MyHistos/pt_fatjet_2.png");
  pt_SubJet2_fatjet2->Draw();
  c->SaveAs("MyHistos/pt_SubJet2_fatjet2.png");
  pt_SubJet1_fatjet2->Draw();
  c->SaveAs("MyHistos/pt_SubJet1_fatjet2.png");
  pt_SubJet2_fatjet1->Draw();
  c->SaveAs("MyHistos/pt_SubJet2_fatjet1.png");
  pt_SubJet1_fatjet1->Draw();
  c->SaveAs("MyHistos/pt_SubJet1_fatjet1.png");
  inv_M_add_jets->Draw();
  c->SaveAs("MyHistos/inv_M_add_jets.png");
  DeltaEta->Draw();
  c->SaveAs("MyHistos/DeltaEta.png");
  NSubJet_fatjet1->Draw();
  c->SaveAs("MyHistos/NSubJet_fatjet1.png");
  NSubJet_fatjet2->Draw();
  c->SaveAs("MyHistos/NSubJet_fatjet2.png");
  tau2bytau1_fatjet1->Draw();
  c->SaveAs("MyHistos/tau2bytau1_fatjet1.png");
  tau2bytau1_fatjet2->Draw();
  c->SaveAs("MyHistos/tau2bytau1_fatjet2.png");
  eta1_x_eta2->Draw();
  c->SaveAs("MyHistos/eta1_x_eta2.png");

  delete c; 

  h_cutflow->Scale(1./h_cutflow->GetBinContent(1)); 

  fout->cd();
  fout->Write();
  fout->Close();

}
