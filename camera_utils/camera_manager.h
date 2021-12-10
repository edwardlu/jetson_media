/*
Lubin 
camera manager -  signle instance
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "jetson_v4l2.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#define MAX_CAMERA_DEVICES_NUM 9 //last camera is not available

/* camera status in init stage,not defined in running status
 */
enum class camera_status : int
{
	CAMERA_INITED = 0,
	CAMERA_NOTINITED
};

/* camera type in enum int to compare with device_id
 */
enum class camera_type : int 
{
	CAMERA_0 = 0,
	CAMERA_1,
	CAMERA_2,
	CAMERA_3,
	CAMERA_4,
	CAMERA_5,
	CAMERA_6,
	CAMERA_7,
	CAMERA_NONE
};

inline std::string get_camera_desc(camera_type type)
{
	switch(type)
	{
		case camera_type::CAMERA_0:
		return "Front_Middle";
		case camera_type::CAMERA_1:
		return "Front_Left";
		case camera_type::CAMERA_2:
		return "Front_Right";
		case camera_type::CAMERA_3:
		return "Rare_Middle";
		case camera_type::CAMERA_4:
		return "Rare_Left";
		case camera_type::CAMERA_5:
		return "Rare_Right";
		case camera_type::CAMERA_6:
		return "Aux_Camear_0";
		case camera_type::CAMERA_7:
		return "Aux_Camear_1";
		default:
		return "Camera_Not_Defined";
	}
}

namespace camera_config
{
struct camera_param
{
	unsigned int cam_pixfmt;
	unsigned int cam_w;
	unsigned int cam_h;
	std::string dev_name;
	std::string v4l2_path;
	int device_id;
};

/* Singleton manager
 * camera manager class to holds the info from config files
 */
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

	camera_param& get_camera_desc(const std::string cam_name);

	bool parse_camera_config_file(const char *path);
private:
	camera_manager()
	{
		std::cout<<"camera_manager inited"<<std::endl;
		cams_st.reserve(MAX_CAMERA_DEVICES_NUM);
		cams_param.reserve(MAX_CAMERA_DEVICES_NUM);
	}
	std::vector<camera_status> cams_st;	
	std::vector<camera_param> cams_param;	
};
}
