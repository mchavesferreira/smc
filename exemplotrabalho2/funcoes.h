


// Definições da rede WiFi
const char* ssid = "seuwifi";
const char* password = "seuwifi";

const char* ssid2 = "seuwifi";      // Nome da segunda rede Wi-Fi
const char* password2 = "seuwifi"; // Senha da segunda rede Wi-Fi

const char* nomedevice = "esp32_projeto2smc";


// Função para esperar pela conexão WiFi com timeout (10 segundos por padrão)
bool waitForConnection(unsigned long timeout = 10000)
{
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - startTime > timeout)
        {
            return false; // Timeout alcançado
        }
        delay(500);
        Serial.print("."); // Mostra progresso da conexão
    }
    return true; // Conexão bem-sucedida
}

void setup_wifi()
{
    delay(10);
    Serial.println();

    // Tenta conectar à primeira rede
    Serial.print("Tentando conectar a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    if (waitForConnection())
    {
        Serial.println("Conectado à primeira rede!");
        Serial.print("Endereço IP: ");
        Serial.println(WiFi.localIP());
        return; // Se conectou, sai da função
    }

    // Se falhar, tenta conectar à segunda rede
    Serial.println("Falha ao conectar à primeira rede. Tentando segunda rede...");
    WiFi.begin(ssid2, password2);
    if (waitForConnection())
    {
        Serial.println("Conectado à segunda rede!");
        Serial.print("Endereço IP: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        // Se nenhuma conexão for bem-sucedida
        Serial.println("Falha ao conectar em ambas as redes.");
    }
}
