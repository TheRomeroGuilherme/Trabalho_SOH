# features/routes_bateria_api.py
from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from typing import List

# importe a função e o modelo do Reports (caminho absoluto)
from features.Reports import gerar_relatorio_grafico, BatteryInputModel

router = APIRouter(prefix="/bateria", tags=["Bateria API"])

class LeiturasRequest(BaseModel):
    leituras: List[BatteryInputModel]

class RelatorioResponse(BaseModel):
    status_soh: str
    imagem_base64: str

@router.post("/relatorios/json", response_model=RelatorioResponse)
def gerar_relatorio_json(payload: LeiturasRequest):
    if not payload.leituras or len(payload.leituras) != 10:
        raise HTTPException(status_code=400, detail="São necessárias exatamente 10 leituras.")

    try:
        img_b64, status_soh = gerar_relatorio_grafico(payload.leituras)
    except FileNotFoundError as e:
        raise HTTPException(status_code=500, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Erro ao gerar relatório: {e}")

    return {"status_soh": status_soh, "imagem_base64": img_b64}
