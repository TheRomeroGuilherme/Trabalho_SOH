# features/Reports.py
import io
import base64
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from typing import List, Optional
from pydantic import BaseModel
from pathlib import Path
import os

class BatteryInputModel(BaseModel):
    tensao: float
    corrente: float

def gerar_relatorio_grafico(leituras: List[BatteryInputModel], referencia_csv_path: Optional[str] = None):
    """
    Gera gráfico e SoH a partir de leituras.
    Se referencia_csv_path for None, procura 'bateria_referencia.csv' na mesma pasta deste módulo.
    """
    # Se nenhum caminho foi fornecido, procura na mesma pasta deste arquivo
    if referencia_csv_path is None:
        referencia_csv_path = str(Path(__file__).resolve().parent / "bateria_referencia.csv")

    # Imprime o caminho usado (vai aparecer no log do uvicorn/terminal)
    print(f"[Reports] Usando CSV de referência em: {referencia_csv_path}")
    print(f"[Reports] CWD do processo: {os.getcwd()}")

    # Leitura do CSV de referência
    try:
        df_ref = pd.read_csv(referencia_csv_path)
    except FileNotFoundError:
        raise FileNotFoundError(f"Arquivo de referência não encontrado: {referencia_csv_path}")
    except Exception as e:
        raise RuntimeError(f"Erro ao ler CSV de referência: {e}")

    # Aceita coluna 'ampere' ou 'corrente'
    if 'ampere' not in df_ref.columns and 'corrente' not in df_ref.columns:
        raise ValueError("CSV de referência deve conter uma coluna 'ampere' ou 'corrente'")

    amperes_ref = df_ref['ampere'].astype(float).tolist() if 'ampere' in df_ref.columns else df_ref['corrente'].astype(float).tolist()
    amperes_arduino = [float(l.corrente) for l in leituras]

    if len(amperes_arduino) < 2 or len(amperes_ref) < 2:
        raise ValueError("São necessárias pelo menos 2 leituras na referência e no Arduino para calcular a integral.")

    # Converte minutos -> horas (cada leitura = 1 minuto => dx = 1/60 horas)
    dx_horas = 1.0 / 60.0
    carga_total_ref_Ah = np.trapz(amperes_ref, dx=dx_horas)
    carga_total_arduino_Ah = np.trapz(amperes_arduino, dx=dx_horas)

    soh_carga = (carga_total_arduino_Ah / carga_total_ref_Ah) * 100 if carga_total_ref_Ah != 0 else 0.0

    limite = 80.0
    if soh_carga < limite:
        status_soh = f"A saúde da bateria é ruim. SoH de Carga: {soh_carga:.2f}% (menor que {limite:.0f}%)"
    else:
        status_soh = f"A saúde da bateria está boa. SoH de Carga: {soh_carga:.2f}%"

    # Gera gráfico
    indices = list(range(1, len(amperes_arduino) + 1))
    plt.figure(figsize=(10, 6))
    plt.plot(range(1, len(amperes_ref) + 1), amperes_ref, marker="o", linestyle="--", label="Ampere Ideal (CSV)")
    plt.plot(indices, amperes_arduino, marker="s", label="Ampere Arduino (Leituras)")
    plt.title("Comparação da Corrente da Bateria")
    plt.xlabel("Leitura (minuto)")
    plt.ylabel("Corrente (A)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    buf = io.BytesIO()
    plt.savefig(buf, format="png")
    buf.seek(0)
    encoded = base64.b64encode(buf.read()).decode("utf-8")
    buf.close()
    plt.close()

    return encoded, status_soh
