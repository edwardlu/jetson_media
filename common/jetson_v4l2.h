#include <iostream>
#include <linux/videodev2.h>
#include <strings.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define CLEAR(x) memset(&(x), 0, sizeof (x))
#define ARRAY_SIZE(a)   (sizeof(a)/sizeof((a)[0]))

unsigned int v4l2_format_code(const char *name);
int xioctl(int fd,int request, void *arg);
bool check_camera_device(char *camera_name);
int open_v4l2_device(char *camera_name);
bool check_capabilities(int video_fd);
bool set_camera_formate(int video_fd, unsigned int pixfmt, unsigned int width, unsigned int height);
bool get_camera_formate(int video_fd, unsigned int& pixfmt, unsigned int& width, unsigned int& height, unsigned int& byte_per_line, unsigned int& image_size);
bool get_camera_frame_rate(int video_fd,unsigned int& denomin, unsigned int& numer);

#ifdef V4L2_FRAME_SIZE_CONTROL
int enum_frame_intervals(int video_fd, unsigned int pixfmt, unsigned int width, unsigned int height);
int enum_frame_sizes(int video_fd, unsigned int pixfmt);
int enum_frame_formats(int video_fd);
#endif
