from pydantic import BaseModel

# Este é o "contrato" dos dados que esperamos receber do Arduino/cliente.
class BatteryDataCreate(BaseModel):
    voltage: float
    current: float
    temperature: float

# Este é o "contrato" da resposta que nossa API enviará de volta.
class BatteryHealthStatus(BaseModel):
    battery_id: str
    estimated_health_percent: float
    message: str