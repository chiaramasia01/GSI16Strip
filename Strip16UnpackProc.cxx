 // N.Kurz, EE, GSI, 15-Jan-2010

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
//A.K.Mistry Edit
//25.06.15.
//16 Strip SHIP detector online sort code
//----------------------------------------------------------------
#include "Strip16UnpackProc.h"
#include "Strip16UnpackEvent.h"

#ifdef USE_MBS_PARAM
 static UInt_t    l_tr    [MAX_TRACE_SIZE];
 static Double_t  f_tr_blr[MAX_TRACE_SIZE];
 static Double_t  f_tr_blr_pileup[MAX_TRACE_SIZE];
 static UInt_t    l_sfp_slaves[MAX_SFP] = {MAX_SLAVE, MAX_SLAVE, MAX_SLAVE, MAX_SLAVE};
 static UInt_t    l_slaves=0;
 static UInt_t    l_trace=0;
 static UInt_t    l_e_filt=0;
#else
 static UInt_t    l_tr    [TRACE_SIZE];
 static Double_t  f_tr_blr[TRACE_SIZE];
 static Double_t  f_tr_blr_pileup[TRACE_SIZE];
 static UInt_t    l_sfp_slaves  [MAX_SFP] = NR_SLAVES;
 static UInt_t    l_sfp_adc_type[MAX_SFP] = ADC_TYPE;
#endif //

static UInt_t    l_adc_type;

static UInt_t    l_evt_ct=0;
static UInt_t    l_evt_ct_phys=0;
static UInt_t    l_good_energy_ct=0;
static UInt_t    l_1_hit_ct=0;
static UInt_t    l_more_1_hit_ct=0;
static UInt_t    l_more_1_hit_first_energy_ok_ct=0;
static UInt_t    l_eeeeee_ct=0;
static UInt_t    l_eeeee1_ct=0;
static UInt_t    l_eeeee2_ct=0;
static UInt_t    l_eeeee3_ct=0;
static UInt_t    l_1_hit_and_eeeeee_ct=0;
static UInt_t    l_more_1_hit_and_eeeeee_ct=0;

static UInt_t    l_e_filt_out_of_trig_wind_ct=0;

static UInt_t    l_first=0;

