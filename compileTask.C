void compileTask() {

	// Load Basic libraries.
	gSystem->Load("libCore.so");
	gSystem->Load("libTree.so");
	gSystem->Load("libGeom.so");
	gSystem->Load("libVMC.so");
	gSystem->Load("libPhysics.so");
	gSystem->Load("libSTEERBase");
	gSystem->Load("libAOD");
	gSystem->Load("libANALYSIS.so");
	gSystem->Load("libANALYSISalice.so");

	gROOT->ProcessLine(".include $ALICE_ROOT/include");	

	// Compile Task.
	gROOT->LoadMacro("AliAnalysisTaskTemplate.cxx+g");

}
