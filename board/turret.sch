EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F1:STM32F103CBTx U1
U 1 1 60028286
P 1950 5350
F 0 "U1" H 1900 3761 50  0000 C CNN
F 1 "STM32F103CBTx" H 1900 3670 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 1350 3950 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 1950 5350 50  0001 C CNN
	1    1950 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR08
U 1 1 6002C0B3
P 2050 7300
F 0 "#PWR08" H 2050 7050 50  0001 C CNN
F 1 "GNDA" H 2055 7127 50  0000 C CNN
F 2 "" H 2050 7300 50  0001 C CNN
F 3 "" H 2050 7300 50  0001 C CNN
	1    2050 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR04
U 1 1 6002C91B
P 1750 7300
F 0 "#PWR04" H 1750 7050 50  0001 C CNN
F 1 "GNDD" H 1754 7145 50  0000 C CNN
F 2 "" H 1750 7300 50  0001 C CNN
F 3 "" H 1750 7300 50  0001 C CNN
	1    1750 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 6850 2050 7300
Wire Wire Line
	1750 6850 1750 6950
Wire Wire Line
	1850 6850 1850 6950
Wire Wire Line
	1850 6950 1750 6950
Connection ~ 1750 6950
Wire Wire Line
	1750 6950 1750 7150
Wire Wire Line
	1950 6850 1950 7150
Wire Wire Line
	1950 7150 1750 7150
Connection ~ 1750 7150
Wire Wire Line
	1750 7150 1750 7300
$Comp
L power:+3V3 #PWR07
U 1 1 600494DA
P 2050 2600
F 0 "#PWR07" H 2050 2450 50  0001 C CNN
F 1 "+3V3" H 2065 2773 50  0000 C CNN
F 2 "" H 2050 2600 50  0001 C CNN
F 3 "" H 2050 2600 50  0001 C CNN
	1    2050 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C5
U 1 1 6004D32A
P 2250 3700
F 0 "C5" V 2475 3700 50  0000 C CNN
F 1 "1u" V 2384 3700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2250 3700 50  0001 C CNN
F 3 "~" H 2250 3700 50  0001 C CNN
	1    2250 3700
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C6
U 1 1 6004DDC1
P 2450 3400
F 0 "C6" V 2675 3400 50  0000 C CNN
F 1 "10n" V 2584 3400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2450 3400 50  0001 C CNN
F 3 "~" H 2450 3400 50  0001 C CNN
	1    2450 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2150 3400 2350 3400
Wire Wire Line
	2350 3700 2750 3700
Wire Wire Line
	2750 3700 2750 3550
Wire Wire Line
	2550 3400 2750 3400
Wire Wire Line
	2750 3400 2750 3550
Connection ~ 2750 3550
$Comp
L Device:CP_Small C3
U 1 1 6007BC2A
P 1650 3650
F 0 "C3" V 1425 3650 50  0000 C CNN
F 1 "100n" V 1516 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1650 3650 50  0001 C CNN
F 3 "~" H 1650 3650 50  0001 C CNN
	1    1650 3650
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR010
U 1 1 6007F849
P 2750 3550
F 0 "#PWR010" H 2750 3300 50  0001 C CNN
F 1 "GNDA" V 2755 3422 50  0000 R CNN
F 2 "" H 2750 3550 50  0001 C CNN
F 3 "" H 2750 3550 50  0001 C CNN
	1    2750 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1850 3850 1850 3750
Wire Wire Line
	1850 3650 1750 3650
Wire Wire Line
	2150 3400 2150 3700
Connection ~ 2150 3700
Wire Wire Line
	2150 3700 2150 3850
$Comp
L Device:CP_Small C2
U 1 1 600A78D4
P 1500 3350
F 0 "C2" V 1275 3350 50  0000 C CNN
F 1 "100n" V 1366 3350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1500 3350 50  0001 C CNN
F 3 "~" H 1500 3350 50  0001 C CNN
	1    1500 3350
	0    1    1    0   
$EndComp
$Comp
L Device:CP_Small C4
U 1 1 600A86C7
P 1700 3050
F 0 "C4" V 1475 3050 50  0000 C CNN
F 1 "100n" V 1566 3050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1700 3050 50  0001 C CNN
F 3 "~" H 1700 3050 50  0001 C CNN
	1    1700 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 3850 1750 3750
Wire Wire Line
	1750 3750 1850 3750
Connection ~ 1850 3750
Wire Wire Line
	1850 3750 1850 3650
$Comp
L Device:CP_Small C1
U 1 1 600B09A7
P 1500 2750
F 0 "C1" V 1275 2750 50  0000 C CNN
F 1 "4u7" V 1366 2750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1500 2750 50  0001 C CNN
F 3 "~" H 1500 2750 50  0001 C CNN
	1    1500 2750
	0    1    1    0   
