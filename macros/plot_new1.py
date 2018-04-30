#!/usr/bin/env python

import os, sys, imp, copy, ROOT
import numpy as np
'''
The script looks for the following input files in the current dir:
  VBF_M1500_W01_PU0.root
  VBF_M3000_W01_PU0.root
  QCD_Mdijet-1000toInf_PU0.rooto

You may also have the same set of files with PU=200:
  VBF_M1500_W01_PU200.root
  VBF_M3000_W01_PU200.root
  QCD_Mdijet-1000toInf_PU200.rooto
'''

helper   = imp.load_source('fix'     , 'help.py')
tdrstyle = imp.load_source('tdrstyle', 'tdrstyle.py')
CMS_lumi = imp.load_source('CMS_lumi', 'CMS_lumi.py') 

ROOT.gROOT.SetBatch()
ROOT.gROOT.SetStyle('Plain')
ROOT.gStyle.SetOptTitle(0) 
ROOT.gStyle.SetOptStat(0000) 
ROOT.gStyle.SetOptFit(0111) 
ROOT.gStyle.SetErrorX(0.0001);

xsecs={
    'QCD'   : 99.1990,
    'TTJets': 864.5,
    'BG1500': 0.001,
    'BG2000': 0.001,
    'BG3000': 0.001,
    'BG3000_W05':0.001,
    }

nEvts={
    0: {
      'QCD':     4098542, 
      'TTJets':  4979816,
      'BG1500':  80200,
      'BG2000':	 100000 ,
      'BG3000':  91351,
      'BG3000_W05': 86640,
      },
    200: {
      'QCD':    3802314,
      'TTJets': 2874776,
      'BG1500': 27720,
      'BG2000': 81850,
      'BG3000': 87507,
      'BG3000_W05':42552,
      }
    }

lumi=3000000.

