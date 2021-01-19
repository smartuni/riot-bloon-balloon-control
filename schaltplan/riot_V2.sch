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
L RF_Module:ESP32-WROOM-32 U4
U 1 1 5FC3AE5B
P 3950 4750
F 0 "U4" H 3950 6331 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 3950 6240 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3950 3250 50  0000 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 3650 4800 50  0001 C CNN
	1    3950 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5FC5D146
P 3400 2150
F 0 "J1" H 3508 2331 50  0000 C CNN
F 1 "valve_connector_1" H 3508 2240 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3400 2150 50  0001 C CNN
F 3 "~" H 3400 2150 50  0001 C CNN
	1    3400 2150
	-1   0    0    1   
$EndComp
Text GLabel 2100 950  0    50   Input ~ 0
bat+
$Comp
L balloon_control.llib:dcdc_any_to_3v3 U2
U 1 1 5FD96708
P 2550 1000
F 0 "U2" H 3128 1096 50  0000 L CNN
F 1 "dcdc_any_to_3v3" H 3128 1005 50  0000 L CNN
F 2 "balloon_control:dcdc_any_to_3v3" H 2650 1550 50  0001 C CNN
F 3 "" H 2650 1450 50  0001 C CNN
	1    2550 1000
	1    0    0    -1  
$EndComp
$Comp
L Simulation_SPICE:DIODE D1
U 1 1 5FDA524B
P 2750 2100
F 0 "D1" H 2750 2317 50  0000 C CNN
F 1 "DIODE" H 2750 2226 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P2.54mm_Vertical_AnodeUp" H 2750 2100 50  0001 C CNN
F 3 "~" H 2750 2100 50  0001 C CNN
F 4 "Y" H 2750 2100 50  0001 L CNN "Spice_Netlist_Enabled"
F 5 "D" H 2750 2100 50  0001 L CNN "Spice_Primitive"
	1    2750 2100
	0    1    1    0   
$EndComp
Text GLabel 950  750  3    50   Input ~ 0
GND
Text GLabel 3950 6150 3    50   Input ~ 0
GND
Text GLabel 5950 4050 0    50   Input ~ 0
GND
Text GLabel 1400 4800 0    50   Input ~ 0
GND
Text GLabel 2100 1150 0    50   Input ~ 0
VCC_3V3
Text GLabel 1400 4700 0    50   Input ~ 0
VCC_3V3
Text GLabel 3950 3350 1    50   Input ~ 0
VCC_3V3
Text GLabel 5950 750  2    50   Input ~ 0
VCC_3V3
Text GLabel 5950 3950 0    50   Input ~ 0
VCC_3V3
Text GLabel 5950 2250 2    50   Input ~ 0
GND
Text GLabel 4550 4550 2    50   Input ~ 0
ESP_U2RXD
Text GLabel 4150 1350 0    50   Input ~ 0
ESP_U2RXD
Text GLabel 4550 4650 2    50   Input ~ 0
ESP_U2TXD
Text GLabel 4150 1250 0    50   Input ~ 0
ESP_U2TXD
Text GLabel 4550 4950 2    50   Input ~ 0
ESP_I2C_SDA
Text GLabel 1400 5000 0    50   Input ~ 0
ESP_I2C_SDA
Text GLabel 4550 5050 2    50   Input ~ 0
ESP_I2C_SCL
Text GLabel 1400 4900 0    50   Input ~ 0
ESP_I2C_SCL
Text GLabel 4550 3750 2    50   Input ~ 0
ESP_GPIO2
Text GLabel 4550 5650 2    50   Input ~ 0
ESP_GPIO33
Text GLabel 5950 3350 0    50   Input ~ 0
ESP_GPIO33
Text GLabel 4550 5250 2    50   Input ~ 0
ESP_GPIO25
Text GLabel 5950 3450 0    50   Input ~ 0
ESP_GPIO25
Text GLabel 4550 5350 2    50   Input ~ 0
ESP_GPIO26
Text GLabel 5950 3550 0    50   Input ~ 0
ESP_GPIO26
Text GLabel 4550 5450 2    50   Input ~ 0
ESP_GPIO27
Text GLabel 5950 3650 0    50   Input ~ 0
ESP_GPIO27
Text GLabel 4550 5550 2    50   Input ~ 0
ESP_GPIO32
Text GLabel 5950 3250 0    50   Input ~ 0
ESP_GPIO32
Text GLabel 4550 4350 2    50   Input ~ 0
ESP_HSPI_SCK
Text GLabel 5950 4150 0    50   Input ~ 0
ESP_HSPI_SCK
Text GLabel 4550 4450 2    50   Input ~ 0
ESP_HSPI_CS0
Text GLabel 5950 4450 0    50   Input ~ 0
ESP_HSPI_CS0
Text GLabel 4550 4250 2    50   Input ~ 0
ESP_HSPI_MOSI
Text GLabel 5950 4350 0    50   Input ~ 0
ESP_HSPI_MOSI
Text GLabel 4550 4150 2    50   Input ~ 0
ESP_HSPI_MISO
Text GLabel 5950 4250 0    50   Input ~ 0
ESP_HSPI_MISO
Text GLabel 2100 1500 0    50   Input ~ 0
bat+
Text GLabel 2100 1600 0    50   Input ~ 0
GND
Text GLabel 2100 1050 0    50   Input ~ 0
GND
Wire Wire Line
	3200 2050 3200 1950
