/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    system.h

  @Summary:
    This is the sysetm.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ256GB108
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// CONFIG3
#pragma config WPFP = WPFP511    //Write Protection Flash Page Segment Boundary->Highest Page (same as page 170)
#pragma config WPDIS = WPDIS    //Segment Write Protection Disable bit->Segmented code protection disabled
#pragma config WPCFG = WPCFGDIS    //Configuration Word Code Page Protection Select bit->Last page(at the top of program memory) and Flash configuration words are not protected
#pragma config WPEND = WPENDMEM    //Segment Write Protection End Page Select bit->Write Protect from WPFP to the last page of memory

// CONFIG2
#pragma config POSCMOD = XT    //Primary Oscillator Select->XT oscillator mode selected
#pragma config DISUVREG = OFF    //Internal USB 3.3V Regulator Disable bit->Regulator is disabled
#pragma config IOL1WAY = ON    //IOLOCK One-Way Set Enable bit->Write RP Registers Once
#pragma config OSCIOFNC = ON    //Primary Oscillator Output Function->OSCO functions as port I/O (RC15)
#pragma config FCKSM = CSECMD    //Clock Switching and Monitor->Clock switching is enabled, Fail-safe Clock Monitor is disabled
#pragma config FNOSC = FRC    //Oscillator Select->FRC
#pragma config PLL_96MHZ = ON    //96MHz PLL Disable->Enabled
#pragma config PLLDIV = DIV2    //USB 96 MHz PLL Prescaler Select bits->Oscillator input divided by 2 (8MHz input)
#pragma config IESO = OFF    //Internal External Switch Over Mode->IESO mode (Two-speed start-up)disabled

// CONFIG1
#pragma config WDTPS = PS32768    //Watchdog Timer Postscaler->1:32768
#pragma config FWPSA = PR128    //WDT Prescaler->Prescaler ratio of 1:128
#pragma config WINDIS = OFF    //Watchdog Timer Window->Standard Watchdog Timer enabled,(Windowed-mode is disabled)
#pragma config FWDTEN = OFF    //Watchdog Timer Enable->Watchdog Timer is disabled
#pragma config ICS = PGx2    //Comm Channel Select->Emulator functions are shared with PGEC2/PGED2
#pragma config BKBUG = OFF    //Background Debug->Device resets into Operational mode
#pragma config GWRP = OFF    //General Code Segment Write Protect->Writes to program memory are allowed
#pragma config GCP = OFF    //General Code Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF    //JTAG Port Enable->JTAG port is disabled

#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "spi1.h"
#include "delay.h"
#include "interrupt_manager.h"
#include "traps.h"
#include "ext_int.h"
#include "uart1.h"
#include "adc1.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    CLOCK_Initialize();
    ADC1_Initialize();
    SPI1_Initialize();
    UART1_Initialize();
    EXT_INT_Initialize();
}

/**
 End of File
*/