def plotStacked(hists, pu, xtitle, ytitle, xlow, xhigh, rebin, logy):

  histnames = hists.split(',')

  c0 = ROOT.TCanvas('c_compare_%s_%i_Logy%i' % (hists.replace(',','_'), pu, logy),'',800,600)
  c0.cd()
  c0.SetLogy(logy)

  leg = ROOT.TLegend(0.50,0.70,0.88,0.85,'','brNDC')
  leg.SetHeader('PU = %i' % pu)
  leg.SetBorderSize(0)
  leg.SetFillColor(0)
  leg.SetTextSize(0.030)
  leg.SetMargin(0.2)  
  leg.SetNColumns(2)
  leg.SetColumnSeparation(0.05)
  leg.SetEntrySeparation(0.05)

  hqcd = ROOT.TH1D()
  fqcd = ROOT.TFile.Open('QCD_%iPU.root' % pu)
  for hist in histnames:
    #if hqcd.GetName() == '': hqcd = fqcd.Get('h_mjj_vbfsel_scaledHTagEff')
    if hqcd.GetName() == '': hqcd = fqcd.Get(hist)
    else: hqcd.Add(fqcd.Get(hist))
  hqcd.Rebin(rebin)
  helper.fix(hqcd)
  hqcd.Scale(xsecs['QCD']*lumi/nEvts[pu]['QCD'])

  hqcd.SetLineColor(16)
  hqcd.SetFillColor(16)
  hqcd.Draw('hist')

  ymax = hqcd.GetMaximum()
  hqcd.GetXaxis().SetRangeUser(xlow,xhigh)
  hqcd.GetXaxis().SetTitle(xtitle)
  hqcd.SetAxisRange(1,1e5,"Y")
  hqcd.GetYaxis().SetTitle(ytitle)

  leg.AddEntry(hqcd, 'QCD', 'lf')

  print 'histnames = ', histnames


  msigs = [1500,2000,3000]
  hsig = ROOT.TH1D()
  for m in msigs:
    fsig = ROOT.TFile.Open('VBF_M%i_W01_PU%i.root' % (m, pu))
    hs = ROOT.TH1D()
    for h in histnames:
      if hs.GetName() == '': hs = fsig.Get(h)
      else: hs.Add(fsig.Get(h))
    hsig = copy.deepcopy(hs.Clone(hists.replace(',', '_')+'BG%i' % m))
    hsig.Rebin(rebin)
    helper.fix(hsig)
    hsig.Scale(xsecs['BG%s' % str(m)]*lumi/nEvts[pu]['BG%s' % str(m)])
    ymax = max(ymax, hsig.GetMaximum())
    hsig.SetName("h_mjj_BG%i" % m)
    #hsig.SetLineStyle(1+msigs.index(m))
    hsig.SetLineColor(600+(m/100))
    hsig.SetLineWidth(3)
    hsig.Draw('histsame')
    c0.SetSelected(hsig)
    leg.AddEntry(hsig, 'BG%i_W01' % m, 'lf')
    print "Nsig %s = %f" % (hsig.GetName(),hsig.Integral())
  nsigs = [3000]
  hsig1 = ROOT.TH1D()
  for n in nsigs:
    fsig1 = ROOT.TFile.Open('VBF_M%i_W05_PU%i.root' % (n, pu))
    hs1 = ROOT.TH1D()
    for h1 in histnames:
      if hs1.GetName() == '': hs1 = fsig1.Get(h1)
      else: hs1.Add(fsig1.Get(h1))
    hsig1 = copy.deepcopy(hs1.Clone(hists.replace(',', '_')+'BG%i' % n))
    hsig1.Rebin(rebin)
    helper.fix(hsig1)
    hsig1.Scale(xsecs['BG%s_W05' % str(n)]*lumi/nEvts[pu]['BG%s_W05' % str(n)])
    ymax = max(ymax, hsig1.GetMaximum())
    hsig1.SetName("h_mjj_BG%i_W05" % n)
    hsig1.SetLineStyle(1+nsigs.index(n))
    hsig1.SetLineColor(415)
    hsig1.SetLineWidth(3)
    hsig1.Draw('histsame')
    c0.SetSelected(hsig1)
    leg.AddEntry(hsig1, 'BG%i_W05' % n, 'lf')
    print "Nsig %s = %f" % (hsig1.GetName(),hsig1.Integral())
    c0.Update()
    
    

  leg.Draw()

  c0.RedrawAxis()
  c0.Update()

  CMS_lumi.lumi_14TeV = ""
  CMS_lumi.writeExtraText = 1
  CMS_lumi.extraText = "Simulation Preliminary"
        
  iPos = 33
  if( iPos==0 ): CMS_lumi.relPosX = 0.13
       
  CMS_lumi.CMS_lumi(c0, 1, iPos)
  c0.Update() 
 
  c0.SaveAs(c0.GetName()+'.pdf')
  c0.SaveAs(c0.GetName()+'.png')
  print "Nqcd = %f" % hqcd.Integral()

