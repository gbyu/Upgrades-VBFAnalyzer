#!/usr/bin/env python

import os, sys, ROOT
import numpy as np

ROOT.gROOT.SetBatch(1)
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPalette(1)
ROOT.gStyle.SetNdivisions(405,"x");
ROOT.gStyle.SetEndErrorSize(0.)
ROOT.gStyle.SetErrorX(0.001)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)

def getSJBTagEff(ptin, etain, fmap):
  etain = abs(etain)
  f = ROOT.TFile.Open(fmap)
  heff = f.Get('heff')
  for i in range(0, heff.GetNbinsX()+2):
    for j in range(0, heff.GetNbinsY()+01):
      pt       = heff.GetXaxis().GetBinLowEdge(i)
      eta      = heff.GetYaxis().GetBinLowEdge(j)
      ptwidth  = heff.GetXaxis().GetBinWidth(i)
      etawidth = heff.GetYaxis().GetBinWidth(j)
      if pt <= ptin < pt+ptwidth and eta <= etain < eta+etawidth:
        return heff.GetBinContent(i,j)
      else: continue
  return 0

def getHTagEff(ptin, etain):
  etain = abs(etain)
  f = ROOT.TFile.Open('heff.root')
  heff = f.Get('heff')
  for i in range(0, heff.GetNbinsX()+2):
    for j in range(0, heff.GetNbinsY()+01):
      pt       = heff.GetXaxis().GetBinLowEdge(i)
      eta      = heff.GetYaxis().GetBinLowEdge(j)
      ptwidth  = heff.GetXaxis().GetBinWidth(i)
      etawidth = heff.GetYaxis().GetBinWidth(j)
      if pt <= ptin < pt+ptwidth and eta <= etain < eta+etawidth:
        return heff.GetBinContent(i,j)
      else: continue
  return 0

import optparse

