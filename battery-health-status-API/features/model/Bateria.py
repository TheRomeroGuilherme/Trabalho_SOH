from pydantic import BaseModel
from typing import List

class BatteryInput(BaseModel):
    tensao: float
    corrente: float

class BatteryReference(BaseModel):
    tensao: float
    corrente: float

class BatteryDataSeries(BaseModel):
    referencia: BatteryReference
    leituras: List[BatteryInput]  
