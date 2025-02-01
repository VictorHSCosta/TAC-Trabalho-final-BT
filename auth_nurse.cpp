//SyncConditionNodeExample with Output Port

#include <string>
#include <iostream>

class AuthNurse: public BT::ConditionNode
{
public:
	std::string key;

  AuthNurse(const std::string& name, const BT::NodeConfiguration& config): BT::ConditionNode(name, config){
		key = "auth_token";
	}

  static BT::PortsList providedPorts()
  {
    return { BT::InputPort<std::string>("auth") };
  }

  // ohis Action writes a value into the port "text"
	BT::NodeStatus tick() override
  {
		BT::Optional<std::string> msg = getInput<std::string>("auth");
		if(!msg)
			throw BT::RuntimeError("missing auth input", msg.error());

		if(msg.value() != this->key){
			std::cout << "Barcode does not match auth key\n";
			return BT::NodeStatus::FAILURE;
		}

		std::cout << "Nurse authenticated successfully\n";
		return BT::NodeStatus::SUCCESS;
  }
};
