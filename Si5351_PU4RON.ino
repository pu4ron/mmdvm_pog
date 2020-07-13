/*
Ronualdo - PU4RON

Biblioteca usada: Etherkit Si5351

*/

#include <Wire.h>
#include <si5351.h>

#define TCXO_SI5351           25000000ULL      // Valor do cristal do modulo si5351
#define valor_ajuste          89550ULL         // Valor de ajuste do modulo si5351
#define Tempo                 300000ULL        // Tempo de atualização do modulo si5351
#define Freq_out0_mmdvm       1200000000ULL    // Frequencia de saida CLK0 para placa MMDVM_POG
#define Freq_out1_mmdvm       1420000000ULL    // Frequencia de saida CLK1 para placa MMDVM_POG
#define Freq_out2_mmdvm       1920000000ULL    // Frequencia de saida CLK2 para placa MMDVM_POG


char pA = "SI5351_DRIVE_2MA";
char pB = "SI5351_DRIVE_4MA";
char pC = "SI5351_DRIVE_6MA";
char pD = "SI5351_DRIVE_8MA";
int  sim = 1;
int  nao = 0;
Si5351   dmr;

char Pot_out0 = pA;                            // Potencia de saida do SI5351. Valores permitidos: "pA"=default(2MA); "pB"=4MA;  "pC"=6MA  "pD"=8MA 
char Pot_out1 = pA;                            // Potencia de saida do SI5351. Valores permitidos: "pA"=default(2MA); "pB"=4MA;  "pC"=6MA  "pD"=8MA 
char Pot_out2 = pA;                            // Potencia de saida do SI5351. Valores permitidos: "pA"=default(2MA); "pB"=4MA;  "pC"=6MA  "pD"=8MA 

int  Inv_sinal0 = 1;                           // Inversao de sinal. 0=desligado 1=Ligado.
int  Inv_sinal1 = 1;                           // Inversao de sinal. 0=desligado 1=Ligado.
int  Inv_sinal2 = 1;                           // Inversao de sinal. 0=desligado 1=Ligado.

int clk0 = sim;                                 // Ativa=(sim) ou desativa=(nao) saida clk0
int clk1 = sim;                                 // Ativa=(sim) ou desativa=(nao) saida clk1
int clk2 = sim;                                 // Ativa=(sim) ou desativa=(nao) saida clk2


void setup() {     
         
     dmr.output_enable(SI5351_CLK0, clk0);
     dmr.output_enable(SI5351_CLK1, clk1);
     dmr.output_enable(SI5351_CLK2, clk2);
     
     dmr.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
     dmr.set_pll(SI5351_PLL_FIXED, SI5351_PLLB);
     
     dmr.init(SI5351_CRYSTAL_LOAD_8PF, TCXO_SI5351, 0);
     
     dmr.set_correction(valor_ajuste, SI5351_PLL_INPUT_XO);
     
     dmr.drive_strength(SI5351_CLK0, Pot_out0);
     dmr.drive_strength(SI5351_CLK1, Pot_out1);
     dmr.drive_strength(SI5351_CLK2, Pot_out2);
     
     dmr.set_clock_invert(SI5351_CLK0, Inv_sinal0);
     dmr.set_clock_invert(SI5351_CLK1, Inv_sinal1);
     dmr.set_clock_invert(SI5351_CLK2, Inv_sinal2);
}

void loop(){

     dmr.set_freq(Freq_out0_mmdvm, SI5351_CLK0);
     dmr.set_freq(Freq_out1_mmdvm, SI5351_CLK1);
     dmr.set_freq(Freq_out2_mmdvm, SI5351_CLK2);
     delay(Tempo);
}
