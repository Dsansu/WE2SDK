/*
 * hx_drv_pmu_export.h
 *
 *  Created on: 2021�~12��10��
 *      Author: 902447
 */

#ifndef DRIVERS_INC_HX_DRV_PMU_EXPORT_H_
#define DRIVERS_INC_HX_DRV_PMU_EXPORT_H_


/**
 * \defgroup	PMU_DRV	Power Management Driver
 * \ingroup		PMU_DRV
 * \brief	Power Management Driver Declaration
 * \details Application can use PMU driver Data Structure and Power Management library to control WE-1 Power Management\n
 */

/**
 * \defgroup	PMU_DRV_ENUM	PMU Driver Enumeration
 * \ingroup	PMU_DRV
 * \brief	Defines some enumeration of PMU Driver need.
 * @{
 */

/**
 * \enum PMU_NFRAMEEND_CTRL_E
 * \brief PMU NFrame End Ctrl
 */
typedef enum PMU_NFRAMEEND_CTRL_S
{
	PMU_NFRAMEEND_CTRL_SC = 0,
	PMU_NFRAMEEND_CTRL_I2C
}PMU_NFRAMEEND_CTRL_E;

/**
 * \enum PMU_MIPIRXPHY_CTRL_E
 * \brief PMU MIPIRXPHY Ctrl
 */
typedef enum PMU_MIPIRXPHY_CTRL_S
{
	PMU_MIPIRXPHY_CTRL_PMU = 0,
	PMU_MIPIRXPHY_CTRL_CPU
}PMU_MIPIRXPHY_CTRL_E;

/**
 * \enum PMU_INT_INDEX_E
 * \brief PMU Interrupt SRC Type
 */
typedef enum PMU_INT_INDEX_S
{
	PMU_INT_WDT_TIMEOUT,
	PMU_INT_ADC_TIMEOUT,
	PMU_INT_MAX
}PMU_INT_INDEX_E;
/**
 * \enum PMU_WAKEUPEVENT_E
 * \brief PMU Trigger wakeup to all on event
 */
