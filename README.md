x264-playground
===============
### Tutorials
- [v4l2/simplest_x264_encoder.c at master · 373518155/v4l2](https://github.com/373518155/v4l2/blob/master/yuyv_to_h264/simplest_x264_encoder.c)
  - [World's Smallest H.264 Encoder - Contract Engineering, Product Design & Development Company - Cardinal Peak](https://www.cardinalpeak.com/blog/worlds-smallest-h-264-encoder)
    ```bash
    ffmpeg.exe -i angel.mov -s sqcif -pix_fmt yuv420p angel.yuv

    # I compile the H.264 encoder:
    gcc ?Wall ?ansi hello264.c ?o hello264

    # And run it:
    hello264 <angel.yuv >angel.264

    #Finally, I use ffmpeg to copy the raw H.264 NAL units into an MP4 file:
    ffmpeg.exe -f h264 -i angel.264 -vcodec copy angel.mp4
    ```
- [H.264 入门篇 - 00 (简介)_advanced video coding for generic audiovisual serv-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127333307?spm=1001.2014.3001.5502)
- [H.264 入门篇 - 01 (Bitstream)_h264bitstream-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127338270)
- [H.264 入门篇 - 02 (帧内预测相邻像素推导)_h264预测像素-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127338716)
- [H.264 入门篇 - 03 (宏块类型)_h.264 宏块-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127338752)
- [H.264 入门篇 - 04 (B_Skip、P_Skip 、B_Direct宏块)_h264 p_skip-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127338873)
- [H.264 入门篇 - 05 (帧内预测)-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127338910)
- [H.264 入门篇 - 06 (帧间预测 - 运动估计)_h264帧间预测-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127341877)
- [H.264 入门篇 - 07 (帧间预测 - 解码图像缓存 DPB)_h264 codec picture buffer-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342017)
- [H.264 入门篇 - 08 (帧间预测 - 已解码参考帧的标记)_memory_management_control_operation-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342182)
- [H.264 入门篇 - 09 (帧间预测 - 参考帧列表)-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342301)
- [H.264 入门篇 - 10 (帧间预测 - 参考帧列表修改/重排)_参考帧 重建帧-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342398)[H.264 入门篇 - 11 (帧间预测 - DPB 管理策略)_h264的dpb管理-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342456)
- [H.264 入门篇 - 11 (帧间预测 - DPB 管理策略)_h264的dpb管理-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342456)
- [H.264 入门篇 - 12 (帧间预测 - MVP 求解)_h264 双向预测-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342600)
- [H.264 入门篇 - 13 (POC 求解)_h.264的poc计算-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127342722)
- [H.264 入门篇 - 14 (去块滤波)-CSDN博客](https://stephenzhou.blog.csdn.net/article/details/127344818)

### Using
- [dirkarnez/x264-prebuilt](https://github.com/dirkarnez/x264-prebuilt)

