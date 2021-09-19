#include "umd.h"
#include "controller.h"
#include "gz_flags.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"

namespace UMDIndicator {
using namespace Controller;

static bool lastFrameADown = false;
static bool lastFrameBDown = false;

static bool start_timer = false;
uint32_t previous_counter = 0;
uint32_t current_counter = 0;
uint32_t counter_difference = 0;
static int firstPressedButton = -1;
static bool exitCheck = false;
static char buf[20];

static const char* getPressedButtonText() {
    if (!button_is_held(A, POST_GAME_LOOP) && button_is_down(A))
        return "A";
    else if (!button_is_held(B, POST_GAME_LOOP) && button_is_down(B))
        return "B";
 
    return "";
}

void run() {
    //Reset everything if map is not active
    if (g_meter2_info.mMapStatus != 2 && g_meter2_info.mMapStatus != 3) {
        counter_difference = 0;
        firstPressedButton = -1;
        exitCheck = false;
        start_timer = false;
    }

    if (g_meter2_info.mMenuWindowClass != NULL) {
        current_counter = cCt_getFrameCount();

        //Activate frame counter as soon as a map opening was scheduled
        if (start_timer == false && (g_meter2_info.mMapStatus == 2 || g_meter2_info.mMapStatus == 3)) {

            bool eventRunning = dMw_c__isEventCheck(g_meter2_info.mMenuWindowClass);

            if (!eventRunning) {
                start_timer = true;
                previous_counter = current_counter;
                counter_difference = 0;
            }
        }

        if (start_timer == true && !exitCheck) {

            counter_difference += current_counter - previous_counter;
            previous_counter = current_counter;

            //Only care up to 15f after
            if (counter_difference < 15) {

                //Ensure A or B was freshly pressed
                if ((!button_is_held(A, POST_GAME_LOOP) && button_is_down(A)) || (!button_is_held(B, POST_GAME_LOOP) && button_is_down(B))) {

                    if (counter_difference == 0) {

                        //A or B were pressed together (first button) = BAD
                        if ((!button_is_held(A, POST_GAME_LOOP) && button_is_down(A)) && (!button_is_held(B, POST_GAME_LOOP) && button_is_down(B))) {
                            FIFOQueue::push("hit both A/B as first", Queue, 0x0000FF00);
                            exitCheck = true;
                        } else {
                            //A or B is pressed here (first button) = GOOD
                            if (!button_is_held(A, POST_GAME_LOOP) && button_is_down(A))
                                firstPressedButton = 0;
                            else
                                firstPressedButton = 1;

                            tp_sprintf(buf, "got first %s", getPressedButtonText());
                            FIFOQueue::push(buf, Queue, 0x00CC0000);
                        }

                    } else if (counter_difference == 1 && firstPressedButton != -1) {
                        // B or A was pressed here as second button, success
                        FIFOQueue::push("got UMD", Queue, 0x00CC0000);
                        exitCheck = true;
                    } else { //We went late

                        //Missed second button
                        if (firstPressedButton != -1) {

                            //Ensure this is the button that needs to be pressed
                            if ((firstPressedButton == 0 && button_is_down(B)) || (firstPressedButton == 1 && button_is_down(A))) {
                                tp_sprintf(buf, "%df late on second %s", counter_difference - 1, getPressedButtonText());
                                FIFOQueue::push(buf, Queue, 0x99000000);
                                exitCheck = true;
                            }           
                        } else { //Missed first button
                            tp_sprintf(buf, "%df late on first %s", counter_difference, getPressedButtonText());
                            FIFOQueue::push(buf, Queue, 0x99000000);
                            exitCheck = true;
                        }
                    }
                }
                else { //Neither A or B was freshly pressed

                    if (counter_difference == 0) { //A or B wasn't pressed on frame 0, we possibly went early

                        if (lastFrameADown && lastFrameBDown) {
                            FIFOQueue::push("1f early on A/B", Queue, 0x0000FF00);
                            exitCheck = true;
                        }
                        else if (lastFrameADown) {
                            FIFOQueue::push("1f early on A", Queue, 0x0000FF00);
                            exitCheck = true;
                        }  
                        else if (lastFrameBDown) {
                            FIFOQueue::push("1f early on B", Queue, 0x0000FF00);
                            exitCheck = true;
                        }
                    }
                }             
            } else {
                exitCheck = true;
            }
        }
    }

    lastFrameADown = button_is_down(A) && !button_is_held(A, POST_GAME_LOOP);
    lastFrameBDown = button_is_down(B) && !button_is_held(B, POST_GAME_LOOP);
}
}  // namespace UMDIndicator