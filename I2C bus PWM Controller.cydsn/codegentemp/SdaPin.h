/*******************************************************************************
* File Name: SdaPin.h  
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

#if !defined(CY_PINS_SdaPin_H) /* Pins SdaPin_H */
#define CY_PINS_SdaPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SdaPin_aliases.h"


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
} SdaPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SdaPin_Read(void);
void    SdaPin_Write(uint8 value);
uint8   SdaPin_ReadDataReg(void);
#if defined(SdaPin__PC) || (CY_PSOC4_4200L) 
    void    SdaPin_SetDriveMode(uint8 mode);
#endif
void    SdaPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   SdaPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SdaPin_Sleep(void); 
void SdaPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SdaPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SdaPin_DRIVE_MODE_BITS        (3)
    #define SdaPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SdaPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SdaPin_SetDriveMode() function.
         *  @{
         */
        #define SdaPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SdaPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SdaPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SdaPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SdaPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SdaPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SdaPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SdaPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SdaPin_MASK               SdaPin__MASK
#define SdaPin_SHIFT              SdaPin__SHIFT
#define SdaPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SdaPin_SetInterruptMode() function.
     *  @{
     */
        #define SdaPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SdaPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SdaPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SdaPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SdaPin__SIO)
    #define SdaPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SdaPin__PC) && (CY_PSOC4_4200L)
    #define SdaPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SdaPin_USBIO_DISABLE              ((uint32)(~SdaPin_USBIO_ENABLE))
    #define SdaPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SdaPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SdaPin_USBIO_ENTER_SLEEP          ((uint32)((1u << SdaPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SdaPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define SdaPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SdaPin_USBIO_SUSPEND_SHIFT)))
    #define SdaPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SdaPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define SdaPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SdaPin__PC)
    /* Port Configuration */
    #define SdaPin_PC                 (* (reg32 *) SdaPin__PC)
#endif
/* Pin State */
#define SdaPin_PS                     (* (reg32 *) SdaPin__PS)
/* Data Register */
#define SdaPin_DR                     (* (reg32 *) SdaPin__DR)
/* Input Buffer Disable Override */
#define SdaPin_INP_DIS                (* (reg32 *) SdaPin__PC2)

/* Interrupt configuration Registers */
#define SdaPin_INTCFG                 (* (reg32 *) SdaPin__INTCFG)
#define SdaPin_INTSTAT                (* (reg32 *) SdaPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SdaPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SdaPin__SIO)
    #define SdaPin_SIO_REG            (* (reg32 *) SdaPin__SIO)
#endif /* (SdaPin__SIO_CFG) */

/* USBIO registers */
#if !defined(SdaPin__PC) && (CY_PSOC4_4200L)
    #define SdaPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SdaPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SdaPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SdaPin_DRIVE_MODE_SHIFT       (0x00u)
#define SdaPin_DRIVE_MODE_MASK        (0x07u << SdaPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SdaPin_H */


/* [] END OF FILE */
