from .model.Bateria import BatteryInput, BatteryReference
import statistics

class Battery:
    def __init__(self, tensao: float, corrente: float):
        self.tensao = tensao
        self.corrente = corrente

    def potencia(self):
        return self.tensao * self.corrente

    def soh(self, referencia: "Battery"):
        return (self.potencia() / referencia.potencia()) * 100
