#include "display.h"
#include <esp_log.h>
#include "core2forAWS.h"

#define TAG "display"

//Nyan Cat
#define NUM_IMAGES 6
LV_IMG_DECLARE(original_key_0);
LV_IMG_DECLARE(original_key_1);
LV_IMG_DECLARE(original_key_2);
LV_IMG_DECLARE(original_key_3);
LV_IMG_DECLARE(original_key_4);
LV_IMG_DECLARE(original_key_5);

// STAR IMAGES
#define STAR_FRAMES 6
LV_IMG_DECLARE(star_key_0);
LV_IMG_DECLARE(star_key_1);
LV_IMG_DECLARE(star_key_2);
LV_IMG_DECLARE(star_key_3);
LV_IMG_DECLARE(star_key_4);
LV_IMG_DECLARE(star_key_5);


static const lv_img_dsc_t *my_images[NUM_IMAGES] = {
    &original_key_0,
    &original_key_1,
    &original_key_2,
    &original_key_3,
    &original_key_4,
    &original_key_5
};


static const lv_img_dsc_t *star_frames[STAR_FRAMES] = {
    &star_key_0,
    &star_key_1,
    &star_key_2,
    &star_key_3,
    &star_key_4,
    &star_key_5
};
static void star_looper(lv_task_t *task) {
		  
	//(void)param;
	
	static int frame_index = 0;
	lv_img_set_src(task->user_data, star_frames[frame_index]); /* Set the next image */
	
	frame_index++;
	if(frame_index == 6)
         frame_index = 0;	    
}

static lv_obj_t *img_loop;
static void img_looper(lv_task_t *param) {
		  
	(void)param;
	
	static int img_index = 0;
	lv_img_set_src(img_loop, my_images[img_index]); /* Set the next image */
	
	img_index++;
	if(img_index == 6)
         img_index = 0;	    
}


void create_canvans(lv_obj_t * canvas, uint32_t x_pos, uint32_t y_pos){
    lv_draw_line_dsc_t line_dsc_1;
    lv_draw_line_dsc_init(&line_dsc_1);
    line_dsc_1.width = 20;
    line_dsc_1.color = lv_color_hex(0xff0000);

    lv_draw_line_dsc_t line_dsc_2;
    lv_draw_line_dsc_init(&line_dsc_2);
    line_dsc_2.width = 20;
    line_dsc_2.color = lv_color_hex(0xff9900);

    lv_draw_line_dsc_t line_dsc_3;
    lv_draw_line_dsc_init(&line_dsc_3);
    line_dsc_3.width = 20;
    line_dsc_3.color = lv_color_hex(0xffff00);

    lv_draw_line_dsc_t line_dsc_4;
    lv_draw_line_dsc_init(&line_dsc_4);
    line_dsc_4.width = 20;
    line_dsc_4.color = lv_color_hex(0x33ff00);

    lv_draw_line_dsc_t line_dsc_5;
    lv_draw_line_dsc_init(&line_dsc_5);
    line_dsc_5.width = 20;
    line_dsc_5.color = lv_color_hex(0x0099ff);

    lv_draw_line_dsc_t line_dsc_6;
    lv_draw_line_dsc_init(&line_dsc_6);
    line_dsc_6.width = 20;
    line_dsc_6.color = lv_color_hex(0x6633ff);


    static lv_point_t line_points_1[] = { {0, 10}, {60, 10} };
    static lv_point_t line_points_2[] = { {0, 30}, {60, 30} };
    static lv_point_t line_points_3[] = { {0, 50}, {60, 50} };
    static lv_point_t line_points_4[] = { {0, 70}, {60, 70} };
    static lv_point_t line_points_5[] = { {0, 90}, {60, 90} };
    static lv_point_t line_points_6[] = { {0, 110}, {60, 110} };


    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(60, 20 * 6)];
    
    lv_canvas_set_buffer(canvas, cbuf, 60, 20 * 6, LV_IMG_CF_TRUE_COLOR);
    //lv_canvas_fill_bg(canvas, LV_COLOR_WHITE, LV_OPA_50);
    lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, x_pos, y_pos);
    lv_canvas_draw_line(canvas, line_points_1, 2, &line_dsc_1);
    lv_canvas_draw_line(canvas, line_points_2, 2, &line_dsc_2);
    lv_canvas_draw_line(canvas, line_points_3, 2, &line_dsc_3);
    lv_canvas_draw_line(canvas, line_points_4, 2, &line_dsc_4);
    lv_canvas_draw_line(canvas, line_points_5, 2, &line_dsc_5);
    lv_canvas_draw_line(canvas, line_points_6, 2, &line_dsc_6);
}

#define CANVAS_WIDTH 100
#define CANVAS_HEIGHT 60

#define THREAD_WIDTH 10
#define THREAD_HEIGHT 112

