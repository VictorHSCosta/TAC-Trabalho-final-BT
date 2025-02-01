#include "behaviortree_cpp_v3/bt_factory.h"
#include "approach_object.cpp"
#include "check_battery.cpp"
#include "read_barcode.cpp"
#include "auth_nurse.cpp"

int main()
{
    // We use the BehaviorTreeFactory to register our custom nodes
	BT::BehaviorTreeFactory factory;

  // The recommended way to create a Node is through inheritance.
  factory.registerNodeType<ApproachObject>("ApproachObject");
  factory.registerNodeType<ReadBarcode>("ReadBarcode");
  factory.registerNodeType<AuthNurse>("AuthNurse");

  // Registering a SimpleActionNode using a function pointer.
  // You can use C++11 lambdas or std::bind
  factory.registerSimpleCondition("CheckBattery", [&](BT::TreeNode&) { return CheckBattery(); });

  // Trees are created at deployment-time (i.e. at run-time, but only 
  // once at the beginning). 
    
  // IMPORTANT: when the object "tree" goes out of scope, all the 
  // TreeNodes are destroyed
   auto tree = factory.createTreeFromFile("./my_tree.xml");

  // To "execute" a Tree you need to "tick" it.
  // The tick is propagated to the children based on the logic of the tree.
  // In this case, the entire sequence is executed, because all the children
  // of the Sequence return SUCCESS.
  auto result = tree.tickRootWhileRunning();

	std::cout << "\nBT ended with result: " << result << std::endl;

  return 0;
}