def main():

  options = optparse.OptionParser()
  
  options.add_option('-f', '--files',  
      dest="files", 
      default="VBF_M1500_W01_PU200.txt",
      type="string",
      )
  options.add_option('-n', '--maxEvts',  
      dest="maxEvts", 
      default=-1,
      type="int",
      )
  
  evtsel = optparse.OptionGroup(options, "Event selections",
                          "Caution: Do not change by hand")
                                              
  evtsel.add_option("--nak8min", 
      dest="nak8Min", 
      default=2,
      type="int",
      )
  
  evtsel.add_option("--ptak8_0_Min", 
      dest="ptak8_0_Min", 
      default=300.,
      type="float",
      )
  
  evtsel.add_option("--ptak8_1_Min", 
      dest="ptak8_1_Min", 
      default=300.,
      type="float",
      )
  
  evtsel.add_option("--etaak8_0_Max", 
      dest="etaak8_0_Max", 
      default=3.0,
      type="float",
      )
  
  evtsel.add_option("--etaak8_1_Max", 
      dest="etaak8_1_Max", 
      default=3.0,
      type="float",
      )
  
  evtsel.add_option("--detaak8Max", 
      dest="detaak8Max", 
      default=100.,
      type="float",
      )
  
  evtsel.add_option("--t21_0_Max", 
      dest="t21_0_Max", 
      default=0.60,
      type="float",
      )
  
  evtsel.add_option("--t21_1_Max", 
      dest="t21_1_Max", 
      default=0.60,
      type="float",
      )
  
  evtsel.add_option("--msd_0_Min", 
      dest="msd_0_Min", 
      default=90.,
      type="float",
      )
  
  evtsel.add_option("--msd_0_Max", 
      dest="msd_0_Max", 
      default=140.,
      type="float",
      )
  
  evtsel.add_option("--msd_1_Min", 
      dest="msd_1_Min", 
      default=90.,
      type="float",
      )
  
  evtsel.add_option("--msd_1_Max", 
      dest="msd_1_Max", 
      default=140.,
      type="float",
      )
  
  evtsel.add_option("--deepcsvMin", 
      dest="deepcsvMin", 
      default=0.1522, # deepcsvl=0.1522 deepcsvm=0.4941
      type="float",
      )
  
  evtsel.add_option("--ptak4Min", 
      dest="ptak4Min", 
      default=50., 
      type="float",
      )
  
  evtsel.add_option("--etaak4Max", 
      dest="etaak4Max", 
      default=5.0, 
      type="float",
      )
  
  evtsel.add_option("--detavbfMin", 
      dest="detavbfMin", 
      default=5.0, 
      type="float",
      )
  
  evtsel.add_option("--mjjvbfMin", 
      dest="mjjvbfMin", 
      default=300., 
      type="float",
      )
  
  options.add_option_group(evtsel)
  
  opt, remainder = options.parse_args()
  
  print opt
  
  fout = ROOT.TFile(opt.files.rstrip().replace('txt', 'root'), 'RECREATE')
  fout.cd()
  
  h2_msd0_npv                  = ROOT.TH2D("h2_msd0_npv"                  ,";n(PV);Soft dropped mass (leding AK8) [GeV];;"  , 200, 0., 200., 20, 0., 200.)
  h2_msd1_npv                  = ROOT.TH2D("h2_msd1_npv"                  ,";n(PV);Soft dropped mass (2nd AK8) [GeV];;"     , 200, 0., 200., 20, 0., 200.)
  
  h2_bFl_sjpt_sjeta            = ROOT.TH2D("h2_bFl_sjpt_sjeta"            ,";p_{T} (subjet) [GeV]; #eta (subjet);;", 200, 0., 2000, 50, -5, 5)
  h2_bFl_sjpt_sjeta_btagged    = ROOT.TH2D("h2_bFl_sjpt_sjeta_btagged"    ,";p_{T} (subjet) [GeV]; #eta (subjet);;", 200, 0., 2000, 50, -5, 5)
                                                   
  h2_cFl_sjpt_sjeta            = ROOT.TH2D("h2_cFl_sjpt_sjeta"            ,";p_{T} (subjet) [GeV]; #eta (subjet);;", 150, 0., 3000, 50, -5, 5)
  h2_cFl_sjpt_sjeta_btagged    = ROOT.TH2D("h2_cFl_sjpt_sjeta_btagged"    ,";p_{T} (subjet) [GeV]; #eta (subjet);;", 150, 0., 3000, 50, -5, 5)
                                                   
  h2_lFl_sjpt_sjeta            = ROOT.TH2D("h2_lFl_sjpt_sjeta"            ,";p_{T} (subjet) [GeV]; #eta (subjet);;", 150, 0., 3000, 50, -5, 5)
  h2_lFl_sjpt_sjeta_btagged    = ROOT.TH2D("h2_lFl_sjpt_sjeta_btagged"    ,";p_{T} (subjet) [GeV]; #eta (subjet);;", 150, 0., 3000, 50, -5, 5)
  
  h2_ak4pt_ak4eta              = ROOT.TH2D("h2_ak4pt_ak4eta"              ,";p_{T} (AK4) [GeV]; #eta (AK4);;", 150, 0., 3000, 50, -5, 5)
  
  h_genH_pt                    = ROOT.TH1D("h_genH_pt"                    ,"p_{T} (H) [GeV]; Events;;"     ,300  ,0.    ,3000)
  h_genH_eta                   = ROOT.TH1D("h_genH_eta"                   ,"#eta (H) [GeV]; Events;;"      ,200  ,-5    ,5)

  h_nak8                       = ROOT.TH1D("h_nak8"                       ,";N(AK8) [GeV]; Events;;"       ,11   ,-0.5  ,10.5 )
  h_nak4                       = ROOT.TH1D("h_nak4"                       ,";N(AK4) [GeV]; Events;;"       ,501  ,-0.5  ,501.5)
  
  h_ak80pt                     = ROOT.TH1D("h_ak80pt"                     ,";p_{T} [GeV]; Events;;"        ,300  ,0.    ,3000 )
  h_ak81pt                     = ROOT.TH1D("h_ak81pt"                     ,";p_{T} [GeV]; Events;;"        ,300  ,0.    ,3000 )
  h_ak80eta                    = ROOT.TH1D("h_ak80eta"                    ,";#eta;;"                       ,200  ,-5    ,5    )
  h_ak81eta                    = ROOT.TH1D("h_ak81eta"                    ,";#eta;;"                       ,200  ,-5    ,5    )
  h_ak80_tau2_tau1_3b          = ROOT.TH1D("h_ak80_t2byt1_3b"                ,";#tau_{2}/#tau_{1};;"          ,100  ,0     ,1    )
  h_ak81_tau2_tau1_3b          = ROOT.TH1D("h_ak81_t2byt1_3b"                ,";#tau_{2}/#tau_{1} ;;"         ,100  ,0     ,1    )
  h_ak80_tau2_tau1_4b          = ROOT.TH1D("h_ak80_t2byt1_4b"                ,";#tau_{2}/#tau_{1};;"          ,100  ,0     ,1    )
  h_ak81_tau2_tau1_4b          = ROOT.TH1D("h_ak81_t2byt1_4b"                ,";#tau_{2}/#tau_{1} ;;"         ,100  ,0     ,1    )
  h_sdmass_ak80_3b             = ROOT.TH1D("h_sdmass_ak80_3b"                ,";softdropped_mass[GeV];;"      ,100  ,0     ,1000 )
  h_sdmass_ak81_3b             = ROOT.TH1D("h_sdmass_ak81_3b"                ,";softdropped_mass[GeV];;"      ,100  ,0     ,1000 )
  h_sdmass_ak80_4b             = ROOT.TH1D("h_sdmass_ak80_4b"                ,";softdropped_mass[GeV];;"      ,100  ,0     ,1000 )
  h_sdmass_ak81_4b             = ROOT.TH1D("h_sdmass_ak81_4b"                ,";softdropped_mass[GeV];;"      ,100  ,0     ,1000 )
  h_nvbfpairs                  = ROOT.TH1D("h_nvbfpairs"                  ,";N(VBF pairs); Events;;"       ,201  ,-0.5  ,200.5 )
  h_vbf0pt                     = ROOT.TH1D("h_vbf0pt"                     ,";p_{T} (VBF) [GeV]; Events;;"  ,100  ,0.    ,1000 )
  h_vbf1pt                     = ROOT.TH1D("h_vbf1pt"                     ,";p_{T} (VBF) [GeV]; Events;;"  ,100  ,0.    ,1000 )
  h_vbf0eta                    = ROOT.TH1D("h_vbf0eta"                    ,";#eta (VBF); Events;"          ,200  ,-5    ,5    )
  h_vbf1eta                    = ROOT.TH1D("h_vbf1eta"                    ,";#eta (VBF); Events;"          ,200  ,-5    ,5    )
  h_deltaEta                   = ROOT.TH1D("h_deltaEta"                   ,";#delta#eta of VBF jets;;"     ,20   ,0     ,10   )
  h_mjjvbf                     = ROOT.TH1D("h_mjjvbf"                     ,";M(jj) (VBF) [GeV]; Events;"   ,200  ,0.    ,2000 )
  
  h_sj0_pts                    = ROOT.TH1D("h_sj0_pts"                    ,";p_{T} of subjet_1;;"          ,300   ,0     ,3000 )
  h_sj1_pts                    = ROOT.TH1D("h_sj1_pts"                    ,";p_{T} of subjet_2;;"          ,300   ,0     ,3000 )
  h_sj0_csvv2                  = ROOT.TH1D("h_sj0_csvv2"                  ,";CSVv2 of subjet_1;;"          ,100   ,0.    ,1.   )
  h_sj1_csvv2                  = ROOT.TH1D("h_sj1_csvv2"                  ,";CSVv2 of subjet_2;;"          ,100   ,0.    ,1.   )
  h_sj0_deepcsv                = ROOT.TH1D("h_sj0_deepcsv"                ,";DeepCSV of subjet_1;;"        ,100   ,0.    ,1.   )
  h_sj1_deepcsv                = ROOT.TH1D("h_sj1_deepcsv"                ,";DeepCSV of subjet_2;;"        ,100   ,0.    ,1.   )
  
  h_mjj_3b                     = ROOT.TH1D("h_mjj_3b"                     ,";M(jj) [GeV]; Events;"         ,400  ,500.   ,4500 )
  h_mjj_4b                     = ROOT.TH1D("h_mjj_4b"                     ,";M(jj) [GeV]; Events;"         ,400  ,500.   ,4500 )
  
  h_mass_qq                    = ROOT.TH1D("h_mass_qq"                   ,";#hat{M}_{qq} [GeV]; Events;"	   ,100  ,0.   ,5000. )
  
  h_cutflow                    = ROOT.TH1D("h_cutflow"                    ,";;Events;"                     ,10   ,0.5    ,10.5 )
      
  h_cutflow.GetXaxis().SetBinLabel(1 ,"All evts") ; 
