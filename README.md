# 🌡️ ESP32 DHT11 – MQTT Temperature & Humidity Monitoring System

## 📌 Description générale

Ce projet est un **système de surveillance de température et d’humidité** basé sur le protocole **MQTT**.

Il est conçu principalement pour :

* 🎓 **Étudiants** en systèmes embarqués / IoT
* 🔧 **Enthusiasts** souhaitant apprendre MQTT, ESP32 et le monitoring temps réel

Le système est composé de **trois parties indépendantes mais connectées** :

1. Un **broker MQTT Mosquitto** installé sur Linux (Ubuntu)
2. Un **ESP32 + capteur DHT11** qui publie les données
3. Une **interface Web** qui s’abonne au broker et affiche les données en temps réel
4. Un **script Linux** optionnel pour afficher et stocker les données dans un fichier `.log`

---

## 🧱 Architecture du système

![Architecture globale du système](docs/images/architecture.png)

```
[DHT11] → ESP32 → MQTT → Mosquitto (Linux)
                               ↓
                      Web Interface (MQTT WebSocket)
                               ↓
                         Script Logger (.log)
```

[DHT11] → ESP32 → MQTT → Mosquitto (Linux)
↓
Web Interface (MQTT WebSocket)
↓
Script Logger (.log)

````

---

## 🐧 Partie 1 : Linux (Broker MQTT Mosquitto)

### 🔹 Rôle
Le broker MQTT agit comme un **serveur central** qui reçoit les données envoyées par l’ESP32 et les redistribue aux clients abonnés (page web, scripts, etc.).

### 🔹 Installation de Mosquitto (Ubuntu)
```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients
````

### 🔹 Vérification

```bash
mosquitto -v
```

### 🔹 Activation au démarrage

```bash
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

### 🔹 Activation du WebSocket MQTT

Éditer le fichier de configuration :

```bash
sudo nano /etc/mosquitto/mosquitto.conf
```

Ajouter :

```conf
listener 1883
protocol mqtt

listener 8080
protocol websockets
allow_anonymous true
```

Puis redémarrer :

```bash
sudo systemctl restart mosquitto
```

---

## 🔌 Partie 2 : ESP32 + DHT11

### 🔹 Rôle

* Lire la **température** et l’**humidité** via le capteur DHT11
* Publier les valeurs toutes les **2 secondes** sur le broker MQTT

### 🔹 Topics MQTT utilisés

```text
esp32/dht11/temperature
esp32/dht11/humidity
```

### 🔹 Données envoyées

* Température : °C
* Humidité : %

### 🔹 Fréquence

⏱️ Toutes les **2 secondes**

![Schéma de câblage ESP32 + DHT11](docs/images/esp32_dht11_wiring.png)

---

## 🌐 Partie 3 : Interface Web

### 🔹 Rôle

* S’abonner aux topics MQTT
* Afficher les valeurs **en temps réel**
* Fonctionne via **MQTT over WebSocket**

### 🔹 Technologies utilisées

* HTML / CSS
* JavaScript
* Bibliothèque `mqtt.js`

### 🔹 Fonctionnalités

* Affichage moderne (dark UI)
* Indicateur d’état de connexion
* Mise à jour en temps réel

![Interface Web – Affichage temps réel](docs/images/web_interface.png)

---

## 📜 Partie 4 : Script Logger Linux

### 🔹 Rôle

* S’abonner aux mêmes topics MQTT
* Afficher les données dans le terminal
* Enregistrer les valeurs dans un fichier `.log`

### 🔹 Exemple d’utilisation

```bash
python3 mqtt_logger.py
```

### 🔹 Exemple de fichier log

```text
2025-01-10 14:32:01 | Température: 25.3 °C | Humidité: 54 %
2025-01-10 14:32:03 | Température: 25.4 °C | Humidité: 55 %
```

---

## 🚀 Objectifs pédagogiques

* Comprendre **MQTT** (publish / subscribe)
* Apprendre l’architecture **IoT distribuée**
* Utiliser **ESP32** avec capteurs
* Créer une **interface Web temps réel**
* Manipuler Linux pour des services réseau

---

## 🔮 Améliorations possibles

* Authentification MQTT
* Base de données (InfluxDB, SQLite)
* Dashboard avancé (Grafana)
* Ajout d’alertes (seuil température)
* Support DHT22 / BME280

---

## 👤 Auteur

Projet réalisé à des fins **éducatives et expérimentales**.

---

## 📄 Licence

Libre pour usage pédagogique et personnel.