$EndComp
$Comp
L power:GNDD #PWR03
U 1 1 600B1865
P 1400 3650
F 0 "#PWR03" H 1400 3400 50  0001 C CNN
F 1 "GNDD" V 1404 3540 50  0000 R CNN
F 2 "" H 1400 3650 50  0001 C CNN
F 3 "" H 1400 3650 50  0001 C CNN
	1    1400 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 3850 1950 3350
Wire Wire Line
	1950 3350 1600 3350
Wire Wire Line
	2050 3050 1800 3050
Wire Wire Line
	2050 3050 2050 2750
Wire Wire Line
	2050 2750 1600 2750
Connection ~ 2050 3050
Wire Wire Line
	2050 2750 2050 2600
Connection ~ 2050 2750
$Comp
L power:GNDD #PWR024
U 1 1 60127C5A
P 9850 3250
F 0 "#PWR024" H 9850 3000 50  0001 C CNN
F 1 "GNDD" V 9854 3140 50  0000 R CNN
F 2 "" H 9850 3250 50  0001 C CNN
F 3 "" H 9850 3250 50  0001 C CNN
	1    9850 3250
	0    1    1    0   
$EndComp
Entry Wire Line
	3000 6450 3100 6550
Entry Wire Line
	3000 6550 3100 6650
Text Label 2600 6450 0    50   ~ 0
SWDIO
Text Label 2600 6550 0    50   ~ 0
SWCLK
Entry Wire Line
	9550 3350 9450 3250
Entry Wire Line
	9550 3150 9450 3050
Text Label 9850 3150 0    50   ~ 0
SWCLK
Text Label 9850 3350 0    50   ~ 0
SWDIO
Entry Wire Line
	3000 5350 3100 5450
Entry Wire Line
	3000 5450 3100 5550
Text Label 2600 5350 0    50   ~ 0
SER_TX
Text Label 2600 5450 0    50   ~ 0
SER_RX
Entry Wire Line
	9450 3450 9550 3550
Entry Wire Line
	9450 3550 9550 3650
Text Label 9850 3550 0    50   ~ 0
SER_TX
Text Label 9850 3650 0    50   ~ 0
SER_RX
Wire Wire Line
	2050 3050 2050 3850
$Comp
L power:+3V3 #PWR05
U 1 1 6023283F
P 1850 3650
F 0 "#PWR05" H 1850 3500 50  0001 C CNN
F 1 "+3V3" H 1865 3823 50  0000 C CNN
F 2 "" H 1850 3650 50  0001 C CNN
F 3 "" H 1850 3650 50  0001 C CNN
	1    1850 3650
	1    0    0    -1  
$EndComp
Connection ~ 1850 3650
$Comp
L power:+3V3 #PWR06
U 1 1 60232F9E
P 1950 3350
F 0 "#PWR06" H 1950 3200 50  0001 C CNN
F 1 "+3V3" H 1965 3523 50  0000 C CNN
F 2 "" H 1950 3350 50  0001 C CNN
F 3 "" H 1950 3350 50  0001 C CNN
	1    1950 3350
	1    0    0    -1  
$EndComp
Connection ~ 1950 3350
$Comp
L power:+3V3 #PWR09
U 1 1 60233C06
P 2150 3400
F 0 "#PWR09" H 2150 3250 50  0001 C CNN
F 1 "+3V3" H 2165 3573 50  0000 C CNN
F 2 "" H 2150 3400 50  0001 C CNN
F 3 "" H 2150 3400 50  0001 C CNN
	1    2150 3400
	1    0    0    -1  
$EndComp
Connection ~ 2150 3400
$Comp
L power:GNDD #PWR02
U 1 1 60238B25
P 1250 3350
F 0 "#PWR02" H 1250 3100 50  0001 C CNN
F 1 "GNDD" V 1254 3240 50  0000 R CNN
F 2 "" H 1250 3350 50  0001 C CNN
F 3 "" H 1250 3350 50  0001 C CNN
	1    1250 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2750 1300 2750
Wire Wire Line
	1600 3050 1300 3050
Wire Wire Line
	1300 3050 1300 2750
Connection ~ 1300 2750
Wire Wire Line
	1300 2750 1150 2750
Wire Wire Line
	1400 3350 1250 3350
Wire Wire Line
	1400 3650 1550 3650
Entry Wire Line
	3000 5550 3100 5650
Entry Wire Line
	3000 5650 3100 5750
Entry Wire Line
	3000 5750 3100 5850
