from fastapi import FastAPI
from features.battery.router import router as battery_router

app = FastAPI(
    title="Battery Health Status API",
    description="API para analisar a saúde de baterias em tempo real.",
    version="0.1.0"
)

# Endpoint raiz para um teste rápido de status
@app.get("/", tags=["Root"])
def read_root():
    return {"status": "API online e funcionando!"}

# Inclui todas as rotas definidas no router da feature de bateria
app.include_router(battery_router)