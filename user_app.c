/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/
 /*
void TimeXus(INPUT_PARAMETER_)
Sets Timer0 to count u16Microseconds_
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
*/
  void TimeXus(u16 u16Microsecond)
{
    T0CON0 &= 0x7F; // Turn off timer
 
    TMR0H = ((0xFFFF - u16Microsecond) >> 8) & 0xFF; // Sets TMR0H to the desired value
    TMR0L = (0xFFFF - u16Microsecond) & 0xFF; // Sets TMR0L registers to the desired value
        
    PIR3 &= 0x7F; // Set interrupt flag to 0
    T0CON0 |= 0x80; // Turn on Timer
  }
/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{


} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u16 u16Counter = 0; //  counter delay value
    static u8 u8Index = 0; // indexing value
    static u8 au8Pattern[] = {0x04, 0x08, 0x02, 0x10, 0x01, 0x20}; // LED position array
    
    if (u16Counter == 500) // Increase u16Counter until 500 
    {
        LATA &= 0x00; 
        LATA = au8Pattern[u8Index]; // Individually enable LEDs using u8Array and u8Index 
        u16Counter = 0; // Reset counter to 0
        u8Index++;
        
        if (u8Index == 6)
        {
            u8Index = 0;
        }
    }
       u16Counter++;
    
  } /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