Entry Wire Line
	3000 5850 3100 5950
Wire Wire Line
	2550 5550 3000 5550
Wire Wire Line
	2550 5650 3000 5650
Wire Wire Line
	2550 5750 3000 5750
Wire Wire Line
	2550 5850 3000 5850
Text Label 2600 5550 0    50   ~ 0
SPI_NSS
Text Label 2600 5650 0    50   ~ 0
SPI_SCK
Text Label 2600 5750 0    50   ~ 0
SPI_MISO
Text Label 2600 5850 0    50   ~ 0
SPI_MOSI
$Comp
L Memory_Flash:W25Q32JVSS U2
U 1 1 60313CB0
P 4950 6750
F 0 "U2" H 4950 7331 50  0000 C CNN
F 1 "W25Q32JVSS" H 4950 7240 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4950 6750 50  0001 C CNN
F 3 "http://www.winbond.com/resource-files/w25q32jv%20revg%2003272018%20plus.pdf" H 4950 6750 50  0001 C CNN
	1    4950 6750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 60313CC3
P 5750 6950
F 0 "R2" V 5554 6950 50  0000 C CNN
F 1 "50K" V 5645 6950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5750 6950 50  0001 C CNN
F 3 "~" H 5750 6950 50  0001 C CNN
	1    5750 6950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R1
U 1 1 60313CC9
P 4350 6500
F 0 "R1" V 4154 6500 50  0000 C CNN
F 1 "50K" V 4245 6500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4350 6500 50  0001 C CNN
F 3 "~" H 4350 6500 50  0001 C CNN
	1    4350 6500
	-1   0    0    1   
$EndComp
Wire Wire Line
	5450 6950 5600 6950
$Comp
L power:+3V3 #PWR014
U 1 1 60313CD0
P 6050 6900
F 0 "#PWR014" H 6050 6750 50  0001 C CNN
F 1 "+3V3" H 6065 7073 50  0000 C CNN
F 2 "" H 6050 6900 50  0001 C CNN
F 3 "" H 6050 6900 50  0001 C CNN
	1    6050 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 6950 6050 6950
Wire Wire Line
	6050 6950 6050 6900
Wire Wire Line
	4450 6650 4350 6650
Wire Wire Line
	4350 6350 4950 6350
$Comp
L power:GNDD #PWR011
U 1 1 603213FC
P 4950 7300
F 0 "#PWR011" H 4950 7050 50  0001 C CNN
F 1 "GNDD" H 4954 7145 50  0000 C CNN
F 2 "" H 4950 7300 50  0001 C CNN
F 3 "" H 4950 7300 50  0001 C CNN
	1    4950 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 7150 4950 7300
$Comp
L Device:CP_Small C7
U 1 1 6032CF4F
P 5350 6150
F 0 "C7" H 5262 6104 50  0000 R CNN
F 1 "100n" H 5262 6195 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5350 6150 50  0001 C CNN
F 3 "~" H 5350 6150 50  0001 C CNN
	1    5350 6150
	-1   0    0    1   
$EndComp
$Comp
L power:GNDD #PWR012
U 1 1 6032DBD3
P 5350 6000
F 0 "#PWR012" H 5350 5750 50  0001 C CNN
F 1 "GNDD" H 5354 5845 50  0000 C CNN
F 2 "" H 5350 6000 50  0001 C CNN
F 3 "" H 5350 6000 50  0001 C CNN
	1    5350 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5350 6000 5350 6050
$Comp
L power:+3V3 #PWR013
U 1 1 60338F8F
P 5600 6350
F 0 "#PWR013" H 5600 6200 50  0001 C CNN
F 1 "+3V3" V 5615 6478 50  0000 L CNN
F 2 "" H 5600 6350 50  0001 C CNN
F 3 "" H 5600 6350 50  0001 C CNN
	1    5600 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 6350 5350 6350
Connection ~ 4950 6350
Wire Wire Line
	5350 6350 5600 6350
Connection ~ 5350 6350
Entry Wire Line
	3850 6550 3950 6650
Entry Wire Line
	3850 6750 3950 6850
Wire Wire Line
	3950 6650 4350 6650
Connection ~ 4350 6650
Wire Wire Line
	3950 6850 4450 6850
Wire Wire Line
	5350 6350 5350 6250
Entry Wire Line
	5850 6550 5950 6450
Entry Wire Line
	5850 6650 5950 6550
Wire Wire Line
	5450 6550 5850 6550
Wire Wire Line
	5450 6650 5850 6650
