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

#include "Strip16UnpackEvent.h"

#include "Riostream.h"

//***********************************************************
Strip16UnpackEvent::Strip16UnpackEvent() :
   TGo4EventElement()
{
    cout << "**** Strip16UnpackEvent: Create instance" << endl;
}
//***********************************************************
Strip16UnpackEvent::Strip16UnpackEvent(const char* name) :
   TGo4EventElement(name)
{
  cout << "**** Strip16UnpackEvent: Create instance " << name << endl;
}
//***********************************************************
Strip16UnpackEvent::~Strip16UnpackEvent()
{
  cout << "**** Strip16UnpackEvent: Delete instance " << endl;
}

//-----------------------------------------------------------
void  Strip16UnpackEvent::Clear(Option_t *t)
{
   // cout << "1a"<< endl;
  for(int i=0; i<4; i++){
      for(int j=0;j<16;j++){
                Strip_sum[i][j]=0;
                Pos_t[i][j]=0;
                Pos_b[i][j]=0;
                hit_time[i][j]=0;
                TOF_max[i][j]=0;
                    }
                }

  for (int i=0; i<3096; i++){
        fTrace[i]=0;
                    }
                    
    trg_time=0;
    TOF=0;
    l_t_trig = -1;
    pileup=0;
    //event_number=0;

 // for(int i=0; i<5; i++){for(int j=0;j<16;j++){l_T[0][i][j]=0;}}

	//	fPatternUnit = 0;
}

// void  Strip16UnpackEvent::ClearEvent()
// 
// {
//     
//   //Marija output event of Unpack
//         for(int i=0; i<4; i++){for(int j=0;j<16;j++){Strip_sum[i][j]=0;}}
//   for(int i=0; i<4; i++){for(int j=0;j<16;j++){Pos_t[i][j]=0;}}
//   for(int i=0; i<4; i++){for(int j=0;j<16;j++){Pos_b[i][j]=0;}}
//                 //  Time=0;
// 
//         //Julien output event of unpack
//         for(int i=0; i<3; i++){for(int j=0;j<16;j++){hit_time[i][j]=0;}}
//                 trg_time=0;
//                 TOF=0;
// //                       l_sfp = -1;
// //                         l_feb = -1;
// //                         l_cha = -1;
//                  l_t_trig = -1;
// 
//         //      fPatternUnit = 0;
// }

//----------------------------END OF GO4 SOURCE FILE ---------------------