typedef enum PMU_WAKEUPEVENT_S
{
	PMU_WAKEUP_NONE                     = 0x0,
	PMU_WAKEUP_DPD_EXT_FORCE 			= 0x1,  	//[0]: PS_DPD : wakeup by (ext_force_pmu_dc_sync)
	PMU_WAKEUP_DPD_RTC_INT	   			= 0x2,  	//[1]: PS_DPD wakeup by (~pmu_sc_active && RTC_timer_int)
	PMU_WAKEUP_DPD_ANTI_TAMP_INT	    = 0x4,  	//[2]: PS_DPD wakeup by (anti_tamp_int)
	PMU_WAKEUP_PD_DC_FORCE  			= 0x08,  	//[3]: PS_PD wakeup by ((REG_FORCE_EVENT_NSTATE==5'b10000) && REG_FORCE_EVENT_TRIG)
	PMU_WAKEUP_PD_EXTGPIO  				= 0x10,  	//[4]: PS_PD wakeup by ((REG_FORCE_EVENT_NSTATE==5'b10000) && REG_FORCE_EVENT_TRIG)
	PMU_WAKEUP_PD_RTC_TIMER_INT			= 0x20, 	//[5]: PS_PD wakeup by (RTC_timer_int)
	PMU_WAKEUP_PD_SB_TIMER_INT			= 0x40, 	//[6]: PS_PD wakeup by (|SB_timer_int[5:1](VerA))(|SB_timer_int[8:1](VerB))
	PMU_WAKEUP_PD_CMP_int				= 0x80,  	//[7]: PS_PD wakeup by (CMP_int)
	PMU_WAKEUP_PD_TS_int	   			= 0x100, 	//[8]: PS_PD wakeup by (TS_int)
	PMU_WAKEUP_PD_I2C_W_int				= 0x200, 	//[9]: PS_PD wakeup by (I2C_W_int)
	PMU_WAKEUP_PD_SB_timer0_int			= 0x400,	//[10]: PS_PD wakeup by (REG_CPU_SCENARIO == 4'b0010 && SB_timer_int[0])

	PMU_WAKEUP_SCL_AUDONLY_SW_TRIG		= 0x800,	//[11]: PS_SCL wakeup by ((REG_FORCE_EVENT_NSTATE==5'b10000) && REG_FORCE_EVENT_TRIG)
	PMU_WAKEUP_SCL_SENEXTINT			= 0x1000,	//[12]: PS_SCL wakeup by (~pmu_sc_active && Sensor_EXT_INT)
	PMU_WAKEUP_SCL_EXTDC				= 0x2000,	//[13]: PS_SCL wakeup by (ext_int_nxt_dc)
	PMU_WAKEUP_SCL_RTC_TIMER_INT		= 0x4000,   //[14]: PS_SCL wakeup by (RTC_timer_int)
	PMU_WAKEUP_SCL_SB_TIMER_INT			= 0x8000,	//[15]: PS_SCL wakeup by (SB_timer_int[5:1](VerA))(|SB_timer_int[8:1](VerB))
	PMU_WAKEUP_SCL_ADCC_int				= 0x10000,	//[16]: PS_SCL wakeup by (ADCC_int)
	PMU_WAKEUP_SCL_TS_INT				= 0x20000,	//[17]: PS_SCL wakeup by (TS_int)
	PMU_WAKEUP_SCL_I2C_INT				= 0x40000, 	//[18]: PS_SCL wakeup by (I2C_W_int)
	PMU_WAKEUP_SCL_PMUWDG_TIMEOUT		= 0x80000,  //[19]: PS_SCL wakeup by (pmu_sc_active && pmu_wdg_timeout_int)

	PMU_WAKEUP_SCH_VIDAUD_SW_TRIG 		= 0x100000,  //[20]: PS_SCH wakeup by ((REG_FORCE_EVENT_NSTATE==5'b10000) && REG_FORCE_EVENT_TRIG)
	PMU_WAKEUP_SCH_ext_int_nxt_dc 		= 0x200000,  //[21]: PS_SCH wakeup by (ext_int_nxt_dc)
	PMU_WAKEUP_SCH_RTC_TIMER_INT 		= 0x400000,  //[22]: PS_SCH wakeup by (RTC_timer_int)
	PMU_WAKEUP_SCH_SB_TIMER_INT 		= 0x800000,  //[23]: PS_SCH wakeup by (|SB_timer_int[5:1](VerA))(|SB_timer_int[8:1](VerB))
	PMU_WAKEUP_SCH_ADCC_int				= 0x1000000,	//[24]: PS_SCH wakeup by (ADCC_int)
	PMU_WAKEUP_SCH_TS_INT				= 0x2000000,	//[25]: PS_SCH wakeup by (TS_int)
	PMU_WAKEUP_SCH_I2C_INT				= 0x4000000, 	//[26]: PS_SCH wakeup by (I2C_W_int)
	PMU_WAKEUP_SCH_PMUWDG_TIMEOUT		= 0x8000000,  //[27]: PS_SCH wakeup by (pmu_wdg_timeout_int)
	PMU_WAKEUP_SCH_XDMA_ABNORMAL		= 0x10000000,  //[28]: PS_SCH wakeup by (WRDMAx_abnormal_int)
	PMU_WAKEUP_SCH_DP_ABNORMAL			= 0x20000000,  //[29]: PS_SCH wakeup by (DP_ABNORMAL_INT)
	PMU_WAKEUP_SCH_VIDONLY_CDM			= 0x40000000,  //[30]: PS_SCH wakeup by ((REG_CPU_SCENARIO==4'b0100) && SC_sen_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT)
	PMU_WAKEUP_SCH_VIDAUD_CDM			= 0x80000000,  //[31]: PS_SCH wakeup by((REG_CPU_SCENARIO==4'b1100) && SC_sen_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT)"
}PMU_WAKEUPEVENT_E;

/**
 * \enum PMU_WAKEUPEVENT1_E
 * \brief PMU Trigger wakeup to all on event
 */
typedef enum PMU_WAKEUPEVENT1_S
{
	PMU_WAKEUPEVENT1_NONE                   	= 0x0,
	PMU_WAKEUPEVENT1_DPD_PAD_AON_GPIO_0 		= 0x1,  	//[0]: PS_DPD wakeup by (~pmu_sc_active &&PAD_AON_GPIO_0)
	PMU_WAKEUPEVENT1_DPD_PAD_VMUTE 				= 0x2,  	//[1]: PS_DPD wakeup by (~pmu_sc_active &&PAD_VMUTE)
	PMU_WAKEUPEVENT1_EXT_INT	 				= 0x4,  	//[2]: PS_DPD wakeup by (~pmu_sc_active && ext_int_nxt_dc)
	PMU_WAKEUPEVENT1_PD_ANTI_TAMP_INT 			= 0x100,  	//[8]: PS_PD wakeup by (anti_tamp_int)
	PMU_WAKEUPEVENT1_SCL_ANTI_TAMP_INT 			= 0x10000,  	//[16]: PS_SCL wakeup by (anti_tamp_int)
	PMU_WAKEUPEVENT1_SCH_I2CNOACK 				= 0x1000000,  	//[24]: PS_SCH wakeup by (SC_sen_noack)
	PMU_WAKEUPEVENT1_SCH_ANTI_TAMP_INT 			= 0x2000000,  	//[25]: PS_SCH wakeup by (anti_tamp_int)
	PMU_WAKEUPEVENT1_RES 						= 0x80000000,  	//[31]: PS_SCH wakeup by (SC_sen_noack)
}PMU_WAKEUPEVENT1_E;
/**
 * \enum PMU_ERROR_E
 * \brief PMU Errors Type
 */