Text Label 5500 6550 0    50   ~ 0
SPI_MOSI
Text Label 5500 6650 0    50   ~ 0
SPI_MISO
Text Label 3950 6850 0    50   ~ 0
SPI_SCK
Text Label 3950 6650 0    50   ~ 0
SPI_NSS
Wire Wire Line
	4350 6400 4350 6350
Wire Wire Line
	4350 6650 4350 6600
Wire Wire Line
	5450 6850 5600 6850
Wire Wire Line
	5600 6850 5600 6950
Connection ~ 5600 6950
Wire Wire Line
	5600 6950 5650 6950
$Comp
L Custom_IC:TPA2005D1DGN U3
U 1 1 6005E159
P 9300 5400
F 0 "U3" H 9300 5981 50  0000 C CNN
F 1 "TPA2005D1DGN" H 9300 5890 50  0000 C CNN
F 2 "Custom_IC:TI_VSSOP-PowerPAD-8_3.0x3.0mm_P0.65mm_ThermalVias" H 9300 5400 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tpa2005d1.pdf" H 9300 5400 50  0001 C CNN
	1    9300 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 5200 10150 5200
Wire Wire Line
	10150 5200 10150 5250
Wire Wire Line
	10150 5350 10150 5400
Wire Wire Line
	10150 5400 9700 5400
Wire Wire Line
	9300 5800 9300 5950
$Comp
L Device:C_Small C11
U 1 1 60085220
P 9550 4700
F 0 "C11" V 9321 4700 50  0000 C CNN
F 1 "100n" V 9412 4700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 9550 4700 50  0001 C CNN
F 3 "~" H 9550 4700 50  0001 C CNN
	1    9550 4700
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR025
U 1 1 60087C0E
P 9850 4700
F 0 "#PWR025" H 9850 4450 50  0001 C CNN
F 1 "GNDA" V 9855 4572 50  0000 R CNN
F 2 "" H 9850 4700 50  0001 C CNN
F 3 "" H 9850 4700 50  0001 C CNN
	1    9850 4700
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDA #PWR021
U 1 1 600887BA
P 9300 5950
F 0 "#PWR021" H 9300 5700 50  0001 C CNN
F 1 "GNDA" H 9305 5777 50  0000 C CNN
F 2 "" H 9300 5950 50  0001 C CNN
F 3 "" H 9300 5950 50  0001 C CNN
	1    9300 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 4700 9650 4700
Wire Wire Line
	9300 4600 9300 4700
Wire Wire Line
	9450 4700 9300 4700
Connection ~ 9300 4700
Wire Wire Line
	9300 4700 9300 5000
$Comp
L Device:R_Small R6
U 1 1 600AF2B8
P 8700 5750
F 0 "R6" H 8641 5704 50  0000 R CNN
F 1 "50K" H 8641 5795 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 8700 5750 50  0001 C CNN
F 3 "~" H 8700 5750 50  0001 C CNN
	1    8700 5750
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 600B0BEA
P 8500 5500
F 0 "R5" H 8559 5546 50  0000 L CNN
F 1 "150K" H 8559 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 8500 5500 50  0001 C CNN
F 3 "~" H 8500 5500 50  0001 C CNN
	1    8500 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 600BEADE
P 8250 5600
F 0 "C9" V 8021 5600 50  0000 C CNN
F 1 "10n" V 8112 5600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8250 5600 50  0001 C CNN
F 3 "~" H 8250 5600 50  0001 C CNN
	1    8250 5600
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR018
U 1 1 600C1177
P 7950 5600
F 0 "#PWR018" H 7950 5350 50  0001 C CNN
F 1 "GNDA" V 7955 5473 50  0000 R CNN
F 2 "" H 7950 5600 50  0001 C CNN
F 3 "" H 7950 5600 50  0001 C CNN
	1    7950 5600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R4
U 1 1 600C1F81
P 8500 5100
F 0 "R4" H 8559 5146 50  0000 L CNN
F 1 "150K" H 8559 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 8500 5100 50  0001 C CNN
F 3 "~" H 8500 5100 50  0001 C CNN
	1    8500 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 600C3883
P 7950 5100
F 0 "C8" H 8042 5146 50  0000 L CNN
F 1 "100n" H 8042 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7950 5100 50  0001 C CNN
F 3 "~" H 7950 5100 50  0001 C CNN
	1    7950 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R3
U 1 1 600C4AB1
P 7850 4800
F 0 "R3" V 8046 4800 50  0000 C CNN
F 1 "400" V 7955 4800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 7850 4800 50  0001 C CNN
F 3 "~" H 7850 4800 50  0001 C CNN
	1    7850 4800
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDD #PWR017
U 1 1 600C6014
P 7750 5200
F 0 "#PWR017" H 7750 4950 50  0001 C CNN
F 1 "GNDD" V 7754 5090 50  0000 R CNN
F 2 "" H 7750 5200 50  0001 C CNN
F 3 "" H 7750 5200 50  0001 C CNN
	1    7750 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	8900 5600 8700 5600
