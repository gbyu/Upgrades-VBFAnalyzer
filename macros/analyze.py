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

fin = sys.argv[1]
f = ROOT.TFile(fin, "READ")

print f.ls()

tree = f.Get("ana/anatree")
entries = tree.GetEntriesFast()

ievt = 0
for event in tree:
  print " Processing evt %i" % ievt

  pts = event.AK8JetsPuppi_pt
  print "Njets = %i" %len(pts)
  genjetpts = event.AK8JetsPuppi_genjetpt
  ijet = 0
  for pt in pts:
    genjetpt = event.AK8JetsPuppi_genjetpt[ijet]
    if genjetpt > 10.:  ### Doing this to suppress PU jets
      print "pt = %f genjetpt = %f" % (pt, genjetpt)
    ijet += 1
  ievt += 1
