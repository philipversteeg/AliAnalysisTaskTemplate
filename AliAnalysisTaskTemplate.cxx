#include <iostream>
#include "TH1F.h"
#include "TChain.h"
#include "TList.h"

// Analysis Includes
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskSE.h"
#include "AliInputEventHandler.h"

// AOD includes.
#include "AliAODEvent.h"
#include "AliAODTrack.h"
#include "AliAODHandler.h"
#include "AliAODVertex.h"
#include "AliAODInputHandler.h"
#include "AliAODMCParticle.h"
#include "AliAODMCHeader.h"

#include "AliAnalysisTaskTemplate.h"

using namespace std;

ClassImp(AliAnalysisTaskTemplate);

// -------------------------------------------------------------------------
AliAnalysisTaskTemplate::AliAnalysisTaskTemplate():
	AliAnalysisTaskSE(),
	fOutputList(0x0),
	fPtDistribution(0x0)

{

	// Default constructor.

}

// -------------------------------------------------------------------------
AliAnalysisTaskTemplate::AliAnalysisTaskTemplate(const char* name):
	AliAnalysisTaskSE(name),
	fOutputList(0x0),
	fPtDistribution(0x0)

{

	// Named Constructor. 

	DefineInput(0,TChain::Class());
	DefineOutput(1, TList::Class());

}

// -------------------------------------------------------------------------
AliAnalysisTaskTemplate::~AliAnalysisTaskTemplate() {}

// -------------------------------------------------------------------------
void AliAnalysisTaskTemplate::UserCreateOutputObjects() {

	// Getting a pointer to the analysis manager and input handler.
	//AliAnalysisManager* manager = AliAnalysisManager::GetAnalysisManager();
	//AliInputEventHandler* inputHandler = dynamic_cast<AliInputEventHandler*> (manager->GetInputEventHandler());

	// Create the output list.
	fOutputList = new TList();
	fOutputList->SetOwner(kTRUE);

	// Create Spectrum.
	fPtDistribution = new TH1F("fPtDistribution","P_{T} Distribution;p_{T};N_{ch}",100,0.,10.);
	fOutputList->Add(fPtDistribution);

	PostData(1,fOutputList);

}

// -------------------------------------------------------------------------
void AliAnalysisTaskTemplate::UserExec(Option_t*) {

	AliAODEvent* currentEvent = dynamic_cast<AliAODEvent*>(InputEvent());

	// Input the event handler.
	AliInputEventHandler* InputHandler = (AliInputEventHandler*)((AliAnalysisManager::GetAnalysisManager())->GetInputEventHandler());
	if (!InputHandler) return;

	// Select min. bias events.
	UInt_t trigger = InputHandler->IsEventSelected();
	if (!(trigger & AliVEvent::kMB)) {return;}

	// Fill Pt distribution.
	for (Int_t iTrack = 0; iTrack < currentEvent->GetNumberOfTracks(); iTrack++) {

		AliAODTrack* currentTrack = (AliAODTrack*)currentEvent->GetTrack(iTrack);
		fPtDistribution->Fill(currentTrack->Pt());

	}

	PostData(1,fOutputList);

}
// -------------------------------------------------------------------------
void AliAnalysisTaskTemplate::Terminate(Option_t*) {}
// -------------------------------------------------------------------------
