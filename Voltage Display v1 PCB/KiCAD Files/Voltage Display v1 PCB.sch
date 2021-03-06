EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:matts_components
LIBS:Voltage Display v1 PCB-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "9 jul 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1600 3150 1600 3100
Wire Wire Line
	9850 2550 10450 2550
Wire Wire Line
	10450 2100 10300 2100
Wire Wire Line
	10450 2100 10450 2250
Connection ~ 7150 3900
Wire Wire Line
	7150 3900 7150 3500
Wire Wire Line
	7150 3500 6100 3500
Wire Wire Line
	6100 3500 6100 3600
Wire Wire Line
	6100 3600 5700 3600
Connection ~ 5850 3450
Wire Wire Line
	5700 3450 5850 3450
Wire Wire Line
	1600 2550 1600 2700
Wire Wire Line
	10300 2100 10300 2200
Connection ~ 3400 3600
Wire Wire Line
	3700 3600 3150 3600
Wire Wire Line
	3700 3600 3700 3400
Wire Wire Line
	2100 3100 2100 2950
Wire Wire Line
	3400 2800 3600 2800
Connection ~ 3300 3600
Wire Wire Line
	3300 3700 3300 3600
Wire Wire Line
	3150 3050 3150 2900
Wire Wire Line
	4800 2400 4800 2700
Wire Wire Line
	5800 3250 5800 4000
Wire Wire Line
	5800 4000 5950 4000
Wire Wire Line
	5950 3350 5950 3800
Wire Wire Line
	5950 3900 5850 3900
Wire Wire Line
	5850 3900 5850 3300
Wire Wire Line
	6750 4000 6850 4000
Wire Wire Line
	6850 4000 6850 4100
Wire Wire Line
	4800 1800 4800 2000
Wire Wire Line
	6750 3800 6850 3800
Wire Wire Line
	3150 3600 3150 3450
Wire Wire Line
	3400 3600 3400 3450
Connection ~ 3400 2900
Wire Wire Line
	3150 2900 3700 2900
Wire Wire Line
	3700 2900 3700 3000
Wire Wire Line
	4800 1950 5050 1950
Wire Wire Line
	4800 2450 5050 2450
Wire Wire Line
	1700 2650 1600 2650
Connection ~ 1600 2650
Wire Wire Line
	2750 2750 2750 2600
Connection ~ 2750 2650
Wire Wire Line
	5950 3750 5700 3750
Connection ~ 5950 3750
Wire Wire Line
	5700 3900 5800 3900
Connection ~ 5800 3900
Wire Wire Line
	10450 2350 10400 2350
Wire Wire Line
	10400 2350 10400 2250
Wire Wire Line
	10400 2250 10450 2250
Wire Wire Line
	10050 2650 10450 2650
Wire Wire Line
	2750 3200 2750 3150
Wire Wire Line
	6850 3800 6850 3750
Wire Wire Line
	10100 2450 10450 2450
Wire Wire Line
	3400 2000 3400 2150
NoConn ~ 1500 4500
NoConn ~ 1500 4350
NoConn ~ 1500 4200
NoConn ~ 1500 4050
Text Notes 1300 4700 0    60   ~ 0
Mounting holes
$Comp
L CONN_1 MH4
U 1 1 516547D7
P 1650 4500
F 0 "MH4" H 1730 4500 40  0000 L CNN
F 1 "CONN_1" H 1650 4555 30  0001 C CNN
F 2 "" H 1650 4500 60  0001 C CNN
F 3 "" H 1650 4500 60  0001 C CNN
	1    1650 4500
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 MH3
U 1 1 516547D4
P 1650 4350
F 0 "MH3" H 1730 4350 40  0000 L CNN
F 1 "CONN_1" H 1650 4405 30  0001 C CNN
F 2 "" H 1650 4350 60  0001 C CNN
F 3 "" H 1650 4350 60  0001 C CNN
	1    1650 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 MH2
U 1 1 516547D2
P 1650 4200
F 0 "MH2" H 1730 4200 40  0000 L CNN
F 1 "CONN_1" H 1650 4255 30  0001 C CNN
F 2 "" H 1650 4200 60  0001 C CNN
F 3 "" H 1650 4200 60  0001 C CNN
	1    1650 4200
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 MH1
U 1 1 516547CF
P 1650 4050
F 0 "MH1" H 1730 4050 40  0000 L CNN
F 1 "CONN_1" H 1650 4105 30  0001 C CNN
F 2 "" H 1650 4050 60  0001 C CNN
F 3 "" H 1650 4050 60  0001 C CNN
	1    1650 4050
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P3
U 1 1 51652149
P 10800 2500
F 0 "P3" V 10750 2500 60  0000 C CNN
F 1 "FTDI_OUTPUT" V 10850 2500 60  0000 C CNN
F 2 "" H 10800 2500 60  0001 C CNN
F 3 "" H 10800 2500 60  0001 C CNN
	1    10800 2500
	1    0    0    -1  
