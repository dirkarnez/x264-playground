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
### Using
- [dirkarnez/x264-prebuilt](https://github.com/dirkarnez/x264-prebuilt)