Wire Wire Line
	8700 5600 8700 5650
Wire Wire Line
	8900 5400 8500 5400
Wire Wire Line
	8500 5600 8350 5600
Wire Wire Line
	7950 5600 8150 5600
Wire Wire Line
	8900 5200 8500 5200
Wire Wire Line
	7950 5200 7750 5200
Wire Wire Line
	7950 5000 7950 4950
Entry Wire Line
	7250 4700 7350 4800
Entry Wire Line
	8150 6000 8250 5900
Text Label 8350 5900 0    50   ~ 0
MUTE
Wire Wire Line
	7350 4800 7750 4800
Text Label 7450 4800 0    50   ~ 0
AUDIO
Wire Wire Line
	8250 5900 8700 5900
Wire Wire Line
	8700 5900 8700 5850
$Comp
L power:+5V #PWR020
U 1 1 601F76D6
P 9300 4600
F 0 "#PWR020" H 9300 4450 50  0001 C CNN
F 1 "+5V" H 9315 4773 50  0000 C CNN
F 2 "" H 9300 4600 50  0001 C CNN
F 3 "" H 9300 4600 50  0001 C CNN
	1    9300 4600
	1    0    0    -1  
$EndComp
Text Notes 7400 4400 0    50   ~ 0
Low-pass 4KHz filter
Wire Notes Line
	8150 4450 8150 5350
Wire Notes Line
	8150 5350 7400 5350
Wire Notes Line
	7400 5350 7400 4450
Wire Notes Line
	7400 4450 8150 4450
$Comp
L power:GNDD #PWR022
U 1 1 6019F1AA
P 9850 2400
F 0 "#PWR022" H 9850 2150 50  0001 C CNN
F 1 "GNDD" V 9854 2290 50  0000 R CNN
F 2 "" H 9850 2400 50  0001 C CNN
F 3 "" H 9850 2400 50  0001 C CNN
	1    9850 2400
	0    1    1    0   
$EndComp
Entry Wire Line
	700  5650 800  5750
Entry Wire Line
	700  5750 800  5850
Text Label 850  5750 0    50   ~ 0
SCL
Text Label 850  5850 0    50   ~ 0
SDA
Wire Wire Line
	2550 5950 3000 5950
Wire Wire Line
	2550 6050 3000 6050
Entry Wire Line
	3000 5950 3100 6050
Entry Wire Line
	3000 6050 3100 6150
Text Label 2600 5950 0    50   ~ 0
AUDIO
Text Label 2600 6050 0    50   ~ 0
MUTE
Wire Wire Line
	2550 5350 3000 5350
Wire Wire Line
	2550 5450 3000 5450
Wire Wire Line
	2550 6550 3000 6550
Wire Wire Line
	2550 6450 3000 6450
Entry Wire Line
	9450 3350 9550 3450
Text Label 9850 3450 0    50   ~ 0
RESET
Wire Wire Line
	9850 3250 10150 3250
Wire Wire Line
	9550 3150 10150 3150
Wire Wire Line
	10150 3350 9550 3350
Wire Wire Line
	10150 3450 9550 3450
Wire Wire Line
	10150 3550 9550 3550
Wire Wire Line
	10150 3650 9550 3650
Entry Wire Line
	700  3950 800  4050
Text Label 850  4050 0    50   ~ 0
RESET
$Comp
L power:+3V3 #PWR023
U 1 1 603703F9
P 9850 2500
F 0 "#PWR023" H 9850 2350 50  0001 C CNN
F 1 "+3V3" V 9865 2628 50  0000 L CNN
F 2 "" H 9850 2500 50  0001 C CNN
F 3 "" H 9850 2500 50  0001 C CNN
	1    9850 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10150 2600 9550 2600
Wire Wire Line
	10150 2700 9550 2700
Entry Wire Line
	9450 2500 9550 2600
Entry Wire Line
	9450 2600 9550 2700
Wire Wire Line
	9850 2400 10150 2400
Wire Wire Line
	9850 2500 10150 2500
Text Label 9850 2600 0    50   ~ 0
SDA
Text Label 9850 2700 0    50   ~ 0
SCL
$Comp
L power:GNDD #PWR01
U 1 1 604032C9
P 1150 2750
F 0 "#PWR01" H 1150 2500 50  0001 C CNN
F 1 "GNDD" V 1154 2640 50  0000 R CNN
F 2 "" H 1150 2750 50  0001 C CNN
F 3 "" H 1150 2750 50  0001 C CNN
	1    1150 2750
	0    1    1    0   