$EndComp
Text GLabel 5700 3900 0    60   Input ~ 0
RESET
Text GLabel 5700 3750 0    60   Input ~ 0
MISO
Text GLabel 5700 3600 0    60   Input ~ 0
MOSI
Text GLabel 5700 3450 0    60   Output ~ 0
SCK
$Comp
L CONN_3 K1
U 1 1 5164624D
P 9350 3050
F 0 "K1" V 9300 3050 50  0000 C CNN
F 1 "IO_0-2" V 9400 3050 40  0000 C CNN
F 2 "" H 9350 3050 60  0001 C CNN
F 3 "" H 9350 3050 60  0001 C CNN
	1    9350 3050
	1    0    0    -1  
$EndComp
Text Notes 10000 1950 0    60   ~ 0
Serial Connection
Text GLabel 9850 2550 0    60   Output ~ 0
Rx
Text GLabel 10050 2650 0    60   Input ~ 0
Tx
$Comp
L GND #PWR01
U 1 1 51642DC5
P 10300 2200
F 0 "#PWR01" H 10300 2200 30  0001 C CNN
F 1 "GND" H 10300 2130 30  0001 C CNN
F 2 "" H 10300 2200 60  0001 C CNN
F 3 "" H 10300 2200 60  0001 C CNN
	1    10300 2200
	1    0    0    -1  
$EndComp
Text Notes 6050 4300 0    60   ~ 0
Programming port
Text Notes 5950 1250 0    60   ~ 0
MicroController ATTiny
Text Notes 1950 2350 0    60   ~ 0
5V Power Supply
Text Notes 3000 3900 0    60   ~ 0
Voltage Measurement
$Comp
L ZENER D2
U 1 1 50D5DC34
P 3700 3200
F 0 "D2" H 3700 3300 50  0000 C CNN
F 1 "5v1" H 3700 3100 40  0000 C CNN
F 2 "" H 3700 3200 60  0001 C CNN
F 3 "" H 3700 3200 60  0001 C CNN
	1    3700 3200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 50D5DBD7
P 2750 3200
F 0 "#PWR02" H 2750 3200 30  0001 C CNN
F 1 "GND" H 2750 3130 30  0001 C CNN
F 2 "" H 2750 3200 60  0001 C CNN
F 3 "" H 2750 3200 60  0001 C CNN
	1    2750 3200
	1    0    0    -1  
$EndComp
Text GLabel 3600 2800 2    60   Output ~ 0
V
Text GLabel 8150 2550 2    60   Input ~ 0
Rx
Text GLabel 8100 1550 2    60   Input ~ 0
V
Text GLabel 7950 2450 2    60   Output ~ 0
Tx
$Comp
L GND #PWR03
U 1 1 50D5D9A9
P 4800 2700
F 0 "#PWR03" H 4800 2700 30  0001 C CNN
F 1 "GND" H 4800 2630 30  0001 C CNN
F 2 "" H 4800 2700 60  0001 C CNN
F 3 "" H 4800 2700 60  0001 C CNN
	1    4800 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 50D5D9A6
P 1600 3150
F 0 "#PWR04" H 1600 3150 30  0001 C CNN
F 1 "GND" H 1600 3080 30  0001 C CNN
F 2 "" H 1600 3150 60  0001 C CNN
F 3 "" H 1600 3150 60  0001 C CNN
	1    1600 3150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 50D5D9A4
P 2750 2600
F 0 "#PWR05" H 2750 2690 20  0001 C CNN
F 1 "+5V" H 2750 2690 30  0000 C CNN
F 2 "" H 2750 2600 60  0001 C CNN
F 3 "" H 2750 2600 60  0001 C CNN
	1    2750 2600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 50D5D99E
P 4800 1800
F 0 "#PWR06" H 4800 1890 20  0001 C CNN
F 1 "+5V" H 4800 1890 30  0000 C CNN
F 2 "" H 4800 1800 60  0001 C CNN
F 3 "" H 4800 1800 60  0001 C CNN
	1    4800 1800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 50D5D99A
P 6850 3750
F 0 "#PWR07" H 6850 3840 20  0001 C CNN
F 1 "+5V" H 6850 3840 30  0000 C CNN
F 2 "" H 6850 3750 60  0001 C CNN
F 3 "" H 6850 3750 60  0001 C CNN
	1    6850 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 50D5D97E
