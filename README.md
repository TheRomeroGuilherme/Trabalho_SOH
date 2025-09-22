# Trabalho_SOH: API de Análise de Saúde da Bateria

Este projeto consiste em uma API desenvolvida com FastAPI para analisar a saúde (State of Health - SoH) de baterias a partir de leituras de tensão e corrente. O sistema gera um relatório detalhado e um gráfico de curva de descarga para visualização.

O projeto inclui dois componentes principais:

-   **`battery-health-status-API`**: O servidor back-end em Python que processa os dados e gera os relatórios.
-   **`arduino-battery-health-status-API`**: O código para um microcontrolador Arduino que enviaria os dados de tensão e corrente para a API.

## 🚀 Como Rodar o Projeto

Para rodar a aplicação, você precisa iniciar o servidor da API (back-end) e servir a página HTML (front-end) localmente.

### Pré-requisitos

Certifique-se de que você tem o Python 3 instalado em seu sistema.

### 1. Configuração e Inicialização da API (Back-end)

1.  Navegue até o diretório da API no seu terminal:
    ```sh
    cd battery-health-status-API
    ```

2.  Instale as dependências necessárias. O arquivo `requirements.txt` lista o `fastapi` e `uvicorn`, mas a funcionalidade de geração de gráficos também requer outras bibliotecas. Use o comando a seguir para instalar todas as dependências:
    ```sh
    pip install -r requirements.txt pandas numpy matplotlib
    ```

3.  Inicie o servidor da API. Ele será executado na porta `8000`.
    ```sh
    uvicorn main:app --reload
    ```
    O servidor estará ativo e pronto para receber requisições.

### 2. Configuração e Inicialização do Front-end

A página HTML precisa ser servida por um servidor para evitar erros de CORS (Cross-Origin Resource Sharing).

1.  **Ajuste o Código HTML**:
    O arquivo `battery_report.html` usa um caminho relativo para a API. Para que funcione corretamente em um servidor local, você precisa editá-lo para usar um caminho absoluto.
    * Abra o arquivo `battery_report.html` em um editor de texto.
    * Procure pela linha que começa com `const response = await fetch('/bateria/relatorios/json', {`.
    * Substitua o caminho relativo pelo caminho completo da API: `http://localhost:8000/bateria/relatorios/json`.
        ```javascript
        const response = await fetch('http://localhost:8000/bateria/relatorios/json', {
        ```

2.  **Inicie o Servidor do Front-end**:
    * Abra um **novo terminal** e navegue até a pasta `templates`:
        ```sh
        cd battery-health-status-API/templates
        ```
    * Inicie um servidor web simples com Python na porta `8001` (para não conflitar com a API):
        ```sh
        python -m http.server 8001
        ```

3.  **Acesse a Aplicação**:
    * Abra seu navegador e acesse a URL:
        ```
        http://localhost:8001/battery_report.html
        ```
    * Agora, a página HTML pode enviar os dados para a API e exibir o relatório corretamente.