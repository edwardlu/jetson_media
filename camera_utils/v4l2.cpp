
int xioctl(int fd,int request, void *arg)
{
	int ret;

	do ret = ioctl(fd, request, arg);
	while(-1 == ret && EINTR == errno);

	return ret;
}

bool check_camera_device(char *camera_name)
{
	struct stat st;
	CLEAR(st);

	if(-1 == stat(camera_name, &st)) 
	{
		std::cout<<"can not identify : "<<camera_name<<std::endl;
		return false;
	}

	if(!S_ISCHR(st.st_mode)) 
	{
		std::cout<<"no device"<<std::endl;
		return false;
	}

	return true;
}

int open_device(char *camera_name)
{
	struct stat st;
	if(camera_name == NULL)
	{
		std::cout<<"invalid camera device name"<<std::endl;
		return -1;
	}
	
	int fd = open(camera_name, O_RDWR/* required */|O_NONBLOCK, 0);
	if(-1 == fd)
	{
		std::cout<<"failed to open camera : "<<camera_name<<std::endl;
		return -1;
	} 

	return fd;
}

bool check_capabilities(int video_fd)
{
	struct v4l2_capability cap;
	CLEAR(cap);
	if(-1 == xioctl(video_fd,VIDIOC_QUERYCAP,&cap))
	{
		std::cout<<"VIDIOC_QUERYCAP failed"<<std::endl;
		return false;
	}
	if(!(cap.capabilities&V4L2_CAP_VIDEO_CAPTURE)) 
	{
		std::cout<<"V4L2_CAP_VIDEO_CAPTURE not support"<<std::endl;
		return false;
	}
	
	return true;
}

bool set_camera_formate(int video_fd, unsigned int pixfmt, unsigned int width, unsigned int height)
{
	struct v4l2_format fmt;
	CLEAR(fmt);

	fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width       = width;
	fmt.fmt.pix.height      = height;
	fmt.fmt.pix.pixelformat = pixfmt;
	fmt.fmt.pix.field       = V4L2_FIELD_NONE;

	if(-1 == xioctl(video_fd, VIDIOC_S_FMT, &fmt))
	{
		std::cout<<"VIDIOC_S_FMT failed"<<std::endl;
		return false;
	}

	return true;
}

/*
fmt.fmt.pix.bytesperline
fmt.fmt.pix.sizeimage
*/
bool get_camera_formate(int video_fd, unsigned int& pixfmt, unsigned int& width, unsigned int& height, unsigned int& byte_per_line, unsigned int& image_size)
{
	struct v4l2_format fmt;
	CLEAR(fmt);

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if(-1 == xioctl(video_fd, VIDIOC_G_FMT, &fmt))
	{
		std::cout<<"VIDIOC_S_FMT failed"<<std::endl;
		return false;
	}

	if(fmt.fmt.pix.width != width_in || 
		fmt.fmt.pix.height != height_in ||
		fmt.fmt.pix.pixelformat != pixfmt_in)
	{
		std::cout<<"VIDIOC_S_FMT is not correct"<<std::endl;
		return false;
	}
	pixfmt = fmt.fmt.pix.pixelformat;
	width  = fmt.fmt.pix.width;
	height = fmt.fmt.pix.height;
	byte_per_line = fmt.fmt.pix.bytesperline;
	image_size = fmt.fmt.pix.sizeimage;

	return true;
}


bool get_camera_frame_rate(int video_fd,unsigned int& denomin, unsigned int& numer)
{
	struct v4l2_streamparm streamparm;
	CLEAR(streamparm);
	streamparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if(-1 == xioctl(video_fd, VIDIOC_G_PARM, &streamparm))
	{
		std::cout<<"VIDIOC_G_PARM failed"<<std::endl;
	}
	
	denomin = streamparm.parm.capture.timeperframe.denominator,
	numer = streamparm.parm.capture.timeperframe.numerator);

	return true;
}

