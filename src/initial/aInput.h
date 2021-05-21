

/* xInput buttonset(3);
 *  short buttonDef[6] = {0, 300, 370,460,600,900};
 *  buttonset.setup(6, buttonDef);  
 * Serial.print(buttonset.check()); > [0:4]  
 */

class xInput{

  public:
    xInput(byte pinID){ pin = pinID;}

    byte pin;
    byte keys;
    byte result;

    short chData;
    short lsthan[10];

    void setup(byte k, short x[]);
    byte check();
    };
    
void xInput::setup(byte k, short x[]){
  for(int i=0; i<k; i++){
    lsthan[i] = x[i];    
    }
    keys = k;
  }

byte xInput::check(){
  chData = analogRead(pin);
  byte res =0;
  for(int j=1; j<keys; j++){
    if(chData > lsthan[j-1] && chData <= lsthan[j]) res = j-1;
    }
  return res;
  } 
