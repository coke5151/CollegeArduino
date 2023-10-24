// CentripetalForce.ino
//====================================
// 宣告變數區
unsigned int count = 0;
const byte counterPin = 2;
unsigned long time;
unsigned int Cycle;
unsigned int SumCycle = 0;
const byte grid_num = 10;
const byte Sensor = A0;
int Force = 0;
int sensorValue;
//====================================
// 副程式
void counter() { // 計數函數
    count++;
}
//====================================
void setup() {
    Serial.begin(9600);
    pinMode(counterPin, INPUT);
    attachInterrupt(0, counter, FALLING); // 計數，以電壓由 HIGH 轉變 LOW 算一次
    // 外部中斷處理函式指令，
    // 參數 1：編號 0 指的是 pin2
    // 參數2：counter 當 pin 狀態從 HIGH 到 LOW 時觸發中斷；FALLING 又稱負緣觸發
    count = 0;
    Cycle = 0;
    time = 0;
}
//====================================
void loop() {
    byte n = 1; // 宣告計數變數
    Serial.print("測量次數 n:");
    do {
        if (millis() - time >= 1000) { // 每秒計算一次中斷次數
            detachInterrupt(0);        // 計算週期時，停止計時計數
            // 移除指定腳位之中斷功能，參數為中斷編號，0 or 1
            // 週期 = 每圈的柵格數 10 * (時間差/偵測次數)
            Cycle = grid_num * ((millis() - time) / count);
            time = millis();
            count = 0;

            Serial.print(n);
            Serial.print(" ");
            SumCycle = SumCycle + Cycle;
            sensorValue = analogRead(Sensor); // 取得 A0 的數值
            Force = Force + sensorValue;
            n++;
            attachInterrupt(0, counter, FALLING); // 重啟計數
        }
    } while (n < 11);   // 十次就離開迴圈
    Serial.print("\n"); // 換行
    //====================================
    // 此處原本是註解，但實驗時會需要解除註解
    Serial.print("Cycle(ms) = ");
    Serial.println(SumCycle / 10, DEC); // 顯示 10 次的平均
    //====================================
    Serial.print("Force = ");
    Serial.println(Force / 10, DEC); // 顯示 10 次的平均
    n = 1;
    SumCycle = 0;
    Force = 0;
}