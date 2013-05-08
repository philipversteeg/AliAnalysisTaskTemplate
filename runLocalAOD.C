void runLocalAOD(Bool_t IsMC, Int_t AODproduction, Int_t runnumber, Int_t nfiles, Int_t nevt = 100000000)

{

    // Standard Libraries.
	gSystem->Load("libCore.so");
	gSystem->Load("libTree.so");
	gSystem->Load("libGeom.so");
	gSystem->Load("libVMC.so");
	gSystem->Load("libPhysics.so");
	gSystem->Load("libSTEERBase");
	gSystem->Load("libAOD");
	gSystem->Load("libANALYSIS");
	gSystem->Load("libANALYSISalice");
    
	gROOT->ProcessLine(".include $ALICE_ROOT/include");
	
	AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisMan");
	AliAODInputHandler *aodH = new AliAODInputHandler();
	mgr->SetInputEventHandler(aodH);
 	
	// Compile libraries and Analysis Task.
	gROOT->LoadMacro("AliAnalysisTaskTemplate.cxx++g");	

	// Add Analysis Task.
    gROOT->LoadMacro("AddTaskTemplate.C");
    AliAnalysisTaskTemplate* UserTask = AddTaskTemplate(IsMC,AODproduction,runnumber,nfiles);

	mgr->SetDebugLevel(10);
	if (!mgr->InitAnalysis()) return;
	mgr->PrintStatus();
	
	TChain *analysisChain = new TChain("aodTree");
	
	if (IsMC) {
		for (Int_t ii = 1; ii < (nfiles + 1); ii++) {
			analysisChain->Add(Form("/Users/mishaveldhoen/LocalData/sim/LHC11a10a_bis/%d/AOD%03d/%04d/AliAOD.root",runnumber,AODproduction,ii));
		}
	} else {
		for (Int_t ii = 1; ii < (nfiles + 1); ii++) {
			analysisChain->Add(Form("/Users/mishaveldhoen/LocalData/data/2010/LHC10h/000%d/ESDs/pass2/AOD%03d/%04d/AliAOD.root",runnumber,AODproduction,ii));
		}
	}

	const char *analysisMode = "local";
	
	cout<<"Number of trees in the chain: "<<analysisChain->GetNtrees()<<endl;

	mgr->StartAnalysis(analysisMode, analysisChain, nevt);

}

