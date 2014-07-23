/*******************************************************************************
* File Name: AMux_Neg.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "AMux_Neg.h"

static uint8 AMux_Neg_lastChannel = AMux_Neg_NULL_CHANNEL;


/*******************************************************************************
* Function Name: AMux_Neg_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMux_Neg_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < AMux_Neg_CHANNELS ; chan++)
    {
#if (AMux_Neg_MUXTYPE == AMux_Neg_MUX_SINGLE)
        AMux_Neg_Unset(chan);
#else
        AMux_Neg_CYAMUXSIDE_A_Unset(chan);
        AMux_Neg_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    AMux_Neg_lastChannel = AMux_Neg_NULL_CHANNEL;
}


#if (!AMux_Neg_ATMOSTONE)
/*******************************************************************************
* Function Name: AMux_Neg_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_Neg_Select(uint8 channel) 
{
    AMux_Neg_DisconnectAll();        /* Disconnect all previous connections */
    AMux_Neg_Connect(channel);       /* Make the given selection */
    AMux_Neg_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: AMux_Neg_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_Neg_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( AMux_Neg_lastChannel != AMux_Neg_NULL_CHANNEL)
    {
        AMux_Neg_Disconnect(AMux_Neg_lastChannel);
    }

    /* Make the new channel connection */
#if (AMux_Neg_MUXTYPE == AMux_Neg_MUX_SINGLE)
    AMux_Neg_Set(channel);
#else
    AMux_Neg_CYAMUXSIDE_A_Set(channel);
    AMux_Neg_CYAMUXSIDE_B_Set(channel);
#endif


    AMux_Neg_lastChannel = channel;   /* Update last channel */
}


#if (AMux_Neg_MUXTYPE == AMux_Neg_MUX_DIFF)
#if (!AMux_Neg_ATMOSTONE)
/*******************************************************************************
* Function Name: AMux_Neg_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_Neg_Connect(uint8 channel) 
{
    AMux_Neg_CYAMUXSIDE_A_Set(channel);
    AMux_Neg_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: AMux_Neg_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_Neg_Disconnect(uint8 channel) 
{
    AMux_Neg_CYAMUXSIDE_A_Unset(channel);
    AMux_Neg_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (AMux_Neg_ATMOSTONE)
/*******************************************************************************
* Function Name: AMux_Neg_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMux_Neg_DisconnectAll(void) 
{
    if(AMux_Neg_lastChannel != AMux_Neg_NULL_CHANNEL) 
    {
        AMux_Neg_Disconnect(AMux_Neg_lastChannel);
        AMux_Neg_lastChannel = AMux_Neg_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
