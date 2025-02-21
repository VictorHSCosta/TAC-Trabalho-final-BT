#include "behaviortree_cpp_v3/bt_factory.h"
#include <bits/stdc++.h>
#define SS BT::NodeStatus::SUCCESS
#define FF BT::NodeStatus::FAILURE
#define INPUT BT::InputPort<std::string>
#define OUTPUT BT::OutputPort<std::string>
using namespace std;
#include <thread>  // Para usar std::this_thread::sleep_for
#include <chrono>  // Para std::chrono::seconds
//		Foi adaptado o codigo do github em que a behaviour tree corresponderia ao arquivo exercicio.xml
//		que seria o exercicio passado. Comandos para compilar e executar seriam:
//		>> cmake .
//		>> make
//		>> ./BT

class VerificarEquipamentos : public BT::ConditionNode
{
public:
    VerificarEquipamentos(const std::string& name, const BT::NodeConfiguration& config)
        : BT::ConditionNode(name, config) 
    {
        srand(time(nullptr)); // Inicializa o gerador de números aleatórios
    }

    // Esse nó não precisa de portas, pois apenas verifica um estado interno
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[VerificarEquipamentos] Checando disponibilidade dos equipamentos..." << std::endl;

        // Simulando um resultado aleatório com 50% de chance
        bool equipamentos_disponiveis = (rand() % 2 == 0);  // Retorna true ou false com 50% de chance

        if (equipamentos_disponiveis)
        {
            std::cout << "[VerificarEquipamentos] Tenho os equipamentos necessários." << std::endl;
            return BT::NodeStatus::SUCCESS;  // Sucesso se os equipamentos estiverem disponíveis
        }

        std::cout << "[VerificarEquipamentos] Não tenho os equipamentos necessários." << std::endl;
        return BT::NodeStatus::FAILURE;  // Falha se os equipamentos não estiverem disponíveis
    }
};

class VerificarBateria : public BT::ConditionNode
{
public:
    VerificarBateria(const std::string& name, const BT::NodeConfiguration& config)
        : BT::ConditionNode(name, config) 
    {
        srand(time(nullptr)); // Inicializa o gerador de números aleatórios
    }

    // Esse nó não precisa de portas, pois apenas verifica um estado interno
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[VerificarBateria] Checando nível da bateria..." << std::endl;

        // Gera um nível de bateria aleatório entre 10% e 100%
        int nivel_bateria = 10 + (rand() % 91);

        // Sempre imprime a carga da bateria
        std::cout << "[VerificarBateria] Nível da bateria: " << nivel_bateria << "%" << std::endl;

        // Se a bateria estiver abaixo de 30%, precisa recarregar (retorna FAILURE)
        if (nivel_bateria < 30)
        {
            std::cout << "[VerificarBateria] Preciso de recarga para completar a missão." << std::endl;
            return BT::NodeStatus::FAILURE;
        }

        // Se a bateria estiver acima de 30%, a missão pode continuar (retorna SUCCESS)
        std::cout << "[VerificarBateria] Missão pode ser concluída com sucesso." << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

class TempoParaConcluir : public BT::SyncActionNode
{
public:
    TempoParaConcluir(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config) 
    {
        srand(time(nullptr)); // Inicializa o gerador de números aleatórios
    }

    // Define a porta de saída "ttc"
    static BT::PortsList providedPorts()
    {
        return { BT::OutputPort<int>("ttc") };
    }

    BT::NodeStatus tick() override
    {
        std::cout << "[TempoParaConcluir] Calculando tempo estimado para conclusão..." << std::endl;

        // Gera um tempo aleatório entre 10 e 120 minutos
        int tempo_estimado = 10 + (rand() % 111); 

        // Define a saída "ttc" com o tempo gerado
        setOutput("ttc", tempo_estimado);

        std::cout << "[TempoParaConcluir] Tempo estimado para conclusão: " << tempo_estimado << " minutos." << std::endl;
        
        return BT::NodeStatus::SUCCESS;
    }
};

class SalaEstaLivre : public BT::ConditionNode
{
public:
    SalaEstaLivre(const std::string& name, const BT::NodeConfiguration& config)
        : BT::ConditionNode(name, config) 
    {
        srand(time(nullptr)); // Inicializa o gerador de números aleatórios
    }

