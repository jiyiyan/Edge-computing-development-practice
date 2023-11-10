#include <ges_inferencing.h>

//# include <gesture_2_inferencing.h>
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <BleKeyboard.h>   //ble
#define G 9.736//杭州重力加速度
Adafruit_MPU6050 mpu;
// this is the final band
static float features[125]={0};
/**
 * @brief      Copy raw feature data in out_ptr
 *             Function called by inference library
 *
 * @param[in]  offset   The offset
 * @param[in]  length   The length
 * @param      out_ptr  The out pointer
 *
 * @return     0
 */
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

void print_inference_result(ei_impulse_result_t result);

/**
 * @brief      Arduino setup function
 */

BleKeyboard bleKeyboard; // ble



void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Wire.begin(1,0);//set I2C pins(scl,sda)=(0,1)
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    Serial.println("Starting BLE work!");
    bleKeyboard.begin();
    pinMode(2,INPUT);
    

    while (!Serial);
    Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);//加速度范围
 /* Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }*/
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);//角速度范围
 /* Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
*/
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);//带宽
  /*Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);*/
    //Serial.println("Edge Impulse Inferencing Demo");
}

/**
 * @brief      Arduino main function
 */
void loop()
{
    ei_printf("Edge Impulse standalone inferencing (Arduino)\n");
    Serial.print("Action !!!\r\n");
  delay(2000);
    int i = 0 ; 
    for(i = 0 ; i<125 ;i++){
        features[i] = analogRead(2);
        //ei_printf("%d \r\n", features[i]);
    }
    //ei_impulse_result_t result = { 0 };

    //print_inference_result(result);
     
    if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        ei_printf("The size of your 'features' array is not correct. Expected %lu items, but had %lu\n",
            EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
        delay(100);
        return;
    }

    ei_impulse_result_t result = { 0 };

    // the features are stored into flash, and we don't want to load everything into RAM
    signal_t features_signal;
    features_signal.total_length = sizeof(features) / sizeof(features[0]);
    features_signal.get_data = &raw_feature_get_data;

    // invoke the impulse
    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false /* debug */);
    if (res != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", res);
        return;
    }

    // print inference return code
    ei_printf("run_classifier returned: %d\r\n", res);
    print_inference_result(result);
    
    float gesture = 0 ; 
    for (uint16_t k = 0; k < EI_CLASSIFIER_LABEL_COUNT; k++) {
      if(result.classification[k].value > gesture){
        gesture = result.classification[k].value ; 
      }
      
    }
    
    ei_printf("GESTURE = %.5f \r\n",gesture);
    
    
    /*
    int Signal1 = 0 ;
    int Signal2 =0; 
    int Signal3 =0 ;
    Signal1 = digitalRead(5);//A1
    Signal2 = digitalRead(6);//A2
    Signal3 = digitalRead(7);//A3
    
    ei_printf("Signal1 = %d \r\n",Signal1);
    ei_printf("Signal2 = %d \r\n",Signal2);
    ei_printf("Signal3 = %d \r\n",Signal3);
    int signal = Signal1 * 100 + Signal2 * 10 + Signal3 * 1 ;
    
    ei_printf("Signal = %d \r\n",signal);
    
   
    float Signal1a = 0 ;
    float Signal2a =0; 
    float Signal3a =0 ;
    Signal1 = analogRead(5);//A1
    Signal2 = analogRead(6);//A2
    Signal3 = analogRead(7);//A3
    
    ei_printf("Signal1 = %lf \r\n",Signal1a);
    ei_printf("Signal2 = %lf \r\n",Signal2a);
    ei_printf("Signal3 = %lf \r\n",Signal3a);
    /*
    int signal = Signal1 * 100 + Signal2 * 10 + Signal3 * 1 ;
    
    delay(1000);
    */
    
    
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

