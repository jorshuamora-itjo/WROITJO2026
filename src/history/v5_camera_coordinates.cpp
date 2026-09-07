#include <Arduino.h>
#include <Pixy2.h>

Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  pixy.init();
  Serial.print("\033[2J"); 
}

void loop() {
  int numeroDeObjetos = pixy.ccc.getBlocks();
  
  if (numeroDeObjetos > 0) {
    
    Serial.print("\033[H"); 

    Serial.println("=== DATOS DE LA PIXY2 ===");
    Serial.print("Objetos detectados: ");
    Serial.println(numeroDeObjetos);
    Serial.println("-------------------------");
    
    
    Serial.print("Firma: ");  Serial.println(pixy.ccc.blocks[0].m_signature);
    Serial.print("Coord X: "); Serial.print(pixy.ccc.blocks[0].m_x);      Serial.println("   "); 
    Serial.print("Coord Y: "); Serial.print(pixy.ccc.blocks[0].m_y);      Serial.println("   ");
    Serial.print("Ancho: ");   Serial.print(pixy.ccc.blocks[0].m_width);  Serial.println("   ");
    Serial.print("Alto: ");    Serial.print(pixy.ccc.blocks[0].m_height); Serial.println("   ");
    Serial.println("=========================");
  }
  
  
  delay(200); 
}
