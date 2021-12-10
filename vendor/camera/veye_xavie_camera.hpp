#include "camera_interface.h"
namespace vendor_veye {
class veye_camera : public camera_intf::camera_interface
{
public:
	veye_camera();
	~veye_camera();

	void init_camera_device() override;
	void close_camera_device() override;
	void stat_camera_capture() override;
	
	//i2c control interface
private:

};
}
