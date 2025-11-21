# GS_Edge

# Integrantes

Clara Barboza Costa </br>
Pedro Henrique Lamin Rodrigues</br>
Tomás Antonio Braga Cantuária</br>

# Links

Thingspeak: https://thingspeak.mathworks.com/channels/3172040/private_show </br>
Wokwi: https://wokwi.com/projects/447645612540498945
Vídeo:
https://youtu.be/xgLjY3sWh98?feature=shared

# Descrição do problema

Profissionais que trabalham em ambientes de alta pressão muitas vezes não percebem quando estão ultrapassando seus limites físicos e emocionais. Isso pode gerar queda de desempenho, ansiedade, problemas cardiovasculares e até burnout.

Monitorar indicadores fisiológicos simples, como frequência cardíaca e temperatura corporal, pode ajudar a identificar momentos de estresse elevado e emitir alertas preventivos.

# Solução Desenvolvida

O projeto consiste em um ESP32, capaz de:

Ler batimentos cardíacos simulados com um potenciômetro

Medir temperatura e umidade com o sensor DHT22

Calcular automaticamente um Índice de Estresse (0 a 100)

Acionar alarme sonoro e LED quando o estresse estiver alto

Enviar todos os dados para o ThingSpeak em tempo real

# Componentes

ESP32

Sensor DHT22 (temperatura e umidade)

Potenciômetro (simula batimentos cardíacos)

Buzzer

LED
