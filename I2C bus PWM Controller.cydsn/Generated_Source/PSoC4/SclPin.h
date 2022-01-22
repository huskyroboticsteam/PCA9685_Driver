/*******************************************************************************
* File Name: SclPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SclPin_H) /* Pins SclPin_H */
#define CY_PINS_SclPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SclPin_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} SclPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SclPin_Read(void);
void    SclPin_Write(uint8 value);
uint8   SclPin_ReadDataReg(void);
#if defined(SclPin__PC) || (CY_PSOC4_4200L) 
    void    SclPin_SetDriveMode(uint8 mode);
#endif
void    SclPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   SclPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SclPin_Sleep(void); 
void SclPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SclPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SclPin_DRIVE_MODE_BITS        (3)
    #define SclPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SclPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SclPin_SetDriveMode() function.
         *  @{
         */
        #define SclPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SclPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SclPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SclPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SclPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SclPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SclPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SclPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SclPin_MASK               SclPin__MASK
#define SclPin_SHIFT              SclPin__SHIFT
#define SclPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SclPin_SetInterruptMode() function.
     *  @{
     */
        #define SclPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SclPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SclPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SclPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SclPin__SIO)
    #define SclPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SclPin__PC) && (CY_PSOC4_4200L)
    #define SclPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SclPin_USBIO_DISABLE              ((uint32)(~SclPin_USBIO_ENABLE))
    #define SclPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SclPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SclPin_USBIO_ENTER_SLEEP          ((uint32)((1u << SclPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SclPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define SclPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SclPin_USBIO_SUSPEND_SHIFT)))
    #define SclPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SclPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define SclPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SclPin__PC)
    /* Port Configuration */
    #define SclPin_PC                 (* (reg32 *) SclPin__PC)
#endif
/* Pin State */
#define SclPin_PS                     (* (reg32 *) SclPin__PS)
/* Data Register */
#define SclPin_DR                     (* (reg32 *) SclPin__DR)
/* Input Buffer Disable Override */
#define SclPin_INP_DIS                (* (reg32 *) SclPin__PC2)

/* Interrupt configuration Registers */
#define SclPin_INTCFG                 (* (reg32 *) SclPin__INTCFG)
#define SclPin_INTSTAT                (* (reg32 *) SclPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SclPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SclPin__SIO)
    #define SclPin_SIO_REG            (* (reg32 *) SclPin__SIO)
#endif /* (SclPin__SIO_CFG) */

/* USBIO registers */
#if !defined(SclPin__PC) && (CY_PSOC4_4200L)
    #define SclPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SclPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SclPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SclPin_DRIVE_MODE_SHIFT       (0x00u)
#define SclPin_DRIVE_MODE_MASK        (0x07u << SclPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SclPin_H */


/* [] END OF FILE */
