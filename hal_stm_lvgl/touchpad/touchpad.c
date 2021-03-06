/**
 * @file indev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "main.h"
#include "../tft/tft.h"
#include "../../lvgl/src/hal/lv_hal.h"

#include "../../Drivers/BSP/STM32H7B3I-DK/stm32h7b3i_discovery.h"
#include "../../Drivers/BSP/STM32H7B3I-DK/stm32h7b3i_discovery_ts.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void touchpad_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

/**********************
 *  STATIC VARIABLES
 **********************/
static TS_State_t  TS_State;
static uint32_t Instance=0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize your input devices here
 */
void touchpad_init(void)
{
    BSP_TS_Init(TFT_HOR_RES, TFT_VER_RES);

    static lv_indev_drv_t indev_drv;                       /*Descriptor of an input device driver*/
    lv_indev_drv_init(&indev_drv);                  /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;         /*The touchpad is pointer type device*/
    indev_drv.read_cb = touchpad_read;

    lv_indev_drv_register(&indev_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Read an input device
 * @param indev_id id of the input device to read
 * @param x put the x coordinate here
 * @param y put the y coordinate here
 * @return true: the device is pressed, false: released
 */
static void touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    /* Read your touchpad */
    static int16_t last_x = 0;
    static int16_t last_y = 0;
    //BSP_LED_Toggle(LED3);

    BSP_TS_GetState(Instance, &TS_State);
    if(TS_State.TouchDetected) {
    		data->point.x = TS_State.TouchX;  //data->point.x = TS_State.TouchX[0];
    		data->point.y = TS_State.TouchY;  //data->point.y = TS_State.TouchY[0];
            last_x = data->point.x;
            last_y = data->point.y;
            data->state = LV_INDEV_STATE_PRESSED;
    } else {
            data->point.x = last_x;
            data->point.y = last_y;
            data->state = LV_INDEV_STATE_RELEASED;
    }
}
