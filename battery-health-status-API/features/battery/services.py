from . import schemas

def calculate_battery_health(battery_id: str, data: schemas.BatteryDataCreate) -> schemas.BatteryHealthStatus:
    """
    Esta função contém a lógica de cálculo.
    Por enquanto, é apenas um exemplo simples.
    """
    print(f"Recebido para cálculo: Voltagem={data.voltage}, Temperatura={data.temperature}")

    # --- LÓGICA DE EXEMPLO ---
    health = 100.0
    if data.voltage < 3.5:
        health -= 15.0  # Perde saúde se a voltagem for baixa

    if data.temperature > 40.0:
        health -= 20.0  # Perde saúde se a temperatura for alta
    # --- FIM DA LÓGICA ---

    # Retorna o resultado usando o schema de resposta
    return schemas.BatteryHealthStatus(
        battery_id=battery_id,
        estimated_health_percent=health,
        message="Cálculo de exemplo concluído."
    )