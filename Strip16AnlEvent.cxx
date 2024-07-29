#include "Strip16AnlEvent.h"

Strip16AnlEvent::Strip16AnlEvent()
  :TGo4EventElement("Strip16AnlEvent")
{
                   fE_kev   = 0;
                   fTOF_bit = 0;
                   fTAC = 0;
  //fXY_lt=0;
                    fxStrip16CP = 0;
                    fxStrip16FS = 0;

                    fB_pulse = 0;
   fIDY = 0;
    fIDX = 0;
   fTimeStrip=0;
   fev_num=0;
   fTimeTrig = 0;
   for (int i=0; i<3096; i++){
             fTraceTrig[i]=0;
              fSample[i]=0;
         }
   //fTrig=0;
   
}
//-------------
Strip16AnlEvent::Strip16AnlEvent(const Text_t * name)
  :TGo4EventElement(name)
{
    
            fE_kev   = 0;
 // fTime = 0;

  //fXY_lt=0;
            fTOF_bit = 0;
            fTAC = 0;
            fxStrip16CP = 0;
            fxStrip16FS = 0;
  
            fB_pulse = 0;
            fIDY = 0;
            fIDX = 0;
            fTimeStrip=0;
            fev_num=0;
            fTimeTrig = 0;
            for (int i=0; i<3096; i++){
             fTraceTrig[i]=0;
              fSample[i]=0;
         }
   // fTrig=0;
  
}
//-----------------------
Strip16AnlEvent::~Strip16AnlEvent()
{
}
//----------------------------
// assignment operator '='

Strip16AnlEvent Strip16AnlEvent::operator = (const Strip16AnlEvent &from)
{
   if (this == &from) return *this; // selfassignment
   
            fE_kev      = from.fE_kev;
   //fTime = from.fTime;
   //fXY_lt = from.fXY_lt;
            fxStrip16CP    = 0;
            fxStrip16FS    = 0;
            fTOF_bit = from.fTOF_bit;
            fTAC = from.fTAC;
            fB_pulse = from.fB_pulse;
            fIDY = from.fIDY;
            fIDX = from.fIDX;
            fTimeStrip=from.fTimeStrip;
            fev_num=from.fev_num;
            fTimeTrig = from.fTimeTrig;
  //          fTrig=from.fTrig;
            for (int i=0; i<3096; i++){
             fTraceTrig[i]=from.fTraceTrig[i];
              fSample[i]=from.fSample[i];
         }
   

   return *this;
}
//--------------------------
Int_t Strip16AnlEvent::Init()
{
  // check for different source types
  Int_t rev = 0;
  Clear();
  // is it used by Anl step as output ?
  if(CheckEventSource("Strip16AnlProc")){
    fxStrip16CP = (Strip16AnlProc*)GetEventSource();
    cout << "**** Strip16AnlEvent init for Analysis step" << endl;
  }
  // or is it used from Correlation step as input ?
  else if(CheckEventSource("TGo4FileSource")) {
    fxStrip16FS = (TGo4FileSource*)GetEventSource();
    cout << "**** Strip16AnlEvent init for Correlation step" << endl;
  }
  else rev = 1;
  return rev;
}
//------------------------
Int_t Strip16AnlEvent::Fill()
{
  Int_t rev = 0;
   Clear();
   // check for different source types
   if(fxStrip16CP) fxStrip16CP->Strip16EventAnalysis(this); // process input - analyze and calibrate ...
   if(fxStrip16FS) fxStrip16FS->BuildEvent(this); // Go4 framework method - restore event from tree
   return rev;
}
//-----------------------------
void Strip16AnlEvent::Clear(Option_t *t)
{

            fE_kev   = 0;
 // fTime = 0;

  //fXY_lt=0;
             fTOF_bit = 0;
             fTAC = 0;

//             fxStrip16CP = 0;
//             fxStrip16FS = 0;

            fB_pulse = 0;
            fIDY = 0;
            fIDX = 0;
            fTimeStrip=0;
            fev_num=0;
            fTimeTrig = 0;
            for (int i=0; i<3096; i++){
             fTraceTrig[i]=0;
              fSample[i]=0;
         }
   // fTrig=0;
            
}

void Strip16AnlEvent::ClearEvent()
{

            fE_kev   = 0;
 // fTime = 0;

  //fXY_lt=0;
            fTOF_bit = 0;
            fTAC = 0;
            fxStrip16CP = 0;
            fxStrip16FS = 0;

            fB_pulse = 0;
            fIDY = 0;
            fIDX = 0;
            fTimeStrip=0;
            fev_num=0;
            fTimeTrig = 0;
            for (int i=0; i<3096; i++){
             fTraceTrig[i]=0;
              fSample[i]=0;
         }
   // fTrig=0;
}
//-----------------------------
ClassImp(Strip16AnlEvent)
