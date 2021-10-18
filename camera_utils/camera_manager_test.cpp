#include <iostream>
#include "camera_manager.h"

int main()
{
	camera_manager& manager1 = camera_manager::get_instance();
	camera_manager& manager2 = camera_manager::get_instance();
	camera_manager& manager3 = camera_manager::get_instance();
	camera_manager& manager4 = camera_manager::get_instance();

	return 0;
}
