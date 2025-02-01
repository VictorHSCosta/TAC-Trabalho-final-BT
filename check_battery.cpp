#include <iostream>
#include <string>

BT::NodeStatus CheckBattery()
{
	int battery_level;;

	// User inputs battery level from terminal (STDIN)
	std::cout << "Please input current battery level:" << std::endl;
	std::cin >> battery_level;

	if(battery_level < 30){
		std::cout << "BATTERY LOW" << std::endl;
		return BT::NodeStatus::FAILURE;
		
	}

	std::cout << "Battery OK" << std::endl;
	return BT::NodeStatus::SUCCESS;
}