$EndComp
Entry Wire Line
	700  5550 800  5650
Entry Wire Line
	700  5450 800  5550
Text Label 850  5550 0    50   ~ 0
SRV_SEN
Wire Wire Line
	800  5550 1250 5550
Wire Wire Line
	800  5650 1250 5650
Wire Wire Line
	800  5750 1250 5750
Wire Wire Line
	800  5850 1250 5850
Wire Wire Line
	800  4050 1250 4050
Text Label 850  5650 0    50   ~ 0
SRV_LAS
$Comp
L power:GNDD #PWR028
U 1 1 60612C1B
P 10650 1100
F 0 "#PWR028" H 10650 850 50  0001 C CNN
F 1 "GNDD" V 10654 990 50  0000 R CNN
F 2 "" H 10650 1100 50  0001 C CNN
F 3 "" H 10650 1100 50  0001 C CNN
	1    10650 1100
	0    -1   -1   0   
$EndComp
Entry Wire Line
	9450 1000 9550 1100
Wire Wire Line
	10500 1100 10650 1100
Text Label 9650 1100 0    50   ~ 0
LASER
Wire Wire Line
	9550 1100 10000 1100
Entry Wire Line
	700  6450 800  6550
Wire Wire Line
	800  6550 1250 6550
Text Label 850  6550 0    50   ~ 0
LASER
Entry Wire Line
	9450 1700 9550 1800
$Comp
L power:GNDD #PWR027
U 1 1 600A6754
P 10600 2050
F 0 "#PWR027" H 10600 1800 50  0001 C CNN
F 1 "GNDD" V 10604 1940 50  0000 R CNN
F 2 "" H 10600 2050 50  0001 C CNN
F 3 "" H 10600 2050 50  0001 C CNN
	1    10600 2050
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR026
U 1 1 600A7B15
P 10600 1550
F 0 "#PWR026" H 10600 1400 50  0001 C CNN
F 1 "+3V3" V 10615 1678 50  0000 L CNN
F 2 "" H 10600 1550 50  0001 C CNN
F 3 "" H 10600 1550 50  0001 C CNN
	1    10600 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	10200 1950 10200 2050
Wire Wire Line
	10200 2050 10600 2050
Wire Wire Line
	10600 1550 10200 1550
Text Label 9600 1800 0    50   ~ 0
ANGLE_POT
Wire Wire Line
	10200 1550 10200 1650
Wire Wire Line
	9550 1800 10050 1800
Entry Wire Line
	3000 5250 3100 5350
Wire Wire Line
	2550 5250 3000 5250
Text Label 2600 5250 0    50   ~ 0
ANGLE_POT
$Comp
L Device:R_POT VOL1
U 1 1 6014F374
P 8500 4150
F 0 "VOL1" V 8293 4150 50  0000 C CNN
F 1 "10K" V 8384 4150 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 8500 4150 50  0001 C CNN
F 3 "~" H 8500 4150 50  0001 C CNN
	1    8500 4150
	0    1    1    0   
$EndComp
$Comp
L Device:CP C10
U 1 1 60151056
P 8500 4700
F 0 "C10" H 8618 4746 50  0000 L CNN
F 1 "10n" H 8618 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8538 4550 50  0001 C CNN
F 3 "~" H 8500 4700 50  0001 C CNN
	1    8500 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4850 8500 5000
Wire Wire Line
	8500 4550 8500 4300
$Comp
L power:GNDA #PWR019
U 1 1 601761A7
P 8850 4150
F 0 "#PWR019" H 8850 3900 50  0001 C CNN
F 1 "GNDA" V 8855 4022 50  0000 R CNN
F 2 "" H 8850 4150 50  0001 C CNN
F 3 "" H 8850 4150 50  0001 C CNN
	1    8850 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8650 4150 8850 4150
Wire Wire Line
	8350 4150 8250 4150
Wire Wire Line
	8250 4150 8250 4950
Wire Wire Line
	8250 4950 7950 4950
Connection ~ 7950 4950
Wire Wire Line
	7950 4950 7950 4800
$Comp
L Device:Speaker SPK1
U 1 1 6005F9DD
P 10350 5250
F 0 "SPK1" H 10520 5246 50  0000 L CNN
F 1 "Speaker" H 10520 5155 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 10350 5050 50  0001 C CNN
F 3 "~" H 10340 5200 50  0001 C CNN
	1    10350 5250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 PROG1