P 6850 4100
F 0 "#PWR08" H 6850 4100 30  0001 C CNN
F 1 "GND" H 6850 4030 30  0001 C CNN
F 2 "" H 6850 4100 60  0001 C CNN
F 3 "" H 6850 4100 60  0001 C CNN
	1    6850 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 50D5D741
P 3300 3700
F 0 "#PWR09" H 3300 3700 30  0001 C CNN
F 1 "GND" H 3300 3630 30  0001 C CNN
F 2 "" H 3300 3700 60  0001 C CNN
F 3 "" H 3300 3700 60  0001 C CNN
	1    3300 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 50D5D73A
P 2100 3100
F 0 "#PWR010" H 2100 3100 30  0001 C CNN
F 1 "GND" H 2100 3030 30  0001 C CNN
F 2 "" H 2100 3100 60  0001 C CNN
F 3 "" H 2100 3100 60  0001 C CNN
	1    2100 3100
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 50D5D72D
P 3150 3250
F 0 "C3" H 3200 3350 50  0000 L CNN
F 1 "100n" H 2950 3150 50  0000 L CNN
F 2 "" H 3150 3250 60  0001 C CNN
F 3 "" H 3150 3250 60  0001 C CNN
	1    3150 3250
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 50D5D70C
P 1600 2350
F 0 "D1" H 1600 2450 40  0000 C CNN
F 1 "1N4001" H 1600 2250 40  0000 C CNN
F 2 "" H 1600 2350 60  0001 C CNN
F 3 "" H 1600 2350 60  0001 C CNN
	1    1600 2350
	0    1    1    0   
$EndComp
$Comp
L CONN_3X2 P2
U 1 1 50D46DA8
P 6350 3950
F 0 "P2" H 6350 4200 50  0000 C CNN
F 1 "ISP" V 6350 4000 40  0000 C CNN
F 2 "" H 6350 3950 60  0001 C CNN
F 3 "" H 6350 3950 60  0001 C CNN
	1    6350 3950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 50D36545
P 3400 3200
F 0 "R2" V 3480 3200 50  0000 C CNN
F 1 "R" V 3400 3200 50  0000 C CNN
F 2 "" H 3400 3200 60  0001 C CNN
F 3 "" H 3400 3200 60  0001 C CNN
	1    3400 3200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 50D36543
P 3400 2400
F 0 "R1" V 3480 2400 50  0000 C CNN
F 1 "R" V 3400 2400 50  0000 C CNN
F 2 "" H 3400 2400 60  0001 C CNN
F 3 "" H 3400 2400 60  0001 C CNN
	1    3400 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 50D3652B
P 850 2450
F 0 "P1" V 800 2450 40  0000 C CNN
F 1 "INPUT" V 900 2450 40  0000 C CNN
F 2 "" H 850 2450 60  0001 C CNN
F 3 "" H 850 2450 60  0001 C CNN
	1    850  2450
	-1   0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 50D363C9
P 4800 2200
F 0 "C4" H 4850 2300 50  0000 L CNN
F 1 "100n" H 4850 2100 50  0000 L CNN
F 2 "" H 4800 2200 60  0001 C CNN
F 3 "" H 4800 2200 60  0001 C CNN
	1    4800 2200
	1    0    0    1   
$EndComp
$Comp
L 7805 U1
U 1 1 50D3634F
P 2100 2700
F 0 "U1" H 2250 2504 60  0000 C CNN
F 1 "7805/LM2931" H 2100 2900 60  0000 C CNN
F 2 "" H 2100 2700 60  0001 C CNN
F 3 "" H 2100 2700 60  0001 C CNN
	1    2100 2700
	1    0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 50D36323
P 2750 2950
F 0 "C2" H 2800 3050 50  0000 L CNN
F 1 "100u" H 2800 2850 50  0000 L CNN
F 2 "" H 2750 2950 60  0001 C CNN
F 3 "" H 2750 2950 60  0001 C CNN
	1    2750 2950
	1    0    0    -1  
$EndComp
Text Notes 10050 2050 0    60   ~ 0
FTDI CONNECTION
$Comp
L CP1 C1
U 1 1 50D3631F
P 1600 2900
F 0 "C1" H 1650 3000 50  0000 L CNN
F 1 "10uf" H 1650 2800 50  0000 L CNN
F 2 "" H 1600 2900 60  0001 C CNN
F 3 "" H 1600 2900 60  0001 C CNN
	1    1600 2900
	1    0    0    -1  
$EndComp
NoConn ~ 10450 2750
Wire Wire Line
	2500 2650 2750 2650
