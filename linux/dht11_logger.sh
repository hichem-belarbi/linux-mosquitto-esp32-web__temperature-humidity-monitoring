#!/bin/bash

LOGFILE="dht11.log"


echo "-------------------------------------------------------------" >> "$LOGFILE"
echo " Démarrage du logging DHT11 : $(date '+%Y-%m-%d %H:%M:%S')" >> "$LOGFILE"
echo "-------------------------------------------------------------" >> "$LOGFILE"


RED="\e[31m"
BLUE="\e[34m"
GREEN="\e[32m"
YELLOW="\e[33m"
RESET="\e[0m"

# Fonction de logging
log_data() {
    local topic="$1"
    local value="$2"
    local timestamp=$(date "+%Y-%m-%d %H:%M:%S")

    
    printf "%s | %-10s | %s\n" "$timestamp" "$topic" "$value" >> "$LOGFILE"

   
    case "$topic" in
        "temperature")
            echo -e "${RED}[TEMP]${RESET} $timestamp → ${YELLOW}${value}°C${RESET}"
            ;;
        "humidity")
            echo -e "${BLUE}[HUM] ${RESET} $timestamp → ${GREEN}${value}%${RESET}"
            ;;
        *)
            echo -e "$timestamp | $topic | $value"
            ;;
    esac
}


mosquitto_sub -h localhost -t esp32/dht11/temperature | while read temp
do
    log_data "temperature" "$temp"
done &

mosquitto_sub -h localhost -t esp32/dht11/humidity | while read hum
do
    log_data "humidity" "$hum"
done &


wait

