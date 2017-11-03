Analyzer to process PhaseII samples for upgrade studies. 

Instructions to check out code and run:
Set up CMSSW area:
```
setenv SCRAM_ARCH slc6_amd64_gcc630
cmsrel CMSSW_9_3_2
cd CMSSW_9_3_2/src
cmsenv
```
Check out code:
```
git clone git@github.com:dmajumder/Upgrades-VBFAnalyzer.git Upgrades/VBFAnalyzer
```
Alternatively, use the https protocol:
```
git clone https://github.com/dmajumder/Upgrades-VBFAnalyzer.git Upgrades/VBFAnalyzer
```
Compile:
```
cd Upgrades/VBFAnalyzer
scramv1 b -k -j8
```
To run:
```
cd test
cmsRun runAnalysisRD.py
```
The output is a ROOT file containing a TTree.
