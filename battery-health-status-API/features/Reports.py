import io
import base64
import matplotlib.pyplot as plt
from .model.Bateria import BatteryDataSeries
from .Service import Battery

def gerar_relatorio_grafico(data: BatteryDataSeries):
    ref = Battery(data.referencia.tensao, data.referencia.corrente)
    leituras = [Battery(l.tensao, l.corrente) for l in data.leituras]

    potencias = [b.potencia() for b in leituras]
    soh_values = [b.soh(ref) for b in leituras]
    indices = list(range(1, len(leituras)+1))

    plt.figure(figsize=(8,5))
    plt.plot(indices, soh_values, marker="o", label="SoH (%)")
    plt.plot(indices, potencias, marker="s", label="Potência (W)")
    plt.axhline(100, color="green", linestyle="--", label="SoH ideal")
    plt.xlabel("Leitura")
    plt.ylabel("Valor")
    plt.title("Relatório de Saúde da Bateria")
    plt.legend()
    plt.grid(True)

    # Salva imagem em memória
    buf = io.BytesIO()
    plt.savefig(buf, format="png")
    buf.seek(0)
    encoded = base64.b64encode(buf.read()).decode("utf-8")
    buf.close()
    plt.close()

    return encoded
