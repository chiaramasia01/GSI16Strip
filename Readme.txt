Readme

How to perform a new calibration

- Extract data using the Strip16AnalProc.cxx which produces a text file. Change the name of the outfile everytime otherwise it gets overwritten.
- When extracting the data for the calibration in the file Strip16CalibParameter.cxx the reading files should be set to Calib_Energy_blank.dat and Calib_position_blank.dat
- With the text file the first step of calibration can be performed. This step produces a Calib_position.dat file that can be exchanged with the blank file in Strip16CalibParameter.cxx
- Once the first file is changed go to GO4 and extract data from the energy 1d histogram of each strip as ASCII file. Use this to perform the last step of calibration
- This step produces a Calib_Energy.dat file to be exchanged with the blank in Strip16CalibParameter.cxx

Files cointained in the repository:

- NewCalibration.py: class file that contains the functions to perform the calibration
- main_calibration.ipynb: main file. Also shows the result of calibration for all strips.