    // Esse nó não precisa de portas, pois apenas verifica um estado interno
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[SalaEstaLivre] Verificando se a sala está livre..." << std::endl;

        // Simulando um resultado aleatório com 50% de chance
        bool sala_livre = (rand() % 2 == 0);  // Retorna true ou false com 50% de chance

        if (sala_livre)
        {
            std::cout << "[SalaEstaLivre] Sala está livre!" << std::endl;
            return BT::NodeStatus::SUCCESS;  // Sucesso se a sala estiver livre
        }

        std::cout << "[SalaEstaLivre] Sala ocupada!" << std::endl;
        return BT::NodeStatus::FAILURE;  // Falha se a sala estiver ocupada
    }
};

class PassarPano : public BT::SyncActionNode
{
public:
    PassarPano(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config) {}

    // Nenhuma porta necessária, pois a ação é fixa
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[PassarPano] Iniciando processo de limpeza..." << std::endl;

        // Simula um tempo de 2 segundos para passar o pano
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "[PassarPano] Chão limpo com sucesso!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};



class MoverMobilia : public BT::SyncActionNode
{
public:
    MoverMobilia(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config) {}

    // Esse nó não precisa de portas, pois a movimentação ocorre sem parâmetros
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[MoverMobilia] Iniciando movimentação da mobília..." << std::endl;

        // Simula um tempo de movimentação de 2 segundos
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "[MoverMobilia] Mobília movida com sucesso!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

class IrParaDestino : public BT::AsyncActionNode
{
public:
    IrParaDestino(const std::string& name, const BT::NodeConfiguration& config)
        : BT::AsyncActionNode(name, config) {}

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<int>("x"), BT::InputPort<int>("y") };
    }

    BT::NodeStatus tick() override
    {
        int x, y;

        // Obtendo as coordenadas de destino
        if (!getInput<int>("x", x))
        {
            throw BT::RuntimeError("Parâmetro [x] ausente em IrParaDestino");
        }
        if (!getInput<int>("y", y))
        {
            throw BT::RuntimeError("Parâmetro [y] ausente em IrParaDestino");
        }

        // Simulando o movimento do robô
        std::cout << "Movendo para (" << x << ", " << y << ")..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simula tempo de deslocamento

        std::cout << "Chegou ao destino (" << x << ", " << y << ")!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};


class EsterilizarMobilia : public BT::SyncActionNode
{
public:
    EsterilizarMobilia(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config) {}

    // Esse nó não precisa de portas, pois a esterilização é um processo fixo
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[EsterilizarMobilia] Iniciando processo de esterilização..." << std::endl;

        // Simula um tempo de processamento de 2 segundos
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "[EsterilizarMobilia] Esterilização concluída com sucesso!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

class EnviarMensagemParaGerente : public BT::SyncActionNode
{
public:
    EnviarMensagemParaGerente(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config) {}

    // Definição da porta de entrada "mensagem"
    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("mensagem") };
    }

    BT::NodeStatus tick() override
    {
        // Obtendo a mensagem da blackboard
        BT::Optional<std::string> mensagem = getInput<std::string>("mensagem");

        // Verifica se a mensagem foi recebida corretamente
        if (!mensagem)
        {
            throw BT::RuntimeError("Erro: parâmetro [mensagem] ausente em EnviarMensagemParaGerente");
        }

        // Imprime a mensagem no console
        std::cout << "[EnviarMensagemParaGerente] Mensagem: " << mensagem.value() << std::endl;

        return BT::NodeStatus::SUCCESS;
    }
};

class DetectarObstaculoLIDAR : public BT::ConditionNode
{
public:
    DetectarObstaculoLIDAR(const std::string& name, const BT::NodeConfiguration& config)
        : BT::ConditionNode(name, config) {}

    // Nenhuma porta necessária, pois o nó apenas verifica a presença de um obstáculo
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[DetectarObstaculoLIDAR] Verificando se há obstáculos..." << std::endl;

        // Simulando uma detecção aleatória de obstáculo
        bool obstaculo_detectado = (rand() % 2 == 0);  // 50% de chance de ter obstáculo

        if (obstaculo_detectado)
        {
            std::cout << "[DetectarObstaculoLIDAR] Obstáculo detectado pelo LIDAR!" << std::endl;
            return BT::NodeStatus::FAILURE; // Retorna FALHA se houver obstáculo
        }