//***********************************************************
Strip16UnpackProc::Strip16UnpackProc() : TGo4EventProcessor("Proc")
{
  cout << "**** Strip16UnpackProc: Create instance " << endl;
}
//***********************************************************
Strip16UnpackProc::~Strip16UnpackProc()
{
     l_first=0;
    cout << "**** Setting l_first = 0 " << endl;
  cout << "**** Strip16UnpackProc: Delete instance " << endl;
}
//***********************************************************
// this one is used in standard factory
Strip16UnpackProc::Strip16UnpackProc(const char* name) : TGo4EventProcessor(name)
{
  cout << "**** Strip16UnpackProc: Create instance " << name << endl;

  //printf ("Histograms created \n");  fflush (stdout);
}
//-----------------------------------------------------------
// event function
Bool_t Strip16UnpackProc::BuildEvent(TGo4EventElement* target)
{  // called by framework. We dont fill any output event here at all

  //output event for the next step

fOutput=dynamic_cast<Strip16UnpackEvent*>(target);
if(fOutput==0){
cout << "wrong event type in buildEvent!!!!!!!!!!!!!";
return false;
}

  fOutput->Macropulse=0;
  fOutput->TOF=0;
//   
    
  
        double sumfpga1 = 0;
        double sumfpga2 = 0;
        double Sumfpga = 0;
        double  xlt = 0; //position top
        double  xlb = 0; //position bottom

     UInt_t         l_dat_fir;
     UInt_t         l_dat_sec;

    l_bls_start = BASE_LINE_SUBT_START;
    l_bls_stop  = BASE_LINE_SUBT_START + BASE_LINE_SUBT_SIZE;
 // TGo4MbsSubEvent* psubevt;

     l_hit_cha_id = 0;
    ll_trg_time = 0.;
    f_bls_val=0.;
    f_bls_val_pileup=0.;

  fInput = (TGo4MbsEvent* ) GetInputEvent();
  if(fInput == 0)
  {
    cout << "UnpackProc: no input event !"<< endl;
    return kFALSE;
  }

  l_trig_type_triva = fInput->GetTrigger();
  if (l_trig_type_triva == 1)
  {
     l_evt_ct_phys++;
  }

  l_evt_ct++;
  fInput->ResetIterator();

  psubevt = fInput->NextSubEvent(); // only one subevent
   fOutput->event_number=fInput->GetCount();
//    if (fOutput->event_number==260000){
//         cout << fOutput->event_number << endl;
//    }
  pl_se_dat = (uint32_t *)psubevt->GetDataField();
  l_dat_len = psubevt->GetDlen();
  l_dat_len_byte = (l_dat_len - 2) * 2;

  pl_tmp = pl_se_dat;

  if (pl_se_dat == (UInt_t*)0)
  {
    printf ("ERROR>> HERE ");
//     printf ("pl_se_dat: 0x%x, ", *pl_se_dat);
//     printf ("l_dat_len: 0x%x, ", (UInt_t)l_dat_len);
//     printf ("l_trig_type_triva: 0x%x \n", (UInt_t)l_trig_type_triva); fflush (stdout);
    
    goto bad_event;
  }

  if ( (*pl_tmp) == 0xbad00bad)
  {
    printf ("ERROR>> found bad event (0xbad00bad) \n");
    goto bad_event;
  
  }

  #ifdef WR_TIME_STAMP
  // 4 first 32 bits must be TITRIS time stamp
  l_dat = *pl_tmp++;
  if (l_dat != SUB_SYSTEM_ID)
  {
    printf ("ERROR>> 1. data word is not sub-system id: %d \n");
    printf ("should be: 0x%x, but is: 0x%x\n", SUB_SYSTEM_ID, l_dat);
  }

  if (l_dat != 0x100)
  {
    goto bad_event;
  }

  l_dat = (*pl_tmp++) >> 16;
  printf("TS_ID_low %dx \n ", l_dat);
  if (l_dat != TS__ID_L16)
  {
    printf ("ERROR>> 2. data word does not contain low 16bit identifier: %d \n");
    printf ("should be: 0x%x, but is: 0x%x\n", TS__ID_L16, l_dat);
  }
  l_dat = (*pl_tmp++) >> 16;
  printf("TS_ID_middle %dx \n ", l_dat);
  if (l_dat != TS__ID_M16)
  {
    printf ("ERROR>> 3. data word does not contain low 16bit identifier: %d \n");
    printf ("should be: 0x%x, but is: 0x%x\n", TS__ID_M16, l_dat);
  }
  l_dat = (*pl_tmp++) >> 16;
    if (l_dat != TS__ID_H16)
  {
    printf ("ERROR>> 4. data word does not contain low 16bit identifier: %d \n");
    printf ("should be: 0x%x, but is: 0x%x\n", TS__ID_H16, l_dat);
  }
  #endif // WR_TIME_STAMP

  // extract analysis parameters from MBS data
  // ATTENTION:  these data is only present if WRITE_ANALYSIS_PARAM
  //             is enabled in corresponding f_user.c
  // WRITE_ANALYSIS_PARAM (in mbs) and USE_MBS_PARAM (in go4) must be used always together

  #ifdef USE_MBS_PARAM
  l_slaves = *pl_tmp++;
  l_trace  = *pl_tmp++;
  l_e_filt = *pl_tmp++;
  pl_tmp  += 4;
  #endif

  if (l_first == 0)
  {
    l_first = 1;
    #ifdef USE_MBS_PARAM
    printf ("debug: 0x%x, 0x%x, 0x%x \n", l_slaves, l_trace, l_e_filt);
    fflush (stdout);
    #endif
     f_make_histo (0);
  }

//   for (l_i=0; l_i<MAX_SFP; l_i++)
//   {
//     if (l_sfp_slaves[l_i] != 0)
//     {
//       for (l_j=0; l_j<l_sfp_slaves[l_i]; l_j++)
//       {
//         for (l_k=0; l_k<N_CHA; l_k++)
//         {
//        h_trace       [l_i][l_j][l_k]->Reset ("");
//    //h_trace_blr   [l_i][l_j][l_k]->Reset ("");
//  }
//       }
//     }
//   }

  while ( (pl_tmp - pl_se_dat) < (l_dat_len_byte/4) )
  {

    //sleep (1);
    //printf (" begin while loop \n");  fflush (stdout);
    l_dat = *pl_tmp++;   // must be padding word or channel header
    //printf ("l_dat 0x%x \n", l_dat);
    if ( (l_dat & 0xfff00000) == 0xadd00000 ) // begin of padding 4 byte words
    {
      //printf ("padding found \n");
      l_dat = (l_dat & 0xff00) >> 8;
      pl_tmp += l_dat - 1;  // increment by pointer by nr. of padding  4byte words
    }
    else if ( (l_dat & 0xff) == 0x34) //channel header
    {
      l_cha_head = l_dat;
      //printf ("l_cha_head: 0x%x \n", l_cha_head);

      l_trig_type = (l_cha_head & 0xf00)      >>  8;
      l_sfp_id    = (l_cha_head & 0xf000)     >> 12;
      l_feb_id    = (l_cha_head & 0xff0000)   >> 16;
      l_cha_id    = (l_cha_head & 0xff000000) >> 24;

      if ((l_sfp_id > (MAX_SFP-1)) || (l_sfp_id < 0))
      {
        printf ("ERROR>> l_spf_id: %d \n", l_sfp_id);  fflush (stdout);
        goto bad_event;
      }
      if ((l_feb_id > (MAX_SLAVE-1)) || (l_feb_id < 0))
      {
        printf ("ERROR>> l_feb_id: %d \n", l_feb_id); fflush (stdout);
        goto bad_event;
      }
      if ((l_cha_id > (N_CHA-1)) || (l_cha_id < 0))
      {
        if (l_cha_id != 0xff)
        {
          printf ("ERROR>> l_cha_id: %d \n", l_cha_id); fflush (stdout);
          goto bad_event;
        }
      }

      if ( ((l_cha_head & 0xff) >> 0) != 0x34 )
      {
        printf ("ERROR>> channel header type is not 0x34 \n");
        goto bad_event;
      }

      if ( (l_cha_head & 0xff000000) == 0xff000000) // special channel 0xff for E,t from fpga
      {
        //printf ("                            summary channel \n");
        // special channel data size
        l_cha_size = *pl_tmp++;
        //printf ("l_cha_head: 0x%x \n", l_cha_head); sleep (1);
        //printf ("l_cha_size: 0x%x \n", l_cha_size);

        l_spec_head = *pl_tmp++;
        if ( (l_spec_head & 0xff000000) != 0xaf000000)
        {
          printf ("ERROR>> E,t summary: wrong header is 0x%x, must be: 0x%x\n",
                                                 (l_spec_head & 0xff000000)>>24, 0xaf);
          goto bad_event;
          //sleep (1);
        }


                                                //Baatar time
                                                ll_trg_time  = (Long64_t)*pl_tmp++;
                                                ll_time      = (Long64_t)*pl_tmp++;
                                                ll_time += ((ll_trg_time & 0xffffff) << 32);


    //printf("TS_ID_low %llx \n ", ll_trg_time);
        l_n_hit = (l_cha_size - 16) >> 3;
        //printf ("#hits: %d \n", l_n_hit);
        if (l_trig_type_triva == 1) // physics event
        {
      // h_hitpat[l_sfp_id][l_feb_id]->Fill (-1, 1);

          for (l_i=0; l_i<l_n_hit; l_i++)
          {
            l_dat = *pl_tmp++;      // hit time from fpga (+ other info)
            l_hit_cha_id              = (l_dat & 0xf0000000) >> 28;
            l_n_hit_in_cha            = (l_dat & 0xf000000)  >> 24;

            l_more_than_1_hit_in_cha  = (l_dat & 0x400000)   >> 22;
            l_e_filt_out_of_trig_wind = (l_dat & 0x200000)   >> 21;
            l_only_one_hit_in_cha     = (l_dat & 0x100000)   >> 20;

            l_ch_hitpat[l_sfp_id][l_feb_id][l_hit_cha_id] = l_n_hit_in_cha;

            if (l_only_one_hit_in_cha == 1)
            {
              l_1_hit_ct++;
            }

            if (l_more_than_1_hit_in_cha == 1)
            {
             
              if(l_feb_id!=2){
                   //fOutput->pileup++;
                 //  cout<<"fOutput->pileup " <<fOutput->pileup << endl;
                   l_more_1_hit_ct++;
           //   printf ("%d More than 1 hit found for SFP: %d FEBEX: %d CHA: %d:: %d \n",
            //  l_more_1_hit_ct, l_sfp_id, l_feb_id, l_hit_cha_id, l_n_hit_in_cha);
            //  fflush (stdout);
              }
            }
            if (l_e_filt_out_of_trig_wind == 1)
            {
              l_e_filt_out_of_trig_wind_ct++;
              printf ("%d energy filter out of trigger window <<<<<<<<<<<<<<<<<<<<<<\n", l_e_filt_out_of_trig_wind_ct);
            }

            if ((l_more_than_1_hit_in_cha == 1) && (l_only_one_hit_in_cha == 1))
            {
              printf ("ERROR>> haeh? \n"); fflush (stdout);
            }
                        //cout << "1" << endl;
            if (l_only_one_hit_in_cha == 1)
            {
              l_hit_time_sign[l_sfp_id][l_feb_id][l_cha_id] = (l_dat & 0x8000) >> 15;
              l_hit_time[l_sfp_id][l_feb_id][l_cha_id] = l_dat & 0x7ff;     // positive := AFTER  trigger, relative to trigger time
              if (l_hit_time_sign[l_sfp_id][l_feb_id][l_cha_id] == 1)       // negative sign
              {
                l_hit_time[l_sfp_id][l_feb_id][l_cha_id] = l_hit_time[l_sfp_id][l_feb_id][l_cha_id] * (-1); // negative := BEFORE trigger, relative to trigger time
              }
              //printf ("cha: %d, hit fpga time:  %d \n", l_hit_cha_id,  l_hit_time);
          //  h_trgti_hitti[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill (l_hit_time);

              //h_hitpat[l_sfp_id][l_feb_id]->Fill (l_hit_cha_id, 1);
            }
        // h_hitpat[l_sfp_id][l_feb_id]->Fill (l_hit_cha_id, l_n_hit_in_cha);

            l_dat = *pl_tmp++;      // energy from fpga (+ other info)
            l_hit_cha_id2  = (l_dat & 0xf0000000) >> 28;

            if ( (l_dat & 0xfffff0) != 0xeeeee0)
            {
              if (l_hit_cha_id != l_hit_cha_id2)
              {
                printf ("ERROR>> hit channel ids differ in energy and time data word\n");
                goto bad_event;
              }
              if ((l_hit_cha_id > (N_CHA-1)) || (l_hit_cha_id < 0))
              {
                printf ("ERROR>> hit channel id: %d \n", l_hit_cha_id); fflush (stdout);
                goto bad_event;
              }

              if (l_more_than_1_hit_in_cha == 1)
              {
                l_more_1_hit_first_energy_ok_ct++;
              }

              if ( (l_only_one_hit_in_cha == 1) || (l_more_than_1_hit_in_cha == 1) )
              {
                l_good_energy_ct++;
                l_fpga_energy_sign = (l_dat & 0x800000) >> 23;
                //l_fpga_energy      =  l_dat & 0x7ffff;      // positiv
                l_fpga_energy      =  l_dat & 0x3fffff;     // positiv
                if (l_fpga_energy_sign == 1)                // negative sign
                {
                  l_fpga_energy = l_fpga_energy * (-1);     // negative
                }
                               // for (UInt_t i=0; i<16; i++){
                                if(l_feb_id == 0 ){
                                   // sumfpga1= -l_fpga_energy;
                                    sumfpga1= -l_fpga_energy;
									h_fpga_energy[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill(sumfpga1/100);
                                    //cout<<"Sumfpga1" << sumfpga1 << endl;
                                //     h_fpga_energy[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill (Sumfpga/500);


                                }
                                if(sumfpga1>0){ if(l_feb_id == 1){
                                    sumfpga2= -l_fpga_energy;
                                    // cout<<"Sumfpga2" << sumfpga2 << endl;
                                    h_fpga_energy[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill (sumfpga2/100);
                                    }

                                }
                                else {sumfpga1=-1; sumfpga2=-1;}

                               // }
                                Sumfpga= sumfpga1+sumfpga2;
                                /// top and bottom position
                                xlt = 1225/35*sumfpga1/Sumfpga;
                                xlb = 1225/35*sumfpga2/Sumfpga;
//                       if (l_feb_id == 1){
// 												// h_fpga_energy[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill (Sumfpga/100);
// 
//                       }

//                         fOutput->TOF[l_feb_id][l_hit_cha_id] = Sumfpga/1000;
//                       //  h_tof[l_sfp_id][l_feb_id][l_cha_id]->Fill(h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum ());
//                         cout << "2" << endl;
//                       }
                        fOutput->Pos_t[l_feb_id][l_hit_cha_id]=xlt;
                        fOutput->Pos_b[l_feb_id][l_hit_cha_id]=xlb;
                        fOutput->Strip_sum[l_feb_id][l_hit_cha_id]=Sumfpga/100;
                        //cout<< "fOutput" << fOutput->Strip_sum[l_feb_id][l_hit_cha_id] << endl;
                      //  cout << "back y " << fOutput->Back_Y[l_feb_id][l_hit_cha_id] << endl;
                        //h_fpga_e[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill (-l_fpga_energy/250);
//TOF and pulse/pause signals - No MWD

                if (l_fpga_energy < -1000000)
                {
                  //printf ("l_dat: 0x%x, fpga energy: 0x%x \n", l_dat, l_fpga_energy);
                }

                l_fpga_e_found [l_sfp_id][l_feb_id][l_hit_cha_id] = 1;
                                // l_fpga_e[l_sfp_id][l_feb_id][l_hit_cha_id] = l_fpga_energy;

              }
            }
            else
            {
              l_eeeeee_ct++;
              if (l_dat == 0xeeeee1) {l_eeeee1_ct++;}
              if (l_dat == 0xeeeee2) {l_eeeee2_ct++;}
              if (l_dat == 0xeeeee3) {l_eeeee3_ct++;}

              if (l_only_one_hit_in_cha    == 1) {l_1_hit_and_eeeeee_ct++;}
              if (l_more_than_1_hit_in_cha == 1) {l_more_1_hit_and_eeeeee_ct++;}

              //printf ("%d 0xeeeeee found \n", l_eeeeee_ct);
            }
          }
        }
        l_spec_trail = *pl_tmp++;
        if ( (l_spec_trail & 0xff000000) != 0xbf000000)
        {
          printf ("ERROR>> E,t summary: wrong header is 0x%x, must be: 0x%x\n",
                                                 (l_spec_trail & 0xff000000)>>24, 0xbf);
          goto bad_event;
          //sleep (1);
        }
      }
      else // real channel
      {
        //printf ("real channel \n");
        // channel data size
        l_cha_size = *pl_tmp++;

        // trace header
        l_trace_head = *pl_tmp++;
        //printf ("trace header \n");
        if ( ((l_trace_head & 0xff000000) >> 24) != 0xaa)
        {
          printf ("ERROR>> trace header id is not 0xaa \n");
          goto bad_event;
        }

        l_fpga_filt_on_off = (l_trace_head & 0x80000) >> 19;
        l_fpga_filt_mode   = (l_trace_head & 0x40000) >> 18;

        //printf ("fpga filter on bit: %d, fpga filter mode: %d \n", l_fpga_filt_on_off, l_fpga_filt_mode);
        //fflush (stdout);
        //sleep (1);

        if (l_trig_type == 1) // physics event
        {

          if (l_first_trace[l_sfp_id][l_feb_id] == 0)
          {
            l_first_trace[l_sfp_id][l_feb_id] = 1;
            //h_hitpat_tr[l_sfp_id][l_feb_id]->Fill (-1, 1);
          }
      //  h_hitpat_tr[l_sfp_id][l_feb_id]->Fill (l_cha_id, 1);
          l_ch_hitpat_tr[l_sfp_id][l_feb_id][l_cha_id]++;

          // now trace
          l_trace_size = (l_cha_size/4) - 2;     // in longs/32bit

          //das folgende kommentierte noch korrigieren!
          //falls trace + filter trace: cuttoff bei 2000 slices, da 4fache datenmenge!

          //if (l_trace_size != (TRACE_SIZE>>1))
          //{
          //  printf ("ERROR>> l_trace_size: %d \n", l_trace_size); fflush (stdout);
          //  goto bad_event;
          //}

          if (l_fpga_filt_on_off == 0) // only trace. no fpga filter trace data
          {
            for (l_l=0; l_l<l_trace_size; l_l++)   // loop over traces
            {

              // disentangle data
              l_dat_fir = *pl_tmp++;
              l_dat_sec = l_dat_fir;

              #ifdef USE_MBS_PARAM
              l_adc_type = (l_trace_head & 0x800000) >> 23;
              #else
              l_adc_type = (l_sfp_adc_type[l_sfp_id] >> l_feb_id) & 0x1;
              #endif

              if (l_adc_type == 0) // 12 bit
              {
                l_dat_fir =  l_dat_fir        & 0xfff;
                l_dat_sec = (l_dat_sec >> 16) & 0xfff;
              }

              if (l_adc_type == 1)  // 14 bit
              {
                l_dat_fir =  l_dat_fir        & 0x3fff;
                l_dat_sec = (l_dat_sec >> 16) & 0x3fff;
              }

              h_trace[l_sfp_id][l_feb_id][l_cha_id]->SetBinContent (l_l*2  +1, l_dat_fir);
              h_trace[l_sfp_id][l_feb_id][l_cha_id]->SetBinContent (l_l*2+1+1, l_dat_sec);



              l_tr[l_l*2]   = l_dat_fir;
              l_tr[l_l*2+1] = l_dat_sec;


        }


            l_trace_size = l_trace_size * 2;
          }


       if (l_fpga_filt_on_off == 1) // trace AND fpga filter data
          {
            for (l_l=0; l_l<(l_trace_size>>1); l_l++)   // loop over traces
            {
              // disentangle data
              l_dat_trace = *pl_tmp++;
              l_dat_filt  = *pl_tmp++;
              l_filt_sign  =  (l_dat_filt & 0x800000) >> 23;

             #ifdef USE_MBS_PARAM
              l_adc_type = (l_trace_head & 0x800000) >> 23;
              #else
              l_adc_type = (l_sfp_adc_type[l_sfp_id] >> l_feb_id) & 0x1;
              #endif

              if (l_adc_type == 0) // 12 bit
              {
                l_dat_trace = l_dat_trace  & 0xfff;
              }

              if (l_adc_type == 1)  // 14 bit
              {
                l_dat_trace = l_dat_trace  & 0x3fff;
              }

              l_dat_filt  = l_dat_filt   & 0x7fffff;
              if (l_filt_sign == 1) {l_dat_filt = l_dat_filt * -1;}

              h_trace_filt      [l_sfp_id][l_feb_id][l_cha_id]->SetBinContent (l_l, l_dat_trace);
              h_trapez_fpga[l_sfp_id][l_feb_id][l_cha_id]->SetBinContent (l_l, l_dat_filt);

              l_tr[l_l] = l_dat_trace;
            }
            l_trace_size = l_trace_size >> 1;
          }

          // find base line value of trace and correct it to baseline 0
          f_bls_val = 0.;
          for (l_l=l_bls_start; l_l<l_bls_stop; l_l++)
          {
            f_bls_val += (Double_t)l_tr[l_l];
          }
          f_bls_val = f_bls_val / (Double_t)(l_bls_stop - l_bls_start);
          for (l_l=0; l_l<l_trace_size; l_l++)   // create baseline restored trace
          {
            f_tr_blr[l_l] =  (Double_t)l_tr[l_l] - f_bls_val;

            h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->SetBinContent (l_l+1, f_tr_blr[l_l]);
            
            
            
// if(fOutput->event_number==   4738522){
//
//                                     fOutput->fTrace[l_l]=f_tr_blr[l_l];
// }
//                                       // cout <<fOutput->fTrace[l_l]<< endl;


          }

                    if (l_feb_id == 0){h_hits->Fill(l_cha_id);}
                     if (l_feb_id == 1){h_hits->Fill(l_cha_id+16);}
                     //Macropulse and TOF
                       if (l_feb_id == 2 ){
                          h_fpga_energy[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill(h_trace[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum ());


            // Macro on CHA 0 for r301 (SHIPTRAP18) and CHA 15 for RADRIS 2019
                          if (l_cha_id == 0){

          if((h_trace[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum () > 1000)) fOutput->Macropulse=1;
          
           
                       }
//                   else fOutput->Macropulse=0;
//                       if(fOutput->Macropulse==0) cout<<"fOutput->Macropulse " <<fOutput->Macropulse <<endl;
                        if (l_cha_id == 0){
                     // if(h_trace[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum () > 8000) 
                            fOutput->TOF=1;
                          //  fOutput->TOF_max[2][0]=h_trace[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum ();
                        fOutput->TOF_max[2][0]=  h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum ();
                        h_fpga_energy[l_sfp_id][l_feb_id][l_hit_cha_id]->Fill(  h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum ());
                        
                      
                        //cout <<l_fpga_energy << endl;
                           //    cout<< -h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMinimum () << endl;
                        }
                       }
                  h_hits->Fill(l_cha_id+32);

                  //Send time to analysis
                  fOutput->l_t_trig = ll_time;
                  fOutput->hit_time[l_feb_id][l_hit_cha_id] = l_hit_time[l_sfp_id][l_feb_id][l_hit_cha_id];

                
//                        if(fOutput->Macropulse==0 && fOutput->pileup>0){
//                            f_bls_val_pileup = 0.;
//                             for (l_l=l_bls_start; l_l<l_bls_stop; l_l++)
//                             {
//                                 f_bls_val_pileup += (Double_t)l_tr[l_l];
//                             }
//                             f_bls_val_pileup = f_bls_val_pileup / (Double_t)(l_bls_stop - l_bls_start);
//                            for (l_l=0; l_l<l_trace_size; l_l++){
//                            f_tr_blr_pileup[l_l] =  (Double_t)l_tr[l_l] - f_bls_val;
//                            h_trace_blr_Pileup[l_sfp_id][l_feb_id][l_cha_id]->SetBinContent (l_l+1, f_tr_blr_pileup[l_l]);
//                          
//                             }
//                        }
                       
                //  cout <<  fOutput->hit_time[l_feb_id][l_hit_cha_id] << " " << fOutput->l_t_trig << endl;

//      trace_height=TMath::Abs(h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMinimum ());
//  for(int i=0; i<16; i++){
//
//  if(l_feb_id==0 && l_cha_id==i) sum1a=trace_height;
//  if(l_feb_id==1 && l_cha_id==i) sum2a=trace_height;
//      }
//  SumTa = sum1a + sum2a;
//  h_peak_back[l_sfp_id][l_feb_id][l_cha_id]->Fill(SumTa);
//    if(l_feb_id==0 || l_feb_id==1 || l_feb_id==2 ){cout << "3"<< endl;
//      // h_peak_back[l_sfp_id][l_feb_id][l_cha_id]->Fill(TMath::Abs(h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMinimum ()));
//   //   fOutput->Back_Y[l_feb_id][l_cha_id]=TMath::Abs(h_trace_blr[l_sfp_id][l_feb_id][l_cha_id]->GetMaximum ());
//    }



//
//
//                               h_spec[l_sfp_id][l_feb_id][l_cha_id]->Fill(SumT);
//                      //fOutput->Front_X[l_feb_id][l_cha_id]=SumT;
      }

        l_trace_trail = *pl_tmp++;
    //  cout << "trace trailer " << l_trace_trail <<endl;
        if ( ((l_trace_trail & 0xff000000) >> 24) != 0xbb)
        {
          printf ("ERROR>> trace trailer id is not 0xbb, ");
          printf ("SFP: %d, FEB: %d, CHA: %d \n", l_sfp_id, l_feb_id, l_cha_id);
          goto bad_event;
        }
      }
    }
    else
    {
      printf ("ERROR>> data word neither channel header nor padding word \n");
    }
  }

bad_event:


//   if ( (l_evt_ct % 10000) == 0)
//   {
//     printf ("------------------------------------------------------\n");
//    // printf ("nr of events processed:                  %10u \n", l_evt_ct);
// //     printf ("nr of good_energies found:               %10u \n", l_good_energy_ct);
// //     printf ("single hits found in trigger window:     %10u \n", l_1_hit_ct);
// //     printf ("multi hits found in trigger window:      %10u \n", l_more_1_hit_ct);
// //     printf ("multi hits found, first hit energy ok:   %10u \n", l_more_1_hit_first_energy_ok_ct);
// //     printf ("nr of events with failed fpga energy:    %10u \n", l_eeeeee_ct);
//     /*  printf ("nr of good_energies found:               %10u \n", l_good_energy_ct);
//     printf ("single hits found in trigger window:     %10u \n", l_1_hit_ct);
//     printf ("multi hits found in trigger window:      %10u \n", l_more_1_hit_ct);
//     printf ("multi hits found, first hit energy ok:   %10u \n", l_more_1_hit_first_energy_ok_ct);
//     printf ("nr of events with failed fpga energy:    %10u \n", l_eeeeee_ct);
//     printf ("nr of events with eeeee1:                %10u \n", l_eeeee1_ct);
//     printf ("nr of events with eeeee2:                %10u \n", l_eeeee2_ct);
//     printf ("nr of events with eeeee3:                %10u \n", l_eeeee3_ct);
//     printf ("nr of events with failed fpga energy - \n");
//     printf ("and a single hit found in trigger window %10u \n", l_1_hit_and_eeeeee_ct);
//     printf ("nr of events with failed fpga energy - \n");
//     printf ("and multi hits found in trigger window   %10u \n", l_more_1_hit_and_eeeeee_ct);*/
//
//     printf ("------------------------------------------------------\n");
//   }

  return kTRUE;
}

//--------------------------------------------------------------------------------------------------------

void Strip16UnpackProc:: f_make_histo (Int_t l_mode)
{
  Text_t chis[256];
  Text_t chead[256];
  Text_t chis1[256];
  Text_t chead1[256];
  //UInt_t i;
  UInt_t l_i, l_j, l_k;
  UInt_t l_tra_size;
  UInt_t l_trap_n_avg;
//   UInt_t l_left;
//   UInt_t l_right;
//  string traces_isomer;
//   for(i=1; i<400; i++){
//           stringstream a;
//           a<<i;
//
//          traces_isomer = "trace_" + a.str();
//          traces_isomer += ".txt";
//
// tracesout.open (traces_isomer.c_str(), ios::out);
//   }




  #ifdef USE_MBS_PARAM
  l_tra_size   = l_trace & 0xffff;
  l_trap_n_avg = l_e_filt >> 21;
  printf ("f_make_histo: trace size: %d, avg size %d \n", l_tra_size, l_trap_n_avg);
  fflush (stdout);
  l_sfp_slaves[0] =  l_slaves & 0xff;
  l_sfp_slaves[1] = (l_slaves & 0xff00)     >>  8;
  l_sfp_slaves[2] = (l_slaves & 0xff0000)   >> 16;
  l_sfp_slaves[3] = (l_slaves & 0xff000000) >> 24;
  printf ("f_make_histo: # of sfp slaves: 3:%d, 2:%d, 1: %d, 0: %d \n",
          l_sfp_slaves[3], l_sfp_slaves[2], l_sfp_slaves[1], l_sfp_slaves[0]);
  fflush (stdout);
  #else

  l_tra_size   = TRACE_SIZE;
  l_trap_n_avg = TRAPEZ_N_AVG;
  #endif // USE_MBS_PARAM

  for (l_i=0; l_i<MAX_SFP; l_i++)
  {
    if (l_sfp_slaves[l_i] != 0)
    {
      for (l_j=0; l_j<l_sfp_slaves[l_i]; l_j++)
      {
        for (l_k=0; l_k<N_CHA; l_k++)
        {

        sprintf(chis,"Raw/Traces/FEB: %2d CH: %2d", l_j, l_k);
        sprintf(chead,"Trace");
        h_trace[l_i][l_j][l_k] = MakeTH1('I', chis,chead,l_tra_size,0,l_tra_size);


    sprintf(chis,"Raw/Traces/FEB: %2d CH: %2d", l_j, l_k);
        sprintf(chead,"Trace");
        h_trace_filt[l_i][l_j][l_k] = MakeTH1('I', chis,chead,l_tra_size,0,l_tra_size);

        sprintf(chis,"Raw/Traces BLR/TRACE, base line restored SFP: %2d FEBEX: %2d CHAN: %2d", l_i, l_j, l_k);
        sprintf(chead,"Trace, base line restored");
        h_trace_blr[l_i][l_j][l_k] = MakeTH1('F', chis,chead,l_tra_size,0,l_tra_size);
        
//         sprintf(chis,"Pileup/Traces BLR_Pileup/TRACE_Pileup, base line restored SFP: %2d FEBEX: %2d CHAN: %2d", l_i, l_j, l_k);
//         sprintf(chead,"Trace_Pileup, base line restored");
//         h_trace_blr_Pileup[l_i][l_j][l_k] = MakeTH1('F', chis,chead,l_tra_size,0,l_tra_size);

//

    sprintf(chis,"FPGA/Trapez/FPGA Trapez, FEBEX: %2d CHAN: %2d",  l_j, l_k);
        sprintf(chead,"FPGA Trapez");
        h_trapez_fpga[l_i][l_j][l_k] = MakeTH1('F', chis,chead,l_tra_size,0,l_tra_size);

//    sprintf(chis,"Raw/TOF/FEBEX: %2d CHAN: %2d",  l_j, l_k);
//         sprintf(chead,"TOF");
//         h_tof[l_i][l_j][l_k] = MakeTH1('I', chis,chead,20000,-10000,10000);

        sprintf(chis,"FPGA/FPGA Energy Sum/FEBE: %2d CHA: %2d",  l_j, l_k);
        sprintf(chead,"FPGA Energy");
        h_fpga_energy[l_i][l_j][l_k] = MakeTH1('F', chis,chead,40000,0,40000);


         }

    sprintf(chis1,"Hits");
    sprintf(chead1,"Number of hits per strip in all the channels");
    h_hits= MakeTH1('D',chis1,chead1,35,0,35);

    }
  }
}
}
//----------------------------END OF GO4 SOURCE FILE ---------------------
