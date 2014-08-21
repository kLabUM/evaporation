# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Ryan\Documents\summer2014\WindSensor\airmartest.cydsn\airmartest.cyprj
# Date: Tue, 19 Aug 2014 15:42:04 GMT
#set_units -time ns
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {ADC_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 15 29} -nominal_period 583.33333333333326 [list [get_pins {ClockBlock/aclk_glb_0}]]
create_clock -name {ADC_theACLK(fixed-function)} -period 541.66666666666663 -waveform {0 291.666666666667} -nominal_period 583.33333333333326 [get_pins {ClockBlock/aclk_glb_ff_0}]
create_generated_clock -name {clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_SBD_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 53 105} -nominal_period 2166.6666666666665 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Airmar_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 625 1251} -nominal_period 26041.666666666664 [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 41.666666666666664 -waveform {0 20.8333333333333} [get_pins {ClockBlock/clk_bus_glb_ff}]


# Component constraints for C:\Users\Ryan\Documents\summer2014\WindSensor\airmartest.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Ryan\Documents\summer2014\WindSensor\airmartest.cydsn\airmartest.cyprj
# Date: Tue, 19 Aug 2014 15:41:30 GMT