typedef enum PMU_ERROR_S
{
	PMU_NO_ERROR                     	= 0,	/**< No ERROR */
	PMU_ERROR_NOT_INIT              	= 1,	/**< ERROR MSG: not init */
	PMU_ERROR_ALREADY_INIT              = 2,	/**< ERROR MSG: already init */
	PMU_ERROR_INVALID_PARAMETERS        = 3,	/**< ERROR MSG: Invalid parameters */
	PMU_ERROR_NULL_POINTER				= 4,	/**< ERROR MSG: NULL pointer */
 	PMU_UNKNOWN_ERROR      				= 5,	/**< ERROR MSG: UNKNOWN ERROR*/
} PMU_ERROR_E;

/**
 * \enum PMU_SCENARIO_PS_E
 * \brief PMU Scenario Case
 */
typedef enum PMU_SCENARIO_PS_S
{
	PMU_SCENARIO_PS_DC = 0x00,
	PMU_SCENARIO_PS_DPD = 0x01,
	PMU_SCENARIO_PS_PD_NOVIDPRE = 0x02,
	PMU_SCENARIO_PS_VIDPRE_ONLY = 0x04,
	PMU_SCENARIO_PS_AUDPRE_ONLY = 0x08,
	PMU_SCENARIO_PS_VIDPRE_AUDPRE = 0x0C,
}PMU_SCENARIO_PS_E;

/**
 * \enum PMU_SCENARIO_PS_E
 * \brief PMU Scenario Case
 */
typedef enum PMU_PS_STATE_S
{
	PMU_PS_STATE_DPD = 0x01,
	PMU_PS_STATE_PD = 0x02,
	PMU_PS_STATE_SCL = 0x04,
	PMU_PS_STATE_SCH = 0x08,
	PMU_PS_STATE_DC = 0x10
}PMU_PS_STATE_E;

/**
 * \enum PMU_TIMEOUT_E
 * \brief PMU Timeout Type WDT is for CIS Sensor, ADC is for ADC sampling timeout
 */
typedef enum PMU_TIMEOUT_S
{
	PMU_TIMEOUT_WDT = 0,  /**< Timeout for CIS sensor capture frame */
}PMU_TIMEOUT_E;

/**
 * \enum PMU_MEM_RET_E
 * \brief PMU Memory Retention (only work in PS_PD, PS_SCL, PS_SCH)
 */
typedef enum PMU_MEM_RET_S
{
	PMU_MEM_RET_PD = 0,  /**<  Memory Power down*/
	PMU_MEM_RET_RET = 1   /**< Memory Retention */
}PMU_MEM_RET_E;

/**
 * \enum PMU_FRAME_END_CTRL_E
 * \brief PMU N Frame End Control
 */
typedef enum PMU_FRAME_END_CTRL_S
{
	PMU_FRAME_END_CTRL_SC = 0,  /**<  Sensor Control*/
	PMU_FRAME_END_CTRL_I2C = 1   /**< I2C Module */
}PMU_FRAME_END_CTRL_E;

/**
 * \enum PMU_TRIGGER_CTRL_E
 * \brief PMU Trigger Control
 */
typedef enum PMU_TRIGGER_CTRL_S
{
	PMU_TRIGGER_CTRL_SC = 0,  /**<  Sensor Control*/
	PMU_TRIGGER_CTRL_I2C = 1   /**< I2C Module */
}PMU_TRIGGER_CTRL_E;

/**
 * \enum PMU_HV_NOR_SIMO_VOUT1_E
 * \brief PMU HV threshold setting of Normal SIMO VOUT1
 */
