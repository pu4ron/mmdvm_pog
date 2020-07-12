/*
Ronualdo - PU4RON

Biblioteca usada: Etherkit Si5351

*/

#include <Wire.h>
#include <si5351.h>

#define TCXO_SI5351          25000000ULL      // Valor do cristal do modulo si5351
#define Freq_out_mmdvm       1200000000ULL    // Frequencia de saida para placa MMDVM_POG
#define Valor_ajuste         89550ULL         // Valor de ajuste do modulo si5351
#define Tempo                300000ULL        // Tempo de atualização do modulo si5351

char pA = "SI5351_DRIVE_2MA";
char pB = "SI5351_DRIVE_4MA";
char pC = "SI5351_DRIVE_6MA";
char pD = "SI5351_DRIVE_8MA";

char Pot_out = pA;                            // Potencia de saida do SI5351. Valores permitidos: "pA"=default(2MA); "pB"=4MA;  "pC"=6MA  "pD"=8MA 
int  Inv_sinal = 1;                           // Inversao de sinal. 0=desligado 1=Ligado.

Si5351 dmr;




void setup() {     
         
     dmr.output_enable(SI5351_CLK0, 1);
     dmr.output_enable(SI5351_CLK1, 1);
     dmr.output_enable(SI5351_CLK2, 1);
     dmr.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
     dmr.init(SI5351_CRYSTAL_LOAD_8PF, TCXO_SI5351, 0);
     dmr.set_correction(Valor_ajuste, SI5351_PLL_INPUT_XO);
     dmr.drive_strength(SI5351_CLK0, Pot_out);
     dmr.drive_strength(SI5351_CLK1, Pot_out);
     dmr.drive_strength(SI5351_CLK2, Pot_out);
     dmr.set_clock_invert(SI5351_CLK0, Inv_sinal);
     dmr.set_clock_invert(SI5351_CLK1, Inv_sinal);
     dmr.set_clock_invert(SI5351_CLK2, Inv_sinal);
}

void loop(){

     dmr.set_freq(Freq_out_mmdvm, SI5351_CLK0);
     dmr.set_freq(Freq_out_mmdvm, SI5351_CLK1);
     dmr.set_freq(Freq_out_mmdvm, SI5351_CLK2);
     delay(Tempo);
}
