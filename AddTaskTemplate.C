AliAnalysisTaskTemplate* AddTaskTemplate(Bool_t IsMC, Int_t AODproduction, Int_t runnumber, Int_t nfiles, Bool_t OnGrid = kFALSE) {

	// Get the current analysis manager.
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();

    // Create instance of the Task.
    AliAnalysisTaskTemplate* mytask = new AliAnalysisTaskTemplate("Template");

	// Adding Task to the manager.
	mgr->AddTask(mytask);

	// Data containers.
	AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
	mgr->ConnectInput(mytask, 0, cinput); 

	TString* filename;
	if (OnGrid) {
		// For the grid the run is not part of the filename, since multiple runs can be included.
		if (IsMC) filename = new TString(Form("Template_AOD%03i_All.root",AODproduction));
		else filename = new TString(Form("Template_AOD%03i_All.root",AODproduction));
	} else {
		if (IsMC) filename = new TString(Form("MCSpectra_%i_AOD%03i_%i.root",runnumber,AODproduction,nfiles));
		else filename = new TString(Form("Template_%i_AOD%03i_%i.root",runnumber,AODproduction,nfiles));
	}

	AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("Template", TList::Class(), AliAnalysisManager::kOutputContainer,filename->Data());
	mgr->ConnectOutput(mytask,  1, coutput1);

	return mytask;

}
