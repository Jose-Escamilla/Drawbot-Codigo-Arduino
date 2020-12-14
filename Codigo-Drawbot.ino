#include<AccelStepper.h>
#include<multiStepper.h>
#include<Servo.h>
#include<math.h>

#define DIRM1 4
#define STEPM1 5
#define DIRM2 6
#define STEPM2 7
#define motorInterfaceType 1
#define velocidad 1000
int flag=1;
int flag_1=1;
float antx=0;
float anty=0;

const int equipo_1[147][2]={/*Circulo*/{50,250},{48,234},{45,219},{39,204},{30,191},{20,179},{8,169},{4,160},{19,154},{34,151},{19,150},
                                       {65,151},{80,154},{98,160},{108,169},{120,179},{130,191},{139,204},{145,219},{150,0},{148,265},
                                       {145,280},{139,295},{130,308},{120,320},{108,330},{95,339},{80,345},{65,348},{50,350},{34,348},
                                       {19,345},{4,339},{8,330},{20,320},{30,308},{39,295},{19,345},{4,339},{8,330},{20,320},{30,308},
                                       {39,295},{45,280},{48,265}};
                       /*circulo{145,132},{1,1},{145,132},{140,133},{135,136},{131,146},{130,147},
                       {131,152},{135,158},{140,161},{145,161},{150,161},{155,158},{159,152},{160,147},{159,,142},{155,136},
                       {150,133},{144,132},{144,132},{145,131},{0,0}};*/

AccelStepper stepper_1 = AccelStepper(motorInterfaceType, STEPM1, DIRM1);
AccelStepper stepper_2 = AccelStepper(motorInterfaceType, STEPM2, DIRM2);

AccelStepper stepper_x = AccelStepper(motorInterfaceType, STEPM1, DIRM1);
AccelStepper stepper_y = AccelStepper(motorInterfaceType, STEPM2, DIRM2);

multiStepper StepperControl;

Servo servo_1;

void setup() {
    
    Serial.begin(9600);
    
    servo_1.attach(10);
    //velocidades y aceleraciones para la configuración de los motores 1 y 2
    stepper_1.setMaxSpeed(5000); //Esta dado en Pasos por segundo
    stepper_1.setAcceleration(2000); //Esta dado por pasos sobre segundo al cuadrado
    stepper_2.setAcceleration(2000);
    stepper_2.setMaxSpeed(5000);
    //Velocidades y aceleraciones para la configuracion x, y
    stepper_x.setMaxSpeed(700);
    stepper_x.setMinPulseWidth(20);
    stepper_x.setAcceleration(100.000);
    stepper_y.setAcceleration(100.00);
    stepper_y.setMinPulseWidth(20);
    stepper_y.setMaxSpeed(700);
    StepperControl.addStepper(stepper_x);
    StepperControl.addStepper(stepper_y);
    //Interrupción para los motores a pasos
    attachInterrupt(digitalPinToInterrupt(2),SET_1,FALLING);
    attachInterrupt(digitalPinToInterrupt(3),SET_2,FALLING);

}

void loop() {
    
    char datos [8]={};
    float valorx,valory;
    float H;
    float fi_1;
    float fi_3;
    float cfi_3;
    float q_1;
    float ct1:
    float teta;
    float teta_1;
    float teta_2;
    float m_2;
    float m_1;
    float angulo_1;
    float angulo_2;
    long angulox;
    long anguloy;
    float anguloxf;
    float anguloyf;
    long arreglo[2];
    const float factor=39.11111111;  //Factor trasmisión (200)*(16)*(4.4)/(360)
    const float l_x=201.950489;
    const float angulo_set=27.5;     //angulo del eslabon del segundo motor respecto al eje x
    
    SET MOTORS();
    
    delay(1000);
    //ciclos para la función del servo
    for(int i=0; i<221; i++){
     
        if(equipo_1[i][0] == 1 && equipo_1[i][1] == 1){
            servo_1.write(90);
            
          }
        
          if(equipo_1[i][0] == 1 && equipo_1[i][1] == 1){
            servo_1.write(0);
            delay(200);
          }
        
        if(equipo_1[i][1] != 0 && equipo_1[i][0] != 0 && equipo_1[i][1] != 1 && equipo_1[i][1] != 1){
            valorx = (float) equipo_1[i][0]:
            valory = (float) equipo_1[i][1]:
        }    
        
         H = sqrt(pow(valorx,2)+pow(valory,2));
         fi_1 = atan(valory/valorx);
         cfi_3 = ((40000.0+pow(H,2)-pow(l_x,2))/(2*200.0*H));
         fi_3 = atan(2*200.0*H*sqrt(1.0-pow(cfi_3,2))/(40000.0+pow(H,2)-pow(l_x,2)));
         q_1 = PI-((fi_1)+(fi_3));
         m_1 = q_1*(180.0/PI);
        
        ct1 = ((40000.0+pow(l_x,2)-pow(H,2))/(2*200.0*l_x));
        teta_2 = atan(28.0/200.0);
        
        teta_1 = atan ((400.0*l_x*sqrt(1.0*pow(ct1,2)))/(40000.0+pow(l_x,2)-pow(H,2)));
        teta = teta_1-teta_2;
        
        //m_2 es la variable para el motor a paso 2   //variable para M a pasos #2
        m_2=(m_1+angulo_set)-(abs(teta)*180.0/PI);
        
        angulo_1=m_1;
        angulo_2=m_2;
        
        if(angulo_1 >= antx && angulo_2 >= anty ){anguloxf= angulo_1-antx; anguloyf= angulo_2-anty;
           angulox = (long) (anguloxf * factor);
           anguloy = (long) (anguloyf * factor);
        }
        else if(antx == 0 && anty == 0){angulofx = angulo_1; anguloyf = angulo_2;
           angulox = (long) (anguloxf * factor); 
           anguloy = (long) (anguloyf * factor);
        }
        else if(angulo_1 < antx || angulo_2 < anty){anguloxf = antx-angulo_1; anguloyf=anty-angulo_2;
                                                    
           angulox = (long) (anguloxf * factor);
           anguloy = (long) (anguloyf * factor);
           angulox*=-1;                         
           anguloy*=-1;
           delay(1);
        }
        
        
        arreglo[0] = angulox;
        arreglo[1] = anguloy;
        stepper_x.setCurrentPosition(0);
        stepper_y.setCurrentPosition(0);
        StepperControl.moveTo(arreglo);
        StepperControl.runSpeedToPosition();
        
        antx=angulo_1;
        anty=angulo_2;
        
        flag=1;
        flag_1=1;
        
    }
    
    delay(1000);
    

}



/*
* Funciones de interrupciones
*/
void SET_1(){
    
    flag=0;
    
}
void SET_2(){
    
    flag_1=0;
    
}

/*
* Funciones para resetear los motores a
*/
void SET_MOTORS(void){
    
    stepper_1.moveTo(-16426);
    stepper_2.moveTo(-16426);
    servo_1.write(0);
    delay(500);
    
    while( (stepper_1.distanceToGo()!=0) || (stepper_2.distanceToGo()!=0)){
        
        stepper_1.setSpeed(-2500*flag_1);
        stepper_1.runSpeedToPosition();
        stepper_2.setSpeed(-2500*flag);
        stepper_2.runSpeedToPosition();
        
        //reseteamos la posición de los motores a pasos en 0
        if(!flag && !flag_1){
            
            stepper_1.stop();
            stepper_2.stop();
            stepper_1.setCurrentPosition(0);
            stepper_2.setCurrentPosition(0);
            antx=0;
            anty=0;
            
     }
   }
}