#  h_cutflow.GetXaxis().SetBinLabel(2 ,"AK8 jets") ; 
  h_cutflow.GetXaxis().SetBinLabel(2 ,"M_{qq}") ;
  h_cutflow.GetXaxis().SetBinLabel(3 ,"p_{T}+#eta") ; 
  h_cutflow.GetXaxis().SetBinLabel(4 ,"#Delta#Eta(JJ)") ; 
  h_cutflow.GetXaxis().SetBinLabel(5 ,"#tau_{21}") ; 
  h_cutflow.GetXaxis().SetBinLabel(6 ,"M(J)") ; 
  h_cutflow.GetXaxis().SetBinLabel(7 ,"VBF") ; 
  h_cutflow.GetXaxis().SetBinLabel(8 ,"> 1 Subjet b") ; 
  h_cutflow.GetXaxis().SetBinLabel(9 ,"> 2 Subjet b") ; 
  h_cutflow.GetXaxis().SetBinLabel(10,"> 3 Subjet b") ; 
  
  fnames = [line.strip() for line in open(opt.files, 'r')]
  
  try: doqcdmaps = bool(sys.argv[2])
  except: doqcdmaps = False
  
  ievt = 0
  for fname in fnames:
    if opt.maxEvts > 0 and ievt > opt.maxEvts: break
    if ievt%100 == 0: print " Processing evt %i" % ievt
  
    print 'Opening file %s' % fname
    f = ROOT.TFile.Open(fname)
    print f.ls()
  
    tree = f.Get("ana/anatree")
    entries = tree.GetEntriesFast()
  
    for event in tree:
      countqq=0
      if opt.maxEvts > 0 and ievt > opt.maxEvts: break
      if ievt%100 == 0: print " Processing evt %i" % ievt
                                   
      ievt += 1
  
      gen_momid = event.GenParticles_mom0pid
      gen_pt   = event.GenParticles_genpt
      gen_eta  = event.GenParticles_geneta
      gen_phi  = event.GenParticles_genphi
      gen_mass = event.GenParticles_genmass
      gen_id = event.GenParticles_genpid
      gen_status = event.GenParticles_genstatus
      gen_momstatus = event.GenParticles_mom0status
  
      h_cutflow.Fill(1)
      ### Selecting at least two AK8 jets:
