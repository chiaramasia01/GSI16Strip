//A.K.Mistry
//25.06.15.
//16 Strip SHIP detector online sort code


//C.Masia
//06.08.24
//Added lines that should produce a CSV file to be analysed in python


/* This codes creates and fill the histograms visible in go4 */

#include <iomanip>
#include "Strip16AnlProc.h"
#include "Strip16AnlEvent.h"
#include "Strip16CalibParameter.h"
#include "TFile.h"
#include "TTree.h"
#include <sstream>

ofstream   gOutputFile;

float min_strip =0; // minimum number for strips
float max_strip = 16; // there are 16 strips
float bin_strip = 16; 


float max_calib = 10000.;  // calibration values
float min_calib = 0.;
float num_bin_cal = 1000;

float max_tof = 60000;  // time of flight data
float min_tof = 0;
float num_bin_tof = 2000;

float min_uncal_en = 3000; // histogram energy range for uncalibrated data
float max_uncal_en = 5000;


ofstream   outfile;


//Long64_t  DTime = 0;
//***********************************************************

//===================================== Constructor - Initialization of all class members==========================================
// this one is used in Strip16AnlFact

Strip16AnlProc::Strip16AnlProc(Text_t * cname):
TGo4EventProcessor(cname)
{

//===================== initialize all to zero ===========================

  for(int i=0;i<4;i++){for(int j=0;j<16;j++){

      stripsum[i][j]=0;
      //Time[i][j] = 0;
        }
      }

/////////////////////////////////////////////

  Text_t    name[50], descr[50], name1[50], descr1[50], name2[50], descr2[50], name3[50], descr3[50], name4[50], descr4[50], name5[50], descr5[50], name6[50], descr6[50], name7[50], descr7[50], name8[50], descr8[50];



  // boolean member variable used to tell the static variables in Strip16EventAnalysis()
  // to be cleared each time a new analysis settings were submitted
  
  fbNewSubmit = kTRUE;

  //// init user analysis objects:

  // ---- 1. parameters


  
  // these two lines set the formatting to write on the terminal, 4 decimal digits
  cout.flags(ios::fixed); // now 'precision' means number of digits after dot
  cout.precision(4);

   // fParam contains info whether or not to fill
  // the YL-YH calib (fYH_YL_Calib) and Back detector calib (fBack_Calib) graphs.
  // fParam = new Strip16Parameter("Strip16Par");
  //AddParameter(fParam);
  // fParam = (Strip16Parameter*)  GetParameter("Strip16Par"); // get parameter from the memory (or autosave file)
  // if (fParam) fParam->PrintParameter(0,0);
  //else cout << "**** ERRR - Strip16Par doesn't exist - program will crash.\n";

  // calibration parameter - contains all calibration values
  fCal = new Strip16CalibParameter("CalibPar"); // New instance of the class
  AddParameter(fCal);  // Adds the object to the list of parameters 
  // fCal = (Strip16CalibParameter*) GetParameter("CalibPar");
  if (fCal) fCal->PrintParameter(0,0);
  else cout << "**** ERRR - CalibPar doesn't exist - program will crash.\n";
  

//======================== Creating text file for data acquisition =================

// NOTE: remember to change name everytime

  ///Open file to write to 
  outfile.open("20240808_test001_0001_uncal.txt", ios::out);
  

//====================== Creating histograms =========================



   for (int i=1;i<2;i++){     // executes once. NOTE Why do we loop on i? AKM 080824
     
         for (int j=0;j<16;j++){ // executes for each strip
            
        //Position
                int k=0; ///NOTE do we need to define k here? Or even at all?
//                 if(i==1){k=j;sprintf(name,"E vs Postion %02d", k);
//                 sprintf(descr, "E vs Postion top %02d", k);}
//                 RemoveHistogram(name);
//                 h_E_post[i][j]=new TH2D(name,descr,42, 0, 42, 5000, 0, 10000 );
//                 AddHistogram(h_E_post[i][j],"Calibrations/2D_spectra/Positions/Uncalibrated");

                
                /* Creates the histogram of energy vs calibration position*/
                
                /// NOTE adjust histogram parameters for uncalibrated data 
                
                if(i==1){k=j;sprintf(name2,"E vs Calib Postion top %02d", k);             // i is only 1 so the condition is always true
                sprintf(name2,"E vs Calib Postion top %02d", k);}                       // sprintf used to create hist name and description, name is used to refer to the histogram
                sprintf(descr2, "E vs Calib Postion top %02d", k);                      // displayed in the plot title
                RemoveHistogram(name2);                                                  // removes any existing histogram with the same name
                h_E_poscalib[i][j]=new TH2D(name2,descr2, 42, 0, 42, 500, min_uncal_en, max_uncal_en);  // creates 2D histogram, the six numbers are: nbins-x, min-x, max-x, nbins-y, min-y, max-y
                h_E_poscalib[i][j]->SetXTitle("Calibration Position");
                h_E_poscalib[i][j]->SetYTitle("Energy ");
                AddHistogram(h_E_poscalib[i][j],"Calibrations/Positions/");             // The histogram is added to the framework under the path "Calibrations/Positions/"

                //Strip Energies

                if(i==1){k=j; sprintf(name2, "16 Strip Position Corrected Energy %02d", k);  
                sprintf(descr2, "E_keV, strip %02d", k);}
                RemoveHistogram(name2);
                h_corr_E[i][j] = new TH1D (name2, descr2, num_bin_cal, min_calib, max_calib);  // 1D histogram
                h_corr_E[i][j]->SetXTitle("Channel");
                h_corr_E[i][j]->SetYTitle("Counts");
                AddHistogram(h_corr_E[i][j], "Calibrations/16_Strip_Position_Corrected");
                
                // Creates histogram of calibrated energies

                if(i==1){k=j; sprintf(name3, "16 Strip Calibrated %02d", k);  
                sprintf(descr3, "E_keV, strip %02d", k);}
                RemoveHistogram(name3);
                h_stripcalib[i][j] = new TH1D (name3, descr3, num_bin_cal, min_calib, max_calib);  // calibrated strips
                h_stripcalib[i][j]->SetXTitle("Channel");
                h_stripcalib[i][j]->SetYTitle("Counts");
                AddHistogram(h_stripcalib[i][j], "16_Strip_Main/Pulse+Pause/16_strip_Pulse+Pause");
                
                // Creates the veto histogram (uses TOF)

                if(i==1){k=j; sprintf(name3, "16 Strip veto %02d", k);  
                sprintf(descr3, "E_keV, strip %02d", k);}
                RemoveHistogram(name3);
                h_stripveto[i][j] = new TH1D (name3, descr3, num_bin_cal, min_calib, max_calib);  // calibrated strips
                h_stripveto[i][j]->SetXTitle("Channel");
                h_stripveto[i][j]->SetYTitle("Counts");
                AddHistogram(h_stripveto[i][j], "Veto/16_Strip_Veto");
                
                // Creates the antiveto histogram 

                 if(i==1){k=j; sprintf(name3, "16 Strip antiveto %02d", k);  
                sprintf(descr3, "E_keV, strip %02d", k);}
                RemoveHistogram(name3);
                h_stripantiveto[i][j] = new TH1D (name3, descr3, num_bin_cal, min_calib, max_calib);  // calibrated strips
                h_stripantiveto[i][j]->SetXTitle("Channel ");
                h_stripantiveto[i][j]->SetYTitle("Counts");
                AddHistogram(h_stripantiveto[i][j], "AntiVeto/16_Strip_AntiVeto");
                
                // Creates pulse histogram

                if(i==1){k=j; sprintf(name3, "16 Strip Pulse %02d", k);  
                sprintf(descr3, "E_keV, strip %02d", k);}
                RemoveHistogram(name3);
                h_strippulse[i][j] = new TH1D (name3, descr3, num_bin_cal, min_calib, max_calib);  // calibrated strips
                h_strippulse[i][j]->SetXTitle("Channel ");
                h_strippulse[i][j]->SetYTitle("Counts");
                AddHistogram(h_strippulse[i][j], "16_Strip_Main/Pulse/16_Strip_Pulse");
                
                // Creates pause histogram

                if(i==1){k=j; sprintf(name3, "16 Strip Pause %02d", k); 
                sprintf(descr3, "E_keV, strip %02d", k);}
                RemoveHistogram(name3);
                h_strippause[i][j] = new TH1D (name3, descr3, num_bin_cal, min_calib, max_calib);  // calibrated strips
                h_strippause[i][j]->SetXTitle("Channel ");
                h_strippause[i][j]->SetYTitle("Counts");
                AddHistogram(h_strippause[i][j], "16_Strip_Main/Pause/16_Strip_Pause");

           }
        }

                // Creates pulse+pause histogram for the sum of all strips
                
                sprintf(name4,"16 Strip Pulse+Pause Sum");
                sprintf(descr4, "16 Strip Pulse+Pause Sum");
                RemoveHistogram(name4);
                h_strip_sum=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_sum->SetXTitle("Channel ");
                h_strip_sum->SetYTitle("Counts");
                AddHistogram(h_strip_sum,"16_Strip_Main/Pulse+Pause");
                
                // Creates time histogram for time
                
                sprintf(name4,"Time");
                sprintf(descr4, "Time");
                RemoveHistogram(name4);
                hTime=new TH1D(name4,descr4,360000, 0, 360000);
                hTime->SetXTitle("Time [s]");
                AddHistogram(hTime);

//                  sprintf(name4,"hits_test");
//                 sprintf(descr4, "hits_test");
//                 RemoveHistogram(name4);
//                 h_hit_test=new TH1D(name4,descr4,50, 0, 50);
//                 AddHistogram(h_hit_test,"Test");
                
                // Creates histogram for veto sum

                sprintf(name4,"16 Strip Veto Sum");
                sprintf(descr4, "16 Strip Veto");
                RemoveHistogram(name4);
                h_strip_veto_sum=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_veto_sum->SetXTitle("Channel ");
                h_strip_veto_sum->SetYTitle("Counts");
                AddHistogram(h_strip_veto_sum,"Veto/Sum_spectra");
                
                // Creates histogram for antiveto sum
// 
                sprintf(name4,"16 Strip AntiVeto Sum");
                sprintf(descr4, "16 Strip AntiVeto");
                RemoveHistogram(name4);
                h_strip_antiveto_sum=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_antiveto_sum->SetXTitle("Channel ");
                h_strip_antiveto_sum->SetYTitle("Counts [keV]");
                AddHistogram(h_strip_antiveto_sum,"Veto/Sum_spectra");
                
                // Creates histogram for pulse sum

                sprintf(name4,"16 Strip Pulse Sum");
                sprintf(descr4, "16 Strip Pulse");
                RemoveHistogram(name4);
                h_strip_pulse_sum=new TH1D(name4,descr4,1000, 0, 10000);
                h_strip_pulse_sum->SetXTitle("Channel ");
                h_strip_pulse_sum->SetYTitle("Counts");
                AddHistogram(h_strip_pulse_sum,"16_Strip_Main/Pulse");
                
                // Creates histogram for pause sum

                sprintf(name4,"16 Strip Pause Sum");
                sprintf(descr4, "16 Strip Pause");
                RemoveHistogram(name4);
                h_strip_pause_sum=new TH1D(name4,descr4,1000, 0, 10000);
                h_strip_pause_sum->SetXTitle("Channel ");
                h_strip_pause_sum->SetYTitle("Counts");
                AddHistogram(h_strip_pause_sum,"16_Strip_Main/Pause");
                
                // Creates histogram for pause sum for strip number < 11
                
                sprintf(name4,"16 Strip Pause Sum < strip 11");
                sprintf(descr4, "16 Strip Pause < strip 11");
                RemoveHistogram(name4);
                h_strip_pause_sum_llelf=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_pause_sum_llelf->SetXTitle("Channel ");
                h_strip_pause_sum_llelf->SetYTitle("Counts");
                AddHistogram(h_strip_pause_sum_llelf,"16_Strip_Main/Pause");
                
                // Creates histogram for sum, Nobilium gate

                sprintf(name4,"16 Strip No Gate Sum");
                sprintf(descr4, "16 Strip No gate Sum");
                RemoveHistogram(name4);
                h_strip_Nogated_sum=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_Nogated_sum->SetXTitle("Channel ");
                h_strip_Nogated_sum->SetYTitle("Counts");
                AddHistogram(h_strip_Nogated_sum,"16_Strip_Main/Alpha_gate_No");
                
                // Lawrencium gate

                sprintf(name4,"16 Strip Lr Gated Sum");
                sprintf(descr4, "16 Strip Lr gate Sum");
                RemoveHistogram(name4);
                h_strip_Lrgated_sum=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_Lrgated_sum->SetXTitle("Channel ");
                h_strip_Lrgated_sum->SetYTitle("Counts");
                AddHistogram(h_strip_Lrgated_sum,"16_Strip_Main/Alpha_gate_Lr");
                
                // Rutherfordium gate

                sprintf(name4,"16 Strip Rf Gated Sum");
                sprintf(descr4, "16 Strip Rf gate Sum");
                RemoveHistogram(name4);
                h_strip_Rfgated_sum=new TH1D(name4,descr4,num_bin_cal, min_calib, max_calib);
                h_strip_Rfgated_sum->SetXTitle("Channel ");
                h_strip_Rfgated_sum->SetYTitle("Counts");
                AddHistogram(h_strip_Rfgated_sum,"16_Strip_Main/Alpha_gate_Rf");
                
                // Creates 2D histogram of energy-number of strip

                sprintf(name5,"E_vs_Id");
                sprintf(descr5, "E_vs_Id");
                RemoveHistogram(name5);
                h_EId=new TH2D(name5,descr5,bin_strip, min_strip,max_strip,1000,0,10000 );
                h_EId->SetXTitle("Strip Number");
                h_EId->SetYTitle("Energy [keV]");
                AddHistogram(h_EId,"16_Strip_Main/Pulse+Pause");
                
                // Creates 2D histogram of X-Y position pulse+pause

                sprintf(name8,"XvsY");
                sprintf(descr8, "XvsY");
                RemoveHistogram(name8);
                h_posvsstrip=new TH2D(name8,descr8,bin_strip, min_strip,max_strip,100,0,36 );
                h_posvsstrip->SetXTitle("Strip Number");
                h_posvsstrip->SetYTitle("Position [mm]");
                AddHistogram(h_posvsstrip,"16_Strip_Main/Pulse+Pause");
                
                // Creates 2D histogram of X-Y position for pulse

                sprintf(name1,"XvsY_Pulse");
                sprintf(descr1, "XvsY_Pulse");
                RemoveHistogram(name1);
                h_posvsstrip_pulse=new TH2D(name1,descr1,bin_strip, min_strip,max_strip,100,0,36);
                h_posvsstrip_pulse->SetXTitle("Strip Number");
                h_posvsstrip_pulse->SetYTitle("Position [mm]");
                AddHistogram(h_posvsstrip_pulse,"16_Strip_Main/Pulse");
                
                // Creates 2D histogram of X-Y position for pause
                
                sprintf(name1,"XvsY_Pause");
                sprintf(descr1, "XvsY_Pause");
                RemoveHistogram(name1);
                h_posvsstrip_pause=new TH2D(name1,descr1,bin_strip, min_strip,max_strip,100,0,36);
                h_posvsstrip_pause->SetXTitle("Strip Number");
                h_posvsstrip_pause->SetYTitle("Position [mm]");
                AddHistogram(h_posvsstrip_pause,"16_Strip_Main/Pause");
                
                // Creates 2D histogram of X-Y position 

                sprintf(name1,"XvsY_NoGated");
                sprintf(descr1, "XvsY_NoGated");
                RemoveHistogram(name1);
                h_posvsstrip_Nogated=new TH2D(name1,descr1,bin_strip, min_strip,max_strip,100,0,36);
                h_posvsstrip_Nogated->SetXTitle("Strip Number");
                h_posvsstrip_Nogated->SetYTitle("Position [mm]");
                AddHistogram(h_posvsstrip_Nogated,"16_Strip_Main/Alpha_gate_No");
                
                // Creates 2D histogram of X-Y position, Lawrencium gate

                sprintf(name1,"XvsY_LrGated");
                sprintf(descr1, "XvsY_LrGated");
                RemoveHistogram(name1);
                h_posvsstrip_Lrgated=new TH2D(name1,descr1,bin_strip, min_strip,max_strip,100,0,36);
                h_posvsstrip_Lrgated->SetXTitle("Strip Number");
                h_posvsstrip_Lrgated->SetYTitle("Position [mm]");
                AddHistogram(h_posvsstrip_Lrgated,"16_Strip_Main/Alpha_gate_Lr");
                
                // Creates 2D histogram of X-Y position, Rutherfordium gate

                sprintf(name1,"XvsY_RfGated");
                sprintf(descr1, "XvsY_RfGated");
                RemoveHistogram(name1);
                h_posvsstrip_Rfgated=new TH2D(name1,descr1,bin_strip, min_strip,max_strip,100,0,36);
                h_posvsstrip_Rfgated->SetXTitle("Strip Number");
                h_posvsstrip_Rfgated->SetYTitle("Position [mm]");
                AddHistogram(h_posvsstrip_Rfgated,"16_Strip_Main/Alpha_gate_Rf");
                
                // Creates histogram of number of counts per strip

                sprintf(name6,"ProfileX");
                sprintf(descr6, "ProfileX");
                RemoveHistogram(name6);
                hProfileX = new TH1D("ProfileX", "Counts vs strip number", bin_strip, min_strip,max_strip);
                hProfileX->SetXTitle("Strip Number");
                hProfileX->SetYTitle("Counts");
                AddHistogram(hProfileX, "16_Strip_Main");
                
                // Creates histogram of number of counts per Y position

                sprintf(name7,"ProfileY");
                sprintf(descr7, "ProfileY");
                RemoveHistogram(name7);
                RemoveHistogram("ProfileY");
                hProfileY = new TH1D("ProfileY", "Counts vs Y position", 36,0,36);
                hProfileY->SetXTitle("Position [mm]");
                hProfileY->SetYTitle("Counts");
                AddHistogram(hProfileY, "16_Strip_Main");
                
                // Creates histogram of counts per strip, Nobelium gate

                RemoveHistogram("ProfileX_NoGated");
                hProfileX_NoGated = new TH1D("ProfileX_NoGated", "Counts vs strip number,nobelium gated", bin_strip, min_strip,max_strip);
                hProfileX_NoGated->SetXTitle("Strip Number");
                hProfileX_NoGated->SetYTitle("Counts");
                AddHistogram(hProfileX_NoGated, "16_Strip_Main/Alpha_gate_No");
                
                // Creates histogram of number of counts per Y position, Nobelium gate

                RemoveHistogram("ProfileY_NoGated");
                hProfileY_NoGated = new TH1D("ProfileY_NoGated", "Counts vs Y position,nobelium Gated", 36,0,36);
                hProfileY_NoGated->SetXTitle("Position [mm]");
                hProfileY_NoGated->SetYTitle("Counts");
                AddHistogram(hProfileY_NoGated, "16_Strip_Main/Alpha_gate_No");
                
                // creates histogram of counts per strip, Lawrencium gate

                RemoveHistogram("ProfileX_LrGated");
                hProfileX_LrGated = new TH1D("ProfileX_LrGated", "Counts vs strip number, lawrencium gated", bin_strip, min_strip,max_strip);
                hProfileX_LrGated->SetXTitle("Strip Number");
                hProfileX_LrGated->SetYTitle("Counts");
                AddHistogram(hProfileX_LrGated, "16_Strip_Main/Alpha_gate_Lr");
                
                // Creates histogram of number of counts per Y position, Lawrencium gate

                RemoveHistogram("ProfileY_LrGated");
                hProfileY_LrGated = new TH1D("ProfileY_LrGated", "Counts vs Y position, lawrencium Gated", 36,0,36);
                hProfileY_LrGated->SetXTitle("Position [mm]");
                hProfileY_LrGated->SetYTitle("Counts");
                AddHistogram(hProfileY_LrGated, "16_Strip_Main/Alpha_gate_Lr");
                
                // Creates histogram of counts per strip, Rutherfordium gate

                 RemoveHistogram("ProfileX_RfGated");
                hProfileX_RfGated = new TH1D("ProfileX_RfGated", "Counts vs strip number, rutherfordium gated", bin_strip, min_strip,max_strip);
                hProfileX_RfGated->SetXTitle("Strip Number");
                hProfileX_RfGated->SetYTitle("Counts");
                AddHistogram(hProfileX_RfGated, "16_Strip_Main/Alpha_gate_Rf");
                
                // Creates histogram of number of counts per Y position, Rutherfordium gate

                RemoveHistogram("ProfileY_RfGated");
                hProfileY_RfGated = new TH1D("ProfileY_RfGated", "Counts vs Y position, rutherfordium Gated", 36,0,36);
                //hProfileY_RfGated->
                AddHistogram(hProfileY_RfGated, "16_Strip_Main/Alpha_gate_Rf");
     
                // Creates 2D histogram of energy-TOF 
                
                sprintf(name7,"E_vs_TOF");
                sprintf(descr7, "E_vs_TOF");
                RemoveHistogram(name7);
                hEvsTOF=new TH2D(name7,descr7,1600, 0, 16000, 6600, 0, 66000 );
                AddHistogram(hEvsTOF,"16_Strip_Main/2D_spectra");
//
//                 sprintf(name8,"E_vs_TOF2");
//                 sprintf(descr8, "E_vs_TOF2");
//                 RemoveHistogram(name8);
//                 h_E_Tof2=new TH2D(name8,descr8,num_bin_tof,min_tof,max_tof ,num_bin_cal, min_calib, max_calib );
//                 h_E_Tof2->SetYTitle("Energy X (keV)");
//                 h_E_Tof2->SetXTitle("ToF (u.a.)");
//                 AddHistogram(h_E_Tof2,"Calibrations/2D_spectra");
//
//                 sprintf(name9,"E_vs_TOF3");
//                 sprintf(descr9, "E_vs_TOF3");
//                 RemoveHistogram(name9);
//                 h_E_Tof3=new TH2D(name9,descr9,num_bin_tof,min_tof,max_tof ,num_bin_cal, min_calib, max_calib );
//                 h_E_Tof3->SetYTitle("Energy X (keV)");
//                 h_E_Tof3->SetXTitle("ToF (u.a.)");
//                 AddHistogram(h_E_Tof3,"Calibrations/2D_spectra");

      }


