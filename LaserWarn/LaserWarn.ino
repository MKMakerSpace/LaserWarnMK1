int flow = 2;
int buzzer = 12;
int relay = 11;

const int rolling=10;
unsigned long duration;

float ratio;
float average;

void setup()
{
    Serial.begin(9600);
    pinMode(flow, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(relay, OUTPUT);

    average = pulseIn(flow, HIGH, 200000);
    if (average == 0)
    {
        average = 200000;
    }
    ratio=(1.0/rolling);
}

void loop()
{
    duration = pulseIn(flow, HIGH, 200000);
    if (duration == 0)
    {
        duration = 200000;
    }
    average = (average*(1-ratio))+(duration*ratio);
    //average = 450; //debug
    if (average >= 5000)
    {
        kill(HIGH);
        alert(HIGH);
        Serial.print(average);
        Serial.println(" Danger");
    }
    else
    {
        kill(LOW);
        alert(LOW);
        Serial.print(average);
        Serial.println(" Safe");
    }
    delay(100);
}

void kill(bool Mode)
{
    if (Mode == HIGH)
    {
        digitalWrite(relay, LOW);
    }
    else
    {
        digitalWrite(relay, HIGH);
    }
}

void alert(bool Mode)
{
    if (Mode == HIGH)
    {
        digitalWrite(buzzer, HIGH);
        delay(250);
        digitalWrite(buzzer, LOW);
        delay(250);
    }
}