U 1 1 603F2432
P 10350 3350
F 0 "PROG1" H 10430 3342 50  0000 L CNN
F 1 "Conn_01x06" H 10430 3251 50  0000 L CNN
F 2 "Connector_Molex:Molex_SPOX_5267-06A_1x06_P2.50mm_Vertical" H 10350 3350 50  0001 C CNN
F 3 "~" H 10350 3350 50  0001 C CNN
	1    10350 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 QWIIC1
U 1 1 6036EC4D
P 10350 2500
F 0 "QWIIC1" H 10430 2492 50  0000 L CNN
F 1 "Conn_01x04" H 10430 2401 50  0000 L CNN
F 2 "Connector_JST:JST_SH_BM04B-SRSS-TB_1x04-1MP_P1.00mm_Vertical" H 10350 2500 50  0001 C CNN
F 3 "~" H 10350 2500 50  0001 C CNN
	1    10350 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT ANGLE1
U 1 1 60081E37
P 10200 1800
F 0 "ANGLE1" H 10130 1754 50  0000 R CNN
F 1 "10K" H 10130 1845 50  0000 R CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 10200 1800 50  0001 C CNN
F 3 "~" H 10200 1800 50  0001 C CNN
	1    10200 1800
	-1   0    0    1   
$EndComp
Entry Wire Line
	7300 3200 7400 3300
Text Label 7500 3300 0    50   ~ 0
SRV_SEN
$Comp
L power:GNDD #PWR016
U 1 1 60515CCA
P 7750 3500
F 0 "#PWR016" H 7750 3250 50  0001 C CNN
F 1 "GNDD" V 7754 3390 50  0000 R CNN
F 2 "" H 7750 3500 50  0001 C CNN
F 3 "" H 7750 3500 50  0001 C CNN
	1    7750 3500
	0    1    1    0   
$EndComp
$Comp
L Motor:Motor_Servo M2
U 1 1 6053B0A0
P 8200 3400
F 0 "M2" H 8532 3465 50  0000 L CNN
F 1 "SRV_SEN" H 8532 3374 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 8200 3210 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 8200 3210 50  0001 C CNN
	1    8200 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3300 7900 3300
Wire Wire Line
	7750 3500 7900 3500
Entry Wire Line
	7300 2650 7400 2750
Text Label 7500 2750 0    50   ~ 0
SRV_LAS
$Comp
L power:GNDD #PWR015
U 1 1 605B272F
P 7750 2950
F 0 "#PWR015" H 7750 2700 50  0001 C CNN
F 1 "GNDD" V 7754 2840 50  0000 R CNN
F 2 "" H 7750 2950 50  0001 C CNN
F 3 "" H 7750 2950 50  0001 C CNN
	1    7750 2950
	0    1    1    0   
$EndComp
$Comp
L Motor:Motor_Servo M1
U 1 1 605B2735
P 8200 2850
F 0 "M1" H 8532 2915 50  0000 L CNN
F 1 "SRV_LAS" H 8532 2824 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 8200 2660 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 8200 2660 50  0001 C CNN
	1    8200 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2750 7900 2750
Wire Wire Line
	7750 2950 7900 2950
$Comp
L Device:Laserdiode_1C2A LD1
U 1 1 605ED30B
P 10200 1100
F 0 "LD1" H 10150 875 50  0000 C CNN
F 1 "Laserdiode_1C2A" H 10150 966 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 10100 1075 50  0001 C CNN
F 3 "~" H 10230 900 50  0001 C CNN
	1    10200 1100
	-1   0    0    1   
$EndComp
$Comp
L power:GNDA #PWR0103
U 1 1 602200F9
P 5800 5400
F 0 "#PWR0103" H 5800 5150 50  0001 C CNN
F 1 "GNDA" H 5805 5227 50  0000 C CNN
F 2 "" H 5800 5400 50  0001 C CNN
F 3 "" H 5800 5400 50  0001 C CNN
	1    5800 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0104
U 1 1 60220949
P 6050 5400
F 0 "#PWR0104" H 6050 5150 50  0001 C CNN
F 1 "GNDD" H 6054 5245 50  0000 C CNN
F 2 "" H 6050 5400 50  0001 C CNN
F 3 "" H 6050 5400 50  0001 C CNN
	1    6050 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5400 5900 5400
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 60226AF2
P 5900 5400
F 0 "#FLG0103" H 5900 5475 50  0001 C CNN
F 1 "PWR_FLAG" H 5900 5573 50  0000 C CNN
F 2 "" H 5900 5400 50  0001 C CNN
F 3 "~" H 5900 5400 50  0001 C CNN
	1    5900 5400
	1    0    0    -1  
$EndComp
Connection ~ 5900 5400
Wire Wire Line
	5900 5400 6050 5400
