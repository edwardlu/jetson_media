class jetson_xavier_camera : public camera_interface
{
	jetson_xavier_camera();
	~jetson_xavier_camera();

	virtual void init_camera_device() overide;
	virtual void close_camera_device()overide;
	virtual void stat_camera_capture() overide;
};
