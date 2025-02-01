//Sync Node Example with Input Port

#include <string>
#include <iostream>


class ReadBarcode : public BT::SyncActionNode
{
public:
	// Notice that when using ports the constructor is different from the normal version
  ReadBarcode(const std::string& name, const BT::NodeConfiguration& config)
    : BT::SyncActionNode(name, config)
  { }

	//providedPortsMethod must be static
  static BT::PortsList providedPorts()
  {
    return { BT::OutputPort<std::string>("auth") };
  }

  // This Action writes a value into the port "text"
	BT::NodeStatus tick() override
  {
		std::string auth;

		std::cout << "\nInput nurse authentication token:" << std::endl;
		std::cin >> auth;
    // the output may change at each tick(). Here we keep it simple.
		setOutput("auth", auth);
    return BT::NodeStatus::SUCCESS;
  }
};
