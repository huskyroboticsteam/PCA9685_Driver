/*******************************************************************************
* File Name: SclPin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SclPin_ALIASES_H) /* Pins SclPin_ALIASES_H */
#define CY_PINS_SclPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SclPin_0			(SclPin__0__PC)
#define SclPin_0_PS		(SclPin__0__PS)
#define SclPin_0_PC		(SclPin__0__PC)
#define SclPin_0_DR		(SclPin__0__DR)
#define SclPin_0_SHIFT	(SclPin__0__SHIFT)
#define SclPin_0_INTR	((uint16)((uint16)0x0003u << (SclPin__0__SHIFT*2u)))

#define SclPin_INTR_ALL	 ((uint16)(SclPin_0_INTR))


#endif /* End Pins SclPin_ALIASES_H */


/* [] END OF FILE */
