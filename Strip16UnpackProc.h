//-------------------------------------------------------------
//        Go4 Release Package v3.03-05 (build 30305)
//                      05-June-2008
//---------------------------------------------------------------
//   The GSI Online Offline Object Oriented (Go4) Project
//   Experiment Data Processing at EE department, GSI
//---------------------------------------------------------------
//
//Copyright (C) 2000- Gesellschaft f. Schwerionenforschung, GSI
//                    Planckstr. 1, 64291 Darmstadt, Germany
//Contact:            http://go4.gsi.de
//----------------------------------------------------------------
//This software can be used under the license agreements as stated
//in Go4License.txt file which is part of the distribution.
//----------------------------------------------------------------
#ifndef TUNPACKPROCESSOR_H
#define TUNPACKPROCESSOR_H
#include <iostream>
#include <fstream>
//#define WR_TIME_STAMP     1   // white rabbit time stamp is head of data

#include "TH1.h"
#include "TH2.h"
#include "TCutG.h"
#include "snprintf.h"

#include "TGo4MbsEvent.h"
#include "TGo4WinCond.h"
#include "TGo4PolyCond.h"
#include "TGo4CondArray.h"
#include "TGo4Picture.h"
#include "TGo4Fitter.h"
#include "TMath.h"

#define USE_MBS_PARAM     1   //

#include "Strip16UnpackProc.h"
#include "stdint.h"
#include "Riostream.h"

#define MAX_SFP           4
#define MAX_SLAVE        16
#define N_CHA            16

#ifdef WR_TIME_STAMP
#define SUB_SYSTEM_ID      0x100 // sub-system identifier pci express

#define TS__ID_L16         0x0f7
#define TS__ID_M16         0x1f7
#define TS__ID_H16         0x2f7
#endif // WR_TIME_STAMP

#ifdef USE_MBS_PARAM
 #define MAX_TRACE_SIZE    6000   // in samples
 #define MAX_TRAPEZ_N_AVG  1000   // in samples
#else
 #define     TRACE_SIZE    6000   // in samples
 #define     TRAPEZ_N_AVG    64   // in samples
 // nr of slaves on SFP 0    1  2  3
 //                     |    |  |  |
 #define NR_SLAVES    { 1,   0, 0, 0}
 #define ADC_TYPE     { 1, 0x1, 0, 0} // 12 bit: 0, 14 bit: 1
                                         // bit 0 fuer slave module 0
                                         // bit n fuer slave module n (max n = 31)
#endif

#define RON  "\x1B[7m"
#define RES  "\x1B[0m"

#define BASE_LINE_SUBT_START  0
#define BASE_LINE_SUBT_SIZE   150

#include "TGo4EventProcessor.h"
#include "Strip16UnpackEvent.h"

//class Strip16UnpackParam;
class TGo4Fitter;
using std::vector;
class Strip16UnpackProc : public TGo4EventProcessor {
   public:
      Strip16UnpackProc() ;
      Strip16UnpackProc(const char* name);
      virtual ~Strip16UnpackProc() ;
      void f_make_histo (Int_t);

        ofstream tracesout;

      Bool_t BuildEvent(TGo4EventElement* target); // event processing function

 private:
      TGo4MbsEvent  *fInput;  //!
      Strip16UnpackEvent* fOutput; //!

        TH1    *h_trace       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
         TH1    *h_iso_fiss_traces       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
         TH1    *h_fiss_traces       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
         TH1    *trace_isomer       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
         TH1    *h_iso_fiss_energy[MAX_SFP][MAX_SLAVE][N_CHA];  //!
         TH1    *trace_fission       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
         TH1    *h_trace2       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
        TH1    *h_trace_filt  [MAX_SFP][MAX_SLAVE][N_CHA];  //!
        TH1    *h_trace_blr   [MAX_SFP][MAX_SLAVE][N_CHA];  //!
        TH1    *h_trace_blr_Pileup   [MAX_SFP][MAX_SLAVE][N_CHA];  //!
        TH1    *h_tof       [MAX_SFP][MAX_SLAVE][N_CHA];  //!
        TH1    *h_trapez_fpga [MAX_SFP][MAX_SLAVE][N_CHA];
	TH1    *h_fpga_energy [MAX_SFP][MAX_SLAVE][N_CHA];
        TH1    *h_timestamp [MAX_SFP][MAX_SLAVE][N_CHA];
        TH1    *h_fiss_counter;
        TH1    *h_isomer_counter;
        TH1    *h_events;
        TH1    *h_iso_fiss_sum_energy;

         TH1   *h_dT;
        TH1    *h_hits;
        TH1    *h_timestamp_sum;


        UInt_t         l_i, l_l;
  uint32_t       *pl_se_dat;
  uint32_t       *pl_tmp;

  UInt_t         l_dat_len;
  UInt_t         l_dat_len_byte;

  UInt_t         l_dat;
  UInt_t         l_trig_type;
  UInt_t         l_trig_type_triva;
  UInt_t         l_sfp_id;
  UInt_t         l_feb_id;
  UInt_t         l_cha_id;
  UInt_t         l_n_hit;

  UInt_t         l_hit_cha_id;
  Long64_t       ll_time;
  Long64_t       ll_trg_time;

  UInt_t         l_ch_hitpat[MAX_SFP][MAX_SLAVE][N_CHA];
  UInt_t         l_ch_hitpat_tr[MAX_SFP][MAX_SLAVE][N_CHA];
  UInt_t         l_first_trace [MAX_SFP][MAX_SLAVE];


  UInt_t         l_cha_head;
  UInt_t         l_cha_size;
  UInt_t         l_trace_head;
  UInt_t         l_trace_size;
  UInt_t         l_trace_trail;


  UInt_t         l_spec_head;
  UInt_t         l_spec_trail;
  UInt_t         l_n_hit_in_cha;
  UInt_t         l_only_one_hit_in_cha;
  UInt_t         l_more_than_1_hit_in_cha;
  UInt_t         l_e_filt_out_of_trig_wind;
  UInt_t         l_hit_time_sign[MAX_SFP][MAX_SLAVE][N_CHA];
  Double_t         l_hit_time[MAX_SFP][MAX_SLAVE][N_CHA];

//   Double_t       hit_time[MAX_SFP][MAX_SLAVE][N_CHA];
//   Double_t       timestamp[MAX_SFP][MAX_SLAVE][N_CHA];
//   Double_t       timestamp_sum;


  UInt_t         l_hit_cha_id2;
  UInt_t         l_fpga_energy_sign;
   Int_t         l_fpga_energy;

   UInt_t l_fpga_e_found[MAX_SFP][MAX_SLAVE][N_CHA];

  UInt_t         l_dat_fir;
  UInt_t         l_dat_sec;

  UInt_t         l_bls_start; 
  UInt_t         l_bls_stop;  
  Double_t       f_bls_val;
  Double_t       f_bls_val_pileup;


  Int_t       l_fpga_filt_on_off;
  Int_t       l_fpga_filt_mode;
  Int_t       l_dat_trace;
  Int_t       l_dat_filt;
  Int_t       l_filt_sign;

  

  TGo4MbsSubEvent* psubevt;
   ClassDef(Strip16UnpackProc,1)
};
#endif //TUNPACKPROCESSOR_H

//----------------------------END OF GO4 SOURCE FILE ---------------------