Wire Wire Line
	3400 2650 3400 2950
Connection ~ 3400 2800
$Comp
L +5V #PWR011
U 1 1 538A0B77
P 10100 2350
F 0 "#PWR011" H 10100 2440 20  0001 C CNN
F 1 "+5V" H 10100 2440 30  0000 C CNN
F 2 "" H 10100 2350 60  0000 C CNN
F 3 "" H 10100 2350 60  0000 C CNN
	1    10100 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2450 10100 2350
Connection ~ 4800 2450
Connection ~ 4800 1950
$Comp
L RGB_LED D3
U 1 1 538A0D70
P 9750 4400
F 0 "D3" H 9600 4550 50  0000 C CNN
F 1 "RGB_LED" H 9600 3950 50  0000 C CNN
F 2 "~" H 9750 4400 60  0000 C CNN
F 3 "~" H 9750 4400 60  0000 C CNN
	1    9750 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1200 2350 1200 2000
Wire Wire Line
	1200 2000 3950 2000
Wire Wire Line
	1600 2000 1600 2150
$Comp
L GND #PWR012
U 1 1 538A0E57
P 1200 2750
F 0 "#PWR012" H 1200 2750 30  0001 C CNN
F 1 "GND" H 1200 2680 30  0001 C CNN
F 2 "" H 1200 2750 60  0000 C CNN
F 3 "" H 1200 2750 60  0000 C CNN
	1    1200 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2750 1200 2550
Connection ~ 1600 2000
$Comp
L +5V #PWR013
U 1 1 538A1024
P 10400 4400
F 0 "#PWR013" H 10400 4490 20  0001 C CNN
F 1 "+5V" H 10400 4490 30  0000 C CNN
F 2 "" H 10400 4400 60  0000 C CNN
F 3 "" H 10400 4400 60  0000 C CNN
	1    10400 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10250 4550 10400 4550
Wire Wire Line
	10400 4550 10400 4400
$Comp
L R R3
U 1 1 538A109E
P 9200 4400
F 0 "R3" V 9280 4400 50  0000 C CNN
F 1 "120" V 9200 4400 50  0000 C CNN
F 2 "" H 9200 4400 60  0000 C CNN
F 3 "" H 9200 4400 60  0000 C CNN
	1    9200 4400
	0    1    -1   0   
$EndComp
$Comp
L R R4
U 1 1 538A10AD
P 9200 4550
F 0 "R4" V 9280 4550 50  0000 C CNN
F 1 "270" V 9200 4550 50  0000 C CNN
F 2 "" H 9200 4550 60  0000 C CNN
F 3 "" H 9200 4550 60  0000 C CNN
	1    9200 4550
	0    1    -1   0   
$EndComp
$Comp
L R R5
U 1 1 538A10BC
P 9200 4700
F 0 "R5" V 9280 4700 50  0000 C CNN
F 1 "120" V 9200 4700 50  0000 C CNN
F 2 "" H 9200 4700 60  0000 C CNN
F 3 "" H 9200 4700 60  0000 C CNN
	1    9200 4700
	0    1    -1   0   
$EndComp
Wire Wire Line
	9600 4400 9450 4400
Wire Wire Line
	9600 4550 9450 4550
Wire Wire Line
	9600 4700 9450 4700
Wire Wire Line
	8950 4400 8500 4400
Wire Wire Line
	8950 4550 8450 4550
Wire Wire Line
	8400 4700 8950 4700
Wire Wire Line
	8400 2250 8400 4700
$Comp
L ATTINY84-P IC1
U 1 1 538A0E9B
P 6300 2150
F 0 "IC1" H 5550 2900 60  0000 C CNN
F 1 "ATTINY84-P" H 6850 1400 60  0000 C CNN
F 2 "DIP14" H 5600 1400 60  0001 C CNN
F 3 "" H 6300 2150 60  0000 C CNN
	1    6300 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1950 5050 1550
Wire Wire Line
	5050 1550 5250 1550
Wire Wire Line
	5050 2450 5050 2750
Wire Wire Line
	5050 2750 5250 2750
Wire Wire Line
	5850 3300 7500 3300
Wire Wire Line
	7500 3300 7500 1950
Wire Wire Line
	7350 1950 8700 1950
Wire Wire Line
	6750 3900 7550 3900
Wire Wire Line
	7550 3900 7550 2150
Wire Wire Line
	7350 2150 8450 2150
Wire Wire Line
	5950 3350 7600 3350
Wire Wire Line
	7600 3350 7600 2050
Wire Wire Line
	7350 2050 8500 2050
Wire Wire Line
	5800 3250 7450 3250