//=================end of histograms =========================================

//***********************************************************
// default constructor - not used in program

Strip16AnlProc::Strip16AnlProc()
  : TGo4EventProcessor("Strip16AnlProc")
{
  //  cout << "Strip16AnlProc ---- DO NOT USE THIS CONSTRUCTOR !!!!\n";

}

//***********************************************************
// Default Destructor

Strip16AnlProc::~Strip16AnlProc()
{
  // cout << "**** Strip16AnlProc: Closing output file: " << fPrintPar->fPrtFilename << endl;
  //gOutputFile.close();
    outfile.close();
 // cout << "1"<<endl;
}

//***********************************************************
// ---------- BitTest function --------------------
// returns 1 if at 'position' in 'tested' a '1' was found
// positions are starting from 1 (corresponding to bit 0) for
// more convenient usage

Bool_t Strip16AnlProc::BitTest(const Int_t &tested, Int_t position)
{ cout << "position" << position << endl;
  position = position - 1;
return (tested & (1 << position));
}


//***********************************************************
//***********************************************************
// ==========================================================
// here the input event is beeing analysed and output event (which
// comes as a parameter) is filled




void Strip16AnlProc::Strip16EventAnalysis(Strip16AnlEvent* pOutEvent)
{

//==================== variable definition ===========================

  //Int_t tmp=0;
 // Double_t egl[4]={0,0,0,0}, ege[4]={0,0,0,0}, esumge=0; //Ge detector


  Float_t ey[4][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // calibrated energy

  Float_t ey_sum=0;

  Double_t delta_Et[4][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // position shift

  Double_t calpost[4][16] ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};  // calibrated position

 // static Int_t el_bit_all = 0, el_2b = 0, eh_bit_all = 0, eh_2b = 0;
  //static Bool_t bEndOfPeriodReached_msg = kTRUE;

//================= asign crate positions to local variables =============================

 // get input event from the previous (UNPACK) step
   fInput  = (Strip16UnpackEvent*) GetInputEvent();

  // output events are not stored until kTRUE is set
  pOutEvent->SetValid(kTRUE);

  //set to zero so it works
  //for(int i=0;i<4;i++){
for(int j=0;j<16;j++){stripsum[1][j]=0;}
//}


  MapHardware();


// ========================= Calibrations ====================


//----------------------------- Calibration dssd Y-------------------------------
// First correct for ballistic position effect, the data were approximated with a parabola equation Ax**2 + Bx + C, where A B C are the calibration constants (Calib_position.dat)
  
for(int i =0;i<4;i++){
    for(int j =0;j<16;j++){
        if(stripsum[1][j]>0){
            delta_Et[1][j]=(fCal->postA[1][j]*pow(Pos_t[1][j],2))+(fCal->postB[1][j]*Pos_t[1][j])+fCal->postC[1][j];  // Reminder: fCal is the instance of the class Strip16CalibParameter; Pos_t defined in header
 //cout << "delta_Et " << delta_Et[1][j] << endl;
 calpost[i][j]=stripsum[i][j]- delta_Et[1][j]; //Energy correction
              
        }
          
    }
      
}

 //Energy calibration, obtained from a linear fit Ax + B (Calib_Energy.dat)
 
 // Once we found calpost we can use it for this last step
 
 for(int i =0;i<4;i++){ //NOTE Why loop on i? AKM 080824
     for(int j =0;j<16;j++){
         if(stripsum[1][j]>0){ey[1][j]=fCal->A[1][j]*(calpost[1][j] + rand()%1000*0.001)  + fCal->B[1][j];
             
        }         
         
    }

}




//===================== Fill Spectra ===============================


 for(int i =1;i<3;i++){for(int j =0;j<16;j++){
     if(ey[i][j]>0){
       h_corr_E[i][j]->Fill(calpost[i][j]); // 1D hist Position corrected strips
       h_stripcalib[i][j]->Fill(ey[i][j]); // 1D hist paulse+pause Fully calibrated strips (E and Pos.)

       ey_sum=ey[i][j]; 
       
       if(ey_sum>0)  h_strip_sum->Fill(ey_sum); // 1D hist paulse+pause corrected energies
       
       
       
        /// TOF
       
       if(tof==1){

         h_stripveto[i][j]->Fill(ey[i][j]);
         h_strip_veto_sum->Fill(ey_sum);
         // cout << "E TOF" << ey_sum << endl;

       }
       
       if(tof==0){
           h_stripantiveto[i][j]->Fill(ey[i][j]);
           h_strip_antiveto_sum->Fill(ey_sum);
       }


        hEvsTOF->Fill(TOF_max,ey_sum);
        
        
        // Pulse and Pause
       if(macropulse==1){
         h_strippulse[i][j]->Fill(ey[i][j]);
         h_strip_pulse_sum->Fill(ey_sum);

       }
      // cout<<"fInput->pileup " <<fInput->pileup << endl;
        if (macropulse==0){
          h_strippause[i][j]->Fill(ey[i][j]);
          h_strip_pause_sum->Fill(ey_sum);
         
          
//           if(fInput->pileup>0){
//               cout<<"PILEUP " << ey_sum << "Strip " << j <<  endl;
//           }
          ///For 257Rf
          
        if(j<11)  h_strip_pause_sum_llelf->Fill(ey_sum);
          }



       int k=0;
      if(i==1){k=j;h_EId->Fill(k,ey[i][j]); //Energy vs Strip ID

     //h_E_post[i][j]->Fill(Pos_t[i][j],ey[i][j]); //Pre position corrected strips

     h_E_poscalib[i][j]->Fill(Pos_t[i][j],calpost[i][j]); //Post position corrected strips

     sample_time=Time[i][j];
     
     hTime->Fill((l_t_trig+sample_time)*1.7e-8);
   // cout << "Time " << (l_t_trig+sample_time)*1.7e-8 << endl;
     h_posvsstrip->Fill(k,Pos_t[1][j]);
     IDY=Pos_t[1][j];
     IDX=k;


     hProfileX->Fill(k);
     hProfileY->Fill(Pos_t[1][j]);

     /// alpha energy gates
     ///NOTE need to remove hard coded gates and have a separate input file AKM 080824
 // Nobelium gate    
 //    if((ey_sum > 7000) && (ey_sum < 9400) && macropulse==0){
     if((ey_sum > 5000) && (ey_sum < 7500) && macropulse==0){
        hProfileX_NoGated->Fill(k);
        hProfileY_NoGated->Fill(Pos_t[1][j]);
        h_posvsstrip_Nogated->Fill(k,Pos_t[1][j]);
        h_strip_Nogated_sum->Fill(ey_sum);
      }
// Lawrencium gate 8250-8700 AKM
    if((ey_sum > 7900) && (ey_sum < 9500) && macropulse==0){
        hProfileX_LrGated->Fill(k);
        hProfileY_LrGated->Fill(Pos_t[1][j]);
        h_posvsstrip_Lrgated->Fill(k,Pos_t[1][j]);
        h_strip_Lrgated_sum->Fill(ey_sum);
      }
      
// Rutherfordium gate
    if((ey_sum > 9000) && (ey_sum < 9500) && macropulse==0){
       //if((((ey_sum > 8900) && (ey_sum < 9200))||((ey_sum > 8200) && (ey_sum < 8720))) && macropulse==0){
        hProfileX_RfGated->Fill(k);
        hProfileY_RfGated->Fill(Pos_t[1][j]);
        h_posvsstrip_Rfgated->Fill(k,Pos_t[1][j]);
        h_strip_Rfgated_sum->Fill(ey_sum);
      }
      
      if (macropulse==1){
        h_posvsstrip_pulse->Fill(k,Pos_t[1][j]);
          
    }
    
     if (macropulse==0){
        h_posvsstrip_pause->Fill(k,Pos_t[1][j]);
          
    }
//     if (ey_sum>50){
//          h_E_Tof1->Fill(TOF_max,ey_sum);
//     }
     //Energy vs time of flight1
                       // if(TOF[3][0]>tof_thres) {
                            //    DTime = TMath::Abs((l_T[0][i][j]*20)-(l_T[0][3][0]*20));
                         
                                //cout<<"DT "<<DTime<<" for "<<l_E_cal[0][i][j]<<endl;
//                         }
//                                 //Energy vs time of flight2
//                         if(TOF[3][1]>tof_thres) {
//                                 DTime = TMath::Abs((l_T[0][i][j]*20)-(l_T[0][3][1]*20));
//                                 h_E_Tof2->Fill(DTime,ey_sum);//E ToF in mus units
//                                 //cout<<"DT "<<DTime<<" for "<<l_E_cal[0][i][j]<<endl;
//                         }
//                                 //Energy vs time of flight3
//                         if(TOF[3][2]>tof_thres) {
//                                 DTime = TMath::Abs((l_T[0][i][j]*20)-(l_T[0][3][2]*20));
//                                 h_E_Tof3->Fill(DTime,ey_sum);//E ToF in mus units
//                                 //cout<<"DT "<<DTime<<" for "<<l_E_cal[0][i][j]<<endl;
//                                 }
                        }
                }
        }
 }

 


//=================== Fill output event =====================

// Defined in the Strip16Anl.h class
//NOTE is it really 1.7e-8? (17ns binning, thought it was 20ns?) AKM 080824
    pOutEvent->fE_kev = ey_sum;
    pOutEvent->fTAC = TOF_max;  //TAC
    pOutEvent->fTOF_bit = tof;  //TOF veto
    pOutEvent->fIDY = IDY;
    pOutEvent->fIDX = IDX;
    pOutEvent->fTimeTrig = l_t_trig*1.7e-2;
    pOutEvent->fTimeStrip = (l_t_trig+sample_time)*1.7e-2;           //times in [mus]!
    pOutEvent->fB_pulse = macropulse;

 //   cout<<"pOutEvent->fTimeTrig " <<pOutEvent->fTimeTrig << endl;
    pOutEvent->fev_num=fInput->event_number;


//================== Write text file with data ======================

    outfile  <<  pOutEvent->fev_num << " " <<pOutEvent->fTimeStrip << " " << pOutEvent->fIDX <<" "<< pOutEvent->fIDY << " " << pOutEvent->fE_kev <<" " <<  pOutEvent->fB_pulse << endl;
    cout<< "Event Number " <<  pOutEvent->fev_num <<" Time " <<pOutEvent->fTimeStrip << " IDY " << pOutEvent->fIDY << " IDX " << pOutEvent->fIDX << " Energy " << pOutEvent->fE_kev << " Macro "<< pOutEvent->fB_pulse <<endl;


   // pOutEvent->fTrig = fInput->Trig;
    //pOutEvent->fmultihit=fInput->Multihit;

//     for (int i=0; i<3096; i++){
//
//         pOutEvent->fTraceTrig[i]=fInput->fTrace[i];
//          pOutEvent->fSample[i]=i;
//
//     }



}//end of void function for analysis event


//=================== Write CSV file ===================


void Strip16AnlProc::writeCSV(TH1D* hist, const char* filename) {
    std::ofstream file;
    file.open(filename);
    file << "bin_low_edge,bin_center,bin_content\n";
    for (int i = 1; i <= hist->GetNbinsX(); ++i) {
        double binLowEdge = hist->GetBinLowEdge(i);
        double binCenter = hist->GetBinCenter(i);
        double binContent = hist->GetBinContent(i);
        file << binLowEdge << "," << binCenter << "," << binContent << "\n";
    }
    file.close();
}


 // Saving the histogram for pulse+pause corrected energy sum 
 
void Strip16AnlProc::saveCSV(TH1D* hist,int i, int j) { 
    // Save histogram to CSV after filling
    std::ostringstream filename;
    const char* filenamenew;
    std::string filenamenew1;
    
    filenamenew1=filename.str();
    filenamenew=filenamenew1.c_str();
    filename << "h_strip_sum_" << i << "_" << j << ".csv";
    writeCSV(hist, filenamenew);

}
 







//===================================================================

// convert position from channels to mm

Double_t Strip16AnlProc::PosCh2mm(const Double_t &pos)
{
//cout << "The positon is" << pos << endl;

  return (35. / 900. * pos);
}

// =================================================================

// print a serie of 0 and 1

void Strip16AnlProc::PrintBitPattern(const Int_t &pattern, ostream &output)
{
  for (Int_t pos = 1; pos < 17; pos++) {
    if (BitTest(pattern, pos)) output << "1";

    else output << "0";
  cout << BitTest(pattern, pos) << endl;

}
}

void Strip16AnlProc::MapHardware() //NEED TO REMAKE IT AFTER YOU PLUG EVERUTHING -MARIJA

{// ------------- assign crate positions to local variables ------------
  Int_t i;
  Int_t j;

for(int i=0;i<4;i++){for(int j=0;j<16;j++){

         if(fInput->Strip_sum[i][j]>0){
             stripsum[i][j]=fInput->Strip_sum[i][j];

          //ID = j;
      }


     if(fInput->Pos_t[i][j]>0){
                        Pos_t[i][j]=fInput->Pos_t[i][j];
      }
    if (fInput->TOF_max[i][j]>0){
                        TOF_max=fInput->TOF_max[2][0];
                }
            }
        }


//  for(i=2;i<3;i++){for(j=0;j<16;j++){if(fInput->TOF[i][j]>0){
//                         TOF[i][j]=fInput->TOF[i][j];
//
//       }}}

for(i=0;i<4;i++){
    for(j=0;j<16;j++){
       Time[i][j] = fInput->hit_time[i][j];
      // l_t_trig= fInput->l_t_trig;

            }
        }

     macropulse = fInput->Macropulse;
   //  cout<<"macropulse " <<macropulse << endl;
    tof = fInput->TOF;
    l_t_trig= fInput->l_t_trig;

}


int main() {
    
    Strip16AnlProc proc;
    
    proc.saveCSV(proc.h_strip_sum, 1, 15);
    
    outfile.close();
    
    return 0;
    
}

// =================================================================
ClassImp(Strip16AnlProc)
