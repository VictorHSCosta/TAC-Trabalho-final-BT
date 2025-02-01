# Tutorial para Disciplina de TAC

Tutorial para execucao de comportamentos sincronos, exemplos tratam synchronous actions, synchronous conditions e input e output ports da blackboard.

Lembrando o processo para execucao de um no:

1. Modelagem da BT no Groot;
2. Implementacao do comportamento do No (funcao tick)
3. (Opcional) Implementacao dos Ports da Blackboard
4. Registrar os nos com o BT factory

## Como Executar esse repositorio

```bash
source /opt/ros/setup.bash
cmake .
make
```

Note o nome do projeto no arquivo CMake e modifique-o para sua preferencia.