typedef enum PMU_HV_NOR_SIMO_VOUT1_S
{
	PMU_HV_NOR_SIMO_VOUT1_0P525 = 0x00,
	PMU_HV_NOR_SIMO_VOUT1_0P550 = 0x01,
	PMU_HV_NOR_SIMO_VOUT1_0P575 = 0x02,
	PMU_HV_NOR_SIMO_VOUT1_0P600 = 0x03,
	PMU_HV_NOR_SIMO_VOUT1_0P625 = 0x04,
	PMU_HV_NOR_SIMO_VOUT1_0P650 = 0x05,
	PMU_HV_NOR_SIMO_VOUT1_0P675 = 0x06,
	PMU_HV_NOR_SIMO_VOUT1_0P700 = 0x07,
	PMU_HV_NOR_SIMO_VOUT1_0P725 = 0x08,
	PMU_HV_NOR_SIMO_VOUT1_0P750 = 0x09,
	PMU_HV_NOR_SIMO_VOUT1_0P775 = 0x0A,
	PMU_HV_NOR_SIMO_VOUT1_0P800 = 0x0B,
	PMU_HV_NOR_SIMO_VOUT1_0P825 = 0x0C,
	PMU_HV_NOR_SIMO_VOUT1_0P850 = 0x0D,
	PMU_HV_NOR_SIMO_VOUT1_0P875 = 0x0E,
	PMU_HV_NOR_SIMO_VOUT1_0P900 = 0x0F,
	PMU_HV_NOR_SIMO_VOUT1_0P925 = 0x10,
	PMU_HV_NOR_SIMO_VOUT1_0P950 = 0x11,
	PMU_HV_NOR_SIMO_VOUT1_0P975 = 0x12,
	PMU_HV_NOR_SIMO_VOUT1_1P000 = 0x13,
	PMU_HV_NOR_SIMO_VOUT1_1P025 = 0x14,
	PMU_HV_NOR_SIMO_VOUT1_1P050 = 0x15,
	PMU_HV_NOR_SIMO_VOUT1_1P075 = 0x16,
	PMU_HV_NOR_SIMO_VOUT1_1P100 = 0x17,
	PMU_HV_NOR_SIMO_VOUT1_1P150 = 0x18,
	PMU_HV_NOR_SIMO_VOUT1_1P200 = 0x19,
	PMU_HV_NOR_SIMO_VOUT1_1P250 = 0x1A,
	PMU_HV_NOR_SIMO_VOUT1_1P300 = 0x1B,
	PMU_HV_NOR_SIMO_VOUT1_1P350 = 0x1C,
	PMU_HV_NOR_SIMO_VOUT1_1P400 = 0x1D,
	PMU_HV_NOR_SIMO_VOUT1_1P450 = 0x1E,
	PMU_HV_NOR_SIMO_VOUT1_1P500 = 0x1F,
	PMU_HV_NOR_SIMO_VOUT1_1P550 = 0x20,
	PMU_HV_NOR_SIMO_VOUT1_1P600 = 0x21,
	PMU_HV_NOR_SIMO_VOUT1_1P650 = 0x22,
	PMU_HV_NOR_SIMO_VOUT1_1P700 = 0x23,
	PMU_HV_NOR_SIMO_VOUT1_1P750 = 0x24,
	PMU_HV_NOR_SIMO_VOUT1_1P800 = 0x25,
	PMU_HV_NOR_SIMO_VOUT1_1P850 = 0x26,
	PMU_HV_NOR_SIMO_VOUT1_1P900 = 0x27,
	PMU_HV_NOR_SIMO_VOUT1_1P950 = 0x28,
	PMU_HV_NOR_SIMO_VOUT1_2P000 = 0x29,
	PMU_HV_NOR_SIMO_VOUT1_2P050 = 0x2A,
	PMU_HV_NOR_SIMO_VOUT1_2P100 = 0x2B,
	PMU_HV_NOR_SIMO_VOUT1_2P200 = 0x2C,
	PMU_HV_NOR_SIMO_VOUT1_2P300 = 0x2D,
	PMU_HV_NOR_SIMO_VOUT1_2P400 = 0x2E,
	PMU_HV_NOR_SIMO_VOUT1_2P500 = 0x2F,
}PMU_HV_NOR_SIMO_VOUT1_E;

/**
 * \enum PMU_HV_LL_SIMO_VOUT1_E
 * \brief HV threshold setting of Low Leakage SIMO VOUT1
 */
