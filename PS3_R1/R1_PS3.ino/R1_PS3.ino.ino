    #include <Ps3Controller.h>
      
    #define LEFT_FORWARD 32
    #define LEFT_BACKWARD 33
    #define RIGHT_FORWARD 25
    #define RIGHT_BACKWARD 26
                            
    #define FAN_1 14
    #define FAN_2 12

    #define FAN_3 18
    #define FAN_4 19

    #define LIFTER_FW 22 
    #define LIFTER_BW 23
    
     
    #define PWM_FREQUENCY 20000
    #define PWM_RESOLUTION 8
    #define PWM_CHANNEL_1 1
    #define PWM_CHANNEL_2 2
    #define PWM_CHANNEL_3 3
    #define PWM_CHANNEL_4 4
    
    #define PWM_CHANNEL_5 5
    #define PWM_CHANNEL_6 6
    #define PWM_CHANNEL_7 7
    #define PWM_CHANNEL_8 8
    
    #define PWM_CHANNEL_9 9
    #define PWM_CHANNEL_10 10
    
  
  
    #define FAST_SPEED 255
    #define SLOW_SPEED 100
    
    uint8_t forward = 0;
    uint8_t backward = 0;
    uint8_t left = 0;
    uint8_t right = 0;
    uint8_t fast = 0;
    uint8_t slow = 0;
    uint8_t fan = 0;
    uint8_t turn_left = 0;
    uint8_t turn_right = 0;
    
    
    
    int battery = 0;
    
    void notify()
    {
        
        /*  Moving  */
    
    
    
     if( abs(Ps3.event.analog_changed.button.up) ){
          
        forward = Ps3.data.analog.button.up; 
        if (forward >200) forward = 200;
        Serial.println("Foward");
        Serial.println(forward);
        ledcWrite(PWM_CHANNEL_1, forward);
        ledcWrite(PWM_CHANNEL_2, 0);   
        ledcWrite(PWM_CHANNEL_3, forward);
        ledcWrite(PWM_CHANNEL_4, 0);
          
       }
    
       if( abs(Ps3.event.analog_changed.button.right) ){ 
       
        Serial.println("Right Rotate");
        right = Ps3.data.analog.button.right;
        if (right >200) right = 200;  
        Serial.println(right);  
        ledcWrite(PWM_CHANNEL_1, 0);
        ledcWrite(PWM_CHANNEL_2, right);
        ledcWrite(PWM_CHANNEL_3, right);
        ledcWrite(PWM_CHANNEL_4, 0);
       }
    
       if( abs(Ps3.event.analog_changed.button.down) ){    
      
        backward = Ps3.data.analog.button.down;  
        if (backward >200) backward = 200;
        Serial.println(backward); 
        Serial.println("Backward");
        ledcWrite(PWM_CHANNEL_1, 0); 
        ledcWrite(PWM_CHANNEL_2, backward);
        ledcWrite(PWM_CHANNEL_3, 0);
        ledcWrite(PWM_CHANNEL_4, backward);
       }
    
       if( abs(Ps3.event.analog_changed.button.left) ){
        
        left =  Ps3.data.analog.button.left ;
        if (left >200) left = 200;
        Serial.println(left);
        Serial.println("Left Rotate");
        ledcWrite(PWM_CHANNEL_1, left);
        ledcWrite(PWM_CHANNEL_2, 0);
        ledcWrite(PWM_CHANNEL_3, 0);
        ledcWrite(PWM_CHANNEL_4, left);
           
           
       }
        //speed up 
        if( Ps3.event.button_down.r1 ){
          ledcWrite(PWM_CHANNEL_1, 255);
          ledcWrite(PWM_CHANNEL_2, 0);   
          ledcWrite(PWM_CHANNEL_3, 255);
          ledcWrite(PWM_CHANNEL_4, 0);
        }
            
        if( Ps3.event.button_up.r1 )
           {
          ledcWrite(PWM_CHANNEL_1, 0);
          ledcWrite(PWM_CHANNEL_2, 0);   
          ledcWrite(PWM_CHANNEL_3, 0);    
          ledcWrite(PWM_CHANNEL_4, 0);
           }
    
    
        /*setting relay turn On/OFF fan*/
          if (Ps3.data.button.square){
         ledcWrite(PWM_CHANNEL_5, 150);
         ledcWrite(PWM_CHANNEL_6, 0);
         ledcWrite(PWM_CHANNEL_9, 150);
         ledcWrite(PWM_CHANNEL_10, 0);
     
      }     
      if (Ps3.data.button.circle){
         ledcWrite(PWM_CHANNEL_5, 0);
         ledcWrite(PWM_CHANNEL_6, 0);
         ledcWrite(PWM_CHANNEL_9, 0);
         ledcWrite(PWM_CHANNEL_10, 0);

      }
    
        /*lift*/
        if(Ps3.event.button_down.triangle){
          ledcWrite(PWM_CHANNEL_7, 120);
          ledcWrite(PWM_CHANNEL_8, 0);  
        }
        
        if(Ps3.event.button_up.triangle){
          ledcWrite(PWM_CHANNEL_7, 0);
          ledcWrite(PWM_CHANNEL_8, 0);
        }

        if (Ps3.event.button_down.cross){
          ledcWrite(PWM_CHANNEL_7,0 );
          ledcWrite(PWM_CHANNEL_8, 120);
        }
        
        if(Ps3.event.button_up.cross){
          ledcWrite(PWM_CHANNEL_7, 0);
          ledcWrite(PWM_CHANNEL_8, 0);
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
      ledcSetup(PWM_CHANNEL_3, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_4, PWM_FREQUENCY, PWM_RESOLUTION);
  
      ledcSetup(PWM_CHANNEL_5, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_6, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_7, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_8, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_9, PWM_FREQUENCY, PWM_RESOLUTION);
      ledcSetup(PWM_CHANNEL_10, PWM_FREQUENCY, PWM_RESOLUTION);
    
      ledcAttachPin(LEFT_FORWARD, PWM_CHANNEL_1);
      ledcAttachPin(LEFT_BACKWARD, PWM_CHANNEL_2);
      ledcAttachPin(RIGHT_FORWARD, PWM_CHANNEL_3);
      ledcAttachPin(RIGHT_BACKWARD, PWM_CHANNEL_4);
  
      ledcAttachPin(FAN_1, PWM_CHANNEL_5);
      ledcAttachPin(FAN_2, PWM_CHANNEL_6);
        
      ledcAttachPin(FAN_3, PWM_CHANNEL_9);
      ledcAttachPin(FAN_4, PWM_CHANNEL_10);
       
      ledcAttachPin(LIFTER_FW, PWM_CHANNEL_7);
      ledcAttachPin(LIFTER_BW, PWM_CHANNEL_8);

      Serial.begin(115200);
      Ps3.attach(notify);
      Ps3.attachOnConnect(onConnect);
      Ps3.begin("01:02:03:04:05:06");   
      Serial.println("Ready.");
    }
    
    void loop()
    {
      if(!Ps3.isConnected())
        return;
    }
