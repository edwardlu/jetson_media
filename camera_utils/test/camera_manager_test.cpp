#include <iostream>
#include "camera_manager.h"
using namespace camera_config;

int main()
{
	std::string dev = "camera_7";
	camera_manager& manager = camera_manager::get_instance();
	manager.parse_camera_config_file("./camera_config/camera_dev.json");

	camera_param par = manager.get_camera_desc(dev);
	std::cout<<par.device_id<<std::endl;
	std::cout<<par.cam_w<<std::endl;
	std::cout<<par.cam_h<<std::endl;
	std::cout<<par.v4l2_path<<std::endl;

	return 0;
}