Wire Wire Line
	7450 3250 7450 2750
Wire Wire Line
	7450 2750 7350 2750
Wire Wire Line
	7350 2450 7950 2450
Wire Wire Line
	7350 2550 8150 2550
Wire Wire Line
	7350 1550 8100 1550
Wire Wire Line
	7350 2250 8400 2250
Wire Wire Line
	8450 2150 8450 4550
Connection ~ 7550 2150
Wire Wire Line
	8500 2050 8500 4400
Connection ~ 7600 2050
$Comp
L POT RV1
U 1 1 538A1701
P 9100 1600
F 0 "RV1" H 9100 1500 50  0000 C CNN
F 1 "POT" H 9100 1600 50  0000 C CNN
F 2 "" H 9100 1600 60  0000 C CNN
F 3 "" H 9100 1600 60  0000 C CNN
	1    9100 1600
	0    -1   -1   0   
$EndComp
$Comp
L POT RV2
U 1 1 538A1710
P 9400 2000
F 0 "RV2" H 9400 1900 50  0000 C CNN
F 1 "POT" H 9400 2000 50  0000 C CNN
F 2 "" H 9400 2000 60  0000 C CNN
F 3 "" H 9400 2000 60  0000 C CNN
	1    9400 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7350 1650 8650 1650
Wire Wire Line
	8650 1650 8650 1600
Wire Wire Line
	8650 1600 8950 1600
Wire Wire Line
	7350 1750 8900 1750
Wire Wire Line
	8900 1750 8900 2000
Wire Wire Line
	8900 2000 9250 2000
Wire Wire Line
	9100 1850 9100 2450
Wire Wire Line
	9100 2450 9400 2450
Wire Wire Line
	9400 2450 9400 2250
Wire Wire Line
	9100 1350 9100 1200
Wire Wire Line
	9100 1200 9400 1200
Wire Wire Line
	9400 1200 9400 1750
$Comp
L +5V #PWR014
U 1 1 538A18C1
P 9250 1150
F 0 "#PWR014" H 9250 1240 20  0001 C CNN
F 1 "+5V" H 9250 1240 30  0000 C CNN
F 2 "" H 9250 1150 60  0000 C CNN
F 3 "" H 9250 1150 60  0000 C CNN
	1    9250 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 538A18D0
P 9250 2550
F 0 "#PWR015" H 9250 2550 30  0001 C CNN
F 1 "GND" H 9250 2480 30  0001 C CNN
F 2 "" H 9250 2550 60  0000 C CNN
F 3 "" H 9250 2550 60  0000 C CNN
	1    9250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 2550 9250 2450
Connection ~ 9250 2450
Wire Wire Line
	9250 1150 9250 1200
Connection ~ 9250 1200
Wire Wire Line
	7350 1850 8800 1850
Wire Wire Line
	8800 1850 8800 2950
Wire Wire Line
	8800 2950 9000 2950
Wire Wire Line
	7350 2650 8600 2650
Wire Wire Line
	8600 2650 8600 3150
Wire Wire Line
	8600 3150 9000 3150
Wire Wire Line
	9000 3050 8700 3050
Wire Wire Line
	8700 3050 8700 1950
Connection ~ 7500 1950
$Comp
L +5V #PWR016
U 1 1 538C9C81
P 8850 3400
F 0 "#PWR016" H 8850 3490 20  0001 C CNN
F 1 "+5V" H 8850 3490 30  0000 C CNN
F 2 "" H 8850 3400 60  0000 C CNN
F 3 "" H 8850 3400 60  0000 C CNN
	1    8850 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 538C9C90
P 8900 3600
F 0 "#PWR017" H 8900 3600 30  0001 C CNN
F 1 "GND" H 8900 3530 30  0001 C CNN
F 2 "" H 8900 3600 60  0000 C CNN
F 3 "" H 8900 3600 60  0000 C CNN
	1    8900 3600
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K2
U 1 1 538C9C9F
P 9350 3400
F 0 "K2" V 9300 3400 50  0000 C CNN
F 1 "PWR" V 9400 3400 40  0000 C CNN
F 2 "" H 9350 3400 60  0000 C CNN
F 3 "" H 9350 3400 60  0000 C CNN
	1    9350 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 3300 8950 3300
Wire Wire Line
	8950 3300 8950 3200
Wire Wire Line
	8950 3200 3950 3200
Wire Wire Line
	3950 3200 3950 2000
Connection ~ 3400 2000
Wire Wire Line
	8850 3400 9000 3400
Wire Wire Line
	9000 3500 8900 3500
Wire Wire Line
	8900 3500 8900 3600
$EndSCHEMATC