        std::cout << "[DetectarObstaculoLIDAR] Nenhum obstáculo detectado pelo LIDAR." << std::endl;
        return BT::NodeStatus::SUCCESS; // Retorna SUCESSO se não houver obstáculo
    }
};

class DetectarObstaculoCamera : public BT::ConditionNode
{
public:
    DetectarObstaculoCamera(const std::string& name, const BT::NodeConfiguration& config)
        : BT::ConditionNode(name, config) {}

    // Como essa condição não precisa de entradas ou saídas, deixamos as portas vazias.
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[DetectarObstaculoCamera] Verificando se há obstáculos..." << std::endl;

        // Simulando uma detecção aleatória de obstáculo
        bool obstaculo_detectado = (rand() % 2 == 0);  // 50% de chance de ter obstáculo

        if (obstaculo_detectado)
        {
            std::cout << "[DetectarObstaculoCamera] Obstáculo detectado!" << std::endl;
            return BT::NodeStatus::FAILURE; // Se houver obstáculo, retorna FALHA
        }

        std::cout << "[DetectarObstaculoCamera] Nenhum obstáculo detectado." << std::endl;
        return BT::NodeStatus::SUCCESS; // Se não houver obstáculo, retorna SUCESSO
    }
};

class AcoplarNaEstacao : public BT::SyncActionNode
{
public:
    AcoplarNaEstacao(const std::string &name, const BT::NodeConfiguration &config)
      : BT::SyncActionNode(name, config) {}

    // Como esse nó não necessita de portas de entrada ou saída, retornamos uma lista vazia.
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
         std::cout << "robo acoplado" << std::endl;
         return SS;
    }
};

class AspirarChao : public BT::SyncActionNode
{
public:
    AspirarChao(const std::string &name, const BT::NodeConfiguration &config)
        : BT::SyncActionNode(name, config) {}

    // Nenhuma porta necessária
    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 1 segundo
        std::cout << "Chão aspirado com sucesso" << std::endl;
        return SS;
    }
};

class authenticate_nurse : public BT::SyncActionNode{
	public:
  		authenticate_nurse(const std::string& name, const BT::NodeConfiguration& config) :
      		BT::SyncActionNode(name, config){}
    		static BT::PortsList providedPorts() { return {  INPUT("wait_duration_sec"), OUTPUT("message")};}
  		
		BT::NodeStatus tick() override{
			BT::Optional<std::string> wait_duration_seconds = getInput<std::string>("wait_duration_sec");
			string msg;
			cout << "Informe o codigo de autenticacao da enfermeira presente\n>: ";
			cin >> msg;
			setOutput("message", msg);
			if (msg!="A") return FF; // se fosse algo de verdade, usaria algo mais seguro como salvar um hash da senha e uma senha mais complexa
    			return SS;
  		}
};
class publisher_approach_nurse : public BT::SyncActionNode {
	public:
    		publisher_approach_nurse(const std::string& name, const BT::NodeConfiguration& config) :
        	BT::SyncActionNode(name, config) {}

    		static BT::PortsList providedPorts() { return {  INPUT("message"), INPUT("number"), OUTPUT("laboratory_name")};}

    		BT::NodeStatus tick() override {
        		string lab;
			cout << "Qual o laboratorio deseja que o robo va (A/B)?\n>: ";
			cin >> lab;
			setOutput("laboratory_name", lab);
			BT::Optional<std::string> msg = getInput<std::string>("message");
			BT::Optional<std::string> number = getInput<std::string>("number");
			if (lab!="A" and lab!="B") return FF;
        		return SS;
    		}
};
class publisher_nurse_deposit_sample : public BT::SyncActionNode{
	public:
  		publisher_nurse_deposit_sample(const std::string& name, const BT::NodeConfiguration& config) :
      		BT::SyncActionNode(name, config){}
    		static BT::PortsList providedPorts() { return {INPUT("message"), INPUT("number")};}
  		
		BT::NodeStatus tick() override{
			BT::Optional<std::string> message = getInput<std::string>("message");
			BT::Optional<std::string> number = getInput<std::string>("number");
    			return SS;
  		}
};
class publisher_authenticate_robot : public BT::SyncActionNode{
	public:
  		publisher_authenticate_robot(const std::string& name, const BT::NodeConfiguration& config) :
      		BT::SyncActionNode(name, config){}
    		static BT::PortsList providedPorts() { return {  INPUT("duration"), OUTPUT("message")};}
  		
