from struct import calcsize
from network import LoRa
import socket
import machine
import time
import pycom
import ustruct as struct
from LIS2HH12 import LIS2HH12
from SI7006A20 import SI7006A20
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2,ALTITUDE,PRESSURE


lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
lora.init(mode=LoRa.LORA, region=LoRa.EU868,  bandwidth=LoRa.BW_125KHZ, sf=7, preamble=8, coding_rate=LoRa.CODING_4_5)
# for new boards (black)
from pycoproc_2 import Pycoproc
py = Pycoproc()
pre = MPL3115A2(py,mode=PRESSURE) # Returns pressure in Pa.
temp = SI7006A20(py)
g = 4
# for old boards (green, blue)
#from pycoproc_1 import Pycoproc
#py = Pycoproc(Pycoproc.PYSENSE)

# Start your code here...
pycom.heartbeat(False)
while True:
    
    pres = int(pre.pressure()/100)
    tempe = temp.temperature()
    data = struct.pack('!BfH', g, tempe, pres)
    s.setblocking(True)
    s.send(data)
    time.sleep(15)
