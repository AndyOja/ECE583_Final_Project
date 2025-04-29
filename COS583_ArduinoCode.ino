uint8_t a0 = 3;
uint8_t a1 = 4;
uint8_t a2 = 5;
uint8_t b0 = 6;
uint8_t b1 = 7;
uint8_t b2 = 8;
uint8_t ci = 2;
uint8_t s0 = 9;
uint8_t s1 = 10;
uint8_t s2 = 11;
uint8_t cO = 12;

// Global variables to store parsed input
uint8_t operandA = 0;
uint8_t operandB = 0;
uint8_t carryIn = 0;
String inputString = ""; // buffer for incoming serial data
bool stringComplete = false;

void setup() {
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(ci, OUTPUT);
  pinMode(s0, INPUT);
  pinMode(s1, INPUT);
  pinMode(cO, INPUT);

  Serial.begin(9600);
  inputString.reserve(10); // optional: reserve space to avoid fragmenting memory
}

void loop() {
  if (stringComplete) {
    parseInput(inputString + '\n');
    inputString = "";
    stringComplete = false;

    digitalWrite(a0, ((~operandA) & 1));
    digitalWrite(a1, (~(operandA >> 1)) & 1);
    digitalWrite(a2, (~(operandA >> 2)) & 1);
    digitalWrite(b0, ((~operandB) & 1));
    digitalWrite(b1, (~(operandB >> 1)) & 1);
    digitalWrite(b2, (~(operandB >> 2)) & 1);
    digitalWrite(ci, !carryIn);

    delay(500); // wait while result is calculated
    String binaryResultString = "";
    binaryResultString += (char)(digitalRead(cO) + '0');
    binaryResultString += (char)(digitalRead(s2) + '0');
    binaryResultString += (char)(digitalRead(s1) + '0');
    binaryResultString += (char)(digitalRead(s0) + '0');

    int result = strtol(binaryResultString.c_str(), NULL, 2);
    // Serial.print("result = ");
    Serial.println(result);
    delay(250);

    stringComplete = false;
  }
}


// called automatically
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } 
    else {
      inputString += inChar;
    }
  }
}

void parseInput(String str) {
  if ((str.indexOf('+') == 1) && (str.indexOf('\n') == 3)) {
    if (isDigit(str.charAt(0)) && isDigit(str.charAt(2))){
      int tempOperandA = str.charAt(0) - '0';
      int tempOperandB = str.charAt(2) - '0';
      if ((tempOperandA <= 7) && (tempOperandB <= 7)){
        operandA = tempOperandA;
        operandB = tempOperandB;
        carryIn = 0;
      }
      else if((tempOperandA <= 7) && tempOperandB == 8){
        operandA = tempOperandA;
        operandB = tempOperandB - 1;
        carryIn = 1;
      }
      else if((tempOperandB <= 7) && tempOperandA == 8){
        operandA = tempOperandA - 1;
        operandB = tempOperandB;
        carryIn = 1;
      }
      else{
        operandA = 0;
        operandB = 0;
        carryIn = 0;
        Serial.println("Invalid Input");
      }
    }
  }
  else{
    operandA = 0;
    operandB = 0;
    Serial.println("Invalid Input");
  }
}
