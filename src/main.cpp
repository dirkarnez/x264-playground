#include <stdio.h>
#include <stdlib.h>

#include "stdint.h"
#include "x264.h"


#define WIDTH 640
#define HEIGHT 480

#define FRAME_NUM 480
#define FRAME_SIZE (WIDTH * HEIGHT * 2)

unsigned char in_buf[FRAME_SIZE];  // 读取每个YUYV帧的BUFFER

int main(int argc, char** argv)
{

    int ret;
    int y_size;
    int i,j;

    //FILE* fp_src  = fopen("../cuc_ieschool_640x360_yuv444p.yuv", "rb");
    FILE* fp_src  = fopen("./vid_1565629469_640x480_480frames.yuyv", "rb");

    FILE* fp_dst = fopen("output.h264", "wb");

    //Encode 50 frame
    //if set 0, encode all frame
    int frame_num=FRAME_NUM;
    int csp=X264_CSP_I422;  /* yuv 4:2:2 planar */
    int width=WIDTH,height=HEIGHT;

    unsigned char *y_plane;
    unsigned char *u_plane;
    unsigned char *v_plane;

    int iNal   = 0;
    x264_nal_t* pNals = NULL;
    x264_t* pHandle   = NULL;
    x264_picture_t* pPic_in = (x264_picture_t*)malloc(sizeof(x264_picture_t));
    x264_picture_t* pPic_out = (x264_picture_t*)malloc(sizeof(x264_picture_t));
    x264_param_t* pParam = (x264_param_t*)malloc(sizeof(x264_param_t));

    //Check
    if(fp_src==NULL||fp_dst==NULL){
        printf("Error open files.\n");
        return -1;
    }

    x264_param_default(pParam);
    pParam->i_width   = width;
    pParam->i_height  = height;
    /*
    //Param
    pParam->i_log_level  = X264_LOG_DEBUG;
    pParam->i_threads  = X264_SYNC_LOOKAHEAD_AUTO;
    pParam->i_frame_total = 0;
    pParam->i_keyint_max = 10;
    pParam->i_bframe  = 5;
    pParam->b_open_gop  = 0;
    pParam->i_bframe_pyramid = 0;
    pParam->rc.i_qp_constant=0;
    pParam->rc.i_qp_max=0;
    pParam->rc.i_qp_min=0;
    pParam->i_bframe_adaptive = X264_B_ADAPT_TRELLIS;
    pParam->i_fps_den  = 1;
    pParam->i_fps_num  = 25;
    pParam->i_timebase_den = pParam->i_fps_num;
    pParam->i_timebase_num = pParam->i_fps_den;
    */
    pParam->i_csp=csp;
    x264_param_apply_profile(pParam, x264_profile_names[5]);

    pHandle = x264_encoder_open(pParam);

    x264_picture_init(pPic_out);
    x264_picture_alloc(pPic_in, csp, pParam->i_width, pParam->i_height);

    //ret = x264_encoder_headers(pHandle, &pNals, &iNal);

    y_size = pParam->i_width * pParam->i_height;
    //detect frame number
    if(frame_num==0){
        fseek(fp_src,0,SEEK_END);
        switch(csp){
            case X264_CSP_I444:frame_num=ftell(fp_src)/(y_size*3);break;
            case X264_CSP_I420:frame_num=ftell(fp_src)/(y_size*3/2);break;
            default:printf("Colorspace Not Support.\n");return -1;
        }
        fseek(fp_src,0,SEEK_SET);
    }

    //Loop to Encode
    for( i=0;i<frame_num;i++){
        /*
        switch(csp){
            case X264_CSP_I444:{
                fread(pPic_in->img.plane[0],y_size,1,fp_src);	//Y
                fread(pPic_in->img.plane[1],y_size,1,fp_src);	//U
                fread(pPic_in->img.plane[2],y_size,1,fp_src);	//V
                break;}
            case X264_CSP_I420:{
                fread(pPic_in->img.plane[0],y_size,1,fp_src);	//Y
                fread(pPic_in->img.plane[1],y_size/4,1,fp_src);	//U
                fread(pPic_in->img.plane[2],y_size/4,1,fp_src);	//V
                break;}
            default:{
                printf("Colorspace Not Support.\n");
                return -1;}
        }
         */

        // 读取一帧数据
        fread(in_buf, FRAME_SIZE, 1, fp_src);
        /*
         * YUYV的存放顺序是  YUYV YUYV YUYV ... 这种packed格式
         * 数据是交错存储的，因此需要把他们分离出来单独存储
         * 参考  https://blog.csdn.net/zgyulongfei/article/details/7526327
         */
        y_plane = pPic_in->img.plane[0];
        u_plane = pPic_in->img.plane[1];
        v_plane = pPic_in->img.plane[2];
        int is_y = 1, is_u = 1;
        int y_index = 0, u_index = 0, v_index = 0;
        for (j = 0; j < FRAME_SIZE; j++) {
            unsigned char val = in_buf[j];
            if (is_y) {
                *(y_plane + y_index) = val;
                ++y_index;
                is_y = 0;
            } else {
                if (is_u) {
                    *(u_plane + u_index) = val;
                    ++u_index;
                    is_u = 0;
                } else {
                    *(v_plane + v_index) = val;
                    ++v_index;
                    is_u = 1;
                }
                is_y = 1;
            }
        }

        pPic_in->i_pts = i;

        ret = x264_encoder_encode(pHandle, &pNals, &iNal, pPic_in, pPic_out);
        if (ret< 0){
            printf("Error.\n");
            return -1;
        }

        printf("Succeed encode frame: %5d\n",i);

        for ( j = 0; j < iNal; ++j){
            fwrite(pNals[j].p_payload, 1, pNals[j].i_payload, fp_dst);
        }
    }
    i=0;
    //flush encoder
    while(1){
        ret = x264_encoder_encode(pHandle, &pNals, &iNal, NULL, pPic_out);
        if(ret==0){
            break;
        }
        printf("Flush 1 frame.\n");
        for (j = 0; j < iNal; ++j){
            fwrite(pNals[j].p_payload, 1, pNals[j].i_payload, fp_dst);
        }
        i++;
    }
    x264_picture_clean(pPic_in);
    x264_encoder_close(pHandle);
    pHandle = NULL;

    free(pPic_in);
    free(pPic_out);
    free(pParam);

    fclose(fp_src);
    fclose(fp_dst);

    return 0;
}