//#include <TB6612_ESP32.h>

// Obs: não entendi como diabos adicionar um header aqui no arduino, deixei a implementação da classe sumo solta aqui por enquanto
/*  Header Sumo */
class Sumo
{
    public:
        Sumo(char pin);
        ~Sumo();
        int read();
    private:
        char pin;
        double c_LineSensorLimit = 0.9;
        double c_LineSensorResolution = 4095.0;  
};


//motores
const int AIN1 = 2, BIN1 = 7, AIN2 = 4, BIN2 = 8, PWMA = 5, PWMB = 6, STBY = 9;

//sensores de linha
const int LINHAE = 0, LINHAD = 0;

const double c_LineSensorLimit = 0.9;
const double c_LineSensorResolution = 4095;

Sumo sensorEsquerdo(15);

//inicializacao dos motores
//Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
//Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int velPadrao = 255;

void setup(){
    Serial.begin(9600);
    pinMode(LINHAD, INPUT);
    pinMode(LINHAE, INPUT);
}

void loop (){ 
    sensorEsquerdo.read();
    delay(200);
}

/*void controleMotores(int leituraE, int leituraD){
    if (leituraE && leituraD){ //se ambos estao detectando linha preta
        //avanca o robo
        forward(motor1, motor2, velPadrao);
        Serial.println("Avanca puta");
    }
    else if (leituraE == 0 || leituraD == 0){
        backward(motor1, motor2, velPadrao); 
        Serial.println("Joga pra tras coxta encosta");
    }
}*/


/*  Implementation Sumo */
Sumo::Sumo(char pin)
{
    this->c_LineSensorLimit = 0.9;
    this->c_LineSensorResolution = 4095.0;
    this->pin = pin;
}
Sumo::~Sumo()
{

}
int Sumo::read()
{
    double leitura = analogRead(this->pin);

    if (leitura >= this->c_LineSensorLimit*this->c_LineSensorResolution)
    {
        Serial.println("Linha preta");
        return leitura;
    }
    
    Serial.println("Linha branca");
    return leitura;
}
