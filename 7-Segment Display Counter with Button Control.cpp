
// Пины сегментов 7-сегментного дисплея (общий катод)
const int segments[] = {2, 3, 4, 5, 6, 7, 8}; 

// Цифры (0-9) в формате 7-сегментного дисплея (общий катод)
const byte numbers[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

int counter = 0;   // Текущий счётчик
bool buttonState;   // Состояние кнопки
bool lastButtonState = HIGH; // Предыдущее состояние кнопки
unsigned long pressStartTime = 0;  // Время начала нажатия

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
  displayNumber(counter);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  
  // Проверка нажатия кнопки (с дебаунсом)
  if (buttonState == LOW && lastButtonState == HIGH) { 
    delay(50); // Дебаунсинг
    pressStartTime = millis(); // Запоминаем время нажатия
  }

  // Если кнопка удерживается > 1 сек - сбрасываем
  if (buttonState == LOW && (millis() - pressStartTime > 1000)) {
    counter = 0;
    displayNumber(counter);
  }

  // Если кнопка отпущена после короткого нажатия - увеличиваем
  if (buttonState == HIGH && lastButtonState == LOW) {
    if (millis() - pressStartTime < 1000) { // Короткое нажатие
      counter++;
      if (counter > 9) counter = 0; // Если >9 → обнулить
      displayNumber(counter);
    }
  }

  lastButtonState = buttonState;
}

// Функция отображения числа на 7-сегментном дисплее
void displayNumber(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], bitRead(numbers[num], i));
  }
}
