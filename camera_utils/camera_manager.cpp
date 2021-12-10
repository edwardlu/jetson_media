#include "camera_manager.h"

#define DEBUG_CAMERA_CONFIG 1
namespace camera_config {
struct camera_param& camera_manager::get_camera_desc(const std::string cam_name)
{
	for(auto it = cams.begin();it != cams.end();it++)
	{
		#ifdef DEBUG_CAMERA_CONFIG
		std::cout<<"input cam name : "<<cam_name<<std::endl;
		std::cout<<"local cam name : "<<it->dev_name<<std::endl;
		#endif
		if(cam_name == it->dev_name) 
		{
			return *it; 
		} 
	}
	
	return cams[MAX_CAMERA_DEVICES_NUM];
}

bool camera_manager::parse_camera_config_file(const char *path)
{
	if(path == NULL)
		return false;
	
	std::ifstream in(path);
	json cam_config;
	in >> cam_config;

	std::string dev = "camera_";
	std::string v4l2_path = "/dev/video";

	for(int cam_dev = 0; cam_dev<MAX_CAMERA_DEVICES_NUM;cam_dev++)
	{
		std::string dev_node = dev + std::to_string(cam_dev);
		std::string dev_path = v4l2_path + std::to_string(cam_dev);

		auto camera = cam_config.at(dev_node.c_str());

		int dev_id = static_cast<int>(camera.at("device_id"));
		unsigned int width  = static_cast<int>(camera.at("width"));
		unsigned int height = static_cast<int>(camera.at("height"));
		std::string formate = camera.at("formate");
		
		struct camera_param cam_par;
		cam_par.device_id = dev_id;
		cam_par.cam_pixfmt = ::v4l2_format_code(formate.c_str());
		cam_par.cam_w = width;
		cam_par.cam_h = height;
		cam_par.dev_name = dev_node;
		cam_par.v4l2_path = dev_path;

		cams.push_back(cam_par);
#ifdef DEBUG_CAMERA_CONFIG
		std::cout<<"device : "<<dev_id<<" width : "<<width<<" height : "<<height<<" formate : "<<formate<<std::endl;
#endif
	}
	return true;
}
}
