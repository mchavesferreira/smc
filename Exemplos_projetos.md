# Exemplos de projetos

## Sistema de Gerenciamento de Ambiente Doméstico Inteligente, que atende a todos os novos critérios estabelecidos:
https://files.oaiusercontent.com/file-bmA7lScQZ1DGC8n0wwMIuM7m?se=2024-04-05T19%3A03%3A13Z&sp=r&sv=2021-08-06&sr=b&rscc=max-age%3D31536000%2C%20immutable&rscd=attachment%3B%20filename%3D91415577-d803-4deb-aadc-58beaeacedc3.webp&sig=vJNxCkJrOgB%2BRPpHomFdeLAVVTvKVAElH%2BrA/4gGjNE%3D
Descrição Geral:

Este projeto envolve a criação de um sistema de gerenciamento de ambiente doméstico inteligente controlado por um microcontrolador AVR. O sistema permite o controle de iluminação, monitoramento de temperatura, e definição de alarmes, utilizando um display LCD para interface com o usuário e botões para interação.
Requisitos Atendidos:

    Perguntas e Ajustes:
        "Deseja acender as luzes? (Y/N)"
        "Ajustar intensidade da luz? (0-100%)"
        "Configurar alarme? (Y/N)"
        "Ajustar temperatura? (18-30°C)"
        "Ativar modo noturno? (Y/N)"
    Ajustes de Valores Inteiros:
        Intensidade da luz (0-100%)
        Temperatura desejada (18-30°C)
        Tempo de desligamento automático para luzes (1-120 minutos)
    Máquina de Estados (10+ estados):
        Inicialização
        Menu Principal
        Controle de Luzes
        Ajuste de Intensidade da Luz
        Configuração de Alarme
        Ajuste de Temperatura
        Ativação do Modo Noturno
        Monitoramento de Temperatura
        Desligamento Automático de Luzes
        Alarme Ativo
        Retorno ao Menu Principal
    Saídas LED:
        LED verde: Luzes ligadas
        LED amarelo: Modo Noturno ativo
        LED vermelho: Alarme ativo

    # 
