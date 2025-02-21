Aqui está um **README.md** que explica como rodar o projeto em qualquer computador. Ele inclui instruções para instalação das dependências e compilação passo a passo.  

---

### 📌 **README.md**
```markdown
# TAC - Trabalho Final - Behavior Tree

Este projeto implementa uma **árvore de comportamento (Behavior Tree - BT)** usando a biblioteca **BehaviorTree.CPP** para controlar um robô assistente.

## 🛠 **Pré-requisitos**
Antes de compilar e executar, certifique-se de ter as seguintes dependências instaladas:

### 🔹 **1. Instalar o ROS 2 (Humble)**
Se ainda não tiver o **ROS 2 Humble** instalado, siga os passos [aqui](https://docs.ros.org/en/humble/Installation.html).

Depois, ative o ambiente do ROS 2:

```bash
source /opt/ros/humble/setup.bash
```

### 🔹 **2. Instalar a biblioteca BehaviorTree.CPP**
```bash
sudo apt update
sudo apt install ros-humble-behaviortree-cpp-v3
```

Caso não esteja usando o ROS 2, instale manualmente:

```bash
cd ~
git clone https://github.com/BehaviorTree/BehaviorTree.CPP.git
cd BehaviorTree.CPP
mkdir build && cd build
cmake ..
make
sudo make install
```

---

## 🚀 **Como Compilar e Executar**
Execute os seguintes comandos no terminal:

```bash
cd /home/$USER/Downloads/exercicio/sync_behaviors_bt  # Acesse o diretório do projeto
rm -rf build CMakeCache.txt CMakeFiles  # Limpar arquivos antigos
mkdir build  # Criar diretório para build
cp exercicio.xml build  # Copiar o arquivo XML para o diretório de build
cd build
cmake ..  # Configurar a compilação
make  # Compilar o projeto
./BT  # Executar o programa
```

Se o nome do executável for diferente, use `ls` para listar os arquivos na pasta `build` e rodar o nome correto.

---

## 📌 **Solução de Problemas**
### ⚠ **Erro: "libament_index_cpp.so: cannot open shared object file"**
Se ao executar `./BT` aparecer um erro relacionado à `libament_index_cpp.so`, o ambiente ROS 2 pode não estar ativado. Corrija com:

```bash
source /opt/ros/humble/setup.bash
```

Para não precisar rodar esse comando toda vez, adicione ao **~/.bashrc**:

```bash
echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc
source ~/.bashrc
```

### ⚠ **Erro: "Error parsing the XML: XML_ERROR_FILE_NOT_FOUND"**
O arquivo **`exercicio.xml`** pode estar faltando no diretório `build`. Para corrigir, copie novamente:

```bash
cp ../exercicio.xml .
```

Agora, tente rodar `./BT` novamente.

---

## 📝 **Sobre o Projeto**
Este projeto foi desenvolvido para demonstrar o uso de **árvores de comportamento** com a biblioteca BehaviorTree.CPP. Ele simula um robô que executa tarefas baseadas em nós de decisão.

Se precisar de ajuda, abra uma *issue* ou contribua com melhorias! 🚀
```

---

### ✅ **O que esse README resolve?**
✔ Explica **como instalar as dependências** corretamente.  
✔ Garante que o **caminho do usuário (`$USER`) seja dinâmico**, funcionando em qualquer computador.  
✔ Inclui **solução para erros comuns**.  
✔ Explica **como executar o código** de forma clara.  

Agora você pode salvar esse arquivo como **README.md** e adicioná-lo ao seu repositório! 🚀
