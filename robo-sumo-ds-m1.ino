const int motor1=11;
const int motor2=10;
const int motor3=6;
const int motor4=5;

int sensorInfra1=2;
int sensorInfra2=1;
int sensorInfra3=7;

float sensorFrente, sensorEsquerdo, sensorDireito;

// FUNÇÃO PARA ENTRADA E SAÍDA DE DADOS DO SENSOR ULTRASSÔNICO
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
long sensor(int trigger, int echo){
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  return pulseIn(echo, HIGH);
}

void setup(){
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(sensorInfra1, INPUT);
}

//FUNÇÕES DE MOVIMENTO:

//FUNÇÃO PARA O ROBÔ MAPEAR A ÁREA
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void rastreio(float sFrente, float sEsquerda, float sDireita,int m1,int m2,int m3,int m4){
  if(sFrente>71&&sEsquerda>71&&sDireita>71){
  	Serial.println("Rastreando...");
  	analogWrite(m1, 30);
  	analogWrite(m2, 0);
  	analogWrite(m3, 30);
    analogWrite(m4, 0);
  }
}

//FUNÇÃO PARA O ROBÔ DESLIGAR OS MOTORES
void desligarMotores(int m1,int m2,int m3,int m4){
Serial.println("Desligando motores...");
  analogWrite(m1, 0);
  analogWrite(m2, 0);
  analogWrite(m3, 0);
  analogWrite(m4, 0);
  delay(500);
}

//FUNÇÃO PARA O ROBÔ VIRAR PARA A ESQUERDA
void virarEsquerda(int m1,int m2,int m3,int m4){
  Serial.println("Virando esquerda...");
  analogWrite(m1, 0);
  analogWrite(m2, 100);
  analogWrite(m3, 0);
  analogWrite(m4, 50);
  delay(500);
}

//FUNÇÃO PARA VIRAR PARA A DIREITA
void virarDireita(int m1,int m2,int m3,int m4){
  Serial.println("Virando direita...");
  analogWrite(m1, 50);
  analogWrite(m2, 0);
  analogWrite(m3, 100);
  analogWrite(m4, 0);
  delay(500);
}

//FUNÇÃO PARA ATAQUE
void ataque(int m1,int m2,int m3,int m4){
  Serial.println("Atacando!");
  analogWrite(m1, 255);
  analogWrite(m2, 0);
  analogWrite(m3, 0);
  analogWrite(m4, 255);
  delay(500);
}
void frente(int m1,int m2,int m3,int m4){
  Serial.println("Frente");
  analogWrite(m1, 150);
  analogWrite(m2, 0);
  analogWrite(m3, 0);
  analogWrite(m4, 150);
  delay(500);
}

// FUNÇÃO COM A FINALIDADE DE FUGIR, CASO O ROBÔ ESTEJA SENDO 
// EMPURRADO PARA FORA DA ARENA.

// CASO ESTEJA SENDO EMPURRADO PELO LADO ESQUERDO, O SENSOR INFRAVERMELHO
// VAI LER A FAIXA BRANCA DA ARENA, E O ROBÔ IRÁ ANDAR PRA FRENTE
// E FUGIR PARA O LADO DO ATACANTE.
void fuga(int infraCosta,int infraEsquerdo, int infraDireito, float sFrente, float sEsquerdo, float sDireito, int m1,int m2,int m3,int m4){
  if(sEsquerdo<=15&&digitalRead(infraDireito)==1){
    Serial.println(digitalRead(infraDireito)+ String(" Sensor Direito"));
    frente(m1, m2, m3, m4);
    delay(1000);
    desligarMotores(m1, m2, m3, m4);
    virarEsquerda(m1, m2, m3, m4);
    delay(1000);
  }
  if(sDireito<=15&&digitalRead(infraEsquerdo)==1){
    Serial.println(digitalRead(infraEsquerdo)+ String(" Sensor Esquerdo"));
    frente(m1, m2, m3, m4);
    delay(1000);
    desligarMotores(m1, m2, m3, m4);
    virarDireita(m1, m2, m3, m4);
    delay(1000);
  }
  if(digitalRead(infraCosta)==1 && sFrente<=15){
  	Serial.println(digitalRead(infraCosta) + String(" Sensor Costas"));
    frente(m1, m2, m3, m4);
    delay(1000);
  }
}
//====================================================//
// FUNÇÕES PARA DETECÇÃO 

//FUNÇÃO PARA DETECTAR SE HÁ INIMIGOS NA FRENTE DO ROBÔ
void deteccaoFrente(float sFrente,int m1,int m2,int m3,int m4){
  if(sFrente<=70){
    delay(1000);
    Serial.println(sFrente);
    Serial.println("Frente");
    Serial.println("Achei viu!");
    ataque(m1, m2, m3, m4);
  }
}

//FUNÇÃO PARA DETECTAR SE HÁ INIMIGOS NA PARTE ESQUERDA DO ROBÔ
void deteccaoEsquerda(float sEsquerdo,int m1,int m2,int m3,int m4){
  if(sEsquerdo<=70){
    desligarMotores(m1, m2, m3, m4);
    delay(1000);
    Serial.println(sEsquerdo);
    Serial.println("Esquerda");
    Serial.println("Achei viu!");
    virarEsquerda(m1, m2, m3, m4);
  }
}

//FUNÇÃO PARA DETECTAR SE HÁ INIMIGOS NA PARTE DIREITA DO ROBÔ
void deteccaoDireita(float sDireito,int m1,int m2,int m3,int m4){
  if(sDireito<=70){
    desligarMotores(m1, m2, m3, m4);
    delay(1000);
    Serial.println("Direita");
    Serial.println(sDireito);
    Serial.println("Achei viu!");
    virarDireita(m1, m2, m3, m4);
  }
}
// AUTO PROTECAO DE LINHA BRANCA
void autoProtecao(int infraCosta,int infraEsquerdo, int infraDireito,float sFrente, float sEsquerdo, float sDireito,int m1,int m2,int m3,int m4){
  if(digitalRead(infraCosta)==1){
  	desligarMotores(m1, m2, m3, m4);
    frente(m1, m2, m3, m4);
  }
  if(digitalRead(infraEsquerdo)==1){
  	desligarMotores(m1, m2, m3, m4);
    virarDireita(m1, m2, m3, m4);
    desligarMotores(m1, m2, m3, m4);
    frente(m1, m2, m3, m4);
  }
  if(digitalRead(infraEsquerdo)==1){
  	desligarMotores(m1, m2, m3, m4);
    virarEsquerda(m1, m2, m3, m4);
    desligarMotores(m1, m2, m3, m4);
    frente(m1, m2, m3, m4);
  }
}

//====================================================//
void loop(){
  sensorFrente=sensor(4,3)*0.01723;
  sensorEsquerdo=sensor(13,12)*0.01723;
  sensorDireito=sensor(9,8)*0.01723;
  deteccaoEsquerda(sensorEsquerdo, motor1, motor2, motor3, motor4);
  deteccaoDireita(sensorDireito, motor1, motor2, motor3, motor4);
  deteccaoFrente(sensorFrente, motor1, motor2, motor3, motor4);
  fuga(sensorInfra1, sensorInfra3, sensorInfra2, sensorFrente, sensorEsquerdo, sensorDireito, motor1, motor2, motor3, motor4);
  autoProtecao(sensorInfra1, sensorInfra3, sensorInfra2, sensorFrente, sensorEsquerdo, sensorDireito, motor1, motor2, motor3, motor4);
  rastreio(sensorFrente, sensorEsquerdo, sensorDireito, motor1, motor2, motor3, motor4);
}