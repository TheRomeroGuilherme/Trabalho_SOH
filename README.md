# Trabalho_SOH: API de Análise de Saúde da Bateria

Este projeto é composto por dois servidores locais:
* **API (Back-end)**: Responsável por processar os dados e gerar os relatórios e gráficos.
* **Front-end**: Uma página HTML que coleta os dados e exibe o relatório gerado pela API.

## 🚀 Como Rodar o Projeto

Para usar a aplicação, você precisa iniciar o servidor da API e o servidor do front-end em terminais separados.

### 1. Iniciar a API (Back-end)

A API é o servidor principal. Você precisa iniciá-la primeiro.

1.  Abra um terminal e navegue até a pasta `battery-health-status-API`.
    ```sh
    cd battery-health-status-API
    ```

2.  Instale as dependências (se ainda não o fez):
    ```sh
    pip install fastapi uvicorn pandas numpy matplotlib
    ```

3.  Inicie a API. Ela será executada na porta `8000`.
    ```sh
    uvicorn main:app --reload
    ```
    Mantenha este terminal aberto e a API rodando.

### 2. Iniciar o Front-end

O navegador não permite que a página HTML se comunique com a API diretamente. Por isso, você precisa de um servidor simples para o front-end.

1.  Abra um **novo terminal** e navegue para a pasta `templates`.
    ```sh
    cd battery-health-status-API/templates
    ```

2.  Inicie o servidor web simples do Python. Ele usará a porta `8001` para não conflitar com a API.
    ```sh
    python -m http.server 8001
    ```
    Mantenha este terminal aberto.

### 3. Acessar a Aplicação

Com ambos os servidores rodando, abra seu navegador e acesse a página do front-end: http://localhost:8001/battery_report.html








