/* ===================================================================
  Strip16 analysis program
  Peter Cagarda, 2003

  modified
  Stanislav Antalic, 2004

  Licence policy according to GO4 (go4.gsi.de)
=================================================================== */

#ifndef Strip16ANALYSIS_H
#define Strip16ANALYSIS_H

#include "TH1.h"
#include "TFile.h"

#include "Go4Analysis/TGo4Analysis.h"
#include "Go4DynamicList/TGo4HistoFillAction.h"

#include "Strip16UnpackFact.h"
#include "Strip16AnlFact.h"
//#include "Strip16CorrelFact.h"

class Strip16Analysis : public TGo4Analysis
   {
   public:
     Strip16Analysis();
     Strip16Analysis(Text_t* input, Int_t type, Int_t port);
     virtual ~Strip16Analysis() ;
     virtual Int_t UserPreLoop();
     virtual Int_t UserEventFunc();
     virtual Int_t UserPostLoop();
   private:
     TGo4MbsEvent     *fMbsEvent;   // source input event from MBS
     Strip16UnpackEvent *fRawEvent;   // output from the first step (raw event)
     Strip16AnlEvent    *fCalEvent;   // output from the second step (calibrated event) - only parameters needed for correlation search
    // Strip16CorrelEvent *fCorEvent;   // output from the 3rd step (correlation search)

     Int_t     fEvents;        // no. of events
     Int_t     fLastEvent;

     Int_t     fTime;    // running time of experiment (file) in seconds


ClassDef(Strip16Analysis,1)
};
#endif //Strip16ANALYSIS_H

