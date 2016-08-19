# ICF_Report [![Build Status](https://travis-ci.org/loaded02/ICF_Report.svg?branch=master)](https://travis-ci.org/loaded02/ICF_Report)

This is a simple GUI-Programm, which is supposed to help creating a brief ICF Report.
 The ICF Report is used to describe a patient status, e.g. during a medical therapy. 
Check [WHO](http://www.who.int/classifications/icf/en/) for more information about ICF.

## Features:
  * Manage multiple Patients and Therapists with diagnosises etc. 
  * Have for each patient multiple reports corresponding to its date. 
  * An easy to use GUI lets you create your specific reportform with varying numbers of ICF codes and details. 
  * The Programm supports saving content in XML structure on your harddisk for future use. 
  * The result will be a nice formatted output via printing to Pdf.

## BUILD:

  * Qt Creator 3.0.1
  * Based on Qt 5.2.1 (GCC 4.6.1, 64 bit)
  * Ubuntu 13.10, 64 bit

  0. apt-get install qt55base, qt55tools, qt55script, qt55webkit, xsltproc
  1. Clone Repository
  2. mkdir build
  3. cd build
  4. qmake ../ICF_Report.pro -r -spec linux-g++
  5. make
