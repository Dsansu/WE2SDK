/**
 ********************************************************************************************
 *  @file      evt_uartcomm.c
 *  @details   This file contains all uart communication event related function
 *  @author    himax/903730
 *  @version   V1.0.0
 *  @date      14-April-2020
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/

/********************************************************************************************
 *  History :
 *  2020.04.14 - Initial version
 *
 *******************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "WE2_core.h"
#include "xprintf.h"
#include "WE2_debug.h"

#include "hxevent.h"
#include "event_handler_evt.h"
#include "evt_uartcomm.h"

#include "hx_drv_uart.h"

/****************************************************
 * Constant Definition                              *
 ***************************************************/
#define UART_PACKET_SIZE (5*1024)
#define uart_buf_size 7
/***************************************************
 * Static Function Declaration
 **************************************************/
static void uart_rx_callback_fun(uint32_t status);

/****************************************************
 * Variable Declaration                             *
 ***************************************************/
unsigned char g_uart_rx_buf[uart_buf_size]={0,0,0,0,0,0,0};
DEV_BUFFER rx_buffer;
static DEV_UART_PTR dev_uart_comm;
static evthandleruart_CBEvent_t g_uart_rx_hdl = NULL;
extern hx_event_t g_event[];


/***************************************************
 * Function Implementation
 **************************************************/
EVT_UARTCOMM_ERR_E evt_uartcomm_init(void)
{
    uint32_t cmd_uart_buad = EVT_UARTCOMM_BAUDRATE;

    dev_uart_comm = hx_drv_uart_get_dev(EVT_COMMAND_UART_ID);
    dev_uart_comm->uart_open(cmd_uart_buad);

    //use DMA method
    dev_uart_comm->uart_read_udma(g_uart_rx_buf, uart_buf_size, uart_rx_callback_fun);
    dbg_printf(DBG_LESS_INFO,"COMMAND UART ID:%d,  Baud Rate:%d \n", EVT_COMMAND_UART_ID, cmd_uart_buad);

    return EVT_UARTCOMM_NO_ERROR;
}

uint8_t evt_uartcomm_rx_cb(void)
{
    #ifndef __GNU__
    dbg_printf(DBG_LESS_INFO,"EVENT INFRA_EVT_UART_RX: evt_uartcomm_rx_cb TRIGGERED\n");
    uint8_t i;
    for(i = 0; i< uart_buf_size; i++)
    {
        dbg_printf(DBG_LESS_INFO, "g_uart_rx_buf[%d]:0x%02x \n", i, g_uart_rx_buf[i]);
    }
    #endif

    if(g_uart_rx_hdl != NULL)
    {
        g_uart_rx_hdl();
    }else{
        dbg_printf(DBG_LESS_INFO,"EVT_INDEX_CDM_FIFO_ERR g_uart_rx_hdl == NULL\n");
    }

    // clear cmd header
    memset(g_uart_rx_buf, 0xFF, uart_buf_size);
    dev_uart_comm->uart_read_udma(g_uart_rx_buf, uart_buf_size, uart_rx_callback_fun);

    return HX_EVENT_RETURN_DONE;
}

// raise uart rx event
static void uart_rx_callback_fun(uint32_t status)
{
    //dbg_printf(DBG_LESS_INFO,"Raise UART RX EVT \n");
    hx_event_activate_ISR(g_event[EVT_INDEX_UART_RX]);
    return;
}

DEV_UART_PTR get_dev_uart_comm()
{
    return dev_uart_comm;
}

void uartomm_cmd_register_rxcb(evthandleruart_CBEvent_t cb_func)
{
    g_uart_rx_hdl = cb_func;
}


