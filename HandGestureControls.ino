# define numOfValuesReceived 5
# define digitsPerValueReceived 1

int green = 8;
int yellow = 10;
int red = 12;

int valuesReceived[numOfValuesReceived];
int stringLength = numOfValuesReceived * digitsPerValueReceived + 1;
int counter = 0;
bool counterStart = false;
bool allOnes;
bool allZeros;
String receivedString;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void readData() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c=='$'){
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        receivedString = String(receivedString+c);
        counter++;
      }
      if (counter >= stringLength) {
        for (int i=0; i<numOfValuesReceived; i++){
          int num = (i*digitsPerValueReceived) + 1;
          valuesReceived[i] = receivedString.substring(num, num+digitsPerValueReceived).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {

  readData();

  if (valuesReceived[0] == 1 &&
      valuesReceived[1] == 1 &&
      valuesReceived[2] == 1 &&
      valuesReceived[3] == 1 &&
      valuesReceived[4] == 1) {allOn();}

  if (valuesReceived[0] == 0 &&
      valuesReceived[1] == 0 &&
      valuesReceived[2] == 0 &&
      valuesReceived[3] == 0 &&
      valuesReceived[4] == 0) {allOff();}

  if (valuesReceived[0] == 1 &&
      valuesReceived[1] == 0 &&
      valuesReceived[2] == 0 &&
      valuesReceived[3] == 0 &&
      valuesReceived[4] == 0) {greenLed();}

  if (valuesReceived[0] == 0 &&
      valuesReceived[1] == 1 &&
      valuesReceived[2] == 0 &&
      valuesReceived[3] == 0 &&
      valuesReceived[4] == 0) {yellowLed();}

  if (valuesReceived[0] == 0 &&
      valuesReceived[1] == 0 &&
      valuesReceived[2] == 0 &&
      valuesReceived[3] == 0 &&
      valuesReceived[4] == 1) {redLed();}

  
}

void redLed() {
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}
 
void yellowLed() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
}

void greenLed() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
}

void allOn() {
  digitalWrite(red, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, HIGH);
}

void allOff() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}
