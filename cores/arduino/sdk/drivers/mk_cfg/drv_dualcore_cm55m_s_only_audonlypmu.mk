##
# platform (onchip ip) support feature
# Add all of supported ip list here
# The source code should be located in ~\drivers\{ip_name}\
##

		DRIVERS_IP_LIST		?= 2x2 \
					5x5 \
					uart spi\
					iic \
					mb \
					scu \
					timer \
					watchdog \
					rtc	\
					cdm \
					edm \
					jpeg \
					xdma \
					dp \
					inp \
					tpg \
					inp1bitparser \
					inpovparser \
					sensorctrl \
					gpio \
					swreg_aon \
					swreg_lsc \
					dma \
					ppc \
					pmu \
					mpc \
					hxautoi2c_mst \
					csirx 

DRIVERS_IP_INSTANCE  ?= RTC0 \
						RTC1 \
						RTC2 \
						TIMER0 \
						TIMER1 \
						TIMER2 \
						TIMER3 \
						TIMER4 \
						TIMER5 \
						WDT0 \
						WDT1 \
						DMA0 \
						DMA1 \
						DMA2 \
						DMA3 \
						UART0 \
						UART1 \
						UART2 \
						IIC_HOST_SENSOR \
						IIC_HOST \
						IIC_HOST_MIPI \
						IIC_SLAVE0 \
						IIC_SLAVE1 \
						SSPI_HOST \
						QSPI_HOST \
						OSPI_HOST \
						SSPI_SLAVE \
						GPIO_G0 \
						GPIO_G1 \
						GPIO_G2 \
						GPIO_G3 \
						SB_GPIO \
						AON_GPIO \
						I2S_HOST \
						I2S_SLAVE \
						IIIC_SLAVE0 \
						IIIC_SLAVE1 \
						PWM0 \
						PWM1 \
						PWM2 \
						ADCC \
						ADCC_HV 
						
ifneq ($(IC_VER), 10)
DRIVERS_IP_INSTANCE  += TIMER6 \
						TIMER7 \
						TIMER8
endif							
						
DRIVERS_IP_NS_INSTANCE ?=
						