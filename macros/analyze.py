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

fout = ROOT.TFile('fout.root', 'RECREATE')
fout.cd()

h_ak80pt = ROOT.TH1D("h_ak80pt", ";p_{T} [GeV]; Events;;", 150, 0., 3000)
h_ak81pt = ROOT.TH1D("h_ak81pt", ";p_{T} [GeV]; Events;;", 150, 0., 3000)

fin = sys.argv[1]
f = ROOT.TFile(fin, "READ")

try: 
  maxEvts = sys.argv[2]
except: maxEvts = -1

print f.ls()

tree = f.Get("ana/anatree")
entries = tree.GetEntriesFast()

ievt = 0
for event in tree:

  if maxEvts > 0 and ievt > maxEvts: break
  print " Processing evt %i" % ievt

  pts = event.AK8JetsPuppi_pt

  h_ak80pt.Fill(pts[len(pts)-2])
  h_ak81pt.Fill(pts[len(pts)-1])

  genjetpts = event.AK8JetsPuppi_genjetpt
  #ijet = 0
  #for pt in pts:
  #  genjetpt = event.AK8JetsPuppi_genjetpt[ijet]
  #  if genjetpt > 10.:  ### Doing this to suppress PU jets
  #    print "pt = %f genjetpt = %f" % (pt, genjetpt)
  #  ijet += 1

  ievt += 1

fout.Write()
fout.Close()
