define PING_PIN 8      // Пин сигнала PING))) подключен к цифровому пину 8
define GREEN_LED 9     // Зелёный светодиод
define YELLOW_LED 10   // Жёлтый светодиод
define RED_LED 11      // Красный светодиод
define BUZZER 13       // Пин зуммера
define BUTTON_PIN 7    // Кнопка включения системы

void setup() {
    pinMode(PING_PIN, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Кнопка с внутренним подтягивающим резистором
    Serial.begin(9600);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) { // Если кнопка нажата
        long duration;
        int distance;

        // Отправляем ультразвуковой импульс
        pinMode(PING_PIN, OUTPUT);
        digitalWrite(PING_PIN, LOW);
        delayMicroseconds(2);
        digitalWrite(PING_PIN, HIGH);
        delayMicroseconds(5);
        digitalWrite(PING_PIN, LOW);

        // Переключаем на приём и измеряем время возврата сигнала
        pinMode(PING_PIN, INPUT);
        duration = pulseIn(PING_PIN, HIGH);
        
        // Перевод времени в расстояние (см)
        distance = duration / 29 / 2;  

        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");

        // Управление светодиодами и зуммером
        if (distance > 30) { 
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(RED_LED, LOW);
            noTone(BUZZER);
        } 
        else if (distance > 15) { 
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(RED_LED, LOW);
            tone(BUZZER, 1000, 100);
            delay(500);
        } 
        else { 
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(RED_LED, HIGH);
            tone(BUZZER, 2000, 100);
            delay(200);
        }
    } 
    else { // Если кнопка не нажата - выключаем всё
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, LOW);
        noTone(BUZZER);
    }

    delay(100); 
}