Wire Wire Line
	3200 1950 2750 1950
Wire Wire Line
	3200 2150 3200 2250
Wire Wire Line
	3200 2250 2750 2250
Text GLabel 900  750  0    50   Input ~ 0
bat-
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5FFAD04B
P 1450 750
F 0 "J2" H 1558 931 50  0000 C CNN
F 1 "battery_connector" H 1558 840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1450 750 50  0001 C CNN
F 3 "~" H 1450 750 50  0001 C CNN
	1    1450 750 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 750  900  750 
Text GLabel 900  650  0    50   Input ~ 0
bat+
Wire Wire Line
	1250 650  900  650 
Text GLabel 2700 2250 0    50   Input ~ 0
VCC_5V5
Text GLabel 2100 1700 0    50   Input ~ 0
VCC_5V5
Wire Wire Line
	2750 2250 2700 2250
Connection ~ 2750 2250
Text GLabel 7100 2000 0    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5FF45A9D
P 3400 2950
F 0 "J3" H 3508 3131 50  0000 C CNN
F 1 "valve_connector_2" H 3508 3040 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3400 2950 50  0001 C CNN
F 3 "~" H 3400 2950 50  0001 C CNN
	1    3400 2950
	-1   0    0    1   
$EndComp
Text GLabel 1900 2150 0    50   Input ~ 0
ESP_GPIO2
Text GLabel 4550 3950 2    50   Input ~ 0
ESP_GPIO4
Text GLabel 1900 2950 0    50   Input ~ 0
ESP_GPIO4
Text GLabel 2200 2350 3    50   Input ~ 0
GND
Text GLabel 2200 3150 3    50   Input ~ 0
GND
Wire Wire Line
	2200 1950 2750 1950
Connection ~ 2750 1950
$Comp
L Simulation_SPICE:DIODE D2
U 1 1 5FF5193E
P 2750 2900
F 0 "D2" H 2750 3117 50  0000 C CNN
F 1 "DIODE" H 2750 3026 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P2.54mm_Vertical_AnodeUp" H 2750 2900 50  0001 C CNN
F 3 "~" H 2750 2900 50  0001 C CNN
F 4 "Y" H 2750 2900 50  0001 L CNN "Spice_Netlist_Enabled"
F 5 "D" H 2750 2900 50  0001 L CNN "Spice_Primitive"
	1    2750 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	3200 2850 3200 2750
Wire Wire Line
	3200 2750 2750 2750
Wire Wire Line
	3200 2950 3200 3050
Wire Wire Line
	2750 2750 2200 2750
Connection ~ 2750 2750
Text GLabel 2700 3050 0    50   Input ~ 0
VCC_5V5
Wire Wire Line
	2700 3050 2750 3050
Connection ~ 2750 3050
Wire Wire Line
	2750 3050 3200 3050
$Comp
L balloon_control.llib:dcdc_any_to_5v U3
U 1 1 5FD9716B
P 2550 1550
F 0 "U3" H 3078 1596 50  0000 L CNN
F 1 "dcdc_any_to_5v" H 3078 1505 50  0000 L CNN
F 2 "balloon_control:dcdc_any_to_5v" H 2600 2000 50  0001 C CNN
F 3 "" H 2600 1900 50  0001 C CNN
	1    2550 1550
	1    0    0    -1  
$EndComp
Text Label 2400 1950 0    50   ~ 0
Valve_1_DRAIN
Text Label 2400 2750 0    50   ~ 0
Valve_2_DRAIN
Text GLabel 4550 3850 2    50   Input ~ 0
ESP_U0RXD
Text GLabel 4550 3650 2    50   Input ~ 0
ESP_U0TXD
Text GLabel 4550 4750 2    50   Input ~ 0
ESP_VSPI_SCK
Text GLabel 4550 4050 2    50   Input ~ 0
ESP_VSPI_CS0
Text GLabel 4550 4850 2    50   Input ~ 0
ESP_VSPI_MISO
Text GLabel 4550 5150 2    50   Input ~ 0
ESP_VSPI_MOSI
$Comp
L Transistor_FET:AO3400A Q2
U 1 1 5FF441CE
P 2100 2950
F 0 "Q2" H 2305 2996 50  0000 L CNN
F 1 "AO3400A" H 2305 2905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2300 2875 50  0001 L CIN
F 3 "http://www.aosmd.com/pdfs/datasheet/AO3400A.pdf" H 2100 2950 50  0001 L CNN
	1    2100 2950
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:AO3400A Q1
U 1 1 5FF42260
P 2100 2150
F 0 "Q1" H 2305 2196 50  0000 L CNN
F 1 "AO3400A" H 2305 2105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2300 2075 50  0001 L CIN
F 3 "http://www.aosmd.com/pdfs/datasheet/AO3400A.pdf" H 2100 2150 50  0001 L CNN
	1    2100 2150
	1    0    0    -1  
