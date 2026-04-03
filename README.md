# LemonHealth

## Introduction
Command-line based health calculator 
which can calculate various health functions 
and classify the results according to various 
standards by WHO and regional standards 
using age/gender/regional data inputs and 
gives health advice related to the classification 
data outputs from the program.

_**Note:**_ Classifications are still are at basic level, and
simply classifying using the supported functions. More advanced classifications
are expected to be done using the all measurements.

This program is built for running on Microsoft Windows,
using C. Previous features from the Python version ([lemonhealth-python](https://github.com/lochanalmr/lemonhealth-python))
are directly ported to C. 

**_New features are being added only to this version_**.

## Supported functions:-
- **BMI** (Body Mass Index)
- **BAI** (Body Adiposity Index)
- **WHR** (Waist to Hip Ratio)
- **RFM** (Relative Fat Mass)
- **MM** (MultiMeasure) 

_MultiMeasure is a specialized function that can be used to 
calculate all supported functions and display a summary report._

The summary report for MultiMeasure will be automatically exported to the same folder the program is running from. (since version 1.2)
(File name format: lh-mm-report-DATE-TIME)

## Using the program:-
- Make sure to input characters capitalized, to prevent repeated input requests. 
- If '**Metric**' unit system is selected
make sure to only input measurements in **_meters_** and **_kilograms_**.
- If '**Imperial**' unit system is selected, make sure to only input measurements
in **_inches_** and **_pounds_**.
- **Read in-program instructions and follow them.**

## Calculation and classification guidelines adapted from:-
- https://www.nature.com/articles/s41598-018-29362-1
- https://www.ncbi.nlm.nih.gov/books/NBK279167/
- https://www.nature.com/articles/s41366-019-0516-8
- https://pmc.ncbi.nlm.nih.gov/articles/PMC5571887/
- https://www.who.int/publications/i/item/9789241501491
- https://www.omnicalculator.com/health/