/* Print out the values */
    float acc[3] ; 
    acc[0] = a.acceleration.x/G ; 
    acc[1] = a.acceleration.y/G ; 
    acc[2] = a.acceleration.z/G ; 
    Serial.print("Acceleration X: ");
    Serial.println(acc[0]);
    Serial.print(", Y: ");
    Serial.println(acc[1]);
    Serial.print(", Z: ");
    Serial.println(acc[2]);
  int signal = -1 ;




  if(acc[0]>=-0.2&&acc[0]<=0.2&&acc[2]>=0.9){
    Serial.println("朝向：上");
    signal = 0 ; 
  }else if(acc[0]>=0.2&&acc[0]<=0.9&&acc[2]<=0.90&&acc[2]>=0.20){
    Serial.println("朝向：左上");
    signal = 1 ; 
  }else if(acc[0]>=0.9&&acc[2]<=0.20&&acc[2]>=-0.20){
    Serial.println("朝向：左");
    signal = 2 ; 
  }else if(acc[0]>=0.2&&acc[0]<=0.9&&acc[2]<=-0.20&&acc[2]>=-0.90){
    Serial.println("朝向：左下");
    signal = 3 ; 
  }else if(acc[0]>=-0.2&&acc[0]<=0.2&&acc[2]<=-0.90){
    Serial.println("朝向：下");
    signal = 4 ; 
  }else if(acc[0]>=-0.9&&acc[0]<=-0.2&&acc[2]<=-0.20&&acc[2]>=-0.90){
    Serial.println("朝向：右下");
    signal = 5 ; 
  }else if(acc[0]<=-0.9&&acc[2]<=0.20&&acc[2]>=-0.20){
    Serial.println("朝向：右");
    signal = 6 ; 
  }else if(acc[0]>=-0.9&&acc[0]<=-0.2&&acc[2]<=0.90&&acc[2]>=0.20){
    Serial.println("朝向：右上");
    signal = 7 ; 
  }else{
    Serial.println("识别度低，请重试");
  }
  //Serial.println(" m/s^2");
  
  
    delay(100);
    if(bleKeyboard.isConnected()) {






      /*Serial.println("Sending 'Hello world'...");
      bleKeyboard.print("Hello world");

      delay(1000);

      Serial.println("Sending Enter key...");
      bleKeyboard.write(KEY_RETURN);

      delay(1000);

      Serial.println("Sending Play/Pause media key...");
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

      delay(1000);*/

        /*bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.write('r');// 这两步调用程序控制器 模拟  + R 操作
        bleKeyboard.releaseAll();
      //bleKeyboard.press(KEY_DELETE);      
        delay(100);

        bleKeyboard.print("cmd"); // 自动输入需要打开的文件名
        bleKeyboard.press(KEY_RETURN);
        bleKeyboard.releaseAll();
        delay(100) ; */

        //控制信号输出编码
        /*
        序号  动作      编码 A1 A2 A3
        0 上                000
        1 上下摇摆          001
        2 下                010
        3 右                011
        4 左                100
        5 左右摆动          101
        6 画三角            110
        7 画圆圈            111
        */
        
        if(gesture == result.classification[0].value ){//平伸手势
          switch (signal)
          {
          case 0 :// 向上平伸  待机
            ei_printf("DO TEST \r\n");
            /*
            bleKeyboard.press(KEY_LEFT_GUI);
            bleKeyboard.releaseAll();
            delay(100);
            bleKeyboard.press(KEY_LEFT_GUI);
            bleKeyboard.releaseAll();
            */
            break;
          case 1 :// 左上平伸 shift + tab
            ei_printf("左上 平伸 上一个可选选项!");
            bleKeyboard.press(KEY_LEFT_SHIFT);
            bleKeyboard.press(KEY_TAB);
            bleKeyboard.releaseAll();
            break;
          case 2 :// 向左 下键
            ei_printf("向左 平伸 向下箭头!");
            bleKeyboard.press(KEY_DOWN_ARROW);
            delay(1000);
            bleKeyboard.releaseAll();
            break;
          case 3 :// 向左下 窗口恢复
            ei_printf("向左下 平伸 窗口恢复!");
            bleKeyboard.press(KEY_RIGHT_ALT);
            bleKeyboard.press(KEY_RIGHT_ARROW);
            bleKeyboard.releaseAll();
            break;
          case 4 :// 向下 窗口后退
            ei_printf("向下 平伸 窗口后退");
            bleKeyboard.press(KEY_RIGHT_ALT);
            bleKeyboard.press(KEY_LEFT_ARROW);
            bleKeyboard.releaseAll();
            break;
          case 5 :// 向右下 地址栏
            ei_printf("向右下 平伸 定位到地址栏");
            bleKeyboard.press(KEY_F6);
            bleKeyboard.releaseAll();
            break;
          case 6 :// 向右 窗口缩小
            ei_printf("向右 平伸 窗口缩小");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('-');
            bleKeyboard.releaseAll();
            break;
          case 7 :// 向右上 运行
            ei_printf("向右上 平伸 运行程序");
            bleKeyboard.press(KEY_LEFT_GUI);
            bleKeyboard.write('r');
            bleKeyboard.releaseAll();
          default:
            ei_printf("ERROR Gesture");
            break;
          }
        }else if(gesture == result.classification[1].value){// 招手手势
          switch (signal)
          {
          case 0 :// 上招手 返回
            ei_printf("向上 招手 Return");
            bleKeyboard.press(KEY_RETURN);
            bleKeyboard.releaseAll();
            break;
          case 1 :// 左上 tab
            ei_printf("朝向左上 招手 tab!");
            bleKeyboard.press(KEY_TAB);
            bleKeyboard.releaseAll();
            break;
          case 2 :// 向左招手 上键
            ei_printf("向左 招手 上键");
            bleKeyboard.press(KEY_UP_ARROW);
            delay(1000);
            bleKeyboard.releaseAll();
            break;
          case 3 :// 朝向左下，招手 新窗口
            ei_printf("朝向左下 招手 创建新窗口");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('n');
            bleKeyboard.releaseAll();
            break;
          case 4 :// 下 关闭窗口
            ei_printf("朝下 招手 关闭窗口");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('w');
            bleKeyboard.releaseAll();
            break;
          case 5 ://右下 招手 返回键
            ei_printf("朝向右下 招手 在暂无指令!");
            //bleKeyboard.press(KEY_RETURN);
            //bleKeyboard.releaseAll();
            break;
          case 6 ://朝右 招手 窗口放大
            ei_printf("朝右 招手 窗口放大");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('+');
            bleKeyboard.releaseAll();
            break;
          case 7 :// 朝向 招手 语音
            ei_printf("朝向右下 招手 语音!");
            bleKeyboard.press(KEY_LEFT_GUI);
            bleKeyboard.write('h');
            bleKeyboard.releaseAll();
          default:
            ei_printf("ERROR Gesture");
            break;
          }
        }
          
          
          /*if(val == 1 ){//上下摆动 + 张开 shift + tab
            //ei_printf("left&&stretch");
            //bleKeyboard.print("left&&stretch"); 
            bleKeyboard.press(KEY_LEFT_SHIFT);
            bleKeyboard.press(KEY_TAB);
            
            bleKeyboard.releaseAll();
            
          }else if(val==0){// 上下摆动 + 招手 tab
            //ei_printf("left&&shake");
            //bleKeyboard.print("left&&shake"); 
            bleKeyboard.press(KEY_TAB);
            
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else if(location == result.classification[2].value){// 下
          if(val == 1 ){//向下张开 下滑
            bleKeyboard.press(KEY_DOWN_ARROW);
            

            bleKeyboard.releaseAll();
            
          }else if(val==0){//向下招手 上滑
            //ei_printf("right&&shake");
            //bleKeyboard.print("right&&shake"); 
            bleKeyboard.press(KEY_UP_ARROW);
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else if(location == result.classification[3].value){//右
          if(val == 1 ){
            //ei_printf("under&&strech");// 网页恢复
            bleKeyboard.press(KEY_RIGHT_ALT);
            bleKeyboard.press(KEY_RIGHT_ARROW);
            bleKeyboard.releaseAll();
            
          }else if(val==0){// 新建窗口
            ei_printf("under&&shake");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('n');
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else if(location == result.classification[4].value){//左
          if(val == 1 ){
            //ei_printf("under&&strech");网页后退
            bleKeyboard.press(KEY_RIGHT_ALT);
            bleKeyboard.press(KEY_LEFT_ARROW);
            bleKeyboard.releaseAll();
            
          }else if(val==0){// 关闭窗口
            ei_printf("under&&shake");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('w');
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else if(location == result.classification[5].value){//左右摆动
          if(val == 1 ){// 暂无
            ei_printf("under&&strech");
            bleKeyboard.print("under&&stretch"); 
            bleKeyboard.press(KEY_RETURN);
            bleKeyboard.releaseAll();
            
          }else if(val==0){//光标定位到地址栏
            ei_printf("under&&shake");
            bleKeyboard.print("under&&shake"); 
            bleKeyboard.press(KEY_RETURN);
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else if(location == result.classification[6].value){//画三角形
          if(val == 1 ){//搜索程序
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('-');
            bleKeyboard.releaseAll();
            
          }else if(val==0){//网页放大
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('+');
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else if(location == result.classification[7].value){//画圆圈
          if(val == 1 ){//网页缩小
            bleKeyboard.press(KEY_LEFT_GUI);
            bleKeyboard.write('r');
            bleKeyboard.releaseAll();
            
          }else if(val==0){// 语音输入
            ei_printf("under&&shake");
            bleKeyboard.press(KEY_LEFT_GUI);
            bleKeyboard.write('h');
            bleKeyboard.releaseAll();
          }else{
            ei_printf("val is illegal !");
          }
        }else {

          ei_printf("Location is illegal !");

        }
      
      location = 0 ; 
        //i++ ; 

    
    */ 
    /*}else{
        ei_printf("Gesture is illegal !");
    }

    Serial.println("Waiting 5 seconds for next gesture ...");
    delay(5000);
    
    */
    }else{
        ei_printf("BLE disconnected !\r\n");
    }
}



void print_inference_result(ei_impulse_result_t result) {

    // Print how long it took to perform inference
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

    // Print the prediction results (object detection)
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Object detection bounding boxes:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }

    // Print the prediction results (classification)
#else
    ei_printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
    }
#endif

    // Print anomaly result (if it exists)
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("Anomaly prediction: %.3f\r\n", result.anomaly);
#endif

}