$EndComp
$Comp
L balloon_control.llib:DRF1272F_NO_ANT U6
U 1 1 5FFB30D3
P 6150 3000
F 0 "U6" H 7528 2196 50  0000 L CNN
F 1 "DRF1272F_NO_ANT" H 7528 2105 50  0000 L CNN
F 2 "balloon_control:DRF1272F_NO_ANT" H 6850 2200 50  0001 C CNN
F 3 "https://d3s5r33r268y59.cloudfront.net/datasheets/5321/2015-06-23-07-45-23/DRF1272F.pdf" H 6850 2400 50  0001 C CNN
	1    6150 3000
	1    0    0    -1  
$EndComp
$Comp
L balloon_control.llib:bme280_board U1
U 1 1 5FFE402F
P 1650 4900
F 0 "U1" H 2028 4896 50  0000 L CNN
F 1 "bme280_board" H 2028 4805 50  0000 L CNN
F 2 "balloon_control:bme280_board" H 1750 5450 50  0001 C CNN
F 3 "" H 1750 5350 50  0001 C CNN
	1    1650 4900
	1    0    0    -1  
$EndComp
$Comp
L balloon_control.llib:MountingHole_1.5mm H1
U 1 1 6005E2EA
P 5950 2550
F 0 "H1" H 6050 2596 50  0000 L CNN
F 1 "MountingHole_1.5mm" H 6050 2505 50  0000 L CNN
F 2 "balloon_control:MountingHole_1.5mm" H 5950 2550 50  0001 C CNN
F 3 "~" H 5950 2550 50  0001 C CNN
	1    5950 2550
	1    0    0    -1  
$EndComp
$Comp
L balloon_control.llib:L96-M33 U5
U 1 1 600746DA
P 5050 1550
F 0 "U5" H 5050 2617 50  0000 C CNN
F 1 "L96-M33" H 5050 2526 50  0000 C CNN
F 2 "XCVR_L96-M33" H 5050 1550 50  0001 L BNN
F 3 "https://www.quectel.com/UploadImage/Downlad/Quectel_L96_Hardware_Design_V1.2.pdf" H 5050 1550 50  0001 L BNN
F 4 "Quectel Wireless Solutions Co., Ltd" H 5050 1550 50  0001 L BNN "MF"
F 5 "L96 is a concurrent multi-GNSS receiver module with embedded chip antenna. With 33 tracking channels, 99 acquisition channels and 210 PRN channels, L96 supports concurrent reception of up to three GNSS systems _GPS+GLONASS+Galileo_" H 5050 1550 50  0001 L BNN "DESCRIPTION"
F 6 "L96" H 5050 1550 50  0001 L BNN "MP"
F 7 "None" H 5050 1550 50  0001 L BNN "PRICE"
F 8 "SOIC-8 Quectel Wireless Solutions Co., Ltd" H 5050 1550 50  0001 L BNN "PACKAGE"
F 9 "Unavailable" H 5050 1550 50  0001 L BNN "AVAILABILITY"
	1    5050 1550
	1    0    0    -1  
$EndComp
Text GLabel 5950 1150 2    50   Input ~ 0
L96_ANT
Text GLabel 5950 1050 2    50   Input ~ 0
L96_ANT
Text GLabel 7100 1200 0    50   Input ~ 0
ESP_U0RXD
Text GLabel 7100 1100 0    50   Input ~ 0
ESP_U0TXD
Text GLabel 7100 1300 0    50   Input ~ 0
ESP_VSPI_CS0
Text GLabel 7100 1400 0    50   Input ~ 0
ESP_VSPI_MOSI
Text GLabel 7100 1500 0    50   Input ~ 0
ESP_VSPI_MISO
Text GLabel 7100 1600 0    50   Input ~ 0
ESP_VSPI_SCK
Text GLabel 7100 1700 0    50   Input ~ 0
ESP_I2C_SCL
Text GLabel 7100 1800 0    50   Input ~ 0
ESP_I2C_SDA
Text GLabel 7100 1900 0    50   Input ~ 0
VCC_3V3
$Comp
L Connector:Conn_01x12_Male J4
U 1 1 60080608
P 7300 1500
F 0 "J4" H 7272 1382 50  0000 R CNN
F 1 "Conn_01x12_Male" H 7272 1473 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 7300 1500 50  0001 C CNN
F 3 "~" H 7300 1500 50  0001 C CNN
	1    7300 1500
	-1   0    0    1   
$EndComp
Text GLabel 7100 1000 0    50   Input ~ 0
ESP_EN
Text GLabel 7100 900  0    50   Input ~ 0
ESP_IO0
Text GLabel 3350 3550 0    50   Input ~ 0
ESP_EN
Text GLabel 4550 3550 2    50   Input ~ 0
ESP_IO0
$EndSCHEMATC
