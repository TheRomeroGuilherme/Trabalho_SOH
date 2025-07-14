from fastapi import APIRouter
from . import schemas
from . import services

# APIRouter funciona como uma "mini" aplicação FastAPI
router = APIRouter(
    prefix="/battery",            # Adiciona "/battery" antes de todas as rotas aqui
    tags=["Battery Analysis"]     # Agrupa estas rotas na documentação
)

@router.post("/{battery_id}/status", response_model=schemas.BatteryHealthStatus)
def get_battery_analysis(battery_id: str, data: schemas.BatteryDataCreate):
    """
    Recebe dados de telemetria de uma bateria e retorna a análise de saúde.
    """
    # A rota NÃO calcula. Ela chama o SERVIÇO que tem a lógica.
    # Isso mantém o código organizado.
    analysis_result = services.calculate_battery_health(battery_id=battery_id, data=data)
    return analysis_result