#include "Strip16AnlFact.h"

//***********************************************************

Strip16AnlFact::Strip16AnlFact(const Text_t * name)
: TGo4EventServerFactory(name)
{}

//***********************************************************

Strip16AnlFact::Strip16AnlFact()
: TGo4EventServerFactory("Strip16 Analysis Fact")
{}

//***********************************************************

Strip16AnlFact::~Strip16AnlFact()
{}

//***********************************************************

//-----------------------------------------------------------

TGo4EventProcessor * Strip16AnlFact::CreateEventProcessor(TGo4EventProcessorParameter* par)
{ 
   Strip16AnlProc* anlproc = new Strip16AnlProc("Strip16AnlProc");
   return anlproc;
}

//-----------------------------------------------------------

TGo4EventElement * Strip16AnlFact::CreateOutputEvent()
{ 
   Strip16AnlEvent* anlevent = new Strip16AnlEvent("Strip16AnlEvent");
   SetOutputEvent(anlevent); // important for some event store implementations!!!
   return anlevent;
}

//-----------------------------------------------------------

TGo4EventElement * Strip16AnlFact::CreateInputEvent()
{  // name is given in Strip16UnpackEvent
   Strip16UnpackEvent* event = new Strip16UnpackEvent();
   return event;
}

//-----------------------------------------------------------
ClassImp(Strip16AnlFact)

//----------------------------END OF GO4 SOURCE FILE ---------------------