#plotStacked('h_mjj'                       ,   0, 'm_{JJ} [GeV]', 'Events', 500., 5000., 5, 1)
#plotStacked('h_nak8'                      ,   0, 'AK8 jet multiplicity', 'Events', 0., 20, 1, 1)
#plotStacked('h_nak4'                      ,   0, 'AK4 jet multiplicity', 'Events', 0., 20, 1, 1)
#plotStacked('h_ak80pt,h_ak81pt'           ,   0, 'p_{T} (leading two A8 jets) [GeV]', 'Events', 0., 3000., 5, 1)
#plotStacked('h_ak80eta,h_ak81eta'         ,   0, '#eta (leading two A8 jets)', 'Events', -3., 3., 5, 1)
#plotStacked('h_ak80_t2byt1,h_ak81_t2byt1' ,   0, '#tau_{21} (leading two A8 jets)', 'Events', 0., 1., 5, 1)
#plotStacked('h_sj0_deepcsv,h_sj1_deepcsv' ,   0, 'DeepCSV (leading two A8 jets)', 'Events', 0., 1., 5, 1)
#plotStacked('h_vbf0pt,h_vbf0pt'           ,   0, 'p_{T} (VBF jets) [GeV]', 'Events', 0., 1000., 5, 1)
#plotStacked('h_mjjvbf'                    ,   0, 'm(jj) (VBF jets) [GeV]', 'Events', 0., 2000., 5, 1)
#plotStacked('h_deltaEta'                  ,   0, '#Delta#eta(jj) (VBF jets) [GeV]', 'Events', 0., 10., 1, 1)
plotStacked('h_sdmass_ak80,h_sdmass_ak81'  ,   0, 'SD_mass AK8Jets [GeV]', 'Events', 0., 200.,1, 1)
plotStacked('h_sdmass_ak80,h_sdmass_ak81'  ,   200, 'SD_mass AK8Jets [GeV]', 'Events', 0., 200.,1, 1)
#plotStacked('h_mjj'                       , 200, 'm_{JJ} [GeV]', 'Events', 500., 5000., 5, 1)
#plotStacked('h_nak8'                      , 200, 'AK8 jet multiplicity', 'Events', 0., 20, 1, 1)
#plotStacked('h_nak4'                      , 200, 'AK4 jet multiplicity', 'Events', 0., 200, 1, 1)
#plotStacked('h_ak80pt,h_ak81pt'           , 200, 'p_{T} (leading two A8 jets) [GeV]', 'Events', 0., 3000., 5, 1)
#plotStacked('h_ak80eta,h_ak81eta'         , 200, '#eta (leading two A8 jets)', 'Events', -3., 3., 5, 1)
#plotStacked('h_ak80_t2byt1,h_ak81_t2byt1' , 200, '#tau_{21} (leading two A8 jets)', 'Events', 0., 1., 5, 1)
#plotStacked('h_sj0_deepcsv,h_sj1_deepcsv' , 200, 'DeepCSV (leading two A8 jets)', 'Events', 0., 1., 5, 1)
#plotStacked('h_vbf0pt,h_vbf0pt'           , 200, 'p_{T} (VBF jets) [GeV]', 'Events', 0., 1000., 5, 1)
#plotStacked('h_mjjvbf'                    , 200, 'm(jj) (VBF jets) [GeV]', 'Events', 0., 2000., 5, 1)
#plotStacked('h_deltaEta'                  , 200, '#Delta#eta(jj) (VBF jets) [GeV]', 'Events', 0.,10., 1, 1)

def htagEff(fname):
  print "testing...."
  f = ROOT.TFile.Open(fname)
  hd = f.Get('h2_ak8pt_ak8eta')
  hn = f.Get('h2_ak8pt_ak8eta_htagged')

  ptbins = [300., 500., 1000., 3000.]
  etabins = [0., 0.8, 2.4]
  hden = ROOT.TH2D('hden', '', len(ptbins)-1, np.asarray(ptbins, 'd'), len(etabins)-1, np.asarray(etabins, 'd'))
  hnum = ROOT.TH2D('hnum', '', len(ptbins)-1, np.asarray(ptbins, 'd'), len(etabins)-1, np.asarray(etabins, 'd'))

  nbinsx = hd.GetNbinsX()
  nbinsy = hd.GetNbinsY()

  for i in range(0, nbinsx+1):
    for j in range(0, nbinsy+1):
      pt = hd.GetXaxis().GetBinCenter(i)
      eta = abs(hd.GetYaxis().GetBinCenter(j))
      d = hd.GetBinContent(i, j)
      n = hn.GetBinContent(i, j)
      hden.Fill(pt, eta, d)
      hnum.Fill(pt, eta, n)

  heff = hnum.Clone('heff')
  heff.Divide(hden)

  for i in range(1, heff.GetNbinsX()+1):
    for j in range(1, heff.GetNbinsY()+1):
      print "pt %f eta %f eff %f" % (heff.GetXaxis().GetBinCenter(i), heff.GetYaxis().GetBinCenter(j), heff.GetBinContent(i, j))

  ceff = ROOT.TCanvas('ceff_htag', '', 800, 600)
  ceff.cd()
  heff.Draw('colz')
  ceff.SaveAs(ceff.GetName()+'.pdf')

  fout = ROOT.TFile('heff_200PU.root', 'recreate')
  fout.cd()
  hnum.Write()
  hden.Write()
  heff.Write()
  fout.Close()

  return heff

#htagEff('/afs/cern.ch/user/l/lata/public/plots/eta_ak8_3.0/QCD_200PU.root')
