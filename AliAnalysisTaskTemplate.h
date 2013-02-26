#ifndef ALIANALYSISTASKTEMPLATE_H
#define ALIANALYSISTASKTEMPLATE_H

class AliAnalysisTaskTemplate : public AliAnalysisTaskSE {

public:
	AliAnalysisTaskTemplate();
	AliAnalysisTaskTemplate(const char* name);
	virtual ~AliAnalysisTaskTemplate();

	virtual void UserCreateOutputObjects();
	virtual void UserExec(Option_t*);
	virtual void Terminate(Option_t*);	

private:
	TList* 			fOutputList;		//!
	TH1F*			fPtDistribution;	//!

	ClassDef(AliAnalysisTaskTemplate,1);

};

#endif