typedef enum PMU_HV_LL_SIMO_VOUT1_S
{
	PMU_HV_LL_SIMO_VOUT1_0P525 = 0x00,
	PMU_HV_LL_SIMO_VOUT1_0P550 = 0x01,
	PMU_HV_LL_SIMO_VOUT1_0P575 = 0x02,
	PMU_HV_LL_SIMO_VOUT1_0P600 = 0x03,
	PMU_HV_LL_SIMO_VOUT1_0P625 = 0x04,
	PMU_HV_LL_SIMO_VOUT1_0P650 = 0x05,
	PMU_HV_LL_SIMO_VOUT1_0P675 = 0x06,
	PMU_HV_LL_SIMO_VOUT1_0P700 = 0x07,
	PMU_HV_LL_SIMO_VOUT1_0P725 = 0x08,
	PMU_HV_LL_SIMO_VOUT1_0P750 = 0x09,
	PMU_HV_LL_SIMO_VOUT1_0P775 = 0x0A,
	PMU_HV_LL_SIMO_VOUT1_0P800 = 0x0B,
	PMU_HV_LL_SIMO_VOUT1_0P825 = 0x0C,
	PMU_HV_LL_SIMO_VOUT1_0P850 = 0x0D,
	PMU_HV_LL_SIMO_VOUT1_0P875 = 0x0E,
	PMU_HV_LL_SIMO_VOUT1_0P900 = 0x0F,
	PMU_HV_LL_SIMO_VOUT1_0P925 = 0x10,
	PMU_HV_LL_SIMO_VOUT1_0P950 = 0x11,
	PMU_HV_LL_SIMO_VOUT1_0P975 = 0x12,
	PMU_HV_LL_SIMO_VOUT1_1P000 = 0x13,
	PMU_HV_LL_SIMO_VOUT1_1P025 = 0x14,
	PMU_HV_LL_SIMO_VOUT1_1P050 = 0x15,
	PMU_HV_LL_SIMO_VOUT1_1P075 = 0x16,
	PMU_HV_LL_SIMO_VOUT1_1P100 = 0x17,
	PMU_HV_LL_SIMO_VOUT1_1P150 = 0x18,
	PMU_HV_LL_SIMO_VOUT1_1P200 = 0x19,
	PMU_HV_LL_SIMO_VOUT1_1P250 = 0x1A,
	PMU_HV_LL_SIMO_VOUT1_1P300 = 0x1B,
	PMU_HV_LL_SIMO_VOUT1_1P350 = 0x1C,
	PMU_HV_LL_SIMO_VOUT1_1P400 = 0x1D,
	PMU_HV_LL_SIMO_VOUT1_1P450 = 0x1E,
	PMU_HV_LL_SIMO_VOUT1_1P500 = 0x1F,
	PMU_HV_LL_SIMO_VOUT1_1P550 = 0x20,
	PMU_HV_LL_SIMO_VOUT1_1P600 = 0x21,
	PMU_HV_LL_SIMO_VOUT1_1P650 = 0x22,
	PMU_HV_LL_SIMO_VOUT1_1P700 = 0x23,
	PMU_HV_LL_SIMO_VOUT1_1P750 = 0x24,
	PMU_HV_LL_SIMO_VOUT1_1P800 = 0x25,
	PMU_HV_LL_SIMO_VOUT1_1P850 = 0x26,
	PMU_HV_LL_SIMO_VOUT1_1P900 = 0x27,
	PMU_HV_LL_SIMO_VOUT1_1P950 = 0x28,
	PMU_HV_LL_SIMO_VOUT1_2P000 = 0x29,
	PMU_HV_LL_SIMO_VOUT1_2P050 = 0x2A,
	PMU_HV_LL_SIMO_VOUT1_2P100 = 0x2B,
	PMU_HV_LL_SIMO_VOUT1_2P200 = 0x2C,
	PMU_HV_LL_SIMO_VOUT1_2P300 = 0x2D,
	PMU_HV_LL_SIMO_VOUT1_2P400 = 0x2E,
	PMU_HV_LL_SIMO_VOUT1_2P500 = 0x2F,
}PMU_HV_LL_SIMO_VOUT1_E;

/**
 * \enum PMU_HV_NOR_SIMO_VOUT2_E
 * \brief HV threshold setting of Normal SIMO VOUT2
 */
