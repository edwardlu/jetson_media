#include <iostream>
#include <fstream>
#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main()
{
	std::ifstream in("camera_dev.json");
	json cam_config;
	in >> cam_config;
	
	std::string dev = "camera_";

	for(int i = 0;i<8;i++)
	{
		std::string dev_path = dev + std::to_string(i);
		auto camera = cam_config.at(dev_path.c_str());
		int dev_id = static_cast<int>(camera.at("device_id"));
		unsigned int width  = static_cast<int>(camera.at("width"));
		unsigned int height = static_cast<int>(camera.at("height"));
		std::string formate = camera.at("formate");

		std::cout<<"device : "<<dev_id<<" w :"<<width<<" h : "<<height<<" formate : "<<formate<<std::endl;
	}

	return 0;
}
