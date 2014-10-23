#!/usr/bin/env python

from rpisoc import *  
  
RPiSoC('SPI')  
  
My_SAR_ADC = ADC('SAR1')  
  
#ADC value when scale is idle  
ScaleOffset = 2276  

#Set average to offset for faster initial state  
Measurements = 10  
Total = 0
Weight = 0

#Analog value change per gram  
AdcCountPerGram = 2.91045  
  
for x in range (0, Measurements):

  My_SAR_ADC.Start()
  My_SAR_ADC.StartConvert()
  while not My_SAR_ADC.IsEndConversion():  
    pass  
  
  Counts = My_SAR_ADC.GetResult()  

  My_SAR_ADC.StopConvert()  
  My_SAR_ADC.Stop()  
    
  Grams = ((Counts-ScaleOffset) / AdcCountPerGram)  
  Total = Total + Grams
  x = x + 1
      
Weight = Total/Measurements

if Weight > 0:
  print(Weight)
