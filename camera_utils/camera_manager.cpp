#include "camera_manager.h"

camera_param& camera_manager::get_camera_desc(const std::string cam_name)
{
	for (auto it = cams.begin(); it != cams.end();it++)
	{
		if (cam_name == it->device_name) {
			return *it; 
		}
		++it;
	}
}

bool camera_manager::scan_camera_device()
{
	bool ret;
	std::string dev = "/dev/video";

	struct v4l2_capability cap;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;

	for(int i = 0;i<MAX_CAMERA_DEVICES_NUM;i++)
	{
		std::string dev_path = dev + std::to_string(i);
		ret = check_dev_status(dev_path.c_str());
		if(ret == true)
		{
			cams[i].camera_fd = open(dev_path.c_str(), O_RDWR|O_NONBLOCK, 0);
			if(cams[i].camera_fd < 0)
				std::cout<<"Open device "<<dev_path<<" failed"<<endl;
			else {
				if(-1 == xioctl (fd, VIDIOC_QUERYCAP, &cap)) 
				{
					errno_exit("VIDIOC_QUERYCAP");
				} 
				if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) 
				{
					errno_exit("NOT_CAPTURE_DEVICE");
				}

			}
		}
	}
}
