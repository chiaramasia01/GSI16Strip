
// Strip16 UNPACK FACTORY - definition
// management of UNPACK step

#ifndef Strip16UNPACKFACTORY_H
#define Strip16UNPACKFACTORY_H

#include "Go4EventServer/Go4EventServer.h"
#include "Strip16UnpackEvent.h"
#include "Strip16UnpackProc.h"
#include "Go4EventServer/TGo4EventServerFactory.h"

class Strip16UnpackEvent;

class Strip16UnpackFact : public TGo4EventServerFactory {
   public:
      virtual TGo4EventElement   * CreateOutputEvent();
      virtual TGo4EventProcessor * CreateEventProcessor(TGo4EventProcessorParameter* par);
      Strip16UnpackFact();
      Strip16UnpackFact(const Text_t * name);
      virtual ~Strip16UnpackFact();

ClassDef(Strip16UnpackFact,1)
};
#endif //Strip16UNPACKFACTORY_H

