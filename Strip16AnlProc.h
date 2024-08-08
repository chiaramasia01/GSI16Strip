#ifndef Strip16ANLPROCESSOR_H
#define Strip16ANLPROCESSOR_H

#include "TRandom.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TObjArray.h"
#include "TCutG.h"
#include "TGraph.h"

#include "Go4Event/TGo4EventElement.h"
#include "Go4Event/TGo4EventProcessor.h"
#include "Go4Analysis/TGo4Analysis.h"

#include "Strip16UnpackEvent.h"
//#include "Strip16Parameter.h"
#include "Strip16CalibParameter.h"
//#include "Strip16PrintEventParameter.h"

#include "Go4ConditionsBase/TGo4WinCond.h"
#include "Go4ConditionsBase/TGo4PolyCond.h"
#define TOF_GATE 1

#include "Strip16UnpackProc.h"
// macro max
//#define  max(a,b) ( ((a) > (b)) ? (a) : (b) )
#define tof_thres 5000
#define pulse_thres 1

class Strip16AnlEvent;
class Strip16AnlProc : public TGo4EventProcessor {

public:
	Strip16AnlProc() ;
	Strip16AnlProc(Text_t * name);
	void     Strip16EventAnalysis(Strip16AnlEvent* target);
    void     writeCSV(TH1D* hist, const char* filename); 
    void     saveCSV(TH1D* hist,int i, int j) ;
	void     MapHardware();
	virtual ~Strip16AnlProc() ;
	Bool_t   BitTest(const Int_t &tested, Int_t position);
	void     PrintBitPattern(const Int_t &pattern, ostream &output);
	Double_t PosCh2mm(const Double_t &pos); // convert position from channels to mm
	Bool_t   fbNewSubmit;   // TRUE if new analysis was just submited

  // input event (from unpack step)
	Strip16UnpackEvent  *fInput;

	// parameters
	//Strip16Parameter           *fParam;
	Strip16CalibParameter *fCal;
   // Int_t           l_T[MAX_SFP][MAX_SLAVE][N_CHA];
	// conditions
	//	TGo4WinCond		*fCondTMP[5];     // tmp conditions (ignore the 0th condition)

	// histograms

	//1D histos (calibrated)

        TH1D *h_stripcalib[4][16];
        TH1D *h_stripantiveto[4][16];
        TH1D *h_stripveto[4][16];
        TH1D *h_strippulse[4][16];
        TH1D *h_strippause[4][16];
        TH1D *h_corr_E[4][16];
        TH1D *h_strip_sum;
        TH1D *h_hit_test;
        TH1D *h_strip_veto_sum;
        TH1D *h_strip_antiveto_sum;
        TH1D *h_strip_pulse_sum;
        TH1D *h_strip_pause_sum;
        TH1D *h_strip_pause_sum_llelf;
        TH1D *h_strip_Nogated_sum;
        TH1D *h_strip_Lrgated_sum;
        TH1D *h_strip_Rfgated_sum;
        TH1D *hProfileY;
        TH1D *hProfileX;
        TH1D *hProfileX_NoGated;
        TH1D *hProfileY_NoGated;
        TH1D *hProfileX_LrGated;
        TH1D *hProfileY_LrGated;
        TH1D *hProfileX_RfGated;
        TH1D *hProfileY_RfGated;
        TH1D *hTime;
        //2D histos
        TH2D *h_EId;
        TH2D *hEvsTOF;
      //  TH2D *h_E_Tof2;
      //  TH2D *h_E_Tof3;
        TH2D *h_E_post[4][16];
        TH2D *h_E_poscalib[4][16];
        TH2D *h_posvsstrip;
        TH2D *h_posvsstrip_Nogated;
        TH2D *h_posvsstrip_Lrgated;
        TH2D *h_posvsstrip_Rfgated;
        TH2D *h_posvsstrip_pulse;
        TH2D *h_posvsstrip_pause;
            
//============= output events =================

       Bool_t newsetup; //check this out

       Float_t stripsum[4][16];
       Float_t Pos_t[4][16];
       Double_t Time[4][16];
       Double_t sample_time;
       Double_t    l_t_trig;
//     Float_t Posb[4][16];
       Double_t TOF_max;
       UInt_t macropulse;
       UInt_t tof;
       Double_t IDY;
       UInt_t IDX;
     //Float_t l_T[0][4][16];

ClassDef(Strip16AnlProc,1)
};
#endif //Strip16ANLPROCESSOR_H

//----------------------------END OF GO4 SOURCE FILE ---------------------
