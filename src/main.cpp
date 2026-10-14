#include <Arduino.h>

void leituraBloqueante();
void leituraNaoBloqueante();
void processarFrase(const char*);

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  //* readStringUntil espera no máximo esse tempo (ms) pelo '\n'(ENTER)
  //* O padrão é 1000ms

  Serial.println();
  Serial.println("Digite o seu nome e pressione ENTER: ");
}


void loop() {
  leituraNaoBloqueante();
}

void leituraNaoBloqueante(){
  const int TAMANHO_MAX = 50; //* tamanho do vetor (incluir no cálculo o '/0')
  static char frase[TAMANHO_MAX];
  static int position = 0;

  while(Serial.available() > 0){
    char c = Serial.read();

    if(c == '\r') continue;
    //* o continue pula o restanto do while naquela volta e passa para a leitura 
    //* do próximo caractere. O '\r' é lido e simplesmente descartado, sem entrar no vetor.

    if(c == '\n'){
      frase[position] = '\0';
      if(position > 0) processarFrase(frase);
      position = 0;
    }
    else if(position < TAMANHO_MAX -1){
      frase[position] = c;
      position++;
    }
  }
}

void processarFrase(const char* texto){
  char espaco = 32;
  Serial.print(espaco);
  Serial.print(espaco);
  Serial.print(espaco);
  Serial.print(espaco);
  Serial.print(espaco);
  
  Serial.printf("Recebido: [%s] \n\r", texto);

  if(strcmp(texto, "ola") == 0){
    Serial.println("Olá para você tambem");
  }
}

void leituraBloqueante(){
    //* available() diz quantos bytes já chegaram e estão esperando a leitura
  if(Serial.available() > 0){
    
    String texto = Serial.readStringUntil('\n');
    
    //* trim() remove do fim do texto os espaços, '/r', '/t', '\n' que alguns terminais enviam
    texto.trim();
    
    if(texto.length() == 0) return;
    Serial.printf("Seu nome é %s \n\r", texto.c_str());
    Serial.printf("Quantidade de caracteres: %u \n\r", texto.length());

    Serial.printf("Primeira letra: %c \n\r", texto.charAt(0));
    Serial.printf("Ultima letra: %c \n\r", texto[  texto.length() -1] );

    String maiusculo = texto;
    maiusculo.toUpperCase();
    Serial.printf("Em maiusculas: %s \n\r", maiusculo.c_str());

    if(maiusculo == "GUSTAVO"){
      Serial.println("Este é o seu nome correto");
    }
  }
}