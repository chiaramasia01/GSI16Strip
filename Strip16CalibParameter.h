
// Class declaration in a header file


/* This header file defines a class Strip16CalibParameter for managing calibration parameters, with arrays for calibration coefficients and methods for printing and updating these parameters. It leverages the Go4 and ROOT frameworks. To fully implement and use this class, the corresponding source file (.cpp) is needed, where the member functions will be defined.*/


#ifndef Strip16CALIBPAR_H // These lines prevent multiple inclusions of this header file, which can cause compilation errors.
#define Strip16CALIBPAR_H

#include "Go4StatusBase/TGo4Parameter.h" //  includes the base class TGo4Parameter from the Go4 analysis framework.
#include <iomanip> // includes the standard C++ library header for input/output manipulators

class Strip16CalibParameter : public TGo4Parameter {    // This declares a class Strip16CalibParameter that inherits from TGo4Parameter

public:
          Strip16CalibParameter();  // default constructor
          Strip16CalibParameter(const Text_t *name);  // initializes the object with a name, text_t is a ROOT string
  virtual ~Strip16CalibParameter();  // A virtual destructor to ensure proper cleanup of derived classes
  Int_t   PrintParameter(Text_t *buf, Int_t);  // A method to print the parameter's information
  Bool_t  UpdateFrom(TGo4Parameter *);  // A method to update the current object from another TGo4Parameter object
  
  // 16 is the number of strips 

 Double_t A[4][16], B[4][16];  // Arrays for initial calibration parameters. Double_t is defined in the ROOT header file TROOT.h , equivalent to double in c++

 Double_t postA[4][16], postB[4][16], postC[4][16];  // Arrays for post-calibration parameters

 
 
 
 // This macro is used by ROOT, a data analysis framework commonly used in high-energy physics. 
 //provides ROOT with the necessary information to generate dictionary code for I/O and reflection capabilities. The number 4 indicates the class version.
 
ClassDef(Strip16CalibParameter,4)
};

#endif   // This ends the header guard started at the beginning of the file.