$Comp
L power:+5V #PWR0105
U 1 1 6022752A
P 7750 2850
F 0 "#PWR0105" H 7750 2700 50  0001 C CNN
F 1 "+5V" V 7765 2978 50  0000 L CNN
F 2 "" H 7750 2850 50  0001 C CNN
F 3 "" H 7750 2850 50  0001 C CNN
	1    7750 2850
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 60228000
P 7750 3400
F 0 "#PWR0106" H 7750 3250 50  0001 C CNN
F 1 "+5V" V 7765 3528 50  0000 L CNN
F 2 "" H 7750 3400 50  0001 C CNN
F 3 "" H 7750 3400 50  0001 C CNN
	1    7750 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7750 2850 7900 2850
Wire Wire Line
	7750 3400 7900 3400
NoConn ~ 1250 4250
NoConn ~ 1250 4450
NoConn ~ 1250 4550
NoConn ~ 1250 4750
NoConn ~ 1250 4850
NoConn ~ 1250 4950
NoConn ~ 1250 5150
NoConn ~ 1250 5250
NoConn ~ 1250 5350
NoConn ~ 1250 5450
NoConn ~ 1250 5950
NoConn ~ 1250 6050
NoConn ~ 1250 6150
NoConn ~ 1250 6250
NoConn ~ 1250 6350
NoConn ~ 1250 6450
NoConn ~ 1250 6650
NoConn ~ 2550 6650
NoConn ~ 2550 6350
NoConn ~ 2550 6250
NoConn ~ 2550 6150
NoConn ~ 2550 5150
$Comp
L Device:Battery BT1
U 1 1 602AD6DD
P 750 950
F 0 "BT1" H 858 996 50  0000 L CNN
F 1 "Battery" H 858 905 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" V 750 1010 50  0001 C CNN
F 3 "~" V 750 1010 50  0001 C CNN
	1    750  950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 602B0B1E
P 750 1350
F 0 "#PWR0107" H 750 1100 50  0001 C CNN
F 1 "GND" H 755 1177 50  0000 C CNN
F 2 "" H 750 1350 50  0001 C CNN
F 3 "" H 750 1350 50  0001 C CNN
	1    750  1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  1150 750  1350
$Comp
L power:+3V3 #PWR0101
U 1 1 602BBAEC
P 1100 700
F 0 "#PWR0101" H 1100 550 50  0001 C CNN
F 1 "+3V3" H 1115 873 50  0000 C CNN
F 2 "" H 1100 700 50  0001 C CNN
F 3 "" H 1100 700 50  0001 C CNN
	1    1100 700 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 602BC3C4
P 1350 700
F 0 "#PWR0102" H 1350 550 50  0001 C CNN
F 1 "+5V" H 1365 873 50  0000 C CNN
F 2 "" H 1350 700 50  0001 C CNN
F 3 "" H 1350 700 50  0001 C CNN
	1    1350 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  750  750  700 
Wire Wire Line
	750  700  800  700 
Connection ~ 1100 700 
Wire Wire Line
	1100 700  1350 700 
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 602C23BF
P 800 700
F 0 "#FLG0101" H 800 775 50  0001 C CNN
F 1 "PWR_FLAG" H 800 873 50  0000 C CNN
F 2 "" H 800 700 50  0001 C CNN
F 3 "~" H 800 700 50  0001 C CNN
	1    800  700 
	1    0    0    -1  
$EndComp
Connection ~ 800  700 
Wire Wire Line
	800  700  1100 700 
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 602C3193
P 1000 1350
F 0 "#FLG0102" H 1000 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 1000 1523 50  0000 C CNN
F 2 "" H 1000 1350 50  0001 C CNN
F 3 "~" H 1000 1350 50  0001 C CNN
	1    1000 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1350 750  1350
Connection ~ 750  1350
Wire Bus Line
	9450 1600 9450 1900
Wire Bus Line
	700  6400 700  6600
Wire Bus Line
	9450 950  9450 1150
Wire Bus Line
	7300 2550 7300 2800
Wire Bus Line
	7300 3100 7300 3350
Wire Bus Line
	700  3850 700  4050
Wire Bus Line
	8150 5900 8150 6100
Wire Bus Line
	7250 4600 7250 4800
Wire Bus Line
	3100 6500 3100 6750
Wire Bus Line
	3850 6450 3850 6850
Wire Bus Line
	5950 6400 5950 6650
Wire Bus Line
	9450 2400 9450 2700
Wire Bus Line
	9450 2950 9450 3800
Wire Bus Line
	700  5400 700  5850
Wire Bus Line
	3100 5250 3100 6200
$EndSCHEMATC
