#!/bin/sh
export X509_USER_PROXY=/afs/cern.ch/work/l/lata/HH4b/nonreso/DELPHES/x509up_u103989
cd /afs/cern.ch/work/l/lata/HH4b/nonreso/CMSSW_9_1_0_pre3/src
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/l/lata/HH4b/nonreso/DELPHES/delphes
root -l -b -q SubJetSoftDropped_DM.C'(200, 0, 10,"output_1.root")'
