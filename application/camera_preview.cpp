#include "camera_interface.h"
#include "veye_xavie_camera.hpp"

#define CAMERA_CONFIG_PATH "./camera_config/camera_dev.json"

int main()
{
	camera_intf::camera_interface *veye_cam = new vendor_veye::veye_camera();
	camera_config::camera_manager& manager = veye_cam->get_manager();

	manager.parse_camera_config_file(CAMERA_CONFIG_PATH);
	std::string dev = "camera_7";
	camera_config::camera_param par = manager.get_camera_desc(dev);
	std::cout<<par.device_id<<std::endl;
	std::cout<<par.cam_w<<std::endl;
	std::cout<<par.cam_h<<std::endl;
	std::cout<<par.v4l2_path<<std::endl;

	delete veye_cam;
	return 0;
}