#ifdef V4L2_FRAME_SIZE_CONTROL
int enum_frame_intervals(int video_fd, unsigned int pixfmt, unsigned int width, unsigned int height)
{
	int ret;
	struct v4l2_frmivalenum fival;

	CLEAR(fival);
	fival.index = 0;
	fival.pixel_format = pixfmt;
	fival.width = width;
	fival.height = height;

	while((ret = ioctl(video_fd, VIDIOC_ENUM_FRAMEINTERVALS, &fival)) == 0)
	{
		if(fival.type == V4L2_FRMIVAL_TYPE_DISCRETE) {
			printf("%u/%u, ", fival.discrete.numerator, fival.discrete.denominator);
		} else if(fival.type == V4L2_FRMIVAL_TYPE_CONTINUOUS) {
			printf("{min { %u/%u } .. max { %u/%u } }, ",
				fival.stepwise.min.numerator, fival.stepwise.min.numerator,
				fival.stepwise.max.denominator, fival.stepwise.max.denominator);
			break;
		} else if(fival.type == V4L2_FRMIVAL_TYPE_STEPWISE) {
			printf("{min { %u/%u } .. max { %u/%u } / "
				"stepsize { %u/%u } }, ",
				fival.stepwise.min.numerator, fival.stepwise.min.denominator,
				fival.stepwise.max.numerator, fival.stepwise.max.denominator,
				fival.stepwise.step.numerator, fival.stepwise.step.denominator);
			break;
		}
		fival.index++;
	}
	printf("\n");
	if (ret != 0 && errno != EINVAL) {
		printf("ERROR enumerating frame intervals: %d\n", errno);
		return errno;
	}

	return 0;
}

int enum_frame_sizes(int video_fd, unsigned int pixfmt)
{
	int ret;
	struct v4l2_frmsizeenum fsize;

	CLEAR(fsize);
	fsize.index = 0;
	fsize.pixel_format = pixfmt;
	while((ret = ioctl(video_fd, VIDIOC_ENUM_FRAMESIZES, &fsize)) == 0)
	{
		if(fsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) {
			printf("{ discrete: width = %u, height = %u }\n",
				fsize.discrete.width, fsize.discrete.height);
			ret = enum_frame_intervals(dev, pixfmt, fsize.discrete.width, fsize.discrete.height);
			if(ret != 0)
				printf("  Unable to enumerate frame sizes.\n");
			} else if(fsize.type == V4L2_FRMSIZE_TYPE_CONTINUOUS) {
				printf("{ continuous: min { width = %u, height = %u } .. "
					"max { width = %u, height = %u } }\n",
					fsize.stepwise.min_width, fsize.stepwise.min_height,
					fsize.stepwise.max_width, fsize.stepwise.max_height);
				printf("  Refusing to enumerate frame intervals.\n");
				break;
			} else if(fsize.type == V4L2_FRMSIZE_TYPE_STEPWISE) {
				printf("{ stepwise: min { width = %u, height = %u } .. "
					"max { width = %u, height = %u } / "
					"stepsize { width = %u, height = %u } }\n",
					fsize.stepwise.min_width, fsize.stepwise.min_height,
					fsize.stepwise.max_width, fsize.stepwise.max_height,
					fsize.stepwise.step_width, fsize.stepwise.step_height);
				printf("  Refusing to enumerate frame intervals.\n");
				break;
			}
			fsize.index++;
		}
		if(ret != 0 && errno != EINVAL) {
			printf("ERROR enumerating frame sizes: %d\n", errno);
		return errno;
	}

	return 0;
}

int enum_frame_formats(int video_fd)
{
	int ret;
	struct v4l2_fmtdesc fmt;

	CLEAR(fmt);
	fmt.index = 0;
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	while((ret = ioctl(video_fd, VIDIOC_ENUM_FMT, &fmt)) == 0) 
	{
		fmt.index++;
		printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
			fmt.pixelformat & 0xFF, (fmt.pixelformat >> 8) & 0xFF,
			(fmt.pixelformat >> 16) & 0xFF, (fmt.pixelformat >> 24) & 0xFF,
			fmt.description);
		ret = enum_frame_sizes(dev, fmt.pixelformat);
		if (ret != 0)
			printf("  Unable to enumerate frame sizes.\n");
		}
		if (errno != EINVAL) {
			printf("ERROR enumerating frame formats: %d\n", errno);
			return errno;
		}

	return 0;
}
#endif


