#ifndef Strip16ANLFACTORY_H
#define Strip16ANLFACTORY_H

#include "Go4EventServer/Go4EventServer.h"

#include "Strip16UnpackEvent.h"
#include "Strip16AnlEvent.h"
#include "Strip16AnlProc.h"
#include "Go4EventServer/TGo4EventServerFactory.h"

class Strip16AnlFact : public TGo4EventServerFactory {
   public:
      virtual TGo4EventElement   * CreateInputEvent();
      virtual TGo4EventElement   * CreateOutputEvent();
      virtual TGo4EventProcessor * CreateEventProcessor(TGo4EventProcessorParameter* par);
      Strip16AnlFact() ;
      Strip16AnlFact(const Text_t * name);
      virtual ~Strip16AnlFact() ;

ClassDef(Strip16AnlFact,1)
};
#endif //Strip16ANLFACTORY_H