typedef enum PMU_HV_NOR_SIMO_VOUT2_S
{
	PMU_HV_NOR_SIMO_VOUT2_0P525 = 0x00,
	PMU_HV_NOR_SIMO_VOUT2_0P550 = 0x01,
	PMU_HV_NOR_SIMO_VOUT2_0P575 = 0x02,
	PMU_HV_NOR_SIMO_VOUT2_0P600 = 0x03,
	PMU_HV_NOR_SIMO_VOUT2_0P625 = 0x04,
	PMU_HV_NOR_SIMO_VOUT2_0P650 = 0x05,
	PMU_HV_NOR_SIMO_VOUT2_0P675 = 0x06,
	PMU_HV_NOR_SIMO_VOUT2_0P700 = 0x07,
	PMU_HV_NOR_SIMO_VOUT2_0P725 = 0x08,
	PMU_HV_NOR_SIMO_VOUT2_0P750 = 0x09,
	PMU_HV_NOR_SIMO_VOUT2_0P775 = 0x0A,
	PMU_HV_NOR_SIMO_VOUT2_0P800 = 0x0B,
	PMU_HV_NOR_SIMO_VOUT2_0P825 = 0x0C,
	PMU_HV_NOR_SIMO_VOUT2_0P850 = 0x0D,
	PMU_HV_NOR_SIMO_VOUT2_0P875 = 0x0E,
	PMU_HV_NOR_SIMO_VOUT2_0P900 = 0x0F,
	PMU_HV_NOR_SIMO_VOUT2_0P925 = 0x10,
	PMU_HV_NOR_SIMO_VOUT2_0P950 = 0x11,
	PMU_HV_NOR_SIMO_VOUT2_0P975 = 0x12,
	PMU_HV_NOR_SIMO_VOUT2_1P000 = 0x13,
	PMU_HV_NOR_SIMO_VOUT2_1P025 = 0x14,
	PMU_HV_NOR_SIMO_VOUT2_1P050 = 0x15,
	PMU_HV_NOR_SIMO_VOUT2_1P075 = 0x16,
	PMU_HV_NOR_SIMO_VOUT2_1P100 = 0x17,
	PMU_HV_NOR_SIMO_VOUT2_1P150 = 0x18,
	PMU_HV_NOR_SIMO_VOUT2_1P200 = 0x19,
	PMU_HV_NOR_SIMO_VOUT2_1P250 = 0x1A,
	PMU_HV_NOR_SIMO_VOUT2_1P300 = 0x1B,
	PMU_HV_NOR_SIMO_VOUT2_1P350 = 0x1C,
	PMU_HV_NOR_SIMO_VOUT2_1P400 = 0x1D,
	PMU_HV_NOR_SIMO_VOUT2_1P450 = 0x1E,
	PMU_HV_NOR_SIMO_VOUT2_1P500 = 0x1F,
	PMU_HV_NOR_SIMO_VOUT2_1P550 = 0x20,
	PMU_HV_NOR_SIMO_VOUT2_1P600 = 0x21,
	PMU_HV_NOR_SIMO_VOUT2_1P650 = 0x22,
	PMU_HV_NOR_SIMO_VOUT2_1P700 = 0x23,
	PMU_HV_NOR_SIMO_VOUT2_1P750 = 0x24,
	PMU_HV_NOR_SIMO_VOUT2_1P800 = 0x25,
	PMU_HV_NOR_SIMO_VOUT2_1P850 = 0x26,
	PMU_HV_NOR_SIMO_VOUT2_1P900 = 0x27,
	PMU_HV_NOR_SIMO_VOUT2_1P950 = 0x28,
	PMU_HV_NOR_SIMO_VOUT2_2P000 = 0x29,
	PMU_HV_NOR_SIMO_VOUT2_2P050 = 0x2A,
	PMU_HV_NOR_SIMO_VOUT2_2P100 = 0x2B,
	PMU_HV_NOR_SIMO_VOUT2_2P200 = 0x2C,
	PMU_HV_NOR_SIMO_VOUT2_2P300 = 0x2D,
	PMU_HV_NOR_SIMO_VOUT2_2P400 = 0x2E,
	PMU_HV_NOR_SIMO_VOUT2_2P500 = 0x2F,
}PMU_HV_NOR_SIMO_VOUT2_E;

/**
 * \enum PMU_HV_LL_SIMO_VOUT2_E
 * \brief HV threshold setting of Low Leakage SIMO VOUT2
 */
