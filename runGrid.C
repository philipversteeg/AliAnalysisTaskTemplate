void runGrid(const char* runmode = "full") {

	// Load Libraries.
	gSystem->Load("libCore.so");
	gSystem->Load("libTree.so");
	gSystem->Load("libGeom.so");
	gSystem->Load("libVMC.so");
	gSystem->Load("libPhysics.so");
	gSystem->Load("libSTEERBase");
	gSystem->Load("libAOD");
	gSystem->Load("libANALYSIS");
	gSystem->Load("libANALYSISalice");

	// Includes.
	gROOT->ProcessLine(".include $ALICE_ROOT/include");	

	Bool_t IsMC = 0;

	// Creating the Alien handler.
	AliAnalysisGrid *alienHandler = CreateAlienHandler(IsMC,86,runmode,"");
	if (!alienHandler) return;
	alienHandler->Print();

	// Create AnalysisManager and Input Handler.
	AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisMan");
	AliAODInputHandler *aodH = new AliAODInputHandler();
	mgr->SetInputEventHandler(aodH);
	mgr->SetGridHandler(alienHandler);
	
	// Compile libraries and Analysis Task.
	gROOT->LoadMacro("AliAnalysisTaskTemplate.cxx++g");	

	// Add Analysis Task.
    gROOT->LoadMacro("AddTaskTemplate.C");
    AliAnalysisTaskTemplate* UserTask = AddTaskTemplate(IsMC,86,0,0,kTRUE);
	// Proceed with running.
	mgr->SetDebugLevel(10);
	if (!mgr->InitAnalysis()) return;
	mgr->PrintStatus();
	
	mgr->StartAnalysis("grid");

}

// -------------------------------------------------------------------------
AliAnalysisGrid* CreateAlienHandler(Bool_t isMC, Int_t AODproduction, const char* runmode, const char* runlist) {

	// Create Alien Handler
	AliAnalysisAlien *plugin = new AliAnalysisAlien();

	// Configure Run
	plugin->SetOverwriteMode();
	plugin->SetRunMode(runmode);
	plugin->SetAPIVersion("V1.1x");
	plugin->SetROOTVersion("v5-34-05");
	plugin->SetAliROOTVersion("v5-04-58-AN");

	// Load task
	plugin->SetAnalysisSource("AliAnalysisTaskTemplate.cxx");
	plugin->SetAdditionalLibs("AliAnalysisTaskTemplate.cxx AliAnalysisTaskTemplate.h");

	// Add Data Set
	if (isMC) {
		plugin->SetGridDataDir("/alice/sim/LHC11a10a_bis");
		plugin->SetDataPattern(Form("*AOD%03d/*AliAOD.root",AODproduction));
		plugin->SetRunPrefix("");
		if (runlist=="") plugin->AddRunNumber(139510);
		else AddRunList(plugin, runlist);

		plugin->SetGridWorkingDir("work/TemplateTask_MC");
	} else {
		plugin->SetGridDataDir("/alice/data/2010/LHC10h");
		plugin->SetDataPattern(Form("*ESDs/pass2/AOD%03d/*AliAOD.root",AODproduction));
		plugin->SetRunPrefix("000");
		plugin->AddRunNumber(138275);
		//plugin->AddRunNumber(139510);
		plugin->SetGridWorkingDir("work/TemplateTask3");
	}

	// Analysis Executable      
	plugin->SetAnalysisMacro("TemplateTask.C");
    plugin->SetExecutable("TemplateTask.sh");
    plugin->SetJDLName("TemplateTask.jdl");

    // Additional Settings
    plugin->SetExecutableCommand("aliroot -q -b"); 
    plugin->SetGridOutputDir("output");
  	plugin->SetMergeViaJDL(1);
  	plugin->SetOneStageMerging(kFALSE);
  	plugin->SetMaxMergeStages(2);
    plugin->SetTTL(30000);
  	plugin->SetInputFormat("xml-single");
  	plugin->SetPrice(1);    
    plugin->SetSplitMode("se");
    //plugin->SetDefaultOutputs(); // Q: What does this do??
	if (!isMC) plugin->SetSplitMaxInputFileNumber(30);
	else plugin->SetSplitMaxInputFileNumber(90);    // MC files contain much less events I think.
	plugin->SetOutputToRunNo();

	// Change AnalysisMacro name, etc.
	// Does the grid make a merged file for all run numbers?

	return plugin;

}
