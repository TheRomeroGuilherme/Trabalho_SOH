from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from typing import List, Optional

# importe a função e o modelo do Reports (caminho absoluto)
from features.Reports import gerar_relatorio_grafico, BatteryInputModel

router = APIRouter(prefix="/bateria", tags=["Bateria API"])

class LeiturasRequest(BaseModel):
    leituras: List[BatteryInputModel]

class RelatorioResponse(BaseModel):
    status_soh: str
    imagem_base64: str

ultimo_relatorio_gerado: Optional[RelatorioResponse] = None

@router.post("/leituras", response_model=RelatorioResponse)
def receber_leituras_do_esp32(payload: LeiturasRequest):
    """
    Endpoint para o ESP32 enviar as 10 leituras.
    Ele gera o relatório e o armazena na memória.
    """
    global ultimo_relatorio_gerado
    if not payload.leituras or len(payload.leituras) != 10:
        raise HTTPException(status_code=400, detail="São necessárias exatamente 10 leituras.")

    try:
        img_b64, status_soh = gerar_relatorio_grafico(payload.leituras)
        relatorio = RelatorioResponse(status_soh=status_soh, imagem_base64=img_b64)
        
        # Armazena o relatório recém-gerado na variável global
        ultimo_relatorio_gerado = relatorio
        
        print("Novo relatório recebido do ESP32 e armazenado.")
        return relatorio
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Erro ao gerar relatório: {e}")

@router.get("/leituras/ultimo", response_model=Optional[RelatorioResponse])
def obter_ultimo_relatorio_para_frontend():
    """
    ENDPOINT PARA O HTML: A página web vai chamar este endpoint
    repetidamente para buscar o último relatório salvo.
    """
    if ultimo_relatorio_gerado:
        print(">>> Dashboard solicitou o último relatório. Enviando... <<<")
        return ultimo_relatorio_gerado
    else:
        # Se o Wokwi ainda não enviou nada, não retorna nada.
        return None
    


