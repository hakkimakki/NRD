import os
import time
import serial.tools.list_ports
import pandas as pd
import subprocess

#pip3 install pandas pyserial

COM_PORT_Dongle = ''
COM_PORT_Dongle_before = ''

dirpath = os.getcwd() + '\\build'

while(True):
    print('Please Insert Dongle')
    while COM_PORT_Dongle == COM_PORT_Dongle_before:
        #Get the COM Ports
        ports = list(serial.tools.list_ports.comports())
        for p in ports:
            if 'nRF52 SDFU USB' in p.description:
                #print('Assume nRF52 DFU Dongle on: ' + p.device)
                COM_PORT_Dongle = p.device
        time.sleep(1)
    print('Dongle on port:  ' + str(COM_PORT_Dongle) + ' detected.. flashing')
    COM_PORT_Dongle_before = COM_PORT_Dongle
    #Flash the Firmware        
    print("nrfutil dfu usb-serial -pkg " + '"' + dirpath + "\\zephyr.zip" + '"' + " -p " + COM_PORT_Dongle)
    os.system("nrfutil dfu usb-serial -pkg " + '"' + dirpath + "\\zephyr.zip" + '"' + " -p " + COM_PORT_Dongle)






            