void display_init()
{
    Core2ForAWS_Display_SetBrightness(70);
    lv_obj_t* opener_scr = lv_scr_act(); 

    //rainbow colors
    //#ff0000
    //#ff9900;
    //#ffff00;
    //#33ff00
    //#0099ff
    //#6633ff
    // font: SilkscreenNormal, Monaco, "Courier New", Courier, monospace
    //opacity .9

    //Stars
    lv_obj_t * star_1 = lv_canvas_create(opener_scr, NULL);
    lv_obj_align(star_1,NULL,LV_ALIGN_IN_TOP_LEFT,0, 5);
    lv_task_create( star_looper, 280, LV_TASK_PRIO_LOWEST, star_1 );


    lv_anim_t star_animation_1;
    lv_anim_init(&star_animation_1);
    lv_anim_set_exec_cb(&star_animation_1, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&star_animation_1, star_1); 
    lv_anim_set_time(&star_animation_1, 2000);
    lv_anim_set_values(&star_animation_1, 350, 0);
    lv_anim_set_repeat_count(&star_animation_1, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&star_animation_1);


    // lv_obj_t * star_2 = lv_canvas_create(lv_scr_act(), NULL);
    // lv_obj_align(star_2,lv_scr_act(),LV_ALIGN_IN_TOP_LEFT,0, 150);
    // lv_task_create( star_looper, 280, LV_TASK_PRIO_LOWEST, star_2 );


    // lv_anim_t star_animation_2;
    // lv_anim_init(&star_animation_2);
    // lv_anim_set_exec_cb(&star_animation_2, (lv_anim_exec_xcb_t) lv_obj_set_x);
    // lv_anim_set_var(&star_animation_2, star_2); 
    // lv_anim_set_time(&star_animation_2, 2000);
    // lv_anim_set_values(&star_animation_2, 600, 100);
    // lv_anim_set_repeat_count(&star_animation_2, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_start(&star_animation_2);

    // lv_obj_t * star_3 = lv_canvas_create(lv_scr_act(), NULL);
    // lv_obj_align(star_3,lv_scr_act(),LV_ALIGN_IN_TOP_LEFT,0, 250);
    // lv_task_create( star_looper, 280, LV_TASK_PRIO_LOWEST, star_3 );

    // lv_anim_t star_animation_3;
    // lv_anim_init(&star_animation_3);
    // lv_anim_set_exec_cb(&star_animation_3, (lv_anim_exec_xcb_t) lv_obj_set_x);
    // lv_anim_set_var(&star_animation_3, star_3); 
    // lv_anim_set_time(&star_animation_3, 2000);
    // lv_anim_set_values(&star_animation_3, 550, 50);
    // lv_anim_set_repeat_count(&star_animation_3, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_start(&star_animation_3);


    //rainbow
    uint32_t speed = 500;

    lv_obj_t * tail_1 = lv_canvas_create(opener_scr, NULL);
    create_canvans(tail_1, -80, 0);

    lv_obj_t * tail_2 = lv_canvas_create(opener_scr, NULL);
    create_canvans(tail_2, -80, 10);

    lv_obj_t * tail_3 = lv_canvas_create(opener_scr, NULL);
    create_canvans(tail_3, -80, 0);

    lv_obj_t * tail_4 = lv_canvas_create(opener_scr, NULL);
    create_canvans(tail_4, -80, 10);

    lv_anim_t tail_ani_1;
    lv_anim_init(&tail_ani_1);
    lv_anim_set_exec_cb(&tail_ani_1, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&tail_ani_1, tail_1); 
    lv_anim_set_time(&tail_ani_1, speed);
    lv_anim_set_values(&tail_ani_1, 160, 160 - 120);// origen, destino
    lv_anim_set_repeat_count(&tail_ani_1, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&tail_ani_1);

    lv_anim_t tail_ani_2;
    lv_anim_init(&tail_ani_2);
    lv_anim_set_exec_cb(&tail_ani_2, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&tail_ani_2, tail_2); 
    lv_anim_set_time(&tail_ani_2, speed);
    lv_anim_set_values(&tail_ani_2, 100, 100 - 120);
    lv_anim_set_repeat_count(&tail_ani_2, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&tail_ani_2);

    lv_anim_t tail_ani_3;
    lv_anim_init(&tail_ani_3);
    lv_anim_set_exec_cb(&tail_ani_3, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&tail_ani_3, tail_3); 
    lv_anim_set_time(&tail_ani_3, speed);
    lv_anim_set_values(&tail_ani_3, 40, 40 - 120);
    lv_anim_set_repeat_count(&tail_ani_3, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&tail_ani_3);

    lv_anim_t tail_ani_4;
    lv_anim_init(&tail_ani_4);
    lv_anim_set_exec_cb(&tail_ani_4, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&tail_ani_4, tail_4); 
    lv_anim_set_time(&tail_ani_4, speed);
    lv_anim_set_values(&tail_ani_4, -20, -140);
    lv_anim_set_repeat_count(&tail_ani_4, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&tail_ani_4);


  //cat  // Create a new LVGL "screen". Screens can be though of as a window.
    img_loop = lv_img_create(opener_scr, NULL);
    lv_obj_align(img_loop,NULL,LV_ALIGN_CENTER,-80,-60);
    lv_task_create( img_looper, 70, LV_TASK_PRIO_LOWEST, NULL );


    // Background
    static lv_style_t bg_style;
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, LV_STATE_DEFAULT, lv_color_hex(0xf4d8f));
    lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &bg_style); 
}