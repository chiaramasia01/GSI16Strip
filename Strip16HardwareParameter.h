
// parameter holding various data needed for program running


#ifndef SHARDWAREPAR_H
#define SHARDWAREPAR_H

#include "Go4StatusBase/TGo4Parameter.h"
using namespace std;

class Strip16HardwareParameter : public TGo4Parameter {

public:
           Strip16HardwareParameter();
           Strip16HardwareParameter(const char* name);
  virtual ~Strip16HardwareParameter();
  Int_t PrintParameter(const char* n, Int_t);
  Bool_t UpdateFrom(TGo4Parameter *);

  int IsData(ifstream &f);

  Bool_t    fNewSetup;            // true if amux setup is used
	Int_t			fRunID;								// Run ID
	Bool_t		fHW_PulseBit;					// is hardware pause bit used?
	Int_t			fUnpackFilterLevel;		// level for rejecting of the events in Unpack Routine 
	Int_t			fAnalFilterLevel;			// level for rejecting of the events in Analysis part

ClassDef(Strip16HardwareParameter,1)
};

#endif //SPAR_H
