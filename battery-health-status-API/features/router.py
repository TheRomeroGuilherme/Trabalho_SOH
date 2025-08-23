from fastapi import APIRouter, Request, Form
from fastapi.responses import HTMLResponse
from fastapi.templating import Jinja2Templates
from .Reports import gerar_relatorio_grafico
from .model.Bateria import BatteryDataSeries, BatteryInput, BatteryReference


router = APIRouter(prefix="/bateria", tags=["Bateria"])

templates = Jinja2Templates(directory="templates")

@router.get("/relatorios", response_class=HTMLResponse)
def mostrar_formulario_relatorio(request: Request):
    """
    Rota que exibe o formulário inicial para o usuário inserir os dados da bateria.
    """
    return templates.TemplateResponse("relatorio_bateria.html", {"request": request, "relatorio": None})

@router.post("/relatorios", response_class=HTMLResponse)
def gerar_relatorio(
    request: Request,
    tensao_ref: float = Form(...),
    corrente_ref: float = Form(...),
    tensao_atual: float = Form(...),
    corrente_atual: float = Form(...)
):
    """
    Rota que processa os dados do formulário e gera um relatório gráfico.
    """
    # Cria os objetos de dados com as informações do formulário
    dados_bateria = BatteryDataSeries(
        referencia=BatteryReference(tensao=tensao_ref, corrente=corrente_ref),
        leituras=[BatteryInput(tensao=tensao_atual, corrente=corrente_atual)]
    )

    # Gera o gráfico e o retorna como uma string base64
    img_b64 = gerar_relatorio_grafico(dados_bateria)

    # Renderiza a página novamente, mas agora com o relatório para exibir
    return templates.TemplateResponse(
        "battery_report.html",
        {"request": request, "relatorio": img_b64}
    )