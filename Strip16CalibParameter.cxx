
/* The provided code is the implementation file for the Strip16CalibParameter class, extending the functionality defined in the header file. 
 This class manages calibration parameters, reading them from files, and updating them when necessary. */



#include "Strip16CalibParameter.h"  // Includes the class header file
#include <iostream>  // include standard C++ libraries for input/output and file operations

using namespace std;  // allows using standard namespace identifiers without prefixing them with std::

//------------------------------------------------------------
// This constructor initializes the parameter arrays to zero

Strip16CalibParameter::Strip16CalibParameter()
: TGo4Parameter("AnaOnlineCalPar")
{// Int_t i;
  Int_t j;


	for (j = 0; j < 16; j++)
	 {
	   A[1][j] = 0;
	   B[1][j] = 0;
           postA[1][j] = 0;
           postB[1][j] = 0;
           postC[1][j] = 0;

     }


}

//----------------------------------------------

// This constructor initializes the object with the provided name and reads calibration data from two files (Calib_Energy.dat and Calib_position.dat).
// If the files cannot be opened, it sets default values.

Strip16CalibParameter::Strip16CalibParameter(const Text_t *name)
: TGo4Parameter(name)
{
  //Int_t i;
  Int_t j;  // loop counter
  ifstream    file; // An input file stream object used to read data from files

// Read alpha energy calibration

  file.open("Calib_Energy.dat");
  if (file.fail()) {
    cout << "ERROR: Strip16CalibParameter - Could not open file: Calib_Energy.dat ! (params set to 1 and 0)\n"; // if failing to open the files prints out an error message
    //for (i = 0; i < 4; i++) {
	for (j = 0; j < 16; j++) // for loop among the number of strips
	 {
	   A[1][j] = 1.; // if failing to open file sets default parameters for calibration 
	   B[1][j] = 0.;
	// }
	}
  }
  else {
    cout << "Strip16CalibParameter - reading alpha calibration from: Calib_Energy.dat\n";
    //for (i = 0; i < 4; i++) {
	for (j = 0; j < 16; j++)
	 {
	   file >> A[1][j] >> B[1][j];
	   if (file.fail()) cout << "ERROR reading Calib_Energy.dat\n";
	 }}
 // }
  file.close();

// Read position calibration (same structure as the previous section)
  
   file.open("Calib_position.dat");
  if (file.fail()) {
    cout << "ERROR: Strip16CalibParameter - Could not open file: Calib_position.dat ! (params set to 1 and 0)\n";
    for (j = 0; j < 16; j++) {
      postA[1][j] = 0.;
      postB[1][j] = 1.;
      postC[1][j] = 0.;
    }
  }
  else {
    cout << "Strip16CalibParameter - reading Post calibration from: Calib_position.dat\n";
    for (j = 0; j < 16; j++) {
      file >> postA[1][j] >> postB[1][j] >> postC[1][j];
      if (file.fail()) cout << "ERROR reading Calib_position.dat\n";
    }
  }
  file.close();

}

//-----------------------------------------------
// destructor

Strip16CalibParameter::~Strip16CalibParameter()  // The destructor is empty as there are no dynamically allocated resources to clean up
{}


//-------------------------------

// This method of the class prints the current calibration parameters to the standard output

Int_t Strip16CalibParameter::PrintParameter(Text_t *buf, Int_t)  // the function returns an integer number
{
  //Int_t  i;
  Int_t j;
  cout << "\n AnaOnline Calibration Parameter: " << GetName() << endl;  // getname returns the name of the parameter object

  cout << "Alpha Energy calibration:\n";
  //for (i = 0; i < 4; i++){
	for (j = 0; j < 16; j++)
      { cout << "strip " << j << "  \t A = " << A[1][j] // prints the calibration constants for each strip
	     << "\t B = " << B[1][j] << endl;}

  cout << "Pos t calibration:\n";
  //for (i = 0; i < 4; i++){
        for (j = 0; j < 16; j++)
      { cout << "strip " << j << "  \t A = " << postA[1][j]  // prints post calibration constants for each strip
             << "\t B = " << postB[1][j]
             << "\t C = " << postC[1][j] << endl;
        }
        return 1;
       }
//}


//---------------------------------------------------


/* this method updates the current object parameters */

Bool_t Strip16CalibParameter::UpdateFrom(TGo4Parameter *pp)  // the function returns a boolean variable
{
  if(pp->InheritsFrom("Strip16CalibParameter"))
      //the method first checks if the provided parameter object (pp) is of type Strip16CalibParameter using the InheritsFrom method
      //This ensures that the object being updated from is compatible and contains the expected data structure
  {
   // Int_t i;
    Int_t j;
    Strip16CalibParameter *from = (Strip16CalibParameter *) pp;
    
    //The parameter pp is cast to Strip16CalibParameter * and assigned to the pointer from. This allows access to the Strip16CalibParameter specific members and methods

    //Alpha Energy

	for (j = 0; j < 16; j++)  // Iterates over the 16 strips
	 {
	   A[1][j]  = from->A[1][j];  // For each strip, the alpha energy calibration constants A and B are copied from the from object to the current object
	   B[1][j]  = from->B[1][j];

	   cout << "Strip16CalibParameter - Parameter : " << GetName() << " UPDATED\n";
	 }

     //Pos calib

        for (j = 0; j < 16; j++)
         {
           postA[1][j]  = from->postA[1][j];
           postB[1][j]  = from->postB[1][j];
           postC[1][j]  = from->postC[1][j];

           cout << "Strip16CalibParameter - Parameter : " << GetName() << " UPDATED\n"; 
         }
  }
    else {
      cout << "ERROR: Strip16CalibParameter - Wrong parameter object: " << pp->ClassName() << endl;}  // If the provided parameter object pp does not inherit from Strip16CalibParameter, an error message is printed 


  return kTRUE;
}

ClassImp(Strip16CalibParameter)  // The ClassImp ROOT macro is placed in the implementation file (source file) and provides the necessary implementation for the class metadata defined by ClassDef.
