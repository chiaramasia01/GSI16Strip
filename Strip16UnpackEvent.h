//---------------------------------------------------------------
//        Go4 Analysis for Shiptrap experiment
//
//        18-Feburary-2010 (Joern Adamczewski-Musch, GSI)
//                         - first version with adjustments for Go4 4.4
//
//---------------------------------------------------------------
//	 The GSI Online Offline Object Oriented (Go4) Project
//	 Experiment Data Processing at EE department, GSI
//---------------------------------------------------------------
//
//Copyright (C) 2000- Gesellschaft f. Schwerionenforschung, GSI
//                    Planckstr. 1, 64291 Darmstadt, Germany
//Contact:            http://go4.gsi.de
//----------------------------------------------------------------
//This software can be used under the license agreements as stated
//in Go4License.txt file which is part of the distribution.
//----------------------------------------------------------------

#ifndef UNPACKEVENT_H
#define UNPACKEVENT_H


#include "TGo4EventElement.h"

using namespace std;

class Strip16UnpackEvent : public TGo4EventElement {
   public:
      Strip16UnpackEvent();
      Strip16UnpackEvent(const char* name);
      virtual ~Strip16UnpackEvent();

      /** Method called by the framework to clear the event element. */
      void Clear(Option_t *t="");

      //void ClearEvent();
      UInt_t Strip_sum[4][16];
      Double_t Pos_t[4][16];
      UInt_t Pos_b[4][16];
      Double_t TOF_max[4][16];
   //   UInt_t l_T[0][4][16];
      Double_t        fTrace[3096];
      UInt_t Macropulse;
      UInt_t TOF;
      Long64_t trg_time; //real time
      UInt_t hit_time[4][16]; //step in time; multiply by 20ns and add it to real time
      UInt_t event_number;
      // Bool_t fB_pulse;
      Long64_t        l_t_trig;
      Int_t pileup;
      /* Pattern unit */
      // UInt_t  fPatternUnit;



   ClassDef(Strip16UnpackEvent,2)
};
#endif //TEVENT_H




//----------------------------END OF GO4 SOURCE FILE ---------------------
