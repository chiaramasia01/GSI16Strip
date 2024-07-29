
// Strip16 UNPACK FACTORY - implementation
// management of UNPACK step

#include "Strip16UnpackFact.h"

//***********************************************************
// Constructor

Strip16UnpackFact::Strip16UnpackFact(const Text_t * name)
: TGo4EventServerFactory(name)
{
}

//***********************************************************
// Default constructor

Strip16UnpackFact::Strip16UnpackFact()
: TGo4EventServerFactory("Strip16 Event Fact")
{ 
}

//***********************************************************
// Default destructor

Strip16UnpackFact::~Strip16UnpackFact()
{ 
}
//***********************************************************

//-----------------------------------------------------------

TGo4EventProcessor * Strip16UnpackFact::CreateEventProcessor(TGo4EventProcessorParameter* par)
{ 
   Strip16UnpackProc* proc = new Strip16UnpackProc("Strip16UnpackProc");
   return proc;
}

//-----------------------------------------------------------

TGo4EventElement * Strip16UnpackFact::CreateOutputEvent()
{ // name is given in Strip16UnpackEvent
   Strip16UnpackEvent * event = new Strip16UnpackEvent();
   SetOutputEvent(event); // important for some event store implementations!!!
   return event;
}

//-----------------------------------------------------------
ClassImp(Strip16UnpackFact)

