# TP_Syst_MicroContr-leur_3DN  // Faiçal FQUIHI et Adnane HAJJAJI
# A base de carte NUCLEO_L476RG

1/
Test de l’USART2 connecté à la STLink interne (COM7), en utilisant le terminal RealTerm : 
Fonction USART2_SendString(void) 

2/
Redirection de printf du flux sortant stdout vers USART2 en redéfinissant la fonction " int __io_putchar(int chr)"

3/
Développemnt d'un driver pour les leds du GPIO Expander MCP23S17 :
	driver_led.h : 
		6 fonctions publiques
		  -->void LED_Driver_Init(void) : pour initialisation du MCP23S17 
		  -->void LED_SetGPIOA(uint8_t value) : pour envoyer un valeur au GPIOA
		  -->void LED_SetGPIOB(uint8_t value) : pour envoyer un valeur au GPIOB
		  -->void LED_SetPin(uint8_t pinNumber, GPIO_PinState state); // pour commander une led de 0 à 15 : 0->7 : A0->A7, 8->15 : B0->B7
		  -->void chenillard(void) : pour effet chenillard sur toutes les leds
		  -->void chennilard_unport(void) : pour effet chennilard sur un port GPIOA ou GPIOB
		
	driver_led.c
		1 fonction interne :
		  --> static void MCP23S17_WriteRegister(uint8_t reg, uint8_t value) : écriture dans un registre du MCP23S17 via SPI
		  

4/Configuration du CODEC par l’I2C
4.1/ // Lecture de 2 octets depuis le registre CHIP_ID : résultat affichage "CHIP_ID: 0xA011"

MCLK=12.27 MHz
LRCLK = 47.9 KHz
FRq DIN 210KHz

5/Dirver pour le codec SGTL500
sgtl5000.h : 3 fonctions publiques
	void SGTL5000_Init(void)
	void SGTL5000_WriteRegister(uint16_t reg, uint16_t val)
	uint16_t SGTL5000_ReadRegister(uint16_t reg) : pour débugage 

sgtl5000.c	

Génération du signal triangulaire se fait dans le main : void Generate_TriangleWave(void)
Mesures avec oscilloscope :
MCLK=12.27 MHz
LRCLK = 47.9 KHz
FRq DIN 210KHz


