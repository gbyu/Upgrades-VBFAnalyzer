import FWCore.ParameterSet.Config as cms

process = cms.Process("VBFAnalyzer")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())
process.source.fileNames.append('root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRSpring17MiniAOD/RSGluonToTT_M-5000_TuneCUETP8M1_14TeV-pythia8/MINIAODSIM/PU200_91X_upgrade2023_realistic_v3-v3/70000/1A483645-2E74-E711-A47F-0025905B85CC.root')
#root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRFall17MiniAOD/VBF_RS_bulk_M1500_W01pc_14TeV-madgraph/MINIAODSIM/PU200_93X_upgrade2023_realistic_v2-v1/30000/489EA6A6-90BB-E711-9EB5-A4BF0112BD00.root')
#root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRFall17MiniAOD/VBF_RS_bulk_M3000_W01pc_14TeV-madgraph/MINIAODSIM/noPU_93X_upgrade2023_realistic_v2-v1/00000/06059A0B-74BA-E711-90DA-1CB72C1B2D80.root')
#root://cms-xrd-global.cern.ch///store/mc/PhaseIITDRFall17MiniAOD/VBF_RS_bulk_M1500_W01pc_14TeV-madgraph/MINIAODSIM/PU200_93X_upgrade2023_realistic_v2-v1/30000/489EA6A6-90BB-E711-9EB5-A4BF0112BD00.root')
#root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRSpring17MiniAOD/RSGluonToTT_M-5000_TuneCUETP8M1_14TeV-pythia8/MINIAODSIM/PU200_91X_upgrade2023_realistic_v3-v3/70000/1A483645-2E74-E711-A47F-0025905B85CC.root')

process.tree = cms.EDAnalyzer("VBFAnalyzer",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
    elecs = cms.InputTag("slimmedElectrons"),
    jets = cms.InputTag("slimmedJets"),
    jets_ak8 = cms.InputTag("slimmedJetsAK8"),
    mets = cms.InputTag("slimmedMETs"),
    mcLabel = cms.InputTag("prunedGenParticles"),
    subjets_ak8=cms.InputTag("slimmedJets"),
    bDiscriminators = cms.vstring(      # list of b-tag discriminators to access
      #  'pfTrackCountingHighEffBJetTags',
      #  'pfTtrackCountingHighPurBJetTags',
      #  'pfJetProbabilityBJetTags',
      #  'pfJetBProbabilityBJetTags',
      #  'pfSimpleSecondaryVertexHighEffBJetTags',
      #  'pfSimpleSecondaryVertexHighPurBJetTags',
      #  'pfCombinedSecondaryVertexV2BJetTags',
        'pfCombinedInclusiveSecondaryVertexV2BJetTags',
      #  'pfCombinedMVAV2BJetTags'
    )


)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_tree.root"
))

process.p = cms.Path(process.tree)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