typedef enum PMU_HV_LL_SIMO_VOUT2_S
{
	PMU_HV_LL_SIMO_VOUT2_0P525 = 0x00,
	PMU_HV_LL_SIMO_VOUT2_0P550 = 0x01,
	PMU_HV_LL_SIMO_VOUT2_0P575 = 0x02,
	PMU_HV_LL_SIMO_VOUT2_0P600 = 0x03,
	PMU_HV_LL_SIMO_VOUT2_0P625 = 0x04,
	PMU_HV_LL_SIMO_VOUT2_0P650 = 0x05,
	PMU_HV_LL_SIMO_VOUT2_0P675 = 0x06,
	PMU_HV_LL_SIMO_VOUT2_0P700 = 0x07,
	PMU_HV_LL_SIMO_VOUT2_0P725 = 0x08,
	PMU_HV_LL_SIMO_VOUT2_0P750 = 0x09,
	PMU_HV_LL_SIMO_VOUT2_0P775 = 0x0A,
	PMU_HV_LL_SIMO_VOUT2_0P800 = 0x0B,
	PMU_HV_LL_SIMO_VOUT2_0P825 = 0x0C,
	PMU_HV_LL_SIMO_VOUT2_0P850 = 0x0D,
	PMU_HV_LL_SIMO_VOUT2_0P875 = 0x0E,
	PMU_HV_LL_SIMO_VOUT2_0P900 = 0x0F,
	PMU_HV_LL_SIMO_VOUT2_0P925 = 0x10,
	PMU_HV_LL_SIMO_VOUT2_0P950 = 0x11,
	PMU_HV_LL_SIMO_VOUT2_0P975 = 0x12,
	PMU_HV_LL_SIMO_VOUT2_1P000 = 0x13,
	PMU_HV_LL_SIMO_VOUT2_1P025 = 0x14,
	PMU_HV_LL_SIMO_VOUT2_1P050 = 0x15,
	PMU_HV_LL_SIMO_VOUT2_1P075 = 0x16,
	PMU_HV_LL_SIMO_VOUT2_1P100 = 0x17,
	PMU_HV_LL_SIMO_VOUT2_1P150 = 0x18,
	PMU_HV_LL_SIMO_VOUT2_1P200 = 0x19,
	PMU_HV_LL_SIMO_VOUT2_1P250 = 0x1A,
	PMU_HV_LL_SIMO_VOUT2_1P300 = 0x1B,
	PMU_HV_LL_SIMO_VOUT2_1P350 = 0x1C,
	PMU_HV_LL_SIMO_VOUT2_1P400 = 0x1D,
	PMU_HV_LL_SIMO_VOUT2_1P450 = 0x1E,
	PMU_HV_LL_SIMO_VOUT2_1P500 = 0x1F,
	PMU_HV_LL_SIMO_VOUT2_1P550 = 0x20,
	PMU_HV_LL_SIMO_VOUT2_1P600 = 0x21,
	PMU_HV_LL_SIMO_VOUT2_1P650 = 0x22,
	PMU_HV_LL_SIMO_VOUT2_1P700 = 0x23,
	PMU_HV_LL_SIMO_VOUT2_1P750 = 0x24,
	PMU_HV_LL_SIMO_VOUT2_1P800 = 0x25,
	PMU_HV_LL_SIMO_VOUT2_1P850 = 0x26,
	PMU_HV_LL_SIMO_VOUT2_1P900 = 0x27,
	PMU_HV_LL_SIMO_VOUT2_1P950 = 0x28,
	PMU_HV_LL_SIMO_VOUT2_2P000 = 0x29,
	PMU_HV_LL_SIMO_VOUT2_2P050 = 0x2A,
	PMU_HV_LL_SIMO_VOUT2_2P100 = 0x2B,
	PMU_HV_LL_SIMO_VOUT2_2P200 = 0x2C,
	PMU_HV_LL_SIMO_VOUT2_2P300 = 0x2D,
	PMU_HV_LL_SIMO_VOUT2_2P400 = 0x2E,
	PMU_HV_LL_SIMO_VOUT2_2P500 = 0x2F,
}PMU_HV_LL_SIMO_VOUT2_E;

/**
 * \enum PMU_DCDC_EN_CTRL_E
 * \brief PMU DCDC Enable control on/off
 */
typedef enum PMU_DCDC_EN_CTRL_S
{
	PMU_DCDC_EN_CTRL_ALWAYS_ON = 0x00,
	PMU_DCDC_EN_CTRL_PMUONOFF = 0x01,
}PMU_DCDC_EN_CTRL_E;

/**
 * \enum PMU_DCDC_CTRL_SWITCH_E
 * \brief PMU DCDC control by CPU/PMU
 */
typedef enum PMU_DCDC_CTRL_SWITCH_S
{
	PMU_DCDC_CTRL_SWITCH_PMU = 0x00,
	PMU_DCDC_CTRL_SWITCH_CPU = 0x01,
}PMU_DCDC_CTRL_SWITCH_E;

/**
 * \enum PMU_EXT_INT_MASK_E
 * \brief PMU EXT INTTERUPT MASK
 */
