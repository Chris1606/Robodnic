    #include <Ps3Controller.h>
 


    #define LEFT_FORWARD 14
    #define LEFT_BACKWARD 27
    

    #define SERVO 19           
  
    #define PWM_FREQUENCY 20000
    
    #define PWM_RESOLUTION 8
    #define PWM_CHANNEL_1 1
    #define PWM_CHANNEL_2 2
    #define PWM_CHANNEL_3 3

    
  
    uint8_t forward = 0;
    uint8_t backward = 0;
    uint8_t left = 0;
    uint8_t right = 0;
    uint8_t fast = 0;
    uint8_t slow = 0;
    uint8_t fan = 0;
    uint8_t turn_left = 0;
    uint8_t turn_right = 0;
    uint8_t pos = 0 ; 
    
    int battery = 0;
    
    void notify()
    {
        
        /*  Moving  */
    
     if( abs(Ps3.event.analog_changed.button.up) ){
         
          
          forward = Ps3.data.analog.button.up; 
          
          Serial.println("Foward");
          Serial.println(forward);
          
         ledcWrite(PWM_CHANNEL_1, forward);
         ledcWrite(PWM_CHANNEL_2, 0);   

          
       }

        if( abs(Ps3.event.analog_changed.button.cross) ){
        
        pos =  Ps3.data.analog.button.cross ;
        if (pos >180) pos = 180;
        Serial.println("pos");
        Serial.println(pos);
       ledcWrite(PWM_CHANNEL_3, pos);
       delay(10);
           
       }
       if( abs(Ps3.event.analog_changed.button.right) ){ 
       
//        Serial.println("Right Rotate");
//        right = Ps3.data.analog.button.right;

       }
    
       if( abs(Ps3.event.analog_changed.button.down) ){    
      
//        backward = Ps3.data.analog.button.down;  
//        if (backward >200) backward = 200;

       }
    
       if( abs(Ps3.event.analog_changed.button.left) ){
        
//        left =  Ps3.data.analog.button.left ;
//        if (left >200) left = 200;

           
           
       }

 
        //speed up 
        if( Ps3.event.button_down.r1 ){

        }
            
        if( Ps3.event.button_up.r1 )
           {


           }
    
    
        /*setting relay turn On/OFF fan*/
          if (Ps3.data.button.square){

     
      }     
      if (Ps3.data.button.circle){


      }
    
        /*lift*/
        if(Ps3.event.button_down.triangle){

        }
        
        if(Ps3.event.button_up.triangle){

        }

        if (Ps3.event.button_down.cross){

        }
        
     

        
        /* Battery */
        if( battery != Ps3.data.status.battery ){
            battery = Ps3.data.status.battery;
            Serial.print("The controller battery is ");
            if( battery == ps3_status_battery_charging )      Serial.println("charging");
            else if( battery == ps3_status_battery_full )     Serial.println("FULL");
            else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
            else if( battery == ps3_status_battery_low)       Serial.println("LOW");
            else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
            else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
            else Serial.println("UNDEFINED");
        }
    }
    
    void onConnect()
    {
      Serial.println("Connected.");
    }
    
    void setup()
    {
   
      ledcSetup(PWM_CHANNEL_1, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_2, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(SERVO, 50, PWM_RESOLUTION);
    
    
      ledcAttachPin(LEFT_FORWARD, PWM_CHANNEL_1);
      ledcAttachPin(LEFT_BACKWARD, PWM_CHANNEL_2);
      ledcAttachPin(SERVO, PWM_CHANNEL_3);
      
  
      

      Serial.begin(115200);
      Ps3.attach(notify);
      Ps3.attachOnConnect(onConnect);
      Ps3.begin("01:02:03:04:05:07");   
      Serial.println("Ready.");
    }
    
    void loop()
    {
      if(!Ps3.isConnected())
        return;
    }
