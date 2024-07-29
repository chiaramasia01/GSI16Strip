
/*
Stano:
27.3.2005 - Only small change... Strip16-hardware.dat is used as
a input file here. The incorrect printouts were fixed.
*/

#include "Strip16HardwareParameter.h"
#include <fstream>
#include <iostream>

using namespace std;


//***********************************************************
// default constructor

Strip16HardwareParameter::Strip16HardwareParameter()
: TGo4Parameter("Strip16HardwareParameter")
{ 
  // cout << "Strip16HardwareParameter - Default constructor used, parameters set to 0\n";
  fNewSetup = true;
	fRunID = 263;
	fHW_PulseBit = 1;
	fUnpackFilterLevel = 0;
	fAnalFilterLevel = 0;
 
  
}

//***********************************************************
// constructor

Strip16HardwareParameter::Strip16HardwareParameter(const char* name)
: TGo4Parameter(name)
{
  ifstream    file;
  
  file.open("Strip16-hardware.dat");
  if (file.fail())
  {
    cout << "ERROR: Strip16HardwareParameter - Could not open file: Strip16-hardware.dat ! Params set to 0\n";
    fNewSetup = true;
		fRunID = 263; 
		fHW_PulseBit = 0;
		fUnpackFilterLevel = 0;
		fAnalFilterLevel = 0;	
  }
  else 
  {
    cout << "Strip16HardwareParameter - reading from : Strip16-hardware.dat\n";
    if (IsData(file)) file >> fNewSetup;
		if (IsData(file)) file >> fRunID;
		if (IsData(file)) file >> fHW_PulseBit;
		if (IsData(file)) file >> fUnpackFilterLevel;
		if (IsData(file)) file >> fAnalFilterLevel;
    if (file.fail()) cout << "ERROR reading Strip16-hardware.dat\n";
  }
  file.close();
}

//***********************************************************
// default destructor

Strip16HardwareParameter::~Strip16HardwareParameter()
{
}

//***********************************************************

//-----------------------------------------------------------

Int_t Strip16HardwareParameter::PrintParameter(const char* n, Int_t){
  cout << "Parameter " << GetName() << " : \n";
  cout << "New setup is: " << fNewSetup << " : \n";
	cout << "Run ID is: " <<  fRunID << endl;
	if (fHW_PulseBit) cout << "Hardware pause bit is being used... \n";
	else cout << "Software pause bit is being used ... \n";
	cout << "Level for Unpac Filter is: " << fUnpackFilterLevel << endl;
	cout << "Level for Analysis Filter is: " << fAnalFilterLevel << endl;
  return 0;
}

//-----------------------------------------------------------
// this should not be implemented because it will freeze the analysis
// when the parameter is updates (graphs are created in constructor of
// analysis step and this is called only once at the start of analysis)

Bool_t Strip16HardwareParameter::UpdateFrom(TGo4Parameter *pp){
 if(pp->InheritsFrom("Strip16HardwareParameter"))
  {
    Strip16HardwareParameter * from = (Strip16HardwareParameter *) pp;
    fNewSetup    = from->fNewSetup;
    fHW_PulseBit = from->fHW_PulseBit;
		fUnpackFilterLevel = from->fUnpackFilterLevel;
    cout << "Strip16HardwareParameter - Parameter : " << GetName() << " UPDATED\n";
  }
  else
    cout << "Wrong parameter object: " << pp->ClassName() << endl;
  //cout << "CAN NOT BE UPDATED ! Change file Strip16-input.dat and restart analysis.\n";
  return kTRUE;
}

// ==========================================================
// function IsData skips comment lines (begining with #) in file f

int Strip16HardwareParameter::IsData(ifstream &f) {
  char dum;
  char dumstr[300];
  int retval = 0;

  /* 'operator >>' does not read End-of-line, therefore check if read
      character is not EOL (10) */
  do {
    dum = f.get();
    if (dum == '#')    // comment line => read whole line and throw it away
      f.getline(dumstr,300);
  }
  while ((dum == '#') || ((int)dum == 10));

  f.unget();   // go one character back
  retval = 1;
  return retval;
}

// ----------------------------------------------------------
ClassImp(Strip16HardwareParameter)