typedef enum PMU_EXT_INT_MASK_S
{
	PMU_EXT_INT_MASK_AON_GPIO_INT = 0x01,
	PMU_EXT_INT_MASK_SB_GPIO_INT = 0x02,
	PMU_EXT_INT_MASK_SB_WDG0_INT = 0x04,
	PMU_EXT_INT_MASK_SB_WDG1_INT = 0x08,
	PMU_EXT_INT_MASK_PAD_AON_GPIO_0 = 0x80,
	PMU_EXT_INT_MASK_PAD_VMUTE = 0x100,
}PMU_EXT_INT_MASK_E;

/**
 * \enum PMU_EXT_INT_STATUS_E
 * \brief PMU EXT INTTERUPT STATUS
 */
typedef enum PMU_EXT_INT_STATUS_S
{
	PMU_EXT_INT_STATUS_AON_GPIO_INT = 0x01,
	PMU_EXT_INT_STATUS_SB_GPIO_INT = 0x02,
	PMU_EXT_INT_STATUS_SB_WDG0_INT = 0x04,
	PMU_EXT_INT_STATUS_SB_WDG1_INT = 0x08,
	PMU_EXT_INT_STATUS_PAD_AON_GPIO_0 = 0x80,
	PMU_EXT_INT_STATUS_PAD_VMUTE = 0x100,
}PMU_EXT_INT_STATUS_E;


/**
 * \enum PMU_SIMO_PD_OFF_E
 * \brief PMU SIMO_PD_OFF
 */
typedef enum PMU_SIMO_PD_OFF_S
{
	PMU_SIMO_PD_OFF_POWERON = 0x00,
	PMU_SIMO_PD_OFF_POWEROFF = 0x01,
}PMU_SIMO_PD_OFF_E;

/**
 * \enum PMU_CLK_CTRL_E
 * \brief PMU CLK Control
 */
typedef enum PMU_CLK_CTRL_S
{
	PMU_CLK_CTRL_BY_PMU = 0x00,
	PMU_CLK_CTRL_BY_CPU = 0x01,
}PMU_CLK_CTRL_E;


/**
 * \enum PMU_MIPI_LANE_E
 * \brief PMU MIPI Lane Control
 */
typedef enum PMU_MIPI_LANE_S
{
	PMU_MIPI_LANE_ALL_DISABLE = 0x00,
	PMU_MIPI_LANE_FIRST_LANE_EN = 0x01,
	PMU_MIPI_LANE_SECOND_LANE_EN = 0x02,
	PMU_MIPI_LANE_ALL_LANE_EN = 0x03,
}PMU_MIPI_LANE_E;


/**
 * \enum PMU_LSC_IORET_GROUP_E
 * \brief PMU LSC IO Retention Group
 */
typedef enum PMU_LSC_IORET_GROUP_S
{
	PMU_LSC_IORET_GROUP_PIFA = 0x00,
	PMU_LSC_IORET_GROUP_PIFB = 0x01,
}PMU_LSC_IORET_GROUP_E;

/**
 * \enum PMU_LSC_IORET_POLICY_E
 * \brief PMU LSC IO Retention Policy
 */
typedef enum PMU_LSC_IORET_POLICY_S
{
	PMU_LSC_IORET_POLICY_HWAUTO = 0x00,
	PMU_LSC_IORET_POLICY_HWAUTOEN_SWDIS = 0x01,
	PMU_LSC_IORET_POLICY_SWCTRL_IOMODE = 0x02,
}PMU_LSC_IORET_POLICY_E;

/**
 * \enum PMU_LSC_IORET_MODE_E
 * \brief PMU LSC IO Retention Mode
 */
typedef enum PMU_LSC_IORET_MODE_S
{
	PMU_LSC_IORET_MODE_NORMAL = 0x00,
	PMU_LSC_IORET_MODE_IORET = 0x01,
}PMU_LSC_IORET_MODE_E;

/**
 * \enum PMU_DPD_PA01_GPIO_POL_WAKEUP_E
 * \brief PMU DPD PA01 GPIO POLARITY for WAKEUP
 */
typedef enum PMU_DPD_PA01_GPIO_POL_WAKEUP_S
{
	PMU_DPD_PA01_GPIO_POL_WAKEUP_HIGH = 0x00,
	PMU_DPD_PA01_GPIO_POL_WAKEUP_LOW = 0x01,
}PMU_DPD_PA01_GPIO_POL_WAKEUP_E;

/**
 * \brief	Power Managements interrupt callback function
 *
 * \param[in]	param	 Power Management interrupt callback event
 * \return	void.
 */
typedef void (*pmu_cb_t) (void* param);
/** @} */
#endif /* DRIVERS_INC_HX_DRV_PMU_EXPORT_H_ */
