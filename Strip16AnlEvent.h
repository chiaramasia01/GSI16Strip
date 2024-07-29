#ifndef Strip16ANLEVENT_H
#define Strip16ANLEVENT_H

//#include "Strip16Globals.h"

#include "Go4Event/TGo4EventElement.h"
#include "Strip16AnlProc.h"
#include "Go4EventServer/TGo4TreeSource.h"
#include "Go4EventServer/TGo4FileSource.h"


class Strip16AnlEvent : public TGo4EventElement
   {
   public:
       Strip16AnlEvent() ;
       Strip16AnlEvent(const Text_t * name) ;
      ~Strip16AnlEvent() ;
      // operator '=' ; only for the use in correlation processor,
      // do not use in AnlProcessor unless you know what you are doing.
      Strip16AnlEvent operator = (const Strip16AnlEvent &from);

      virtual Int_t Init();
      virtual Int_t Fill();
      virtual void  Clear(Option_t *t="");
      virtual void  ClearEvent();
      // output event from second (analysis) step - contains variables
      // needed for correlations

    
      Double_t fE_kev;        // low energy 
   //   Long64_t fTime;  //analog time
      Double_t fTAC; //TAC
     
      Double_t    fIDY;
      Int_t    fIDX;
      
      Double_t fTimeTrig;
      Double_t fTimeStrip;
      Int_t    fev_num;
      Int_t fB_pulse;
      Int_t fTOF_bit; //TOF veto

       Double_t fTraceTrig[3096];
       Double_t fSample[3096];
      
      //Int_t fTrig;
   private:
      // this object is streamed. Therefore pointers must be excluded!
      // Otherwise these objects are streamed as well
      Strip16AnlProc     * fxStrip16CP;  //! Don't put this to file
      TGo4FileSource   * fxStrip16FS;  //! Don't put this to file



ClassDef(Strip16AnlEvent,2)
};
#endif //Strip16ANLEVENT_H
