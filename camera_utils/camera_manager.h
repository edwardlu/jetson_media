/*
Lubin 
camera manager -  signle instance
*/
#include <iostream>
#include <string>
#include <vector>
#include "common/ioctl.h"

#define MAX_CAMERA_DEVICES_NUM 8

namespace {
enum class camera_type : int 
{
	FRONT_LEFT = 0,
	FRONT_RIGHT,
	FRONT_CENTER,
	RARE_LEFT,
	RARE_RIGHT,
	RARE_CENTER,
	NONE_TYPE
};

struct camera_param
{
	unsigned int cam_pixfmt;
	unsigned int cam_w;
	unsigned int cam_h;
};

struct camera_desc
{
	int camera_fd; 
	std::string device_name;
	std::string camera_desc;
	std::vector<camera_param> param;
};

inline std::string get_camera_desc(camera_type type)
{
	switch(type)
	{
	case FRONT_LEFT:
		return "Front_Left_Camera";
	case FRONT_RIGHT:
		return "Front_Right_Camera";
	case FRONT_CENTER:
		return "Front_Center_Camera";
	case RARE_LEFT:
		return "Rare_Left_Camera";
	case RARE_RIGHT:
		return "Rare_Right_Camera";
	case RARE_CENTER:
		return "Rare_Center_Camera";
	default:
		return "Camera_Not_Defined";
	}
}
}

namespace camera_manager
{
class camera_manager
{
public:
	 ~camera_manager() {
		std::cout<<"camera_manager exit"<<std::endl;
	}
	camera_manager(const camera_manager&) = delete;
	camera_manager& operator=(const camera_manager&) = delete;

	static camera_manager& get_instance()
	{
		static camera_manager instance;
		return instance;
	}

	camera_desc& get_camera_desc(const std::string cam_name);
	
private:
	camera_manager()
	{
		std::cout<<"camera_manager inited"<<std::endl;
		cams.reserve(MAX_CAMERA_DEVICES_NUM);
	}
	bool scan_camera_device();

	std::vector<camera_param> cams;	
};
}