		BT::NodeStatus tick() override{
			BT::Optional<std::string> duration = getInput<std::string>("duration");
			string msg;
			cout << "Robo, informe o codigo de autenticacao\n>: ";
			cin >> msg;
			if (msg!="A") return FF;
			setOutput("message", msg);
    			return SS;
  		}
};


class AbortarMissao : public BT::SyncActionNode
{
public:
    AbortarMissao(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config) {}

    static BT::PortsList providedPorts() { return {}; }

    BT::NodeStatus tick() override
    {
        std::cout << "[AbortarMissao] Abortando a missão e saindo do programa." << std::endl;
        std::exit(0);
        return SS; 
    }
};

class go_to_laboratory : public BT::SyncActionNode{
	public:
  		go_to_laboratory(const std::string& name, const BT::NodeConfiguration& config) :
      		BT::SyncActionNode(name, config){}
    		static BT::PortsList providedPorts() { return {INPUT("laboratory_name")};}
  		
		BT::NodeStatus tick() override{
			BT::Optional<std::string> laboratory_name = getInput<std::string>("laboratory_name");
    			return SS;
  		}
};
class publisher_open_drawer : public BT::SyncActionNode{
	public:
  		publisher_open_drawer(const std::string& name, const BT::NodeConfiguration& config) :
      		BT::SyncActionNode(name, config){}
    		static BT::PortsList providedPorts() { return {INPUT("authorized"), INPUT("message"), INPUT("number")};}
  		
		BT::NodeStatus tick() override{
			BT::Optional<std::string> authorized = getInput<std::string>("authorized");
			BT::Optional<std::string> message = getInput<std::string>("message");
			BT::Optional<std::string> number = getInput<std::string>("number");
    			return SS;
  		}
};
class publisher_close_drawer : public BT::SyncActionNode{
	public:
  		publisher_close_drawer(const std::string& name, const BT::NodeConfiguration& config) :
      		BT::SyncActionNode(name, config){}
    		static BT::PortsList providedPorts() { return {INPUT("message"), INPUT("number")};}
  		
		BT::NodeStatus tick() override{
			BT::Optional<std::string> message = getInput<std::string>("message");
			BT::Optional<std::string> number = getInput<std::string>("number");
    			return SS;
  		}
};

int main(){
	BT::BehaviorTreeFactory factory;
	factory.registerNodeType<VerificarEquipamentos>("VerificarEquipamentos");
	factory.registerNodeType<VerificarBateria>("VerificarBateria");
	factory.registerNodeType<TempoParaConcluir>("TempoParaConcluir");
	factory.registerNodeType<SalaEstaLivre>("SalaEstaLivre");
	factory.registerNodeType<PassarPano>("PassarPano");
	factory.registerNodeType<MoverMobilia>("MoverMobilia");
	factory.registerNodeType<IrParaDestino>("IrParaDestino");
	factory.registerNodeType<EsterilizarMobilia>("EsterilizarMobilia");
	factory.registerNodeType<EnviarMensagemParaGerente>("EnviarMensagemParaGerente");
	factory.registerNodeType<DetectarObstaculoLIDAR>("DetectarObstaculoLIDAR");
	factory.registerNodeType<DetectarObstaculoCamera>("DetectarObstaculoCamera");
	factory.registerNodeType<AspirarChao>("AspirarChao");
	factory.registerNodeType<AcoplarNaEstacao>("AcoplarNaEstacao");
	factory.registerNodeType<AbortarMissao>("AbortarMissao");
  	factory.registerNodeType<authenticate_nurse>("authenticate_nurse");
  	factory.registerNodeType<go_to_laboratory>("go_to_laboratory");
  	factory.registerNodeType<publisher_approach_nurse>("publisher_approach_nurse");
  	factory.registerNodeType<publisher_authenticate_robot>("publisher_authenticate_robot");
  	factory.registerNodeType<publisher_close_drawer>("publisher_close_drawer");
  	factory.registerNodeType<publisher_nurse_deposit_sample>("publisher_nurse_deposit_sample");
  	factory.registerNodeType<publisher_open_drawer>("publisher_open_drawer");
	auto tree = factory.createTreeFromFile("./exercicio.xml");
  	auto result = tree.tickRootWhileRunning();
	std::cout << "\nBT ended with result: " << result << std::endl;
  	return 0;
}

