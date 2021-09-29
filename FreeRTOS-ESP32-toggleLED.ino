//use only core 1
#if CONFIG_FREERTOS_UNICORE
static const Basetype_t app_cpu = 0;
#else
static const Basetype_t app_cpu = 1;
#endif

static const int led_pin = LED_BUILTIN;

//task: blink the LED
void toggleLED(void *parameter){
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin / LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {

  pinMode(led_pin, OUTPUT);

  //task to run forever
  xTaskCreatePinnedToCore(  //use xTaskCreate() in vainilla FreeRTOS
    toggleLED,              //function to be calle
    "Toggle lED",           //name of task
    1024,                   //stack size
    NULL,                   //parameter to pass to function
    1,                      //task priority
    NULL,                   //task handle
    app_cpu);               //run on one core (esp32 only)

  //if this was vainilla FreeRTOS, you'd want to call vTaskStartScheduler() in main
  //after setting up your task

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
