# main.py
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

# importe o router do arquivo onde ele realmente está.
# se o seu arquivo for routes_bateria_api.py no pacote 'features', use:
from features.router import router as battery_router

app = FastAPI(
    title="Battery Health Status API",
    description="API para analisar a saúde de baterias em tempo real.",
    version="0.1.0"
)

# Habilita CORS (útil durante desenvolvimento)
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # em produção limite isso para seus domínios
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/", tags=["Root"])
def read_root():
    return {"status": "API online e funcionando!"}

app.include_router(battery_router)
