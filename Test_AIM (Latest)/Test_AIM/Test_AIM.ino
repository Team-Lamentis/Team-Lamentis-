/////////////////////////////////////////////// create queu ////////////////////////////////////////////////////////////////////////////////
String CarOne,CarTwo;
String queue_car[]= {CarOne,CarTwo};////// tambah car in the queu
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int signal_move = 0;
int signal_wait = 0;

void car_move(void *parameter);
void car_wait(void *parameter);
void car_communicate(void*parameter);


TaskHandle_t TaskHandle_3;

//creating task

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(1200);

  xTaskCreate(car_move, "Car move", 1000, NULL, 1, NULL);
  xTaskCreate(car_wait, "Car wait", 1000, NULL, 1, NULL);
  xTaskCreate(car_communicate, "Car communicate", 1000, NULL, 2, &TaskHandle_3);

   
}

void loop() {}


///////////////////////////////////////////////////////////// task car communicate //////////////////////////////////////////////////////
void car_communicate(void*parameter)
      {
        (void) parameter;
        TickType_t getTick;
        getTick = xTaskGetTickCount(); 
      
        while(1)
          {
            Serial.println("start");
                  
               if(queue_car[0]==CarOne)
                {
                      Serial.println("car one arrive");
                   signal_move= 1;
                   //vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                   Serial.println("path available");
                  
                   
                    
                }


              if(queue_car[1]==CarTwo)
                {
                  Serial.println("car two arrive");
                   signal_wait= 1;
                    //vTaskSuspend(TaskHandle_3); 
                   //vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                   Serial.println("path not available");
                   
                    
                }

             vTaskSuspend(TaskHandle_3);
          }
                     
      }
      

///////////////////////////////////////////////////////////// task car move ///////////////////////////////////////////////////////////////////////

void car_move(void*parameter)
         
          {
          (void) parameter;
           TickType_t getTick;
        getTick = xTaskGetTickCount();
        
      
        while(1)
          {
              
                if(signal_move= 1)
                {
                 Serial.println("car move");
  
          }
                       
      }
          }
//////////////////////////////////////////////////////////// Task Car Wait //////////////////////////////////////////////////////////////////////////

void car_wait(void*parameter)
{
              (void) parameter;
               TickType_t getTick;
              getTick = xTaskGetTickCount(); 

              
       
           while(1)
                {

                                if(signal_wait= 1)
                                 {
                                // signal_wait=1;
                                 Serial.println("car wait");
                                }
               Serial.println("end");
               vTaskResume(TaskHandle_3);
                               }
}