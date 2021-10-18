
class camera_interface
{
public:
	camera_interface() = default;
	~camera_interface() = default;

	virtual void init_camera_device() = 0;
	virtual void close_camera_device() = 0;
	virtual void stat_camera_capture() = 0;
};
