from fastapi import FastAPI
from features.router import router as battery_router

app = FastAPI(
    title="Battery Health Status API",
    description="API para analisar a saúde de baterias em tempo real.",
    version="0.1.0"
)

@app.get("/", tags=["Root"])
def read_root():
    return {"status": "API online e funcionando!"}

app.include_router(battery_router)
