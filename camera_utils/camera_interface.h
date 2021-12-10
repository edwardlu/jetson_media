#ifndef CAMERA_INTERFACE_H
#define CAMERA_INTERFACE_H

#include "camera_manager.h"
namespace camera_intf {
class camera_interface
{
public:
	camera_interface() = default;
	virtual ~camera_interface() {

	}

	virtual void init_camera_device() = 0;
	virtual void close_camera_device() = 0;
	virtual void stat_camera_capture() = 0;
	
	camera_config::camera_manager& get_manager()
	{
		return camera_config::camera_manager::get_instance();
	}
private:
	//none copable and movable
	camera_interface(const camera_interface& inft) = delete;
	camera_interface(camera_interface&& inft) = delete;
	camera_interface& operator=(const camera_interface& inft) = delete;
	camera_interface& operator=(camera_interface&& inft) = delete;
};
}

#endif