<<<<<<< HEAD
=======
      if nak8 < 2: continue
      etas   = event.AK8JetsPuppi_eta
      ptsel  = pts[0] > opt.ptak8_0_Min and pts[1] > opt.ptak8_1_Min

      etasel = abs(etas[0]) < opt.etaak8_0_Max and abs(etas[1]) < opt.etaak8_1_Max
      detasel = abs(etas[0] - etas[1]) < opt.detaak8Max

      tau1s           = event.AK8JetsPuppi_tau1Puppi
      tau2s           = event.AK8JetsPuppi_tau2Puppi
  
      tau21sel = tau2s[0]/tau1s[0] < opt.t21_0_Max and tau2s[1]/tau1s[1] < opt.t21_1_Max
  
      sd_masses       = event.AK8JetsPuppi_softDropMassPuppi 

  
      msdsel     = opt.msd_0_Min < sd_masses[0] < opt.msd_0_Max and opt.msd_1_Min < sd_masses[1] < opt.msd_1_Max
      #### Store Higgs cand p4 for future use

      phis            = event.AK8JetsPuppi_phi
      masses          = event.AK8JetsPuppi_mass
  
      p4_higgses= []
      p4_ak80 = ROOT.TLorentzVector()
      p4_ak81 = ROOT.TLorentzVector()
      p4_ak80.SetPtEtaPhiM(pts[0], etas[0], phis[0], masses[0])
      p4_ak81.SetPtEtaPhiM(pts[1], etas[1], phis[1], masses[1])
      p4_higgses.append(p4_ak80)
      p4_higgses.append(p4_ak81)

#### adding partonic mass distribution #####
>>>>>>> a389278e5e9f85f073cfde238883c3eb61d8689c
      p4_p1 = ROOT.TLorentzVector()
      p4_p2 = ROOT.TLorentzVector()
      for i in range(0, len(gen_pt)):
        if gen_status[i] == 23:
            countqq=countqq+1
            if countqq == 1: count1 = i
            elif countqq == 2: 
		count2 = i
                countqq = 0
      		p4_p1.SetPtEtaPhiM(gen_pt[count1], gen_eta[count1], gen_phi[count1], gen_mass[count1])
                p4_p2.SetPtEtaPhiM(gen_pt[count2], gen_eta[count2], gen_phi[count2], gen_mass[count2])
                if (p4_p1+p4_p2).M() >= 1000.:
		   h_cutflow.Fill(2)
                   h_mass_qq.Fill((p4_p1+p4_p2).M())
                break; 

  fout.cd()
  
  h_cutflow_eff = h_cutflow.Clone("h_cutflow_eff")
  h_cutflow_eff.SetTitle(";;Efficiency;")
  
  h_cutflow_eff.Scale(1./h_cutflow.GetBinContent(1))
  
  for i in range(1,h_cutflow_eff.GetNbinsX()+1):
    print h_cutflow_eff.GetXaxis().GetBinLabel(i), h_cutflow_eff.GetBinContent(i) 
  
  fout.Write()
  fout.Close()

if __name__ == "__main__":
  main()
